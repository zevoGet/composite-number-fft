#include "Complex.h"
#include "common.h"
#include<malloc.h>
#include<cmath>
#include<iostream>
#define ffor(a) for(int i=0;i<a;i++)

int CN_prime[] = {2,3,5,7,11,13,17,19};
int CN_num = 8;


//旋转因子 利用周期性，只计算一次--通用
void cmwnk(Complexf *cm, u_int N){
	for(int i=0;i<N;i++){
		cm[i].setReal(cos( 2 * PI * i / N));
		cm[i].setIm( sin( -2 * PI * i / N));
		//std::cout<<"\nwnk       "<< i << "   "<<cm[i].getReal() <<"  "<<cm[i].getIm()<<std::endl;
	}
	
}





/*
----------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------
for N are no power of 2 
but N are Composite number
start
*/


/*
get number of prime the N can divide
*/
u_int* getPrime(int N){
	int j = 0;
	int k = 0;
	u_int tepN = N;
	u_int *temp = (u_int *) malloc(sizeof(temp) * CN_num);

	for (int i = 0; i < CN_num;i++){
		temp[i] = 0;
	}

	
	while(j<CN_num){
		if(tepN%CN_prime[j] == 0) {
			tepN = tepN /CN_prime[j];
			temp[j]++;
			k++;
		}
		else{
			j++;
		}
	}

	u_int* res = new u_int[k+1];
	res[0] = k;
	k = 1;
	for (int i = 0; i < CN_num; i++){
		while(temp[i]>0) {
			res[k++] = CN_prime[i];
			--temp[i];
		}
	}

	//delete temp
	free(temp);

	//remember to delete
	return res;

}

/*
	合数bit reverse,O(N)
*/
void CN_reverse(Complexf *cm,u_int *pN,u_int N){
	u_int *temp = new u_int[N];
	Complexf *tmp =new Complexf[N];

	for(u_int i=0;i<N;i++){
		temp[i] = 0;
		tmp[i].setData(cm[i]);
	}
	u_int idx,md,t;
	idx = 1;
	t = 1;
	for(u_int i= 1;i<pN[0]+1;i++){
		idx *= pN[i];
		md = N/idx;
		for(u_int k=t;k<idx;k++){
			temp[k] = temp[k-t]+md;
		}
		t = idx;
	}

	for(u_int i=0;i<N;i++){
		cm[i].setData(tmp[temp[i]]);
		//std::cout<<cm[i].getReal()<<"  ";
	}
	//std::cout<<" reverse end\n";
	//删除临时复数数组
	delete[] tmp;

	//删除临时下标数组
	delete[] temp;
}



//base mathod
/*
	first X[i] and x[i] are complex
	X[k] = sum(wnk[i*k]*x(i))  --i=0,N-1
	wnk[j] =[cos(2*pi *j)/N]  -- j=0,N-1
*/
void dft(Complexf *cm,Complexf* wnk,u_int n){
	Complexf *res = (Complexf *)malloc(sizeof(Complexf) * n);
	Complexf temp = Complexf();
	Complexf temp1 = Complexf();

	//std::cout<<"-------------------------------------------------\n  ";
	//k
	for(int i=0;i<n;i++){
		temp1.setReal(0);
		temp1.setIm(0);
		//std::cout<<"\n  ";
		temp1 +=cm[0];
		for(int j=1;j<n;j++)
		{
			temp.setData(cm[j]);
			temp *= wnk[(i*j)%n];
			temp1 += temp;
		}
		//std::cout<<"\n";
		res[i].setData(temp1);
	}
	for(int i=0;i<n;i++){
		cm[i].setData(res[i]);
	}
	free(res);


}


/*
cm    --> input array
res   --> ouput array
wnk   --> common array
n     --> length of cm
nk    --> number array of the wnk's index
*/
void dft(Complexf *cm,Complexf* res,Complexf* wnk,u_int n,u_int *nk){
	Complexf temp = Complexf();
	Complexf temp1 = Complexf();

	//std::cout<<"-------------------------------------------------\n  ";
	//k
	for(int i=0;i<n;i++){
		temp1.setReal(0);
		temp1.setIm(0);
		//temp1 +=cm[0];
		//n
		for(int j=0;j<n;j++)
		{
			temp.setData(cm[j]);
			temp *= wnk[nk[(i*j)%n]];
			/*std::cout<<"\n------  "<<  nk[(i*j)%n+n] <<"   "<<nk[(i*j)%n]<<"  ";*/
			temp1 += temp;
		}
		res[i].setData(temp1);
	}
}


void fast_compute(Complexf *cm,Complexf* res,Complexf* wnk,u_int n,u_int *nk){
	Complexf temp = Complexf();
	Complexf temp1 = Complexf();

	//k
	for(int i=0;i<n;i++){
		temp1.setReal(0);
		temp1.setIm(0);
		//n
		for(int j=0;j<n;j++)
		{
			temp.setData(cm[j]);
			temp *= wnk[(j *(nk[(i)%n]))%nk[n]];
			temp1 += temp;
		}
		res[i].setData(temp1);
	}
}

/*
	input array cm,
	array wnk,
	length of array cm,
	primes of N;
*/
void fft_main_CN(Complexf *cm,Complexf *wnk,int N,u_int *prim){
	int nL = prim[0];
	if(nL==1) 
	{dft(cm,wnk,N);return;}

	int M = nL+1;

	u_int *nk = new u_int[N];
	Complexf *res = new Complexf[N];
	Complexf *tempf = new Complexf[N];
	Complexf tempmm = Complexf();


	u_int cn,md,ni,mp,nidx;

	cn = 1;
	ni = 1;
	//current level in nk
	for(int i=1;i<M;i++){
		
		cn *= prim[i];


		md  = N /cn;

		//------------
		mp = prim[i];

		//for fast compute
		nk[mp] = N;

		for(int m=0;m<N;m+=cn){
			for(int j=0;j<ni;j++){
				//get a compute needed array
				for(int k=0;k<mp;k++){
					nidx = k*ni+j+m;
					tempf[k].setData(cm[nidx]);
					nk[k]=((nidx%cn)* md)%N;
					//std::cout<<"\n================="<<nidx<<"    "<<nk[k] <<"    "<<wnk[nk[k]].getReal()<<"    "<<wnk[nk[k]].getIm()<<" -----;\n";
				}
				
				//first do a DFT computing then continue the fast computing
				if(i==1){ dft(tempf,res,wnk,mp,nk); }
				else{ fast_compute(tempf,res,wnk,mp,nk); }
				

				//rewrite the array
				for(int k=0;k<mp;k++){
					nidx = k*ni+j+m;
					//std::cout<<"\n================="<<nidx<<"    "<<nk[k] <<" -----;\n";
					cm[nidx].setData(res[k]);
				}
				
			}
		}
		ni = cn;
	}


	delete [] res;
	delete [] tempf;
	delete [] nk;
	
}



void fft_CN(Complexf *cm,int N){
	u_int* prim = getPrime(N);
	CN_reverse(cm,prim,N);

	Complexf *cmm  = new Complexf[N];

	cmwnk(cmm,N);

	fft_main_CN(cm,cmm,N,prim);

	delete [] cmm;
	prim = nullptr;
}

void ifft_CN(Complexf *cm,int N){
	for(int i=0;i<N;i++){
		cm[i].setIm(-cm[i].getIm());
	}

	fft_CN(cm,N);

	for(int i=0;i<N;i++){
		cm[i].setReal(cm[i].getReal() /N );
		cm[i].setIm( - cm[i].getIm() / N);
	}
}

/*
for N are no power of 2 
but N are Composite number
end
----------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------
*/


/*
==============================================================================================
----------------------------------------------------------------------------------------------
below are for base 2 algorithm 
For N is the power of 2;
too special
start
*/
u_int log2a(u_int n){
	u_int temp = n;

	u_int k = 0;
	while(true){
		temp = temp >> 1 ;
		if(temp > 0)k++;
		else break;
		
	}
	return k;
};

//翻转，DIT
void bitReverse(Complexf *cm,u_int N){
	u_int temp,idx;
	Complexf *res = (Complexf *)malloc(sizeof(Complexf) * N);
	u_int L = log2a(N);
	//std::printf("bit start %d\n",L);
	Complexf tpcm = Complexf();
	for(u_int i=0;i<N;i++)
	{
		temp = 0;
		idx= i;
		for(int j = 0;j<L;j++)
		{
			temp = temp << 1;
			temp += idx%2;
			idx = idx >> 1;
		}
		/*std::cout<<temp<<"   "<< i <<"----ssss\n";
		std::cout<<cm[temp].getReal()<<"   "<<cm[i].getReal() <<"----ssss\n";*/
		res[i].setData(cm[temp]);
	}

	
	for(int i=0;i<N;i++){
		cm[i].setData(res[i]);
		std::cout<<cm[i].getReal()<<"  ";
	}
	free(res);
	std::printf("bit end\n");
};

/*
while size is the power of 2;
*/
void fft_main_base2(Complexf *cm,int N,Complexf *wnk){
	
	int m = log2a(N);

	Complexf temp = Complexf();
	Complexf temp2 = Complexf();
	u_int nd,cn,pn,ni,wnid1,wnid2;

	//级数，logN,cn means current is in which level.
	for(int i=0;i<m;i++){
		cn = 2 << i;
		ni = cn / 2;
		pn = N / ni;
		//每一级对应点
		for(int j=0;j<ni;j++){
			//std::cout<<"jjjj--------------------------------------------------\n";
			/*
			cm[k] cm[nd] --> G(x)  H(x);
			for example:
			if cn equals 2,then
				G(0) + wnk *H(0) = cm[0] + wnk * cm[1]
				G(1) + wnk1 *H(1) = cm[0] + wnk1 * cm[1]
				and then goto next k,
			because k+=cn , k = 0+cn; then
				G(0) + wnk * H(0) = cm[cn] + wnk * cm[k+1]
				G(1) + wnk1 *H(1) = cm[cn] + wnk1 * cm[cn+1]
			*/
			for(int k=j;k<N;k+=cn){
				
				nd = ni + k;
				temp2.setData(cm[k]);

				temp.setData(cm[nd]);
				wnid1=((k%cn)* (N/cn))%N;
				temp *= wnk[wnid1];
				cm[k] += temp;

				temp.setData( cm[nd] );
				wnid2 = ((nd%cn) *(N/cn)) %N;
				temp *= wnk[wnid2];
				cm[nd].setData( temp2);
				cm[nd] += temp;
			}
		
		}
	
	}//理论总时间 = M * pn * 2 * N / cn  =   N *logN
	/*if(wnk!=nullptr)
	delete(wnk);*/

}




void fft_base2(Complexf *cm,int N){
	bitReverse(cm,N);
	Complexf *cmm  = new Complexf[N];
	cmwnk(cmm,N);

	fft_main_base2(cm,N,cmm);
	delete []cmm;
}

void ifft_base2(Complexf *cm,int N){
	for(int i=0;i<N;i++){
		cm[i].setIm(-cm[i].getIm());
	}
	fft_base2(cm,N);
	for(int i=0;i<N;i++){
		cm[i].setReal(cm[i].getReal() /N );
		cm[i].setIm( - cm[i].getIm() / N);
	}

}

/*
below are for base 2 algorithm 
For N is the power of 2;
too special
end
---------------------------------------------------------------------------------
=================================================================================
*/



/*

fft for 2d
include shift
fft

*/

void swap(Complexf *v1, Complexf *v2)
{
    Complexf tmp = *v1;
    *v1 = *v2;
    *v2 = tmp;
}


/** 
* move to center
*/
void fft_2d_shift(Complexf *cm,u_int n){
	//int n = w* h;
	int halfp ;
	Complexf temph=Complexf();
	if(n%2==0){ 
		halfp = n/2;
		for(int i=0;i<halfp;i++){
			swap(&cm[i],&cm[i+halfp]);
		}
	}
	else{ 
		halfp = (n-1)/2;
		temph.setData(cm[0]);
		for(int i=0;i<halfp;i++){
				//src = i*w+j;
			cm[i].setData(cm[i+halfp +1]);
			cm[i+halfp +1].setData(cm[i+1]);
		}
		cm[halfp].setData(temph);
	}
}

/** 
*/
void fft_2d_unshift(Complexf *cm, u_int n){
	//int n = w* h;
	int halfp;
	Complexf temph = Complexf();
	if (n % 2 == 0){
		halfp = n / 2;
		for (int i = 0; i<halfp; i++){
			swap(&cm[i], &cm[i + halfp]);
		}
	}
	else{
		halfp = (n - 1) / 2;
		temph.setData(cm[n-1]);

		for (int i = n-1; i>=halfp; i--){
			cm[i].setData(cm[i-halfp-1]);
			cm[i - halfp - 1].setData(cm[i-1]);
		}
		cm[halfp].setData(temph);
	}
}

void fft_2d(Complexf *cm,u_int w,u_int h){
	for(int i=0;i<h;i++){
		fft_CN(cm,w);
		cm = cm+w;
	}
	cm = cm -w*h;
	Complexf *temph = (Complexf *)malloc(sizeof(Complexf)* h);
	for(int i=0;i<w;i++){
		for(int j=0;j<h;j++){
			temph[j].setData(cm[j*w + i]);
		}
		fft_CN(temph,h);

		for(int j=0;j<h;j++){
			cm[j*w + i].setData(temph[j]);
		}
	}
	free(temph);
	
	fft_2d_shift(cm, w*h);
}





void ifft_2d(Complexf *cm,u_int w,u_int h){
	
	fft_2d_unshift(cm, w*h);

	Complexf *temph = (Complexf *)malloc(sizeof(Complexf)* h);
	for (int i = 0; i<w; i++){
		for (int j = 0; j<h; j++){
			temph[j].setData(cm[j*w + i]);
		}
		ifft_CN(temph, h);

		for (int j = 0; j<h; j++){
			cm[j*w + i].setData(temph[j]);
		}
	}
	free(temph);
	for (int i = 0; i<h; i++){
		ifft_CN(cm, w);
		cm = cm + w;
	}
	cm = cm - w*h;
	/*for (int i = 0; i<h; i++){
		for (int j = 0; j<w; j++)
			cm[i*w + j].setIm(-cm[i*w + j].getIm());
	};

	fft_2d(cm, w, h);

	int N = w * h;
	for (int i = 0; i<h; i++){
		for (int j = 0; j<w; j++){
			cm[i*w + j].setReal(cm[i*w + j].getReal()/N);
			cm[i*w + j].setIm(-cm[i*w + j].getIm()/N);
		}
	};*/
}

/**
* 求取基础的参数的幂次方，上面
* get base arg power of e
*/
Complexf *baseCmPow(Complexf *cm, int n, int p){
	cm->setReal( cos(p * PI /n));
	cm->setIm( sin(-p * PI / n));
	return cm;
}

/**
* 一般形式的fft
*/
void fft_normal(Complexf *cm, int N){
	u_int L = 1,tmpn = 0,M = N,tn = N * 2;
	while (L < 2*N ){
		L = L * 2;
	} 

	Complexf tempmul = Complexf();
	Complexf *temp = (Complexf *)malloc(L * sizeof(Complexf));
	
	Complexf *temp2 = (Complexf *)malloc(L * sizeof(Complexf));
	for (int i = 0; i < L; i++){
		
		if (i < N){
			tmpn = i*i;
			baseCmPow(&tempmul, N, tmpn);
			temp[i].setData(tempmul);
			temp[i] *= cm[i];

			baseCmPow(&tempmul, N, -tmpn);
			temp2[i].setData(tempmul);
		}else{
			if (i > L - N){
				tmpn = (L - i)*(L - i);
				baseCmPow(&tempmul, N, -tmpn);
				temp2[i].setData(tempmul);
			}else{
				temp2[i].init();
			}
			temp[i].init();
		}
	}

	fft_base2(temp, L);
	fft_base2(temp2, L);
	for (int i = 0; i < L;i++){
		temp[i] *= temp2[i];
	}

	ifft_base2(temp, L);

	for (int i = 0; i < N;i++){
		tmpn = i*i;
		baseCmPow(&tempmul, N, tmpn);
		tempmul *= temp[i];
		cm[i].setData(tempmul);
	}
	free(temp);
	free(temp2);
}
/**
* 一般形式的ifft
*/
void ifft_normal(Complexf *cm, int N){
	for (int i = 0; i<N; i++){
		cm[i].setIm(-cm[i].getIm());
	}

	fft_normal(cm, N);

	for (int i = 0; i<N; i++){
		cm[i].setReal(cm[i].getReal() / N);
		cm[i].setIm(-cm[i].getIm() / N);
	}
}



