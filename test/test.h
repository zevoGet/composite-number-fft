#ifndef test_projfft
#define test_projfft
#include "./../common.h"
#include <time.h>
#include <chrono>
/*get timestamp*/
time_t getTimeStamp();

/*test get prime of CN*/
void testPrime();

/*test log2*/
void test_log2();

/*test dft*/
void test_dft();

/*test bit reverse*/
void test_bitReverse();

/*test CN reverse*/
void test_CN_reverse();

/*test fft base on 2 */
void test_fft2();

/*test shift and unshift*/
void test_fft2d_shift();

/*test fft base on CN*/
void test_fft_CN();
/**test fft_normal */
void test_normal_fft();
#endif
