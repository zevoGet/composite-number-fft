#include "test.h"
#include<iostream>
using namespace std;



void test_fft_CN(){
	//test_fft_CN

	int nn=36;
	float arr[36] = {3,4,5,2,3,4,1,2,5,4,3,5,6,7,2,3,4,4,3,4,5,2,3,4,1,2,5,4,3,5,6,7,2,3,4,4};
	Complexf *cm = new Complexf[nn];
	for(int i=0;i<nn;i++){
		cm[i].setReal(arr[i]);
		cm[i].setIm(0);
	}

	std::cout << "=========================test_fft_CN start=============================\n";

	cout << "\n origin data\n";
	for (int i = 0; i<nn; i++)
		std::cout << i << "   " << cm[i].getReal() << "\t" << cm[i].getIm() << std::endl;

	fft_CN(cm,nn);
	//test_dft(cm,nn);

	cout << "\n fftCN data\n";
	for(int i=0;i<nn;i++)
		std::cout<<i<<"   "<<cm[i].getReal() << "\t" << cm[i].getIm()<<std::endl;

	ifft_CN(cm,nn);

	cout << "\n ifftCN data\n";
	for(int i=0;i<nn;i++)
		std::cout<<i<<"   "<<cm[i].getReal() << "\t" << cm[i].getIm()<<std::endl;

	delete [] cm;
	
	std::cout << "=========================test_fft_CN end=============================\n";
}
