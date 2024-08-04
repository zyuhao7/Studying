#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#define _ALIGN 8

using namespace std;

#if 1
static size_t _S_freelist_index(size_t __bytes)
{
	return (((__bytes) + (size_t)_ALIGN - 1) / (size_t)_ALIGN - 1);
}

int main()
{
	printf("this is my first c program.");

	cout << _S_freelist_index(1) << endl;
}

void print_chars(int n, char c)
{
	int i;
	for (i = 0; i < n; ++i)
	{
		char *s;
		int j;

		s = (char *)calloc(i + 2, 1);
		if (!s)
			perror("calloc");
		for (j = 0; j < i + 1; ++j)
			s[j] = c;
		printf("%s\n", s);
		free(s);
	}
}
int main()
{
	print_chars(5, 'A');
}

#define __STL_TEMPLATE_NULL template <>

template <class Key>
struct Hash
{
	void operator()() { cout << "Hash<T>" << endl; }
};

// 显式特化.
__STL_TEMPLATE_NULL
struct Hash<char>
{
	void operator()() { cout << "Hash<char>" << endl; }
};

__STL_TEMPLATE_NULL
struct Hash<unsigned char>
{
	void operator()() { cout << "Hash<unsigned char>" << endl; }
};

int main()
{
	Hash<long> t1;
	Hash<char> t2;
	Hash<unsigned char> t3;

	t1(); // Hash<T>
	t2(); // Hash<char>
	t3(); // Hash<unsigned char>
}

// P71 1.9.2 临时对象的产生和运用.

template <typename T>
class print
{
public:
	void operator()(const T &elem)
	{
		cout << elem << " ";
	}
};
int main()
{
	int a[] = {0, 1, 2, 3, 4, 5};
	vector<int> v{a, a + 6};
	print<int> p;
	print<int>(); // 临时对象, 不是一个函数调用操作.
	for_each(v.begin(), v.end(), print<int>());
	return 0;
}

// 1.9.3 静态常量整数成员在class内部直接初始化.

template <typename T>
class testClass
{
public:
	static const int _d = 5;
	static const long _ld = 3L;
	static const char _c = 'C';
};

int main()
{
	cout << testClass<int>::_d << endl;	 // 5
	cout << testClass<int>::_ld << endl; // 3
	cout << testClass<int>::_c << endl;	 // C

	return 0;
}

// 1.9.4 increment/decrement/dereference 操作符
class INT
{
	friend ostream &operator<<(ostream &os, const INT &i);

public:
	INT(int i)
		: m_i(i) {};

	// prefix: increment and the fetch 前置
	INT &operator++()
	{
		++(this->m_i);
		return *this;
	}

	// postfix : fetch and then increment 后置.
	const INT operator++(int)
	{
		INT tmp = *this;
		++(*this);
		//++(this->m_i);
		return tmp;
	}

	// prefix : decrement and the fetch
	INT &operator--()
	{
		--(this->m_i);
		return *this;
	}

	// postfix : fetch and then decrement
	const INT operator--(int)
	{
		INT tmp = *this;
		--(this->m_i);
		return tmp;
	}

	// dereference
	int &operator*() const
	{
		return (int &)m_i;
	}

private:
	int m_i;
};

ostream &operator<<(ostream &os, const INT &i)
{
	os << "[" << i.m_i << "]" << endl;
	return os;
}

int main()
{
	INT I(5);
	cout << I++;
	cout << ++I;
	cout << I--;
	cout << --I;
	cout << *I;
	return 0;
}
#endif

// 第二版- ! -
//
// class INT
//{
//	friend ostream& operator << (ostream& os, const INT& i);
// private:
//	int m_i;
// public:
//	INT(int i)
//		:m_i(i)
//	{};
//
//	INT& operator++()
//	{
//		++this->m_i;
//		return *this;
//	}
//
//	INT operator++(int)
//	{
//		INT tmp = *this;
//		++(this	->m_i);
//		return tmp;
//	}
//
//	//INT& operator* () const
//	//{
//	//	return (INT&)m_i;
//	//}
//
//		int& operator*() const
//	{
//		return (int&)m_i;
//	}
//};
//
//
// ostream& operator <<(ostream& os,const INT& i)
//{
//	os << "[" << i.m_i << "]" << endl;
//	return os;
//}
//
// int main()
//{
//	INT I (5);
//	cout << ++I;
//	cout << I++;
//	cout << *I;
//}

// 1.9.5 前闭后开表示法 [ )

template <class InputIterator, class T>
InputIterator find(InputIterator first, InputIterator last, const T &val)
{
	while (first != last && *first != val)
		++first;
	return first;
}

template <class InputIterator, class Function>
Function for_each(InputIterator first, InputIterator last, Function f)
{
	for (; first != last; ++first)
	{
		f(*first);
		return f;
	}
}

#if 1
// 1.9.6 function call 操作符(operator())
// 函数指针版本.
int fcmp(const void *e1, const void *e2)
{
	// return  *((int*)e1) - *((int*)e2);
	const int *i1 = (const int *)e1;
	const int *i2 = (const int *)e2;
	if (*i1 < *i2)
		return -1;
	else if (*i1 == *i2)
		return 0;
	else if (*i1 > *i2)
		return 1;
};

int main()
{
	int a[10] = {32, 92, 67, 58, 10, 4, 20, 52, 59, 54};
	for (int i = 0; i < 10; ++i)
		cout << a[i] << ' '; // 原
	cout << endl;
	qsort(a, sizeof(a) / sizeof(int), sizeof(int), fcmp);
	for (int i = 0; i < 10; ++i)
		cout << a[i] << ' '; // 递增.

	return 0;
}
#endif

#if 1
template <class T>
struct Plus
{
	T operator()(const T &x, const T &y) { return x + y; }
};
template <class T>
struct Minus
{
	T operator()(const T &x, const T &y) { return x - y; }
};

int main()
{
	Plus<int> plusobj;
	Minus<int> minusobj;
	cout << plusobj(3, 5) << endl;	// 8
	cout << minusobj(3, 5) << endl; //-2

	cout << Plus<int>()(43, 50) << endl;  // 93
	cout << Minus<int>()(43, 50) << endl; // -7
	return 0;
}
#endif