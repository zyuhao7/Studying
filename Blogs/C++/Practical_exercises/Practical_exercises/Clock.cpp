#include"Clock.h"
#include<iostream>

using namespace std;
#if 0
Clock::Clock(int h, int m, int s)
{
	this->Hour = h;
	this->Minute = m;
	this->Second = s;
}

Clock::Clock(Clock& c)
{
	this->Hour = c.Hour;
	this->Minute = c.Minute;
	this->Second = c.Second;
}

void Clock::SetTime(int h, int m, int s)
{
	// �Ӳ��� this ָ�붼һ��.
	Hour = h;
	Minute = m;
	Second = s;
}

void Clock::ShowTime()
{
	cout << this->Hour << ":" << this->Minute << ":" << this->Second << endl;
}

Clock::~Clock(){}

int main()
{
	Clock c(0, 0, 0);
	c.SetTime(10, 20, 30);
	c.ShowTime();

	Clock c1(c);
	c1.ShowTime();
	c1.SetTime(90, 98, 99);
	c1.ShowTime();

}

#endif