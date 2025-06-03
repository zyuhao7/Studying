#pragma once
template<typename T>
class Holder;
// 安全转移辅助类
template<typename T>
class Trule
{
private:
	T* ptr;
public:
	explicit Trule(Holder<T>& h)
		:ptr(h.release())
	{}

	Trule(const Trule&) = delete;
	Trule& operator=(const Trule&) = delete;

	Trule(Trule&& other) noexcept
		:ptr(other.ptr)
	{
		other.ptr = nullptr;
	}
	~Trule()
	{
		if (ptr)
		{
			delete ptr;
		}
	}

	// 获取资源(转移给新的 Holder)
	T* yield()
	{
		T* ret = ptr;
		ptr = nullptr;
		return ret;
	}

};