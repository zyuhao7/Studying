#pragma once
#include "trule.h"
// ��Դ������
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
			delete ptr;       // �ͷŵ�ǰ��Դ
			ptr = other.ptr;  // �ӹ�����Դ
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
