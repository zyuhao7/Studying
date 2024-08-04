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
using namespace std;

#if 0
//组态3: __STL_STATIC_TEMPLATE_MEMBER_BUG
template<typename T>
class testClass
{
public:
	static int _data;
};

int testClass<int>::_data = 1;
int testClass<char>::_data = 2;


int main()
{
	cout << testClass<int>::_data << endl; //1
	cout << testClass<char>::_data << endl; //2

	testClass<int> obj1, obj2;
	testClass<char> objc1, objc2;

	cout << obji1._data << endl; //1
	cout << obji2._data << endl; //1
	cout << objc1._data << endl; //2
	cout << objc2._data << endl; //2

	obji1._data = 3;
	objc2._data = 4;

	cout << obji1._data << endl; //3
	cout << obji2._data << endl; //3
	cout << objc1._data << endl; //4
	cout << objc2._data << endl; //4

	return 0;
}
#endif

#if 0
// 组态5: __STL_CLASS_PARTIAL_SPECIALIZATION

//一般化设计
template<class I, class O>
struct testClass
{
	testClass()
	{
		cout << "I,O" << endl;
	}
};

//特殊化设计
template<class T>
struct testClass<T*, T*>
{
	testClass()
	{
		cout << "T*,T*" << endl;
	}
};

template<class T>
struct testClass<const T*, T*>
{
	testClass()
	{
		cout << "const T*,T*" << endl;
	}
};

int main()
{
	testClass<int, char> obj1; //I O
	testClass<int*, int*> obj2;//T* T*
	testClass<const int*, int*> obj3;//const T* T*
}

#endif

#if 0
//组态6: __STL_FUNCTION_TEMP_PARTIAL_ORDER
class alloc{};

template<class T, class Alloc=alloc>
class Vector
{
public:
	void swap(Vector<T, Alloc>&) 
	{
		cout << "swap()" << endl;
	}
};

#ifdef __STL_FUNCTION_TEMP_PARTIAL_ORDER // 只为说明,非本程序内容
template<class T,class Alloc>
inline void SWAP(vector<T, Alloc>& x, vector<T, Alloc>& y)
{
	x.swap(y);
	cout<<"x.swap(y)"<<endl;
}
#endif									 // 只为说明,非本程序内容

int main()
{
	Vector<int> x, y;
	//SWAP(x, y); // 无输出.
	//vector<int> x, y;
	x.swap(y); // swap()  
	return 0;
}
#endif

#if 0
//组态8: __STL_MEMBER_TEMPLATES
class alloc{};

template<class T,class Alloc=alloc>
class Vector
{
public:
	typedef T value_type;
	typedef value_type* iterator;

	template<class I>
	void insert(iterator pos, I first, I last)
	{
		cout << "insert()" << endl;
	}
};

int main()
{
	int a[5] = { 0,1,2,3,4 };
	Vector<int> x;
	Vector<int>::iterator it = nullptr;
	x.insert(it, a, a + 5); // insert()
}
#endif

#if 0
//组态10: __STL_LIMITED_DEFAULT_TEMPLATES
class alloc{};

template<class T, class Alloc=alloc,size_t BufSiz=0>
class Deque {
public:
	Deque() { cout << "Deque" << endl; }
};

template<class T, class Sequence=Deque<T>>
class stack {
public:
	stack() { cout << "stack" << endl; }
private:
	Sequence c;
};

int main()
{
	stack<int> x; //Deque
	              //stack
	return 0;
}
#endif

#if 1
// 组态11: __STL_NON_TYPE_TMPL_PARAM_BUG
class alloc
{
};

inline size_t __deque_buf_size(size_t n, size_t sz)
{
	return n != 0 ? n : (sz < 512 ? size_t(512 / sz) : size_t(1));
}

template <class t, class ref, class ptr, size_t bufsiz>
struct __deque_iterator
{
	typedef __deque_iterator<t, t &, t *, bufsiz> iterator;
	typedef __deque_iterator<t, const t &, const t *, bufsiz> const_iterator;
	static size_t buffer_size()
	{
		return __deque_buf_size(bufsiz, sizeof(t)); // linux 下 sizeof 需要加 () 限定...
	}
};

template <class t, class alloc = alloc, size_t bufsiz = 0>
class Deque
{
public:
	typedef __deque_iterator<t, t &, t *, bufsiz> iterator;
};

int main()
{
	cout << Deque<int>::iterator::buffer_size() << endl;			// 128
	cout << Deque<int, alloc, 64>::iterator::buffer_size() << endl; // 64
	return 0;
}
#endif