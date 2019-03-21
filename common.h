#ifndef __Fourier_tool_
#define __Fourier_tool_

#include "Complex.h"
//#ifndef Endian
//	bool fun(){
//		union TT{
//			int a;
//			char b;
//		}test;
//		test.a = 0x1234;
//		if(test.b == 0x12)
//			return true;
//		else
//			return false;
//	}
//	bool flag = fun();
//	
//#endif

typedef  unsigned long u_long;
typedef  unsigned int u_int;
typedef  unsigned short u_short;
typedef  unsigned char u_char;

//static u_int x = 0x0;

#ifdef __cplusplus
extern "C"{
#endif
	/*
		all below are must agree
		input N must lower than length of 100M(2^22);
	*/
	void fft_base2(Complexf *cm,int N);

	/*just return the floor num of log*/
	u_int log2a(u_int n);

	void ifft_base2(Complexf *cm,int N);

	void bitReverse(Complexf *cm,u_int N);
	u_int *getPrime(int N);
	void fft_CN(Complexf *cm,int N);
	void ifft_CN(Complexf *cm,int N);
	void CN_reverse(Complexf *cm, u_int *pN, u_int N);
	/*void bitVerbose(Complexf *cm,int N);*/
	/*
	type code here
	*/


	/*
	fft 2d shift
	*/
	void fft_2d_shift(Complexf* cm,u_int n);
	/**
	fft 2d unshift
	*/
	void fft_2d_unshift(Complexf* cm, u_int n);


	void fft_2d(Complexf *cm,u_int w,u_int h);
	void ifft_2d(Complexf *cm,u_int w,u_int h);

	/*
		test
	*/
	void dft(Complexf *cm,Complexf* res,Complexf* wnk,u_int n,u_int *nk);
	void test_dft(Complexf *cm,u_int N);
	
	/***/
	void fft_normal(Complexf *cm, int N);
	void ifft_normal(Complexf *cm, int N);

#ifdef __cplusplus
}
#endif

#endif
