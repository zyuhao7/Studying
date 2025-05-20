#include <iostream>
#include <string>
#include <stddef.h>
#include <cstring>
using namespace std;

// 第一部分 - 基础
// day-2025-5-20
template<typename T>
inline T const& Max(T const& a, T const& b)
{
	return a > b ? a : b;
}

template<typename T>
inline T* const& Max(T* const& a, T* const& b)
{
	return *a > *b ? a : b;
}

inline char const* const& Max(char const* const& a, char const* const& b)
{
	return std::strcmp(a, b) < 0 ? b : a;
}


int main()
{
	//int a = 7;
	//int b = 42;
	//cout << "Max(a,b): " << Max(a, b) << endl;

	//std::string s1 = "hello";
	//std::string s2 = "world";
	//cout << "Max(s1,s2): " << Max(s1, s2) << endl;

	//int* p1 = &b;
	//int* p2 = &a;
	//cout << "Max(p1,p2): " << *Max(p1, p2) << endl;

	//char const* str1 = "David";
	//char const* str2 = "Alice";
	//cout << "Max(str1,str2): " << Max(str1, str2) << endl;


	// inline T const& Max(T const& a, T const& b)
	/*
	int i = 42;
	cout << "Max(7,i): " << Max(7, i) << endl;

	double f1 = 3.4;
	double f2 = 6.7;
	cout << "Max(f1,f2): " << Max(f1, f2) << endl;

	string s1 = "hello";
	string s2 = "world";
	cout << "Max(s1,s2): " << Max(s1, s2) << endl;
	*/
}