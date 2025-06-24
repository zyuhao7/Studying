#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <numeric>
#include <string>
#include <set>
#include <boost/ref.hpp>
#include <boost/rational.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/signals2.hpp>

using namespace boost;

// ��ʮһ��-������ص�.
// day-2025-6-24
// signals2
// �� signal ժҪ
//template<typename Signature,
//	typename Combiner = boost::signals2::optional_last_value<R>,
//	typename Group = int,
//	typename GroupCompare = std::less<Group>>
//	class Signal : public boost::signals2::signal_base
//{
//	Signal(const combiner_type & = combiner_type(),
//		const group_compare_type & = group_compare_type());
//	~Signal();
//
//	��۵����ӹ���
//	connection connect(const slot_type&, connect_position = at_back);
//	connection connect(const group_type&, const slot_type&, connect_position = at_back);
//
//	void disconnect(const group_type&);
//	template<typename S>
//	void disConnect(const S&);
//	void  disconnect_all_slots();
//	bool empty() const;
//	std::size_t num_slots() const;
//
//	// ���ò�����
//	result_type operator()(...);
//
//	// �ϲ���
//	combiner_type combiner() const;
//	void set_combiner(const combiner_type&);
//};

void slot1()
{
	std::cout << "slot1 called" << std::endl;
}
void slot2()
{
	std::cout << "slot2 called" << std::endl;
}
template<int N>
struct slots
{
	int operator()(int x)
	{
		std::cout << "slot" << N << "called" << std::endl;
		return x * N;
	}
};

template<typename T>
class Combiner
{
	T v;
public:
	typedef std::pair<T, T> result_type;
	Combiner(T t = T())
		:v(t)
	{}

	template<typename InputIterator>
	result_type operator()(InputIterator begin, InputIterator end) const
	{
		if (begin == end)
		{
			return result_type();
		}
		std::vector<T> vec(begin, end);
		T sum = std::accumulate(vec.begin(), vec.end(), v);
		T max = *std::max_element(vec.begin(), vec.end());

		return result_type(sum, max);
	}
};
using namespace boost::signals2;

template<int N>
bool operator==(const slots<N>&, const slots<N>&)
{
	return true;
}

//class Connection {
//public:
//	Connection();
//	Connection(const Connection&);
//	Connection& operator=(const Connection&);
//
//	void disconnect() const;
//	bool connected() const;
//
//	bool blocked() const;
//	void swap(const Connection&);
//
//	bool operator==(const Connection&) const;
//	bool operator != (const Connection&) const;
//	bool operator <(const Connection&) const;
//};

int main()
{

	//signal<int(int)> sig;
	//assert(sig.empty());
	//sig.connect(0, slots<10>());
	//sig.connect(0, slots<20>());
	//sig.connect(1, slots<30>());
	//assert(sig.num_slots() == 3);
	//sig.disconnect(0);

	//assert(sig.num_slots() == 1);
	//sig.disconnect(slots<30>());
	//assert(sig.empty());



	//boost::signals2::signal<int(int), Combiner<int>> sig;// �൱�� boost::signals2::signal<int(int), Combiner<int>> sig(Combiner<int>());
	//sig.connect(slots<10>());
	//sig.connect(slots<20>());
	//sig.connect(slots<30>(), boost::signals2::at_front);

	//auto x = sig(2);
	//std::cout << x.first << ", " << x.second << std::endl;



	//boost::signals2::signal<int(int)> sig;
	//sig.connect(slots<10>());
	//sig.connect(slots<20>());
	//sig.connect(slots<50>());

	//std::cout << *sig(2) << std::endl;

	//boost::signals2::signal<void()> sig; // ָ��������� void() ����ģ�����ʹ��Ĭ��ֵ
	//// Ȼ�����ǾͿ���ʹ�� connect()�����Ӳ��, ����� operator()�������ź�
	//sig.connect(&slot1);
	//sig.connect(slots<100>(), boost::signals2::at_front);

	//sig.connect(5, slots<51>(), boost::signals2::at_back);
	//sig.connect(5, slots<55>(), boost::signals2::at_front);

	//sig.connect(3, slots<30>(), boost::signals2::at_front);
	//sig.connect(3, slots<33>(), boost::signals2::at_back);

	//sig.connect(10, slots<10>());
	//sig();
}


// function
/*
	function��һ�����������"����"���ڸ�����������C++�� `����ָ��` ���͵ķ�������һ��"���ܺ���ָ��".

*/

// function��ժҪ
//template<typename Signature>
//class Function : public boost::function_n<R, T1, T2, ..., TN>
//{
//public:
//	typedef R result_type;
//	typedef TN argN_type;
//
//	static const int arity = N;				//������������
//
//	Function();
//	template<typename F> Function(F);
//
//	void swap(const Function&);
//	void clear();
//	void empty() const;
//
//	bool safe_bool() const;
//	bool operator!() const;
//	
//	template<typename Functor> Functor* target();
//	template<typename Functor> bool contains(const Functor&) const;
//	const std::type_info& target_type() const;
//
//	result_type operator()(arg1_type, ...) const;
//};

//int f(int a, int b) { return a + b; }
//struct demo_class
//{
//	int add(int a, int b)
//	{
//		return a + b;
//	}
//	int operator()(int x) const
//	{
//		return x * x;
//	}
//};
//
//template<typename T>
//struct summary
//{
//	typedef void result_type;
//	T sum;
//
//	summary(T v = T())
//		:sum(v)
//	{}
//
//	void operator()(T const& x)
//	{
//		sum += x;
//	}
//};

//class demo_class
//{
//private:
//	typedef function<void(int)> func_t; // function���Ͷ���
//	func_t func;
//	int n;
//public:
//	demo_class(int i)
//		:n(i)
//	{}
//	// ���ջص�����
//	template<typename Cb>
//	void accept(Cb f)
//	{
//		func = f;
//	}
//	// ���ûص�����
//	void run()
//	{
//		func(n);
//	}
//};

//void call_back_func(int i)
//{
//	std::cout << "call_back_func:";
//	std::cout << i * 2 << std::endl;
//}
//
//class call_back_obj
//{
//private:
//	int x;
//public:
//	call_back_obj(int i)
//		:x(i)
//	{}
//	void operator()(int i)
//	{
//		std::cout << "call_back_obj: ";
//		std::cout << i * x++ << std::endl;
//	}
//};

//class call_back_factory
//{
//public:
//	void call_back_func1(int i)
//	{
//		std::cout << "call_back_factory1: ";
//		std::cout << i * 2 << std::endl;
//	}
//	void call_back_func2(int i, int j)
//	{
//		std::cout << "call_back_factory2: ";
//		std::cout << i * j * 2 << std::endl;
//	}
//};


//int main()
//{
//	demo_class dc(10);
//	call_back_factory cbf;
//
//	dc.accept(boost::bind(&call_back_factory::call_back_func1, cbf, _1));
//	dc.run();
//
//	dc.accept(boost::bind(&call_back_factory::call_back_func2, cbf, _1, 5));
//	dc.run();

	//demo_class dc(10);
	//call_back_obj cbo(2);
	//dc.accept(ref(cbo));
	//dc.run();
	//dc.run();

	//demo_class dc(10);
	//dc.accept(call_back_func); // ���ջص�����
	//dc.run();				   // ִ�лص�����

	//std::vector<int> v = { 1,3,5,7,9 };
	//summary<int> s;
	//function<void(int const&)> func(ref(s)); // function ��װ����

	//std::for_each(v.begin(), v.end(), func);
	//std::cout << s.sum << std::endl;

	//function<int(demo_class&, int, int)> func1;
	//func1 = boost::bind(&demo_class::add, _1, _2, _3);

	//demo_class sc;
	//std::cout << func1(sc, 10, 20) << std::endl;

	//function<int(int, int)> func2;
	//func2 = boost::bind(&demo_class::add, &sc, _1, _2);
	//std::cout << func2(10, 20) << std::endl;

	//demo_class sc1;
	//function<int(int)> func3;
	//func3 = boost::cref(sc1);
	//std::cout << func3(10) << std::endl;

	//boost::function<decltype(f)> func;
	//assert(!func);

	//func = f;
	//assert(func.contains(&f));
	//
	//if(func)
	//	std::cout << func(1, 2);
	//func = 0;
	//assert(func.empty());
//	return 0;
//}


// day-2025-6-23


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