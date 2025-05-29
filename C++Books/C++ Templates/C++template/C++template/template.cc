#include <iostream>
#include <string>
#include <stddef.h>
#include <cstring>
#include <vector>
#include <list>
#include <stack>
#include <typeinfo>
using namespace std;

// ��һ���� - ����
// day-2025-5-20
//template<typename T>
//inline T const& Max(T const& a, T const& b)
//{
//	return a > b ? a : b;
//}
//
//template<typename T>
//inline T* const& Max(T* const& a, T* const& b)
//{
//	return *a > *b ? a : b;
//}
//
//inline char const* const& Max(char const* const& a, char const* const& b)
//{
//	return std::strcmp(a, b) < 0 ? b : a;
//}


//int main()
//{
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
//}

//#include "stack1.h"
// ��ģ��

// �ֲ��ػ�
//template<typename T1, typename T2>
//class MyClass{};
//
//template<typename T>
//class MyClass<T, T> {};
//
//template<typename T>
//class MyClass<T, int>{};
//
//template<typename T1, typename T2>
//class MyClass<T1*, T2*>{};
//
//template<typename T>
//class MyClass<T*, T*>{};
//
//
//int main()
//{
//	try
//	{
//		Stack<int> intSt;
//		Stack<std::string> stringSt;
//
//		intSt.push(7);
//		cout << "intSt.top(): " << intSt.top() << endl;
//
//		stringSt.push("hello");
//		cout << "stringSt.top(): " << stringSt.top() << endl;
//		stringSt.pop();
//		stringSt.pop();
//	}
//	catch (const std::exception& e)
//	{
//		std::cerr << "Exception: " << e.what() << std::endl;
//		return EXIT_FAILURE;
//	}
//}

//#include <deque>
//#include "stack3.h"
//int main()
//{
//	try
//	{
//		Stack<int> intSt;
//		Stack<double, std::deque<double>> doubleSt;
//		intSt.push(7);
//		cout << "intSt.top(): " << intSt.top() << endl;
//
//		doubleSt.push(3.14);
//		cout << "doubleSt.top(): " << doubleSt.top() << endl;
//		doubleSt.pop();
//		doubleSt.pop();
//	}
//	catch (const std::exception& e)
//	{
//		std::cerr << "Exception : " << e.what() << std::endl;
//		return EXIT_FAILURE;
//	}
//}


//2025-5-21
// ������-������ģ�����
//#include "stack4.h"

//int main()
//{
//	try
//	{
//		Stack<int, 20> int20St;
//		Stack<int, 40> int40St;
//		Stack<string, 20> stringSt;
//
//		int20St.push(7);
//		cout << "int20St.top(): " << int20St.top() << endl;
//
//		int40St.push(42);
//		cout << "int40St.top(): " << int40St.top() << endl;
//
//		stringSt.push("helo");
//		cout << "stringSt.top(): " << stringSt.top() << endl;
//		stringSt.pop();
//		stringSt.pop();
//
//	}
//	catch (const std::exception& e)
//	{
//		std::cerr << "Exception: " << e.what() << std::endl;
//		return EXIT_FAILURE;
//	}
//
//
//	return 0;
//}

// �����͵ĺ���ģ�����
//template<typename T, int N>
//T addN(T const& x)
//{
//	return x + N;
//}
//
//int main()
//{
//	int i = 7;
//	double d = 3.14;
//	cout << "addN<int, 10>(i): " << addN<int, 10>(i) << endl;
//	cout << "addN<double, 5>(d): " << addN<double, 5>(d) << endl;
//	return 0;
//}

// ������-�����Ի���֪ʶ
//template<typename T>
//class MyClass
//{
//	typename T::SubType* ptr; // ��ʹ�� typename ,�� ������Ϊ T::SubType �� ptr �ĳ˻�
//};
//
//template<typename T>
//class Base
//{
//public:
//	void Exit()
//	{
//		cout << "Base::Exit()"<<endl;
//	}
//};
//
//template<typename T>
//class Derived : Base<T> {
//public:
//	void foo()
//	{
//		Base<T>::Exit();
//	}
//};
//
//int main()
//{
//	Derived<int> d;
//	d.foo();
//}

//#include "stack5.h"

//int main()
//{
//	Stack<int> intSt;
//	Stack<double> doubleSt;
//	doubleSt = intSt;
//
//	return 0;
//}
// 
//#include "stack6.h"
//// ģ���ģ�����
//int main()
//{
//	Stack<int, std::deque> intSt;
//	Stack<double, std::deque> doubleSt;
//	intSt.push(7);
//	cout << "intSt.top(): " << intSt.top() << endl;
//	doubleSt.push(3.14);
//	cout << "doubleSt.top(): " << doubleSt.top() << endl;
//	doubleSt.pop();
//	doubleSt.pop();
//
//	return 0;
//}
// 
// 
//#include <deque>
//#include "stack7.h"
//int main()
//{
//	try
//	{
//		Stack<int> intSt;
//		Stack<double> doubleSt;
//		intSt.push(7);
//		intSt.push(42);
//
//		doubleSt.push(7.7);
//
//		doubleSt = intSt;
//		std::cout << doubleSt.top() << endl;
//		doubleSt.pop();
//		std::cout << doubleSt.top() << endl;
//		doubleSt.pop();
//		std::cout << doubleSt.top() << endl;
//		doubleSt.pop();
//	}
//	catch (const std::exception& e)
//	{
//		std::cerr << "Exception: " << e.what() << std::endl;
//	}
//
//}

// ���ʼ��
//template<typename T>
//void foo()
//{
//	T t = T();
//	cout << "t: " << t << endl;
//}
//
//int main()
//{
//	foo<int>();
//	foo<double>();
//	foo<std::string>();
//	foo<int*>();
//	foo<std::string*>();
//	foo<int(*)()>();
//	foo<std::string(*)()>();
//	return 0;
//}

//#include <iostream>
//#include <typeinfo>
//
//template<typename T>
//void ref(T const& x)
//{
//	std::cout << "x in ref(T const&): " << typeid(x).name() << endl;
//}
//
//template<typename T>
//void nonref(T x)
//{
//	std::cout << "x in nonref(T) : " << typeid(x).name() << endl;
//}
//
//template<typename T, int N, int M>
//T const* max(T const (&a)[N], T const (&b)[M]) // ����
//{
//	return a[0] > b[0] ? a : b;
//}
//
//int main()
//{
//	int a[5] = { 2, 2, 3, 4, 5 };
//	int b[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
//	int const* p = max(a, b);
//	std::cout << "p: " << *p << std::endl;
//
//	ref("hello");		// x in ref(T const&): char const [6]
//	nonref("hello");    // x in nonref(T) : char const * __ptr64
//
//	string s = "world";
//	::ref(s);
//	nonref(s);
//}


// ������-ģ��ʵս
//day-2025-5-22
//#include <algorithm>
//#include "tracer.h"
//int main()
//{
//	SortTracer input[] = { 7, 3, 5, 6, 4, 2, 0, 1, 9 ,8 };
//	for (int i = 0; i < 10;++i)
//	{
//		cerr << input[i].val() << " ";
//	}
//	std::cerr << std::endl;
//
//	long created_at_start = SortTracer::creations();
//	long max_live_at_start = SortTracer::max_live();
//	long assigned_at_start = SortTracer::assignments();
//	long compared_at_start = SortTracer::comparisons();
//
//	//ִ���㷨
//	std::cerr << "---[Start std::sort() ]-------------------------" << std::endl;
//	std::sort(&input[0], &input[9] + 1);
//	std::cerr << "---[End std::sort() ]-------------------------" << std::endl;
//
//	// ȷ�Ͻ��
//	for (int i = 0; i < 10; ++i)
//	{
//		cerr << input[i].val() << " ";
//	}
//	std::cerr << std::endl;
//
//	std::cerr << "std::sort() of 10 SortTracer's"
//		<< " was performed by: \n"
//		<< SortTracer::creations() - created_at_start
//		<< " temporary tracers \n"
//		<< "up to "
//		<< SortTracer::max_live()
//		<< " tracers at the same time ("
//		<< max_live_at_start << " before) \n"
//		<< SortTracer::assignments() - assigned_at_start
//		<< " assignments \n"
//		<< SortTracer::comparisons() - compared_at_start
//		<< " comparisons \n";
//}


// day-2025-5-23
// �ڰ���-����ģ�����

// day-2025-5-24
// �ھ���- ģ���е�����
//template<typename T>
//class C
//{
//	friend void f();
//	friend void f(C<T> const&);
//};
//
//void g(C<int> const& c)
//{
//	f(c); // ����
//	f(); // ����
//}
//
//int main()
//{
//	C<int> c;
//	f(c); // ����
//	f(); // ����
//	g(c); // ����
//	return 0;
//}


//int C;
//class C
//{
//private:
//	int i[2];
//public:
//	static int f()
//	{
//		return sizeof(C);
//	}
//};
//
//int f()
//{
//	return sizeof(C);
//}
//
//
//class BX
//{
//public:
//	void f(int);
//	void f(char const*);
//	void g();
//};
//
//class DX : private BX
//{
//public:
//	using BX::f; // ������� BX::f()
//};
//
//int main()
//{
//	std::cout << "C::f() =  " << C::f() << std::endl;
//	std::cout << "::f() =  " << f() << std::endl;
//	return 0;
//}

// �������Ի���
// ��������Ͳ�������ģ���������������ģ�嶨��ʱ���Ѿ���ȫȷ����
//struct Base {
//	void foo() {}
//};
//
//template <typename T>
//struct Derived : Base  // // Base ������ T���Ƿ������Ի���
//{  
//	void bar() 
//	{
//		foo();  // ֱ�ӵ��� Base::foo()
//	}
//};
//����ĳ�Ա���� foo()����ģ�嶨��׶ξͿ��Ա�ֱ�Ӳ��ң�������֪�����Ĵ��ڡ�
//��������Ա�����ڣ�����ģ�嶨��׶α�������ʵ�����׶Σ���

// �����Ի���
//template <typename T>
//struct Base {
//	void foo() { cout << "Base::foo()" << endl; }
//};
//
//template <typename T>
//struct Derived : Base<T> {  // Base<T> ���� T���������Ի���
//	void bar() {
//		// foo();  // ֱ�ӵ��ûᱨ����Ϊ foo() ������������
//		this->foo();  // ��ȷ��ͨ�� this �� Base<T>::foo() ����
//	}
//};
//
//int main()
//{
//	Derived<int> d;
//	d.bar();  // ��ȷ���� Derived::bar()����ӷ��� Base::foo()
//	return 0;
//}

//template <typename Derived>
//struct Base {  // �����Ի���
//	void foo() {
//		static_cast<Derived*>(this)->impl();  // �����������ʵ��
//	}
//};
//
//struct MyDerived : Base<MyDerived> {  // CRTP
//	void impl() {
//		std::cout << "MyDerived::impl()\n";
//	}
//};
//
//int main() {
//	MyDerived d;
//	d.foo();  // ��� "MyDerived::impl()"
//}

// 2025-5-25
// ��ʮ��-ʵ����
//class MyInt
//{
//public:
//	MyInt(int i);
//};
//
//MyInt operator-(MyInt const&);
//bool operator>(MyInt const&, MyInt const&);
//
//typedef MyInt Int;
//template<typename T>
//void f(T i)
//{
//	if (i > 0)
//	{
//		g(-i);
//	}
//}
//
//void g(Int)
//{
//	f<Int>(42);
//}

//template<typename T>
//void f(T x)
//{
//	g1(x);
//}
//
//void g1(int)
//{
//
//}
//
//
//int main()
//{
//	f(7);
//	return 0;
//}

// ��ʮһ��-ģ��ʵ������
//template<int N>
//class X {
//public:
//	typedef int I;
//	void f(int) 
//	{
//		cout << "X::f(int) " << endl;
//	}
//};
//
//template<int N>
//void fppm(void (X<N>::* p)(typename X<N>::I)) {
//	// ����� p ��һ��ָ���Ա������ָ��
//	// �����������ʹ�� p ������ X<N>::f
//	X<N> x;
//	(x.*p)(42); // ���ó�Ա����
//};
//
//
//int main()
//{
//	fppm(&X<33>::f);
//}

//class S{};
//
//template<typename T>
//class Wrapper
//{
//private:
//	T object;
//
//public:
//	Wrapper(T obj) :object(obj){}
//
//	friend void f(Wrapper<T> const& a)
//	{
//		cout << "f(Wrapper<T> const& a)" << endl;
//	}
//};
//
//int main()
//{
//	S s;	
//	Wrapper<S> w(s); 
//	f(w);		// f(Wrapper<T> const& a)
//	//f(s);		// ����û��ƥ��ĺ���
//}

// day-2025-5-26
// ��ʮ����-�ػ�������

//template<typename T>
//int f(T)
//{
//	return 1;
//}
//
//template<typename T>
//int f(T*)
//{
//	return 2;
//}
//
//template<typename T>
//std::string f1(T)
//{
//	return "Template";
//}
//
//std::string f1(int&)
//{
//	return "Nontemplate";
//}
//
//int main()
//{
//	std::cout << f<int*>((int*)0) << endl; // 1
//	std::cout << f<int>((int*)0) << endl;  // 2
//	std::cout << f(0) << endl;			   // 1	
//	std::cout << f((int*)0) << endl;	   // 2
//
//	int x = 7;
//	std::cout << f1(x) << endl;			// Nontemplate
//}

//template<typename T>
//class Invalid{};
//
//Invalid<double> x; // ��ʽר�û�����ʵ������Invalid<double>��
//
//template<>
//class Invalid<double>;

//template<typename T>
//int f(T)
//{
//	return 1;
//}
//
//template<typename T>
//int f(T*)
//{
//	return 2;
//}
//template<>
//int f(int)
//{
//	return 3;
//}
//
//template<>
//int f(int*)
//{
//	return 4;
//}
//
//template<typename T>
//int f(T, T x = 42)
//{
//	return x;
//}

//template<>
//int f(int, int = 35) // err f: ����ģ�����ʽר�û���ʵ�����������κ�Ĭ�ϲ���
//{
//	return 0;
//}

//template<typename T>
//int g(T, T x = 42)
//{
//	return x;
//}
//
//template<>
//int g(int, int y)
//{
//	return y / 2;
//}
//
//int main()
//{
//	cout << g(0) << endl; // 21
//}

// day-2025-5-27
// ��ʮ����-δ���ķ���
//typedef vector<list<int>> ListOfIntLists; // ��ǰ�Ǵ���,�����Ų�����д.
//
//template<typename T>
//class Table
//{
//public:
//	typedef vector<list<T>> Type;
//};
//
//int main()
//{
//	Table<int>::Type table; // ��ȷ��ʹ�� typedef ���������
//
//	
//	return 0;
//}

//class Base {
//public:
//	virtual Base* clone() const {
//		return new Base(*this);
//	}
//	virtual ~Base() {}
//};
//
//class Derived : public Base {
//public:
//	// Э�䷵������ - ���� Derived* ����Base*
//	virtual Derived* clone() const override {
//		return new Derived(*this);
//	}
//};

//day-2025-5-28
// ��ʮ����-ģ��Ķ�̬����
// ��ʮ����-trait �� policy
// s1.h
//namespace A
//{
//	int f(double);
//}
//
//// s2.h
//namespace B
//{
//	using A::f;
//	void g();
//}
//// s3.h
//namespace A
//{
//	int f(int);
//}
//// s4.h
//void B::g()
//{
//	f(1);
//}



// day-2025-5-29
// ��ʮ����-trait �� policy��

//#include <iterator>
//template<typename Iter>
//inline typename std::iterator_traits<Iter>::value_type
//accum(Iter st, Iter ed)
//{
//	typedef typename std::iterator_traits<Iter>::value_type VT;
//	VT total = VT();
//	while (st != ed)
//	{
//		total += *st;
//		++st;
//	}
//	return total;
//}

// ��ָͨ��
//namespace std
//{
//	template<typename T>
//	struct iterator_traits<T*> {
//		typedef T									value_type;
//		typedef ptrdiff_t							difference_type;
//		typedef random_access_iterator_tag			iterator_category;
//		typedef T*									pointer;
//		typedef T&									reference;
//	};
//}

//template<typename T>
//class TypeSize
//{
//public:
//	static size_t const value = sizeof(T);
//};
//int main()
//{
//	cout << "TypeSize<int>::value = " << TypeSize<int>::value << endl;
//
//}


//template<typename T>
//class ElementT;	// ����ģ��
//
//template<typename T>
//class ElementT<std::vector<T>> {	//�ֲ��ػ�
//public:
//	typedef T Type;
//};
//
//template<typename T>
//class ElementT<std::list<T>> {     // //�ֲ��ػ�
//public:
//	typedef T Type;
//};
//
//template<typename T>
//class ElementT<std::stack<T>> {     // //�ֲ��ػ�
//public:
//	typedef T Type;
//};
//
//template<typename T>
//void print_element_type(T const& c)
//{
//	cout << "Container of " << typeid(typename ElementT<T>::Type).name() << " elements." << endl;
//}
//
//int main()
//{
//	stack<bool> st;
//	print_element_type(st);
//}

//template<typename C>
//class EelementT
//{
//public:
//	typedef typename C::value_type Type;
//};

//template<typename T>
//class IsClassT {
//private:
//	typedef char One;
//	typedef struct{ char a[2]; } Two;
//
//	template<typename C>
//	static One test(int C::*){}
//	template<typename C>
//	static Two test(...){} // ... ƥ���������
//
//public:
//	enum { Yes = sizeof(test<T>(0)) == sizeof(One) };
//	enum { No = !Yes };
//};
//
//
//class MyClass{};
//struct MyStruct{};
//union MyUnion{};
//void myfunc() {};
//enum E{e1}  e;
//
//template<typename T>
//void check()
//{
//	if (IsClassT<T>::Yes)
//	{
//		cout << "IsClassT" << endl;
//	}
//	else
//	{
//		cout << "!IsClassT" << endl;
//	}
//}
//
//template<typename T>
//void checkT(T)
//{
//	check<T>();
//}
//
//int main()
//{
//	cout << "int: ";
//	check<int>();
//
//	cout << "MyClass: ";
//	check<MyClass>();
//	
//	cout << "MyStruct: ";
//	MyStruct s;
//	checkT(s);
//
//	cout << "MyUnion: ";
//	check<MyUnion>();
//
//	cout << "enum: ";
//	checkT(e);
//
//	cout << "myfunc():";
//	checkT(myfunc);
//}

// ����ģ��, ���ݵ�һ��ʵ��������, ��ѡ��ڶ���ʵ��, ����ѡ�������ʵ��
//template<bool C, typename Ta, typename Tb>
//class IfThenElse;
//
//// �ֲ��ػ�, true�Ļ�ѡ��ڶ���ʵ��
//template<typename Ta, typename Tb>
//class IfThenElse<true, Ta, Tb>
//{
//public:
//	typedef Ta ResultT;
//};

// �ֲ��ػ�, false�Ļ�ѡ�������ʵ��
//template<typename Ta, typename Tb>
//class IfThenElse<false, Ta, Tb>
//{
//public:
//	typedef Tb ResultT;
//};


// ������������Ļ���ģ��
//template<typename T1, typename T2>
//class Promotion {
//public:
//	typedef typename IfThenElse<(sizeof(T1)> sizeof(T2)),
//		T1, typename IfThenElse<(sizeof(T1)< sizeof(T2)),
//		T2,
//		void
//		>::ResultT
//		>::ResultT ResultT;
//};
//
//template<typename T>
//class Promotion<T, T>
//{
//public:
//	typedef T resultT;
//};
//
//#define MK_PROMOTION(T1, T2, Tr) \
//template<> class Promotion<T1, T2>{ \
//	public: \
//	typedef Tr ResultT; \
//};	\
//template<> class Promotion<T2, T1> {\
//public: \
//		typedef Tr ResultT; \
//}; 
//MK_PROMOTION(bool, char, int)
//MK_PROMOTION(bool, unsigned char, int)
//// ...
//class Array{};
//
//template<typename T1, typename T2>
//class Promotion<Array<T1>, Array<T2>>
//{
//public:
//	typedef Array<typename Promotion<T1, T2>::ResultT> ResultT;
//};
//
//template<typename T>
//class Promotion<Array<T>, Array<T>>
//{
//public:
//	typedef Array<typename Promotion<T, T>::ResultT> ResultT;
//};

//template<typename T>
//class RParam
//{
//public:
//	typedef typename IfThenElse<sizeof(T) <= 2 * sizeof(void*)>,
//		T,
//		T const& > ::ResultT Type;
//};

//template<typename T>
//class RParam {
//public:
//	typedef typename IfThenElse<IsClassT<T>::No,
//		T,
//		Tconst&>::ResultT Type;
//};


int main()
{

}