#include "test.h"
#include<iostream>
using namespace std;



void test_fft2d_shift(){
	//test_fft2d_shift
	int w = 6;
	int h = 6;
	float arr[6][6] = { { 2, 4, 5, 4, 5, 6 }, { 3, 5, 6, 4, 5, 7 }, { 4, 7, 8, 4, 6, 8 }, { 5, 6, 7, 9, 7, 6 }, { 5, 2, 3, 5, 6, 8 }, { 6, 2, 4, 3, 5, 8 } };
	Complexf* cm = (Complexf *)malloc(sizeof(Complexf)* w * h);
	for (int i = 0; i<h; i++){
		for (int j = 0; j<w; j++){
			cm[i*w + j].setReal(arr[i][j]);
			cm[i*w + j].setIm(0);
		}
	}
	std::cout << "=========================test_fft2d_shift start=============================\n";
	printf("\nthe origin array");
	for (int i = 0; i < w*h; i++){
		std::cout << cm[i].getReal() << "\t";
	}

	printf("\nthe shift array");

	fft_2d_shift(cm,w*h);

	for (int i = 0; i < w*h; i++){
		std::cout << cm[i].getReal() << "\t";
	}

	printf("\nthe unshift array");

	fft_2d_unshift(cm, w*h);

	for (int i = 0; i < w*h; i++){
		std::cout << cm[i].getReal() << "\t";
	}
	std::cout << "=========================test_fft2d_shift end=============================\n";

	free(cm);
}
