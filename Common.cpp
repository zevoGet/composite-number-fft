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

	ffor(CN_num){
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
	ffor(CN_num){
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

	for(int i=0;i<N;i++){
		temp[i] = 0;
		tmp[i].setData(cm[i]);
	}
	u_int idx,md,t;
	idx = 1;
	t = 1;
	for(int i= 1;i<pN[0]+1;i++){
		idx *= pN[i];
		md = N/idx;
		for(int k=t;k<idx;k++){
			temp[k] = temp[k-t]+md;
		}
		t = idx;
	}

	for(int i=0;i<N;i++){
		cm[i] = tmp[temp[i]];
		std::cout<<cm[i].getReal()<<"  ";
	}
	std::cout<<" reverse end\n";
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
void dft(Complexf *cm,Complexf* res,Complexf* wnk,u_int n,u_int *nk){
	Complexf temp = Complexf();
	Complexf temp1 = Complexf();

	std::cout<<"-------------------------------------------------\n  ";
	//k
	for(int i=0;i<n;i++){
		temp1.setReal(0);
		temp1.setIm(0);
		std::cout<<"\n  ";
		//n
		for(int j=0;j<n;j++)
		{
			temp.setData(cm[j]);
			temp *= wnk[nk[j]];
			std::cout<<nk[j]<<"  ";
			temp1 += temp;
		}
		std::cout<<"\n";
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
	int M = nL+1;

	u_int *nk = new u_int[N];
	Complexf *res = new Complexf[N];
	Complexf *tempf = new Complexf[N];

	u_int cn,md,ni,mp;

	cn = 1;
	ni = 1;
	for(int i=1;i<M;i++){
		cn *= prim[i];
		md  = N /cn;
		mp = prim[i];
		//for(int j=0;j<md;j++){
			for(int m=0;m<N;m+=cn){
				for(int k=0;k<mp;k++){
					tempf[m+k].setData(cm[m+k*md]);
					nk[k]=(((ni*k+m)%cn)* md)%N;
				}
				
				dft(tempf,res,wnk,mp,nk);

				for(int k=0;k<mp;k++){
					cm[m+k].setData(res[m+k*md]);
				}
				
			}
		//}
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
u_int log2(u_int n){
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
	u_int L = log2(N);
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
	
	int m = log2(N);

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
				/*if(nd==7) 
					{
						std::cout<<"id1 = "<< wnk[wnid2].getReal()<<"   id2 = "<<wnk[wnid2].getIm()<<"\n";
				
						std::cout<<" k=  "<<k<< "   "<<  cm[k].getIm() <<"      nk = "<<nd << "  "<<cm[nd].getIm()<<std::endl;}*/

				//std::cout<<"id1 = "<< wnid2<<"    "<<wnk[wnid2].getReal()<<"    " <<wnk[wnid2].getIm()<<"\n";
				///*if(k==0)
				//	{
				//		std::cout<<"    000000    "<<cm[0].getReal()<<std::endl;
				//}*/
				//std::cout<<" k=  "<<k<< "   "<<  cm[k].getIm() <<"      nk = "<<nd << "  "<<cm[nd].getIm()<<std::endl;
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



