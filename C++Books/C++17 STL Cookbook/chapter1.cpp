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
// ʹ�ýṹ����������󶨵ķ���ֵ
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
//		<< " valid_time: " << ctime(&tt) // ctime �ỻ��
//		<< "price: " << price << endl;
//
//
//	return 0;
//}

// ������������������if��switch������

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

// �µ����ų�ʼ������
//int main()
//{
	//int x1 = 1;
	//int x2{ 2 };
	//int x3(1);
	//vector<int> v1{ 1,2,3 };
	//vector<int> v2 = { 1, 2, 3 };
	//vector<int> v3(10, 20); // 10��Ԫ��,ÿ����ʼΪ20.

	//auto v{ 1 };
	//auto w{ 1, 2 }; // ��w��: ��ֱ���б��ʼ���������У����͡�auto��ֻ�ܴӵ�����ʼֵ�趨����ʽ�Ƶ���
	//auto x = { 1 }; // class std::initializer_list<int>
	//auto y = { 1, 2 };
	//auto z = { 1, 2, 3.0 }; // err:can't deduce element type
//}

// ���캯���Զ��Ƶ�ģ�������
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

// ʹ��constexpr-if�򻯱���ʹ��constexpr-if�򻯱���

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
	// ��������T��std::vector<something>��������U��int��������������ˣ�Ϊ����vector���������Ϊ��ʲô�أ�
	// ��Ӧ���Ƕ�vector�е�ÿ��Ԫ�ؼ���һ����������ʵ��������ܾ���Ҫ��ѭ���н��У�

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

	// ��һ��Ҳ�����һ���������ַ�ʽ�����һ��
	// ���T������һ��vector����ÿ��Ԫ�ض���U���ͣ������ѭ����������ǣ��������ͨ�ļӷ�.
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

// ֻ��ͷ�ļ��Ŀ���������������
//ʹ���۵����ʽʵ�ָ�������
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

// ƥ�䷶Χ�ڵĵ���Ԫ��
//template <typename R, typename ... Ts>
//auto matches(const R& range, Ts ... ts)
//{
//	return (std::count(std::begin(range), std::end(range), ts) + ...);
//}

// ��鼯���еĶ����������Ƿ�ɹ�
//template <typename T, typename ... Ts>
//bool insert_all(T& set, Ts ... ts)
//{
//	return (set.insert(ts).second && ...);
//}

// std::set��insert��Ա�����������£�
//std::pair<iterator, bool> insert(const value_type& value);


// ������в����Ƿ��ڷ�Χ��
//template <typename T, typename ... Ts>
//bool within(T min, T max, Ts ...ts)
//{
//	return ((min <= ts && ts <= max) && ...);
//}

// �����Ԫ������vector��
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