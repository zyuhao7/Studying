#ifndef CLOCK
#define CLOCK

class Clock
{
public:
	Clock(int newH, int newM, int newS);
	Clock(Clock& c);
	void SetTime(int newH, int newM, int newS);
	void ShowTime();
	~Clock();
private:
	int Hour, Minute, Second;
};

#endif