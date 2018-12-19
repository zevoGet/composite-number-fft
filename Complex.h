#ifndef	__Complex_fourier_
#define __Complex_fourier_

#ifndef PI
#define PI 3.14159265359
#endif // !PI



class Complexf
{
private:
	float real;
	float im;
	float temp;
public:

	Complexf():temp(),
	real(0),
	im(0){
	}

	Complexf(float a){
		real = a;
		im = 0;
	}

	void setReal(float real1);
	void setIm(float im1);

	float getReal();
	float getIm();

	float getA();
	void operator +=(Complexf c1);
	void operator *=(Complexf c1);
	void setData(Complexf c1);
	void setSelf(const Complexf &c1);
	void toStrings();
	void show();
	float abs();
	void init();
	//static void (* test)();



	

	//函数入口地址
	//void (*init)(void *,void *);
	//void (*ovrid)(void*);
};

//class aaa{
//private:
//	float a;
//	float b;
//	char c;
//	//short d;
//public:
//	aaa(){
//	};
//	void show();
//	void getb();
//};

#endif // _m_Complex_f_
