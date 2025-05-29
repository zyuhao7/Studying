#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <tuple>
#include <array>
#include <map>
#include <set>
#include <variant>
#include <type_traits>
#include <filesystem>
#include <optional>
#include <string>
#include <any>
#include <functional>
#include <execution>
#include <memory>
#include <thread>
#include <mutex>
using namespace std;
namespace fs = std::filesystem;

// day-2025-5-25
// 折叠表达式
//template<typename... Args>
//constexpr int Sum(Args... args)
//{
//	return (args + ...);
//}
//
//// 想指定一个初始值.
//template<typename... Args>
//auto Func(Args... args)
//{
//	return (args + ... + 100);
//}
//
//// 在 C++17 之前，要实现类似的函数，您必须显式指定递归规则：
//// C++ 14
//auto sum()
//{
//	return 0;
//}
//template<typename Arg, typename... Args>
//auto sum(Arg first, Args... rest)
//{
//	return first + sum(rest...);
//}
//
//template<typename T, typename... Args>
//void PushToVector (std::vector<T>& v, Args&&... args)
//{
//	(v.push_back(std::forward<Args>(args)), ...);
//}
//
//int main()
//{
//	cout << Sum(1, 2, 3, 4, 5) << endl;
//	cout << sum(1, 2, 3, 4, 5) << endl;
//	cout << Func(1, 2, 3, 4, 5) << endl;
//
//	vector<int> lst = { 1, 3, 5, 7 };
//	PushToVector(lst, 2, 4, 6, 8);
//	int res = std::accumulate(lst.begin(), lst.end(), 0, [](int a, int b) {return a + b;});
//	cout << res;
//
//	return 0;
//}

//	模板<auto>

//template<auto n>
//void Func(){
//	cout << "n is : " << n << endl;
//}
//
//// C++ 14
//template<typename Type, Type n>
//void Func2()
//{
//	cout << "n is :" << n << endl;
//}
//
//int main()
//{
//	Func<42>();
//	Func<'c'>();
//
//	Func2<int, 42>();
//	Func2<char, 'c'>();
//}

// 类模板参数推导
// C++ 14
//template<typename T, typename U>
//struct S
//{
//	T first;
//	U second;
//	S(T f, U s)
//	:first(f),
//	second(s)
//	{}
//};
//
//// C++17
//template<typename T, typename U>
//struct S1
//{
//	T first;
//	U second;
//};
//
//template<typename T, typename U>
//S1(const T& f, const U& s) -> S1<T, U>;
//
//int main()
//{
//	// 在 C++17 之前，模板参数推导仅适用于函数，因此，在构造模板类时，始终需要显式指定模板参数: C++14
//	auto p = std::pair<int, char>(10, 'c');
//	auto pr = std::make_pair(10, 'c');
//	pair<char, int> p1 = { 'c', 14 };
//	tuple<char, int, double> t1 = { 'c', 42, 3.14 };
//	S<int, char> s1 = { 10, 'c' };
//
//	//C++ 17
//	pair p2 = { 'c', 42 };
//	tuple t2 = { 'c', 42, 3.14 };
//	S s2 = { 10,'c' };
//
//	S1 s3 = { 42, "hello" };
//	cout << s3.first << " " << s3.second << endl;
//
//	return 0;
//}

// constexpr 表达式
// C++17 使我们能够执行编译时条件分支。这是一个非常强大的工具，在元编程中特别有用。
//template<typename T>
//auto GetValue(T t)
//{
//	if constexpr (std::is_pointer<T>::value)
//		return *t;
//	else
//		return t;
//}

// 在 C++17 之前，我们必须使用 SFINAE 和 enable_if
//template<typename T>
//typename std::enable_if<std::is_pointer<T>::value,
//	std::remove_pointer_t<T>>::type
//	GetValue(T t)
//{
//	return *t;
//}
//
//template<typename T>
//typename std::enable_if<!std::is_pointer<T>::value, T>::type
//GetValue(T t)
//{
//	return t;
//}
//
//int main()
//{
//	int v = 10;
//	cout << GetValue(v) << endl;
//	cout << GetValue(&v) << endl;
//
//}

// constexpr lambda
//constexpr int Func(int x)
//{
//	auto f = [x]() {return x * x;};
//	return x + f();
//}
//
//int main()
//{
//	constexpr int v = Func(10);
//	static_assert(v == 110);
//
//	constexpr auto squared = [](int x) {return x * x;};
//	constexpr int s = squared(5);
//	static_assert(s == 25);
//	return 0;
//}

// *Lambda 表达式中的此捕获
//class SomeClass
//{
//public:
//	int m_x = 0;
//	void f() const
//	{
//		cout << m_x << endl;
//	}
//	void g()
//	{
//		m_x++;
//	}
//	// c++14
//	void Func()
//	{
//		auto lambda1 = [self = *this]() {self.f();};
//		auto lambda2 = [self = *this]() mutable {self.g();};
//		lambda1();
//		lambda2();
//	}
//
//	// C++17
//	void FuncNew()
//	{
//		auto lambda1 = [*this]() {f();};
//		auto lambda2 = [*this]()mutable {g();};
//		lambda1();
//		lambda2();
//	}
//};
//
//int main()
//{
//	SomeClass sc;
//	sc.Func();
//	sc.FuncNew();
//}

// 内联变量
// header.h
//#ifndef _HEADER_H
//#define _HEADER_H
//inline int MyVar = 42;
//#endif 

// source1.h
// #include "header.h"
//MyVar += 10;

// source2.h
// #include "header.h"
//Func(MyVar);

//在 C++17 之前, 程序员必须将 MyVar变量声明为 extern, 并在其中一个 .cpp 为其赋值。

// 结构化绑定

//struct S
//{
//	char x{ 'C' };
//	int y{ 42 };
//	double z{ 3.14 };
//};
//
//int main()
//{
	// C++17
	//set<int> mySet;
	//auto [iter, ok] = mySet.insert(42);

	//S s;
	//auto [a, b, c] = s;
	//cout << a << " " << b << " " << c << endl;	

	//int arr[] = { 1,2,3,4 };
	//auto [a, b, c, d] = arr;
	//cout << a << b << c << d << endl;

	//map<int, int> map;
	//map[1] = 1;
	//map[2] = 2;
	//map[3] = 3;
	//for (const auto& [key, val] : map)
	//{
	//	cout << "key: " << key << ' ';
	//	cout << "val: " << val << endl;
	//}

	// 带有初始化器的 if 和 switch 运算符
	//if(init; condition)
	//switch(init, condition)

	//std::map<int, string> map;
	//if (auto [it, ok] = map.insert({ 2, "hello" }); ok)
	//{

	//}

	// C++14
	//set<int> mySet;
	//set<int>::iterator iter;
	//bool ok;
	//std::tie(iter, ok) = mySet.insert(42);

//}


// 文件系统
//int main()
//{
//	fs::path file_path("/dir1/dir2/file.txt");
//	cout << file_path.parent_path() << '\n'; // It'll print "/dir1/dir2"
//	cout << file_path.filename() << '\n'; // It'll print "file.txt"
//	cout << file_path.extension() << '\n'; // It'll print ".txt"
//
//	file_path.replace_filename("file2.txt");
//	file_path.replace_extension(".cpp");
//	cout << file_path << '\n'; // It'll print "/dir1/dir2/file2.cpp"
//
//	fs::path dir_path("/dir1/");
//	dir_path.append("dir2/file.txt");
//	cout << dir_path << '\n'; // It'll print "/dir1/dir2/file.txt"
//
//	fs::path current_path = fs::current_path();
//	fs::create_directory("/dir");
//	fs::create_directories("/dir/subdir1/subdir2");
//	if (fs::exists("dir/subdir1"))
//		cout << "yes\n";
//
//	for (auto& p : fs::directory_iterator(current_path))
//	{
//		cout << p.path() << endl;
//	}
//
//	for (auto& p : fs::recursive_directory_iterator(current_path))
//	{
//		cout << p.path() << endl;
//	}
//
//}

//std::optional
// 这是一个存储可选值的模板类。

//std::optional<int> convert(int a)
//{
//	if (a) return a;
//	return {};
//}
//
//int main()
//{
//	int data = 10;
//	auto val = convert(data);
//	if (val.has_value())
//	{
//		cout << "conversion is ok,";
//		cout << "val = " << val.value() << endl;
//	}
//	else
//	{
//		cout << "conversion failed!\n";
//	}
//}

// std::any
// std::any 类的对象可以存储任何类型的信息。

//int main()
//{
//	std::any a = 42;
//	cout << any_cast<int>(a) << endl;
//	cout << a.type().name() << endl;
//
//	a = 11.34f;
//	cout << any_cast<float>(a) << endl;
//
//	a = std::string{ "hello" };
//	cout << any_cast<string>(a) << endl;
//	
//}


//std::variant

//int main()
//{
//	std::variant<int, float, char> v;
//	v = '4';
//	auto ptr = std::get_if<int>(&v);
//	if (ptr != nullptr)
//	{
//		cout << "int val: " << *ptr << endl;
//	}

	//cout << get<char>(v) << endl;   //   std::bad_variant_access
	//cout << get<float>(v) << endl;  //	 std::bad_variant_access 

//	std::visit([](auto& arg) {
//		using Type = std::decay_t<decltype(arg)>;
//		if constexpr (std::is_same_v<Type, int>)
//		{
//			cout << "int Value : " << arg << endl;
//		}
//		else if constexpr (std::is_same_v<Type, float>)
//		{
//			cout << "float Value : " << arg << endl;
//		}
//		else if constexpr (std::is_same_v<Type, char>)
//		{
//			cout << "char Value : " << arg << endl;
//		}
//		}, v);
//
//}

// std::string_view
//std::string_view 具有采用 std::string、char[N]、char* 的构造函数

//C++14
//void Func(const char* str);
//void Func(const char str[10]);
//void Func(const string& str);
//
// C++17
//void Func(string_view str);

// try_emplace 和 insert_or_assign

//int main()
//{
//	string s1("hello");
//	map<int, string> myMap;
//	myMap.emplace(1, "aaa");
//	myMap.emplace(2, "nnn");
//	myMap.emplace(3, "ccc");

	//cout << s1.empty() << endl;
	//myMap.emplace(4, std::move(s1));
	//cout << s1.empty() << endl;

	//cout << s1.empty() << endl;
	//myMap.emplace(3, std::move(s1));
	//cout << s1.empty() << endl;

	//cout << s1.empty() << endl;
	//myMap.try_emplace(4, std::move(s1));
	//cout << s1.empty() << endl;
//}

//int main()
//{
//	map<int, string> myMap;
//	myMap.emplace(1, "aaa");
//	myMap.emplace(2, "nnn");
//	myMap.emplace(3, "ccc");
//
//	auto [it1, insert1] = myMap.insert_or_assign(3, "ddd");
//	cout << insert1 << endl;
//
//	auto [it2, insert2] = myMap.insert_or_assign(4, "eee");
//	cout << insert2 << endl;
//
//}

// 非常量字符串::data

//int main()
//{
//	string str = "hello";
//	char* p = str.data();
//	p[0] = 'H';
//	cout << str << endl;
//}


// day-2025-5-29
// 并行算法
//int main()
//{
	//std::vector<int> data = { 5,3,1,4,2 };
	// 1. 并行排序

	//std::sort(std::execution::par, data.begin(), data.end());
	//for (auto& d : data) cout << d << " ";

	// 2. 并行变换
	//vector<int> src{ 1,2,3,4,5 };
	//vector<int> dest(src.size());
	//std::transform(std::execution::par, src.begin(), src.end(), dest.begin(), [](int x) {return x * 2;});
	//for (auto& d : dest) cout << d << " ";

	//std::vector<int> data = { 1, 2, 3, 4, 5 };
	//// 并行遍历
	//std::for_each(std::execution::par,
	//	data.begin(), data.end(),
	//	[](int& x) { x *= 2; });

	//for (int x : data) {
	//	std::cout << x << " ";
	//}

	
//	return 0;
//}

// std::invoke、trait is_invocable

//int Func(int a, int b)
//{
//	return a + b;
//}
//
//void FunC() {};
//
//struct S
//{
//	void operator() (int a)
//	{
//		std::cout << a << '\n';
//	}
//};
//
//int main()
//{
//	std::cout << std::invoke(Func, 10, 20) << '\n'; // 30
//	S()(42); // 42
//	std::invoke(S(), 42); // 42
//	std::invoke([]() { std::cout << "hello\n"; }); // hello
//
//	std::cout << std::is_invocable<decltype(FunC)>::value << '\n'; // 1
//	std::cout << std::is_invocable<int>::value << '\n'; // 0
//
//	return 0;
//}

// std::to_chars、std::from_chars
//#include <charconv>
//
//int main()
//{
//	char arr[128];
//	auto res1 = std::to_chars(std::begin(arr), std::end(arr), 3.14f);
//	if (res1.ec != std::errc::value_too_large)
//	{
//		cout << arr << endl;
//	}
//
//	float val;
//	auto res2 = std::from_chars(std::begin(arr), std::end(arr), val);
//	if (res2.ec != std::errc::invalid_argument &&
//		res2.ec != std::errc::result_out_of_range)
//	{
//		cout << arr << endl;
//	}
//	cout << val << endl;
//
//}

//int main()
//{
//	vector<int> vct = { 3,2,5,1,7,6 };
//	size_t sz = std::size(vct);
//	bool empty = std::empty(vct);
//	auto ptr = std::data(vct);
//	cout << sz << " " << empty << " " << *std::data(vct) <<" "<< typeid(ptr).name() << endl;
//}

// std::clamp
// std::clamp(x, low, high) 如果他在 [low, high], 否则为最接近的值, 则返回 x
//int main()
//{
//	cout << clamp(7, 0, 10) << endl; // 7
//	cout << clamp(7, 0, 5) << endl; // 5
//	cout << clamp(7, 10, 50) << endl; // 10
//}

// GCD 和 LCM
//int main()
//{
//	cout << gcd(24, 60) << endl;
//	cout << lcm(8, 10) << endl;
//}


 // 逻辑运算元函数
//template<typename... Args>
//std::enable_if_t<std::conjunction_v<std::is_integral<Args>...>>
//Func(Args... args)
//{
//	cout << "All type are integral" <<  endl;
//}
//
//template<typename... Args>
//std::enable_if_t<!std::conjunction_v<std::is_integral<Args>...>>
//Func(Args... args)
//{
//	cout << "Not all type are integral" << endl;
//}
//
//int main()
//{
//	Func(42, true);
//	Func(42, "hello");
//}

// emplace_back 的返回值
// emplace_back 现在返回对插入元素的引用;在 C++17 之前，它不返回任何值

//int main()
//{
//	vector<int> vct;
//	auto& r = vct.emplace_back(10);
//	r = 42;
//	for (const auto& i : vct)
//	{
//		std::cout << i << ' ';
//	}
//
//	return 0;
//}

// std::apply
//void Func(char x, int y, double z)
//{
//	cout << x <<" "<<  y << z << endl;
//}
//int main()
//{
//	tuple args{ 'c', 42, 3.14 };
//	apply(Func, args);
//}

// 从元组构造对象 （std::make_from_tuple）
//struct S
//{
//	char m_x;
//	int m_y;
//	double m_z;
//	S(char x, int y, double z) : m_x(x), m_y(y), m_z(z) {}
//};
//
//int main()
//{
//	tuple args{ 'c', 42, 3.14 };
//	S s = make_from_tuple<S>(args);
//	cout << s.m_x << " " << s.m_y << " " << s.m_z << endl;
//}

// std::not_fn （通用否定器 not_fn）

//bool LessThan1O(int a)
//{
//	return a < 10;
//}
//int main()
//{
//	vector<int> vect = { 1,6,3,8, 14, 42, 2 };
//	auto n = count_if(vect.begin(), vect.end(), std::not_fn(LessThan1O));
//	cout << n << endl;
//}


// 访问容器节点
//int main()
//{
	//map<int, string> map1{ {1,"aa"}, {2, "bb"}, {3, "cc"} };
	//map<int, string> map2{ {4,"dd"}, {5, "ee"}, {6, "ff"} };
	//auto node = map1.extract(2);
	//map2.insert(std::move(node));
	//for (const auto& [key, val] : map1)
	//{
	//	cout << key << " " << val << endl;
	//}
	//cout << endl;
	//for (const auto& [key, val] : map2)
	//{
	//	cout << key << " " << val << endl;
	//}

	/*map<int, string> map3{ {1, "Tommy"},
		{2, "Peter"},
		{3, "Andrew"}};
	auto node = map3.extract(2);
	node.key() = 42;
	map3.insert(std::move(node));
	for (const auto& [key, val] : map3)
	{
		cout << key << " " << val << endl;
	}*/

//}

// std::*_v<T...>
// C++14
//static_assert(std::is_integral<T>::value, "Integral required");
//
// C++17
//static_assert(std::is_integral_v<T>, "integral required");

// std::shared_ptr 用于数组
//int main()
//{
//	//C++14
//	std::shared_ptr<int[]> arr1(new int[4],
//		std::default_delete<int[]>());
//
//	// C++17
//	std::shared_ptr<int[]> arr(new int[7]);
//
//	arr.get()[0] = 1;
//	arr.get()[1] = 2;
//	arr.get()[2] = 3;
//	for (int i = 0; i < 3; ++i) cout << arr[i] << " ";
//
//}

// std::scoped_lock
//int var;
//std::mutex varMtx;
//
//void ThreadFunc()
//{
//	std::scoped_lock{ varMtx };
//	var++;
//	cout << this_thread::get_id() << ": " << var << endl;
//}
//
//int main()
//{
//	thread t1(ThreadFunc);
//	thread t2(ThreadFunc);
//	t1.join();
//	t2.join();
//}