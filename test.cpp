#include "Complex.h"
#include "common.h"
#include<iostream>
using namespace std;


void  minit(void *a,void *b){
	std::cout<<*(float*)a<<"\n"<<*(float*)b<<std::endl;

}


void  mminit(void *a,void *b){
	std::cout<<*(float*)b<<"\n"<<*(float*)a<<std::endl;

}





int main(){
	//float a = 6;
	//float b = 7;
	//
	//Complexf cm= Complexf();

	//Complexf cm1 = Complexf();

	//cm1.setReal(10);
	//cm1.setIm(5);

	//cm.setReal(2);
	//cm.setIm(3);
	//std::cout<<sizeof(cm)<<std::endl;
	//std::cout<<sizeof(Complexf)<<std::endl;
	//aaa bcbc = aaa();
	//std::cout<<sizeof(bcbc)<<std::endl;
	//std::cout<<sizeof(aaa)<<std::endl;
	//cm.show();

	//cm + cm1;
	//cm.show();

	//cm * cm1;
	//cm.show();

	////Complexf::test();
	////fff.test();
	//std::cout<<std::endl;
	//system("pause");

	/*
	//test base2
	float arr[16] = {3,4,5,2,3,4,1,2,5,4,3,5,6,7,2,3};
	Complexf *cm = new Complexf[16];
	for(int i=0;i<16;i++){
		cm[i].setReal(arr[i]);
		cm[i].setIm(0);
	}
	std::cout<<"hello\n";
	fft_base2(cm,16);
	for(int i=0;i<16;i++)
		std::cout<<i<<"   "<<cm[i].getReal() << "\t" << cm[i].getIm()<<std::endl;

	ifft_base2(cm,16);


	printf("====================================ifft===========\n");

	for(int i=0;i<16;i++)
		std::cout<<i<<"   "<<cm[i].getReal() << "\t" << cm[i].getIm()<<std::endl;*/


	

	/*
	//test getPrime
	u_int N = 18*27*49*169*256;
	u_int* A = getPrime(N);
	std::cout<<N<<"\n";
	for(int i=1;i<=A[0];i++){
		std::cout<<A[i]<<endl;
	}*/

	
	/*
	//test Cn_reverse
	int nn = 32;
	float arr[32] = {3,4,5,2,3,4,1,2,5,4,3,18,23,7,2,3,3,4,5,2,3,4,1,2,5,4,3,5,6,7,2,3};
	Complexf *cm = new Complexf[nn];
	for(int i=0;i<nn;i++){
		cm[i].setReal(arr[i]);
		cm[i].setIm(0);
	}


	Complexf *cm1 = new Complexf[nn];
	for(int i=0;i<nn;i++){
		cm1[i].setReal(arr[i]);
		cm1[i].setIm(0);
	}
	fft_CN(cm,nn);

	bitReverse(cm1,nn);*/



	
	//test baseCN
	int nn=16;
	float arr[16] = {3,4,5,2,3,4,1,2,5,4,3,5,6,7,2,3};
	Complexf *cm = new Complexf[nn];
	for(int i=0;i<nn;i++){
		cm[i].setReal(arr[i]);
		cm[i].setIm(0);
	}

	std::cout<<"hello\n";

	fft_CN(cm,nn);

	for(int i=0;i<nn;i++)
		std::cout<<i<<"   "<<cm[i].getReal() << "\t" << cm[i].getIm()<<std::endl;

	/*ifft_base2(cm,nn);
	printf("====================================ifft===========\n");
	for(int i=0;i<16;i++)
		std::cout<<i<<"   "<<cm[i].getReal() << "\t" << cm[i].getIm()<<std::endl;*/

	delete [] cm;
	system("pause");
}
