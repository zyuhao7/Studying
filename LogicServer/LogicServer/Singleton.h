#pragma once
#include <iostream>
#include <memory>
#include <mutex>

template<typename T>
class Singleton
{
protected:
	Singleton() = default;
	Singleton(const Singleton<T> &) = delete;
	Singleton& operator=(const Singleton<T> &) = delete;

	static std::shared_ptr<T> _instance;

public:
	static std::shared_ptr<T> GetInstance()
	{
		static std::once_flag s_flag;
		std::call_once(s_flag, [&]() {
			_instance = std::shared_ptr<T>(new T);
			});

		return _instance;
	}
	void PrintAddress()
	{
		std::cout << "print Address is Ox" <<_instance.get() << std::endl;
	}
	~Singleton()
	{
		std::cout << "~Singleton()" << std::endl;
	}
};
template<typename T>
std::shared_ptr<T>	Singleton<T>::_instance = nullptr;