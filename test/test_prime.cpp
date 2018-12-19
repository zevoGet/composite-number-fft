#include "test.h"
#include<iostream>
using namespace std;

void testPrime(){
	//test getPrime
	u_int N = 18*27*49*169*256;
	u_int* A = getPrime(N);
	std::cout << "=========================testPrime start=============================\n";
	std::cout<<"input number"<<N<<"\n";
	std::cout << "the prime of number are below" << N << "\n";
	for(int i=1;i<=A[0];i++){
		cout<<A[i]<<endl;
	}
	std::cout << "=========================testPrime end=============================\n";
	delete A;

}
