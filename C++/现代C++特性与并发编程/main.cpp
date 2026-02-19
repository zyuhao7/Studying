#include <iostream>
#include <list>
#include <thread>
#include <chrono>
#include <future>
#include <Windows.h>

//void Download()
//{
//	using namespace std::chrono_literals;
//	for (int i = 0; i < 10; ++i)
//	{
//		std::cout << '.';
//		std::this_thread::sleep_for(300ms);
//	}
//}
//int main()
//{
	//std::thread t1(Process);
	//HANDLE handle = t1.native_handle();
	//SetThreadDescription(handle, L"MyThread");
	//auto id = t1.get_id();
	//std::cout << "cores: " << std::thread::hardware_concurrency() << std::endl;
	//std::cout << id << std::endl;

	//t1.join();
	//std::future<void> result = std::async(Download);
	//result.get();
//}

//[[deprecated("Use the new version instead")]] //可以应用于类和命名空间
//int* CreateInArray(size_t sz)
//{
//	return new int[sz];
//}
//int main()
//{
	//CreateInArray(3);
	//std::mutex m;
	//std::lock_guard lk(m);
//}

// 折叠

//auto Sum() { return 0; }
//
//template<typename T, typename...Args>
//auto Sum(T a, Args... args) -> int
//{
//	return a + Sum(args...);
//}
//
//template<typename... Args>
//auto Sum2(Args... args)
//{
//	//return (args + ...); 一元右折叠
//	return (... + args);
//
//}
//
//template<typename... Args>
//auto Sum3(Args... args)
//{
//	return (0 + ... + args);
//
//}
//
//template<typename... Args>
//bool Anyof(Args... args)
//{
//	return (... || (args % 2 == 0));
//}
//
//int main()
//{
//	//int sm = Sum3();
//	//std::cout << sm << std::endl;
//	std::cout << std::boolalpha;
//	std::cout << "Anyof even ? "  << Anyof(2, 4, 1) << std::endl;
//}

#include <type_traits>
// Compile-Time if
template<typename T>
void print(const T& v)
{
	if constexpr (std::is_pointer_v<T>)
	{
		std::cout << *v << std::endl;
	}
	else if constexpr (std::is_array_v<T>)
	{
		for (auto& x : v) std::cout << x << " ";
	}
	else
	{
		std::cout << v << std::endl;
	}
}
template<typename T>
std::string ToString(T value)
{
	if constexpr (std::is_arithmetic_v<T>) {
		return std::to_string(value);
	}
	else {
		return std::string{ value };
	}
}

int main()
{
	int value{ 5 };
	print(value);
	print(&value);
	int arr[] = { 1,2,3 };
	auto s = ToString(value);
	std::cout << s << std::endl;
	//print(arr);
}