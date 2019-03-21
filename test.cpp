#include "./test/test.h"
#include "common.h"
#include<iostream>
using namespace std;

#define ffor(a) for(int i=0;i<a;i++)

void  minit(void *a,void *b){
	std::cout<<*(float*)a<<"\n"<<*(float*)b<<std::endl;
}

void  mminit(void *a,void *b){
	std::cout<<*(float*)b<<"\n"<<*(float*)a<<std::endl;

}

/**
test 2d fft
²âÊÔ¶þÎ¬fft
*/
void testfft2d(){
	int w = 3;
	int h = 3;
	float arr[6][6] = { { 2, 4, 5, 4, 5, 6 }, { 3, 5, 6, 4, 5, 7 }, { 4, 7, 8, 4, 6, 8 }, { 5, 6, 7, 9, 7, 6 }, { 5, 2, 3, 5, 6, 8 }, { 6, 2, 4, 3, 5, 8 } };
	Complexf* cm = (Complexf *)malloc(sizeof(Complexf)* w * h);
	for (int i = 0; i<h; i++){
		for (int j = 0; j<w; j++){
			cm[i*w + j].setReal(arr[i][j]);
			cm[i*w + j].setIm(0);
		}
	}


	fft_2d(cm, w, h);

	for (int i = 0; i<h; i++){
		for (int j = 0; j<w; j++){
			std::cout << cm[i*w + j].getReal() << "\t";//<<cm[i*w+j].getIm()<<"\t";
		}
		std::cout << "\n";
	}


	std::cout << "\n";
	ifft_2d(cm, w, h);


	for (int i = 0; i<h; i++){
		for (int j = 0; j<w; j++){
			//std::cout << cm[i*w + j].abs() << "\t";//<<cm[i*w+j].getIm()<<"\t";
			std::cout << cm[i*w + j].getReal() << "\t";
		}
		std::cout << "\n";
	}

}

/*
test*/
void test_dft(Complexf *cm, u_int N){
	Complexf *wnk = new Complexf[N];
	for (int i = 0; i<N; i++){
		wnk[i].setReal(cos(2 * PI * i / N));
		wnk[i].setIm(sin(-2 * PI * i / N));
	}

	u_int *nk = new u_int[N];
	for (int i = 0; i<N; i++){
		nk[i] = i;
	}
	Complexf *res = new Complexf[N];
	dft(cm, res, wnk, N, nk);
	for (int i = 0; i<N; i++){
		std::cout << i << " ----  " << res[i].getReal() << "\t" << res[i].getIm() << std::endl;
	}
}

int main(){
	test_log2();
	testPrime();
	test_bitReverse();
	test_CN_reverse();


	
	test_fft2();
	test_fft_CN();


	test_fft2d_shift();
	testfft2d();
	
	
	
	test_normal_fft();
	return 0;
}


