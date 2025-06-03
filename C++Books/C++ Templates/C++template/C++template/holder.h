#pragma once
#include "trule.h"
// 资源持有者
template<typename T>
class Holder
{
private:
	T* ptr;

public:
	Holder()
	 :ptr(0)
	{}

	explicit Holder(T* p = nullptr)
		:ptr(p)
	{}

	~Holder()
	{
		delete ptr;
	}

	Holder(const Holder&) = delete;
	Holder& operator=(const Holder&) = delete;

	Holder(Holder&& other) noexcept : ptr(other.ptr) {
		other.ptr = nullptr; 
	}

	Holder& operator=(Holder&& other) noexcept {
		if (this != &other) {
			delete ptr;       // 释放当前资源
			ptr = other.ptr;  // 接管新资源
			other.ptr = nullptr;
		}
		return *this;
	}

	T* get() const
	{
		return ptr;
	}

	T* release()
	{
		T* ret = ptr;
		ptr = nullptr;
		return ret;
	}
};
