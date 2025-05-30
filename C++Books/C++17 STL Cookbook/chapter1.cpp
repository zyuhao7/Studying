#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <typeinfo>
#include <algorithm>
#include <string>
#include <vector>
#include <chrono>
#include <type_traits>
#include <tuple>
#include <map>
#include <set>
#include <unordered_map>
using namespace std;
// day-2025-5-30
// 使用结构化绑定来解包绑定的返回值
//std::pair<int, int> divide_remainder(int dividend, int divisor)
//{
//	int n1 = dividend / divisor;
//	int n2 = dividend % divisor;
//	return { n1, n2 };
//}
//static int price = 100;
//
//tuple<string, chrono::system_clock::time_point, unsigned> stock_info(const string& name)
//{
//	return { name,chrono::system_clock::now(),++price };
//}
//
//
//
//int main()
//{
//	const auto result(divide_remainder(16, 3));
//	cout << "16 / 3 is " << result.first << " with a remainder of " << result.second << endl;
//
//	auto [fraction, remainder] = divide_remainder(16, 3);
//
//	std::cout << "16 / 3 is "
//		<< fraction << " with a remainder of "
//		<< remainder << '\n';
//
//	int remainder1;
//	std::tie(std::ignore, remainder1) = divide_remainder(16, 5);
//	std::cout << "16 % 5 is " << remainder1 << '\n';
//
//	const auto [name, valid_time, price] = stock_info("INTC");
//	time_t tt = chrono::system_clock::to_time_t(valid_time);
//
//
//	cout << "name: " << name
//		<< " valid_time: " << ctime(&tt) // ctime 会换行
//		<< "price: " << price << endl;
//
//
//	return 0;
//}

// 将变量作用域限制在if和switch区域内

//int main()
//{
	//unordered_map<char, int> character_map;
	//char c;
	//if (auto it = character_map.find(c); it != character_map.end()){
	//}
	//else {

	//}

	//switch (char c = getchar(); c)
	//{
	//case 'a':
	//	break;
	//default:
	//	break;
	//}


//}

// 新的括号初始化规则
//int main()
//{
	//int x1 = 1;
	//int x2{ 2 };
	//int x3(1);
	//vector<int> v1{ 1,2,3 };
	//vector<int> v2 = { 1, 2, 3 };
	//vector<int> v3(10, 20); // 10个元素,每个初始为20.

	//auto v{ 1 };
	//auto w{ 1, 2 }; // “w”: 在直接列表初始化上下文中，类型“auto”只能从单个初始值设定项表达式推导出
	//auto x = { 1 }; // class std::initializer_list<int>
	//auto y = { 1, 2 };
	//auto z = { 1, 2, 3.0 }; // err:can't deduce element type
//}

// 构造函数自动推导模板的类型
//template<typename T1, typename T2, typename T3>
//class my_wrapper {
//	T1 t1;
//	T2 t2;
//	T3 t3;
//public:
//	explicit my_wrapper(T1 t1_, T2 t2_, T3 t3_)
//		:t1{t1_}, t2{t2_}, t3{t3_}
//	{}
//};

//template<typename T1, typename T2, typename T3>
//my_wrapper<T1, T2, T3> make_wrapper(T1 t1, T2 t2, T3 t3)
//{
//	return { t1, t2, t3 };
//}

//template<typename T>
//struct sum {
//	T value;
//
//	template<typename ... Ts>
//	sum(Ts&& ... values)
//		:value{(values + ...)}
//	{
//		cout << "sum(Ts&& ... values)" << endl;
//	}
//};	
//
//template <typename ... Ts>
//sum(Ts&& ... ts) -> sum<std::common_type_t<Ts...>>;




//int main()
//{
	//my_wrapper<int, double, const char*> wrapper{ 123, 1.2	3, "abc" }; // C++17 prev

	//my_wrapper wrapper1{ 123, 1.23, "abc" }; // C++17 
	//auto wrapper2(make_wrapper(123, 1.23, "abc"));

	//sum s{ 1u, 2.0, 3, 4.0f };
	//sum string_sum{ std::string{"abc"}, "def" };
	//std::cout << s.value << '\n'
	//	<< string_sum.value << '\n';
//}

// 使用constexpr-if简化编译使用constexpr-if简化编译

//template<typename T>
//class addable
//{
//	T val;
//public:
//	addable(T v)
//		:val{v}
//	{}

	//template<typename U>
	//T add(U x) const
	//{
	//	return val + x;
	//}
	// 假设类型T是std::vector<something>，而类型U是int。这里就有问题了，为整个vector添加整数是为了什么呢？
	// 其应该是对vector中的每个元素加上一个整型数。实现这个功能就需要在循环中进行：

	/*template<typename U>
	T add(U x)
	{
		auto copy(val);
		for (auto& n : copy)
		{
			n += x;
		}
		return copy;
	}*/

	// 下一步也是最后一步，将两种方式结合在一起。
	// 如果T类型是一个vector，其每个元素都是U类型，择进行循环。如果不是，则进行普通的加法.
//	template<typename U>
//	T add(U x) const
//	{
//		if constexpr (std::is_same<T, std::vector<U>>::value)
//		{
//			auto copy(val);
//			for (auto& n : copy)
//			{
//				n += x;
//			}
//
//			return copy;
//		}
//		else
//		{
//			return val + x;
//		}
//	}
//};

//int main()
//{
//	cout << addable<int>{1}.add(2) << endl;
//	cout << addable<float>{1.f}.add(2)<<endl;
//	cout << addable<string> {"aa"}.add("bb")<<endl;
//
//	vector<int> v{ 1,2,3 };
//	addable<vector<int>>{v}.add(10);
//	for (auto& x : v) cout << x << " ";
//	cout << endl;
//
//	std::vector<std::string> sv{ "a", "b", "c" };
//	auto svcopy = addable<std::vector<std::string>> {sv}.add(std::string{ "z" }); 
//
//	for (auto& x : svcopy) cout << x << " ";
//
//}

// 只有头文件的库中启用内联变量
//使用折叠表达式实现辅助函数
//template <typename ... Ts>
//auto sum(Ts ... ts);
//
//template<typename ... Ts>
//auto sum(Ts ... ts) {
//	return (ts + ...);
//}
//
//template <typename ... Ts>
//auto sume(Ts ... ts) {
//	return (ts + ... + 0);
//}
//
//template <typename ... Ts>
//auto product(Ts ... ts) {
//	return (ts * ... * 1);
//}

// 匹配范围内的单个元素
//template <typename R, typename ... Ts>
//auto matches(const R& range, Ts ... ts)
//{
//	return (std::count(std::begin(range), std::end(range), ts) + ...);
//}

// 检查集合中的多个插入操作是否成功
//template <typename T, typename ... Ts>
//bool insert_all(T& set, Ts ... ts)
//{
//	return (set.insert(ts).second && ...);
//}

// std::set的insert成员函数声明如下：
//std::pair<iterator, bool> insert(const value_type& value);


// 检查所有参数是否在范围内
//template <typename T, typename ... Ts>
//bool within(T min, T max, Ts ...ts)
//{
//	return ((min <= ts && ts <= max) && ...);
//}

// 将多个元素推入vector中
//template <typename T, typename ... Ts>
//void insert_all(std::vector<T>& vec, Ts ... ts) {
//	(vec.push_back(ts), ...);
//}
//
//int main()
//{
//	int the_sum{ sum(1, 2, 3, 4, 5) }; // value: 15
//	std::string a{ "Hello " };
//	std::string b{ "World" };
//
//	std::cout << sum(a, b) << '\n'; // output: Hello World
//	cout<< sume()<<endl;
//	cout << product(2, 3) << endl;
//
//	std::vector<int> v{ 1, 2, 3, 4, 5 };
//
//	cout<< matches(v, 2, 5); // return 2
//	cout<< matches(v, 100, 200); // return 0
//	cout<< matches("abcdefg", 'x', 'y', 'z'); // return 0
//	cout<< matches("abcdefg", 'a', 'b', 'f'); // return 3
//	cout << endl;
//
//	std::set<int> my_set{ 1, 2, 3 };
//
//	cout<< insert_all(my_set, 4, 5, 6); // Returns true
//	cout<< insert_all(my_set, 7, 8, 2); // Returns false, because the 2 collides
//	cout<< within(10, 20, 1, 15, 30); // --> false
//	cout<< within(10, 20, 11, 12, 13); // --> true
//	cout<< within(5.0, 5.5, 5.1, 5.2, 5.3); // --> true
//
//	std::string aaa{ "aaa" };
//	std::string bcd{ "bcd" };
//	std::string def{ "def" };
//	std::string zzz{ "zzz" };
//
//	cout<< within(aaa, zzz, bcd, def); // --> true
//	cout<< within(aaa, def, bcd, zzz); // --> false
//	
//	cout << endl;
//
//	std::vector<int> vx{ 1, 2, 3 };
//	insert_all(vx, 4, 5, 6);
//}	