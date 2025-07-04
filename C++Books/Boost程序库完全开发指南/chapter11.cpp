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
#include <boost/random.hpp>

using namespace boost::signals2;
using namespace boost;


// 第十一章-函数与回调.
// day-2025-6-27
//class demo_class
//{
//public:
//	typedef signal<void()> signal_t;
//	shared_ptr<signal_t> sig;
//
//	int x;
//	demo_class()
//		:sig(new signal_t),
//		x(10)
//	{}
//};
//
//void print()
//{
//	std::cout << "hello sig. " << std::endl;
//}
//// 下面的合并器当得到一个大于100的返回值就停止调用插槽:
//class Combiner
//{
//public:
//	typedef bool result_type;
//	template<typename InputIterator>
//	result_type operator() (InputIterator begin, InputIterator end) const
//	{
//		for (; begin != end; ++begin)
//		{
//			return true;
//		}
//		return false;
//	}
//};

//typedef signal_type<int(int), keywords::mutex_type<dummy_mutex>>::type signal_t;
//typedef signal_t::extended_slot_type slot_t;
//signal_t sig;
//
//template<int N>
//struct slots
//{
//	int operator()(const connection& conn, int x)
//	{
//		std::cout << "conn = " << conn.connected() << std::endl;
//		return x * N;
//	}
//};
//
//void f()
//{
//	std::cout << "func called" << std::endl;
//}

//int main()
//{
	//function<void()> func;
	//func = f;
	//func(); // 调用函数
	//std::cout << typeid(func()).name() << std::endl;

	//signal<void()> sig;;

	//sig.connect(&f);
	//sig();	// 触发事件, 产生信号, 调用插槽
	//std::cout << typeid(sig()).name() << std::endl;


	// _1 是 connection 对象, _2 是插槽实际使用的参数
	//sig.connect_extended(slot_t(&slots<10>::operator(), slots<10>(), _1, _2));
	//sig.connect_extended(slot_t(&slots<20>::operator(), slots<20>(), _1, _2));
	//sig(5);																	// 将整数5作为 _2 的实际参数传递给插槽
	
	//demo_class obj;
	//assert(obj.sig.use_count() == 1);
	//demo_class obj2(obj);
	//assert(obj2.sig.use_count() == 2);

	//obj.sig->connect(&print);
	//(*obj2.sig)();

//}

/*
	本节我们将使用signals2开发一个完整的观察者模式示例程序，用来演示信号/插槽的用法.
	这个程序将模拟一个日常生活情景：访客按门铃—门铃响—护士开门—婴儿哭闹.
*/


//class ring
//{
//public:
//	typedef signal<void()> signal_t;
//	typedef signal_t::slot_type slot_t;
//
//	connection connect(const slot_t& s)
//	{
//		return alarm.connect(s);
//	}
//	void press()
//	{
//		std::cout << "Romg Alarm ... " << std::endl;
//		alarm();									 // 调用 signal,发出信号, 引发插槽调用
//	}
//
//
//private:
//	signal_t alarm;									// 信号对象
//};
//
//typedef boost::variate_generator<rand48, uniform_smallint<>> bool_rand;
//bool_rand g_rand(rand48(time(0)), uniform_smallint<>(0, 100));
//
//
//// 护士类
//extern char const nurse1[] = "Mary";
//extern char const nurse2[] = "Kate";
//template<char const * name>
//class nurse
//{
//private:
//	bool_rand& rand; // 随机数发生器
//public:
//	nurse()
//		:rand(g_rand)
//	{}
//	void action()
//	{
//		std::cout << name;
//		if (rand() > 30)
//		{
//			std::cout << " wakeup and open the door!" << std::endl;
//		}
//		else
//		{
//			std::cout << " is Sleeping..." << std::endl;
//		}
//	}
//};
//
// // 宝宝类
//extern char const baby1[] = "Tom";
//extern char const baby2[] = "Jerry";
//
//template<char const* name>
//class baby
//{
//private:
//	bool_rand& rand;
//
//public:
//	baby()
//		:rand(g_rand)
//	{}
//
//	void action()
//	{
//		std::cout << "Baby: " << name;
//		if (rand() > 50)
//		{
//			std::cout << " wake up and crying loudly..." << std::endl;
//		}
//		else
//		{
//			std::cout << " is sleeping sweetly!..." << std::endl;
//		}
//	}
//};
//
//class guest
//{
//public:
//	void press(ring& r)
//	{
//		std::cout << "A guest presses the ring." << std::endl;
//		r.press();
//	}
//};
//
//int main()
//{
//	ring r;
//	nurse<nurse1> n1;
//	nurse<nurse2> n2;
//
//	baby<baby1> b1;
//	baby<baby2> b2;
//	guest g;
//
//	r.connect(bind(&nurse<nurse1>::action, n1));
//	r.connect(bind(&nurse<nurse2>::action, n2));
//	r.connect(bind(&baby<baby1>::action, b1));
//	r.connect(bind(&baby<baby2>::action, b2));
//
//	g.press(r);
//}


// day-2025-6-24
// signals2
// 类 signal 摘要
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
//	插槽的连接管理
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
//	// 调用操作符
//	result_type operator()(...);
//
//	// 合并器
//	combiner_type combiner() const;
//	void set_combiner(const combiner_type&);
//};

//void slot1()
//{
//	std::cout << "slot1 called" << std::endl;
//}
//void slot2()
//{
//	std::cout << "slot2 called" << std::endl;
//}
//template<int N>
//struct slots
//{
//	int operator()(int x)
//	{
//		std::cout << "slot" << N << "called" << std::endl;
//		return x * N;
//	}
//};
//
//template<typename T>
//class Combiner
//{
//	T v;
//public:
//	typedef std::pair<T, T> result_type;
//	Combiner(T t = T())
//		:v(t)
//	{}
//
//	template<typename InputIterator>
//	result_type operator()(InputIterator begin, InputIterator end) const
//	{
//		if (begin == end)
//		{
//			return result_type();
//		}
//		std::vector<T> vec(begin, end);
//		T sum = std::accumulate(vec.begin(), vec.end(), v);
//		T max = *std::max_element(vec.begin(), vec.end());
//
//		return result_type(sum, max);
//	}
//};
//using namespace boost::signals2;
//
//template<int N>
//bool operator==(const slots<N>&, const slots<N>&)
//{
//	return true;
//}

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

// slot类摘要如下:
//template<typename Signature,
//	typename SlotFunction = boost::function<R(T1, ..., TN)>>
//	class slot : public boost::signals2::slot_base
//{
//public:
//	template<typename Slot> slot(const Slot&);
//	template<typename Func, typename Arg...>
//	slot(const Func&, const Arg& ...);
//
//	result_type operator()(...);
//	// 跟踪功能
//	slot& track(const boost::weak_ptr<void>&);
//};



//int main()
//{
	//typedef signal<int(int)> signal_t;
	//typedef signal_t::slot_type slot_t;
	//signal_t sig;
	//
	//// 声明两个 shared_ptr
	//auto p1 = boost::make_shared<slots<10>>();
	//auto p2 = boost::make_shared<slots<20>>();

	//function<int(int)> func = ref(*p1); // function 存储引用
	//sig.connect(slot_t(func).track(p1));
	////使用 bind 语法, 直接绑定
	//sig.connect(slot_t(&slots<20>::operator(), p2.get(), _1).track(p2));
	//p1.reset();
	//p2.reset();

	//assert(sig.num_slots() == 0);
	//sig(1);

	//typedef signal<int(int)> signal_t;
	//signal_t sig;

	//sig.connect(slots<10>());
	//auto p = boost::make_shared<slots<20>>();

	//sig.connect(signal_t::slot_type(ref(*p)).track(p));
	//p.reset();
	//assert(sig.num_slots() == 1);

	//sig(1);

	//signal<int(int)> sig;
	//sig.connect(slots<10>());

	//auto p = new slots<20>;
	//sig.connect(ref(*p));

	//delete p;
	//sig(1);

	//signal<int(int)> sig;
	//connection c1 =  sig.connect(0, slots<10>());
	//connection c2 = sig.connect(0, slots<20>());
	//assert(sig.num_slots() == 2);
	//sig(2);							// 调用两个插槽

	//std::cout << "begin blocking ..." << std::endl;
	//{
	//	shared_connection_block block(c1);
	//	assert(sig.num_slots() == 2);
	//	assert(c1.blocked()); 
	//	sig(2);
	//}

	//std::cout << "end blocking ..." << std::endl;

	//assert(!c1.blocked());
	//sig(2);

	//signal<int(int)> sig;
	//sig.connect(0, slots<10>());
	//assert(sig.num_slots() == 1);
	//{
	//	scoped_connection sc = sig.connect(0, slots<20>());
	//	assert(sig.num_slots() == 2);
	//}
	//assert(sig.num_slots() == 1);

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



	//boost::signals2::signal<int(int), Combiner<int>> sig;// 相当于 boost::signals2::signal<int(int), Combiner<int>> sig(Combiner<int>());
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

	//boost::signals2::signal<void()> sig; // 指定插槽类型 void() 其他模板参数使用默认值
	//// 然后我们就可以使用 connect()来连接插槽, 最后用 operator()来产生信号
	//sig.connect(&slot1);
	//sig.connect(slots<100>(), boost::signals2::at_front);

	//sig.connect(5, slots<51>(), boost::signals2::at_back);
	//sig.connect(5, slots<55>(), boost::signals2::at_front);

	//sig.connect(3, slots<30>(), boost::signals2::at_front);
	//sig.connect(3, slots<33>(), boost::signals2::at_back);

	//sig.connect(10, slots<10>());
	//sig();
//}


// function
/*
	function是一个函数对象的"容器"，在概念上它像是C++中 `函数指针` 类型的泛化，是一种"智能函数指针".

*/

// function类摘要
//template<typename Signature>
//class Function : public boost::function_n<R, T1, T2, ..., TN>
//{
//public:
//	typedef R result_type;
//	typedef TN argN_type;
//
//	static const int arity = N;				//参数个数常量
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
//	typedef function<void(int)> func_t; // function类型定义
//	func_t func;
//	int n;
//public:
//	demo_class(int i)
//		:n(i)
//	{}
//	// 接收回调函数
//	template<typename Cb>
//	void accept(Cb f)
//	{
//		func = f;
//	}
//	// 调用回调函数
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
	//dc.accept(call_back_func); // 接收回调函数
	//dc.run();				   // 执行回调函数

	//std::vector<int> v = { 1,3,5,7,9 };
	//summary<int> s;
	//function<void(int const&)> func(ref(s)); // function 包装引用

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
	bind 是对 C++ 标准中函数适配器 bind1st/bind2nd 的泛化和增强，可以适配任意的可调用对象.
	包括函数指针、函数引用、成员函数指针、函数对象 和 lambda 表达式. 
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

	bind的另一个对类的操作是它可以绑定 public 成员变量，它就像是一个选择器，其用法与绑定成员函数类似,
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