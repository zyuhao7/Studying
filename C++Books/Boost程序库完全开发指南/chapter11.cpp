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


// ��ʮһ��-������ص�.
// day-2025-6-23

// signals2
// function

// bind
/*
	bind �Ƕ� C++ ��׼�к��������� bind1st/bind2nd �ķ�������ǿ��������������Ŀɵ��ö���.
	��������ָ�롢�������á���Ա����ָ�롢���������lambda���ʽ. 
*/

// bind �Ļ�����ʽ		 ���������������� f �Ĳ���������ȣ���Щ�����������ݸ�f��Ϊ���
//template<class R, class F> bind(F f);
//template<class R, class F, class A1> bind(F f, A1 a1);

// ����ɺ�, bind�᷵��һ����������, ���ڲ�������f�Ŀ���, ����operator() ����ֵ���ͱ��Զ��Ƶ�Ϊf�ķ���ֵ����
/*
	���磬�����һ������func��������ʽ����:
	func(a1,a2)
	��ô�����ȼ���һ�������޲�operator() ��bind�����������:
	bind(func,a1,a2)()
	����bind��򵥵���ʽ. bind���ʽ�洢��func��a1��a2�Ŀ���, ������һ����ʱ��������.

	ռλ�������ֱ�ʾ���ڵ���ʽ�е�˳�򣬶��󶨱��ʽ��˳��û��Ҫ��_1 ��һ��Ҫ��һ�����֣�Ҳ��һ��ֻ����һ��:
	bind(func,_2,_1) (a1,a2)

	�������뷵��һ���������������ĺ������󣬵�һ�����������ں���func�ĵڶ���λ�ã����ڶ�����������ڵ�һ��λ�ã�
	����ʱ��������ȼ���:
	func(a2,a1)
*/

//namesapce
//{
//	boost::arg<1> _1;
//	boost::arg<2> _2;
//	boost::arg<3> _3;
//	...				 // ��������ռλ������
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
//typedef decltype(&f) f_type;	// ����ָ�붨��
//typedef decltype(&g) g_type;	// ����ָ�붨��

// ������Ա����
/*
	��ĳ�Ա������ͬ����ͨ����,��Ϊ��Ա����ָ�벻��ֱ�ӵ���operator(), �������ȱ��󶨵�һ�������ָ����.
	Ȼ����ܵõ� this ָ��������ó�Ա���������bind��Ҫ��������һ��ռλ����λ��.
	Ҫ���û��ṩһ�����ʵ�������û�ָ�룬ͨ��������Ϊ��һ�����������ó�Ա����:
	bind(&X::func,x,_1,_2,...)

	bind �ܹ��󶨳�Ա���������Ǹ��ǳ����õĹ��ܣ������������׼���������Ի�� mem_fun �� mem_fun_ref ����.
	������ϱ�׼�㷨���������еĶ���.

	bindͬ��֧�ְ������Ա���������÷�������⺯����ͬ���麯������Ϊ����ʵ�ʵ��÷���ʱ��ʵ��������.

	bind����һ������Ĳ����������԰�public��Ա��������������һ��ѡ���������÷���󶨳�Ա��������,
	ֻ��Ҫ��ʹ��һ����Ա����һ��ȥʹ�ó�Ա������.

	ʹ��bind������ʵ�� SGISTL/STLport �еķǱ�׼���������� select1st ��select2nd�Ĺ���,
	ֱ��ѡ���pair�����first��second��Ա.

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
	C++��׼ʹ�ÿɱ����ģ�������ת������bind �Ķ��壨C++11.20.8.9��,����֧�ְ����������Ĳ���:
	template<class R, class F, class... BoundArgs>
	unspecified bind(F&&, BoundArgs&& ...);
	namespace std::placeholders{
	extern unspecified _1;
	extern unspecified _2;
	...
	}

	Ϊռλ������
	boost::arg<1> &_x = _1;
	boost::arg<2> &_y = _2;
	boost::arg<1> &_arg1 = _1;
	boost::arg<2> &_arg2 = _2;

	auto&		  _x = _1;
	decltype(_2)& _y = _2;

	Ƕ�װ�
	���������f��x����g��x��������������ôf��g��x������bind���ʽ����:
	bind(f,bind(g,_1))(x)
*/


//typedef boost::rational<int> ri;
//int main()
//{
	//vector<ri> v = { ri(1,2), ri(3,4), ri(5,6) };
	//// ɾ�����з���Ϊ1��������
	//remove_if(v.begin(), v.end(), bind(&ri::numerator, _1) == 1);
	//assert(v[0].numerator() == 3); // ������ 1/2��ɾ��

	//// ʹ�� find_if �㷨���ҷ����� 1 ��������,������
	//assert(find_if(v.begin(), v.end(), boost::bind(&ri::numerator, _1) == 1) == v.end());

	//// ���� ���Ӵ��� 3 �� ��ĸС�� 8 ��������
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

	//cout << boost::bind(g, r, 1, 1)() << endl; // -56125354 δ������Ϊ.

	//int x = 10;
	//cout << boost::bind(g, _1, boost::cref(x), boost::ref(x))(10) << endl;
	//// һ����������
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


	//cout << boost::bind(f, 1, 2)() << endl;   // �൱�� f(1,2)
	//cout << boost::bind(g, 1, 2, 3)() << endl;// �൱�� g(1,2,3)

	//int x = 10, y = 8, z = 7;
	//cout << boost::bind(f, _1, 9)(x) << endl;		    // �൱�� bind2nd(f,9)
	//cout << boost::bind(f, _1, _2)(x, y) << endl;
	//cout << boost::bind(f, _2, _1)(x, y) << endl;	
	//cout << boost::bind(f, _1, _1)(x, y) << endl;	   // y����������

	//cout << boost::bind(g, _1, 8, _2)(x, y) << endl;
	//cout << boost::bind(g, _3, _2, _2)(x, y, z) << endl; // x����������
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
//	operator T& () const { return *t_; } // ��ʽת��
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
// is_reference_wrapper<T>::value �����ж�T�Ƿ񱻰�װ
// unwrap_reference<T>::type ������ T ����ʵ���ͣ��������Ƿ񾭹���װ��

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
	//boost::unwrap_ref(rw).insert(12); // ֱ�ӽ⿪��װ
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
	//auto rws = boost::ref(str);			// ���� ADL
	//cout << typeid(rws).name() << endl;

	//int x = 10;
	//reference_wrapper<int> rw(x); // ��װ int���͵�����
	//assert(x == rw);			  // ��ʽת��Ϊ int ����
	//(int&)rw = 100;               // ��ʾת��Ϊ int&
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