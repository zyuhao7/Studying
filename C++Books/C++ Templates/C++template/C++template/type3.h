#pragma once
#include "type2.h"
// ���ö��������������
struct SizeOverOne { char c[2]; };

template<typename T,
		bool convert_possible = !CompoundT<T>::IsFuncT &&
								!CompoundT<T>::IsArrayT>
class ConsumeUDC {
public:
	operator T() const;
};

// ���������͵�ת���ǲ������
template<typename T>
class ConsumeUDC<T, false>{
};

// �� void ���͵�ת���ǲ������
template<bool convert_possible>
class ConsumeUDC<void, convert_possible> {

};

char enum_check(bool);
char enum_check(char);
char enum_check(signed char);
char enum_check(unsigned char);
char enum_check(signed short);
char enum_check(unsigned short);
char enum_check(signed int);
char enum_check(unsigned int);
char enum_check(signed long);
char enum_check(unsigned long);

// ����� float �� int ������ת��
char enum_check(float);
char enum_check(double);
char enum_check(long double);

SizeOverOne enum_check(...); // ����ʣ����������
#include "type1.h"


template<typename T>
class IsEnumT {
public:
	enum {Yes = IsFundaT<T>::No &&
				!CompoundT<T>::IsRefT &&
				!CompoundT<T>::IsPtrT && 
				!CompoundT<T>::IsPtrMemT &&
				sizeof(enum_check(ConsumeUDC<T>())) == 1 };
	enum {No = !Yes};
};


