#include "test.h"
#include<iostream>
using namespace std;


void test_bitReverse(){
	int nn = 32;
	float arr[36] = { 3, 4, 5, 2, 3, 4, 1, 2, 5, 4, 3, 5, 6, 7, 2, 3, 4, 4, 3, 4, 5, 2, 3, 4, 1, 2, 5, 4, 3, 5, 6, 7, 2, 3, 4, 4 };
	Complexf *cm = new Complexf[nn];
	for (int i = 0; i<nn; i++){
		cm[i].setReal(arr[i]);
		cm[i].setIm(0);
	}

	std::cout << "=========================test_bitReverse start=============================\n";

	cout << "\n origin data\n";
	for (int i = 0; i<nn; i++)
		std::cout << i << "   " << cm[i].getReal() << "\t" << cm[i].getIm() << std::endl;

	bitReverse(cm, nn);

	cout << "\n test_bitReverse data\n";
	for (int i = 0; i<nn; i++)
		std::cout << i << "   " << cm[i].getReal() << "\t" << cm[i].getIm() << std::endl;

	bitReverse(cm, nn);

	cout << "\n double bitReverse data\n";
	for (int i = 0; i<nn; i++)
		std::cout << i << "   " << cm[i].getReal() << "\t" << cm[i].getIm() << std::endl;

	delete[] cm;

	std::cout << "=========================test_bitReverse end=============================\n";
}
