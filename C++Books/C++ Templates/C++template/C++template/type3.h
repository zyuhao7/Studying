#pragma once
#include "type2.h"
// 辨别枚举类型与类类型
struct SizeOverOne { char c[2]; };

template<typename T,
		bool convert_possible = !CompoundT<T>::IsFuncT &&
								!CompoundT<T>::IsArrayT>
class ConsumeUDC {
public:
	operator T() const;
};

// 到函数类型的转型是不允许的
template<typename T>
class ConsumeUDC<T, false>{
};

// 到 void 类型的转型是不允许的
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

// 避免从 float 到 int 的意外转型
char enum_check(float);
char enum_check(double);
char enum_check(long double);

SizeOverOne enum_check(...); // 捕获剩余的所有情况
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


