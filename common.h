#ifndef __Fourier_tool_
#define __Fourier_tool_


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

static u_int x = 0x0;

#ifdef __cplusplus
extern "C"{
#endif
	/*
		all below are must agree
		input N must lower than length of 100M(2^22);
	*/
	void fft_base2(Complexf *cm,int N);

	u_int log2(u_int n);

	void ifft_base2(Complexf *cm,int N);

	void bitReverse(Complexf *cm,u_int N);
	u_int *getPrime(int N);
	void fft_CN(Complexf *cm,int N);
	void ifft_CN(Complexf *cm,int N);
	/*void bitVerbose(Complexf *cm,int N);*/
	/*
	type code here
	*/
#ifdef __cplusplus
}
#endif

#endif