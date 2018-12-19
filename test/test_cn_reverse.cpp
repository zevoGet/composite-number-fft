#include "test.h"
#include<iostream>
using namespace std;


void test_CN_reverse(){
	int nn = 36;
	float arr[36] = { 3, 4, 5, 2, 3, 4, 1, 2, 5, 4, 3, 5, 6, 7, 2, 3, 4, 4, 3, 4, 5, 2, 3, 4, 1, 2, 5, 4, 3, 5, 6, 7, 2, 3, 4, 4 };
	Complexf *cm = new Complexf[nn];
	for (int i = 0; i<nn; i++){
		cm[i].setReal(arr[i]);
		cm[i].setIm(0);
	}
	u_int* prim = getPrime(nn);
	

	std::cout << "=========================test_CN_reverse start=============================\n";

	cout << "\n origin data\n";
	for (int i = 0; i<nn; i++)
		std::cout << i << "   " << cm[i].getReal() << "\t" << cm[i].getIm() << std::endl;

	CN_reverse(cm, prim,nn);

	cout << "\n test_CN_reverse data\n";
	for (int i = 0; i<nn; i++)
		std::cout << i << "   " << cm[i].getReal() << "\t" << cm[i].getIm() << std::endl;

	/*CN_reverse(cm, prim, nn);

	cout << "\n double CN_reverse data\n";
	for (int i = 0; i<nn; i++)
		std::cout << i << "   " << cm[i].getReal() << "\t" << cm[i].getIm() << std::endl;*/



	delete []cm;
	delete []prim;


	std::cout << "=========================test_CN_reverse end=============================\n";
}
