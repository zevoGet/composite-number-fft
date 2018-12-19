#include "test.h"
#include<iostream>
using namespace std;



void test_fft2(){
	//test_fft2

	int nn = 32;
	float arr[36] = { 3, 4, 5, 2, 3, 4, 1, 2, 5, 4, 3, 5, 6, 7, 2, 3, 4, 4, 3, 4, 5, 2, 3, 4, 1, 2, 5, 4, 3, 5, 6, 7, 2, 3, 4, 4 };
	Complexf *cm = new Complexf[nn];
	for (int i = 0; i<nn; i++){
		cm[i].setReal(arr[i]);
		cm[i].setIm(0);
	}

	std::cout << "=========================test_fft2 start=============================\n";

	cout << "\n origin data\n";
	for (int i = 0; i<nn; i++)
		std::cout << i << "   " << cm[i].getReal() << "\t" << cm[i].getIm() << std::endl;

	fft_base2(cm, nn);
	//test_dft(cm,nn);

	cout << "\n fft2 data\n";
	for (int i = 0; i<nn; i++)
		std::cout << i << "   " << cm[i].getReal() << "\t" << cm[i].getIm() << std::endl;

	ifft_base2(cm, nn);

	cout << "\n ifft2 data\n";
	for (int i = 0; i<nn; i++)
		std::cout << i << "   " << cm[i].getReal() << "\t" << cm[i].getIm() << std::endl;

	/*ifft_base2(cm,nn);
	printf("====================================ifft===========\n");
	for(int i=0;i<16;i++)
	std::cout<<i<<"   "<<cm[i].getReal() << "\t" << cm[i].getIm()<<std::endl;*/

	delete[] cm;

	std::cout << "=========================test_fft2 end=============================\n";
}
