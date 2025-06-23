#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <string>
#include <set>
#include <boost/ref.hpp>
#include <boost/rational.hpp>
#include <boost/bind.hpp>
using namespace std;


// 第十一章-函数与回调.
// day-2025-6-23

// signals2
// function

// bind
/*
	bind 是对 C++ 标准中函数适配器 bind1st/bind2nd 的泛化和增强，可以适配任意的可调用对象.
	包括函数指针、函数引用、成员函数指针、函数对象和lambda表达式. 
*/

// bind 的基本形式		 参数的数量必须与 f 的参数数量相等，这些参数将被传递给f作为入参
//template<class R, class F> bind(F f);
//template<class R, class F, class A1> bind(F f, A1 a1);

// 绑定完成后, bind会返回一个函数对象, 它内部保存了f的拷贝, 具有operator() 返回值类型被自动推导为f的返回值类型
/*
	例如，如果有一个函数func，它的形式如下:
	func(a1,a2)
	那么，它等价于一个具有无参operator() 的bind函数对象调用:
	bind(func,a1,a2)()
	这是bind最简单的形式. bind表达式存储了func和a1、a2的拷贝, 产生了一个临时函数对象.

	占位符的名字表示它在调用式中的顺序，而绑定表达式对顺序没有要求，_1 不一定要第一个出现，也不一定只出现一次:
	bind(func,_2,_1) (a1,a2)

	上述代码返回一个具有两个参数的函数对象，第一个参数将放在函数func的第二个位置，而第二个参数则放在第一个位置，
	调用时上述代码等价于:
	func(a2,a1)
*/

//namesapce
//{
//	boost::arg<1> _1;
//	boost::arg<2> _2;
//	boost::arg<3> _3;
//	...				 // 其余六个占位符定义
//}

//int f(int a, int b)
//{
//	return a + b;
//}
//
//int g(int a, int b, int c)
//{
//	return a + b * c;
//}
//
//typedef decltype(&f) f_type;	// 函数指针定义
//typedef decltype(&g) g_type;	// 函数指针定义

// 操作成员函数
/*
	类的成员函数不同于普通函数,因为成员函数指针不能直接调用operator(), 它必须先被绑定到一个对象或指针上.
	然后才能得到 this 指针进而调用成员函数。因此bind需要“牺牲”一个占位符的位置.
	要求用户提供一个类的实例、引用或指针，通过对象作为第一个参数来调用成员函数:
	bind(&X::func,x,_1,_2,...)

	bind 能够绑定成员函数，这是个非常有用的功能，它可以替代标准库中令人迷惑的 mem_fun 和 mem_fun_ref 绑定器.
	用来配合标准算法操作容器中的对象.

	bind同样支持绑定虚拟成员函数，其用法与非虚拟函数相同，虚函数的行为将由实际调用发生时的实例来决定.

	bind的另一个对类的操作是它可以绑定public成员变量，它就像是一个选择器，其用法与绑定成员函数类似,
	只需要像使用一个成员函数一样去使用成员变量名.

	使用bind，可以实现 SGISTL/STLport 中的非标准函数适配器 select1st 和select2nd的功能,
	直接选择出pair对象的first和second成员.

*/


//struct demo
//{
//	int f(int a, int b)
//	{
//		return a + b;
//	}
//};
//
//struct Point
//{
//	int x, y;
//	Point(int a = 0, int b = 0)
//		:x(a),
//		y(b)
//	{}
//	void print()
//	{
//		cout << "(" << x << "," << y << ")\n";
//	}
//};
//
//struct func
//{
//	int operator()(int a, int b)
//	{
//		return a + b;
//	}
//};
/*
	C++标准使用可变参数模板和完美转发简化了bind 的定义（C++11.20.8.9）,可以支持绑定任意数量的参数:
	template<class R, class F, class... BoundArgs>
	unspecified bind(F&&, BoundArgs&& ...);
	namespace std::placeholders{
	extern unspecified _1;
	extern unspecified _2;
	...
	}

	为占位符更名
	boost::arg<1> &_x = _1;
	boost::arg<2> &_y = _2;
	boost::arg<1> &_arg1 = _1;
	boost::arg<2> &_arg2 = _2;

	auto&		  _x = _1;
	decltype(_2)& _y = _2;

	嵌套绑定
	如果我们有f（x）和g（x）两个函数，那么f（g（x））的bind表达式如下:
	bind(f,bind(g,_1))(x)
*/


//typedef boost::rational<int> ri;
//int main()
//{
	//vector<ri> v = { ri(1,2), ri(3,4), ri(5,6) };
	//// 删除所有分子为1的有理数
	//remove_if(v.begin(), v.end(), bind(&ri::numerator, _1) == 1);
	//assert(v[0].numerator() == 3); // 有理数 1/2被删除

	//// 使用 find_if 算法查找分子是 1 的有理数,不存在
	//assert(find_if(v.begin(), v.end(), boost::bind(&ri::numerator, _1) == 1) == v.end());

	//// 查找 分子大于 3 且 分母小于 8 的有理数
	//auto pos = find_if(v.begin(), v.end(),
	//	boost::bind(&ri::numerator, _1) > 3 && boost::bind(&ri::denominator, _1) < 8);

	//auto pos2 = find_if(v.begin(), v.end(), [](ri& r)
	//	{
	//		return r.numerator() > 3 && r.denominator() < 8;
	//	});

	//boost::bind<int>(printf, " %d + %d = %d\n", _1, 1, _2)(6, 7);

	//int x = 10;
	//auto r = boost::ref(x);
	//{
	//	int* y = new int(20);
	//	r = boost::ref(*y);

	//	cout << r << endl;
	//	cout << boost::bind(g, r, 1, 1)() << endl;
	//	delete y;
	//}

	//cout << boost::bind(g, r, 1, 1)() << endl; // -56125354 未定义行为.

	//int x = 10;
	//cout << boost::bind(g, _1, boost::cref(x), boost::ref(x))(10) << endl;
	//// 一个函数对象
	//func af;
	//cout << boost::bind<int>(boost::ref(af), _1, _2)(10, 20) << endl;

	//auto x = boost::bind(greater<int>(), _1, _2);
	//cout << x(10, 20) << endl;

	//auto lf = [](int x) {
	//	return f(x, 9);
	//};
	//assert(lf(10) == bind(f, _1, 9)(10));

	//cout << std::bind(f, std::placeholders::_1, 20)(10) << endl;
	//cout << boost::bind<int>(func(), _1, _2)(10, 20) << endl;

	//typedef pair<int, string>

	//vector<Point> v(10);
	//vector<int> v2(10);
	//transform(v.begin(), v.end(), v2.begin(), boost::bind(&Point::x, _1));
	//
	//for (auto x : v2) cout << x << " ";

	//demo a, & ra = a;
	//demo* p = &a;
	//cout << boost::bind(&demo::f, a, _1, 20)(20) << endl;
	//cout << boost::bind(&demo::f, ra, _2, _1)(10, 20) << endl;
	//cout << boost::bind(&demo::f, p, _1, _2)(10, 20) << endl;

	//f_type pf = f;
	//g_type pg = g;
	//int x = 1, y = 2, z = 3;
	//cout << boost::bind(pf, _1, 9)(x) << endl;	//(*pf)(x, 9)
	//cout << boost::bind(pg, _3, _2, _2)(x, y, z) << endl;	//(*pg)(3, 2, 2)


	//cout << boost::bind(f, 1, 2)() << endl;   // 相当于 f(1,2)
	//cout << boost::bind(g, 1, 2, 3)() << endl;// 相当于 g(1,2,3)

	//int x = 10, y = 8, z = 7;
	//cout << boost::bind(f, _1, 9)(x) << endl;		    // 相当于 bind2nd(f,9)
	//cout << boost::bind(f, _1, _2)(x, y) << endl;
	//cout << boost::bind(f, _2, _1)(x, y) << endl;	
	//cout << boost::bind(f, _1, _1)(x, y) << endl;	   // y参数被忽略

	//cout << boost::bind(g, _1, 8, _2)(x, y) << endl;
	//cout << boost::bind(g, _3, _2, _2)(x, y, z) << endl; // x参数被忽略
//}

// ref
//struct square
//{
//	typedef void result_type;
//	void operator()(int& x)
//	{
//		x = x * x;
//	}
//};
//
//template<typename T>
//class Reference_wrapper
//{
//public:
//	explicit Reference_wrapper(T& t)
//		:t_(&t)
//	{}
//	operator T& () const { return *t_; } // 隐式转换
//	T& get() const { return *t_; }			
//	T* get_pointer() const { return t_; }
//
//	Reference_wrapper<T>
//		ref(T& t);
//	Reference_wrapper<T const>
//		cref(T const& t);
//
//
//private:
//	T* t_;
//};
// is_reference_wrapper<T>::value 可以判断T是否被包装
// unwrap_reference<T>::type 表明了 T 的真实类型（无论它是否经过包装）

//class Big_class
//{
//private:
//	int x;
//public:
//	Big_class()
//		:x(0)
//	{}
//	void print()
//	{
//		cout << "big_class!" << ++x << endl;
//	}
//};
//
//template<typename T>
//void print(T a)
//{
//	for (int i = 0; i < 2; ++i)
//		boost::unwrap_ref(a).print();
//}

//int main()
//{
	//Big_class c;
	//auto rw = boost::ref(c);
	//c.print();

	//print(c);
	//print(rw);
	//print(c);
	//c.print();

	//set<int> s;
	//auto rw = boost::ref(s);
	//boost::unwrap_ref(rw).insert(12); // 直接解开包装
	//
	//string str("test");
	//auto rws = boost::cref(str);
	//cout << boost::unwrap_ref(rws) << endl;

	//cout << boost::unwrap_ref(str) << endl;

	//vector<int> v(10, 2);
	//auto rw = boost::cref(v);
	//assert(boost::is_reference_wrapper<decltype(rw)>::value);
	//assert(!boost::is_reference_wrapper<decltype(v)>::value);

	//string str;
	//auto rws = boost::ref(str);
	//cout << typeid(boost::unwrap_reference<decltype(rws)>::type).name() << endl;
	//cout << typeid(boost::unwrap_reference<decltype(str)>::type).name() << endl;

	//double x = 2.0;
	//cout << sqrt(ref(x)) << endl;

	//double x = 2.71828;
	//auto rw = cref(x);
	//cout << typeid(rw).name() << endl;

	//string str;
	//auto rws = boost::ref(str);			// 避免 ADL
	//cout << typeid(rws).name() << endl;

	//int x = 10;
	//reference_wrapper<int> rw(x); // 包装 int类型的引用
	//assert(x == rw);			  // 隐式转换为 int 类型
	//(int&)rw = 100;               // 显示转换为 int&
	//assert(x == 100);

	//reference_wrapper<int> rw2(rw);
	//assert(rw2.get() == 100);

	//string str;
	//Reference_wrapper<string> rws(str);
	//*rws.get_pointer() = "test reference_wrapper";
	//cout << rws.get().size() << endl;
		
	//vector<int> v = { 1,2,3,4,5 };
	//for_each(v.begin(), v.end(), square());
	//for (auto e : v) cout << e << " ";
//}