#include "Complex.h"
#include<cmath>
#include <stdio.h>
	void Complexf::setReal(float real1){
		
		real = real1;
	};
	void Complexf::setIm(float im1){
		im = im1;
	};

	float Complexf::getReal(){
		return real;
	};
	float Complexf::getIm(){
		return im;
	};

	void Complexf::operator +=(Complexf c1){
		real = real + c1.getReal();
		im = im + c1.getIm();
	};
	void Complexf::operator *=(Complexf c1){
		temp = real;
		real = real * c1.getReal() - im * c1.getIm();
		im = temp * c1.getIm() +  im * c1.getReal();
	};
	void Complexf::show(){
		printf("\n.....%f%f\n",real,im);;
	}

	float Complexf::getA(){

		return real;
	}

	void Complexf::setData(Complexf c1){
		real = c1.getReal();
		im = c1.getIm();
	}

	void Complexf::toStrings(){
		real = -real;
		im = -im;
	}
	float Complexf::abs(){
		return sqrt(real * real + im * im);
	}

	void Complexf::init(){
		real = 0;
		im = 0;
	}
