#include "test.h"
#include<iostream>
using namespace std;

/*getTime*/
time_t getTimeStamp()
{
	chrono::time_point<std::chrono::system_clock, chrono::milliseconds> tp = chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
	auto tmp = chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());
	time_t timestamp = tmp.count();
	return timestamp;
}

void test_log2(){
	//test log2
	time_t t1,t2,t3;
	t1 = getTimeStamp();
	for (int i = 0; i < 10000000; i++){
		log2a(i);
	}
	t2 = getTimeStamp();
	for (int i = 0; i < 10000000; i++){
		log2(i);
	}
	t3 = getTimeStamp();
	std::cout << "=========================test_log2 start=============================\n";
	std::cout <<  "compute 10000000 times of log2\n";
	
	std::cout << "\nlocal log2 cost " << t2 - t1 <<"\n";
	std::cout << "\nsystem log2 cost " << t3 - t2 << "\n";
	std::cout << "=========================test_log2 end=============================\n";
}
