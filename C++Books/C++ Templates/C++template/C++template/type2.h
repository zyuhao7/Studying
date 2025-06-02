#pragma once
// 辨别组合类型
#include <stddef.h>

template<typename T>
class IsFunctionT {
private:
	typedef char One;
	typedef struct { char a[2]; } Two;
	template<typename U>
	static One test(...) {}

	template<typename U>
	static Two test(U(*)[1]) {} // 函数类型不能作为数组元素类型, 不过还有局部引用和 void 同样也不能.
public:
	enum { Yes = sizeof(test<T>(0)) == sizeof(One) };
	enum { No = !Yes };
};

template<typename T>
class IsFunctionT<T&> {
public:
	enum { Yes = 0 };
	enum { No = !Yes };
};

template<>
class IsFunctionT<void> {
public:
public:
	enum { Yes = 0 };
	enum { No = !Yes };
};

template<>
class IsFunctionT<void const> {
public:
	enum { Yes = 0 };
	enum { No = !Yes };
};

template<typename T>
class CompoundT {
public:
	enum {IsPtrT = 0, IsRefT = 0, IsArrayT = 0,
	IsFuncT = IsFunctionT<T>::Yes, IsPtrMemT = 0};

	typedef T BaseT;
	typedef T BottomT;
	typedef CompoundT<void> ClassT;
};


template<typename T>
class CompoundT<T&> {
public:
	enum {
		IsPtrT = 0, IsRefT = 1, IsArrayT = 0,
		IsFuncT = 0, IsPtrMemT = 0
	};
	typedef T BaseT;
	typedef typename CompoundT<T>::BottomT BottomT;
	typedef CompoundT<void> ClassT;
};

template<typename T>
class CompoundT<T*> {
public:
	enum {
		IsPtrT = 1, IsRefT = 0, IsArrayT = 0,
		IsFuncT = 0, IsPtrMemT = 0
	};
	typedef T BaseT;
	typedef typename CompoundT<T>::BottomT BottomT;
	typedef CompoundT<void> ClassT;
};

template<typename T, size_t N>
class CompoundT<T[N]> {	// 针对数组的局部特化
public:
	enum {
		IsPtrT = 0, IsRefT = 0, IsArrayT = 1,
		IsFuncT = 0, IsPtrMemT = 0
	};
	typedef T BaseT;
	typedef typename CompoundT<T>::BottomT BottomT;
	typedef CompoundT<void> ClassT;
};

template<typename T>
class CompoundT<T[]> {	// 针对空数组的局部特化
public:
	enum {
		IsPtrT = 0, IsRefT = 0, IsArrayT = 1,
		IsFuncT = 0, IsPtrMemT = 0
	};
	typedef T BaseT;
	typedef typename CompoundT<T>::BottomT BottomT;
	typedef CompoundT<void> ClassT;
};

template<typename T, typename C>
class CompoundT<T C::*> {	// 针对成员指针的局部特化
public:
	enum {
		IsPtrT = 0, IsRefT = 0, IsArrayT = 0,
		IsFuncT = 0, IsPtrMemT = 1
	};
	typedef T BaseT;
	typedef typename CompoundT<T>::BottomT BottomT;
	typedef C ClassT;
};

// 函数模板辨别
template<typename R>
class CompoundT<R()> {
public:
	enum {
		IsPtrT = 0, IsRefT = 0, IsArrayT = 0,
		IsFuncT = 1, IsPtrMemT = 0
	};
	typedef R BaseT();
	typedef R BottomT();
	typedef CompoundT<void> ClassT;
};

template<typename R, typename P1>
class CompoundT<R(P1)> {
public:
	enum {
		IsPtrT = 0, IsRefT = 0, IsArrayT = 0,
		IsFuncT = 1, IsPtrMemT = 0
	};
	typedef R BaseT(P1);
	typedef R BottomT(P1);
	typedef CompoundT<void> ClassT;
};


template<typename R, typename P1>
class CompoundT<R(P1, ...)> {
public:
	enum {
		IsPtrT = 0, IsRefT = 0, IsArrayT = 0,
		IsFuncT = 1, IsPtrMemT = 0
	};
	typedef R BaseT(P1);
	typedef R BottomT(P1);
	typedef CompoundT<void> ClassT;
};

