#include "test.h"
#include<iostream>
using namespace std;



void test_normal_fft(){
	//test_fft2

	int nn = 31;
	float arr[36] = { 3, 4, 5, 2, 3, 4, 1, 2, 5, 4, 3, 5, 6, 7, 2, 3, 4, 4, 3, 4, 5, 2, 3, 4, 1, 2, 5, 4, 3, 5, 6, 7, 2, 3, 4, 4 };
	Complexf *cm = new Complexf[nn];
	for (int i = 0; i<nn; i++){
		cm[i].setReal(arr[i]);
		cm[i].setIm(-1);
	}

	std::cout << "=========================test_normal_fft start=============================\n";

	cout << "\n origin data\n";
	for (int i = 0; i<nn; i++)
		std::cout << i << "   " << cm[i].getReal() << "\t" << cm[i].getIm() << std::endl;



	cout << "\ntest_normal_fft data11111\n";
	fft_normal(cm, nn);
	for (int i = 0; i<nn; i++)
		std::cout << i << "   " << cm[i].getReal() << "\t" << cm[i].getIm() << std::endl;

	cout << "\ntest_normal_fft data\n";
	ifft_normal(cm, nn);
	for (int i = 0; i<nn; i++)
		std::cout << i << "   " << cm[i].getReal() << "\t" << cm[i].getIm() << std::endl;


	delete[] cm;

	std::cout << "=========================test_normal_fft end=============================\n";



}
