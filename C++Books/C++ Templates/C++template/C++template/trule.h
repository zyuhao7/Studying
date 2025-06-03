#pragma once
template<typename T>
class Holder;
// ��ȫת�Ƹ�����
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

	// ��ȡ��Դ(ת�Ƹ��µ� Holder)
	T* yield()
	{
		T* ret = ptr;
		ptr = nullptr;
		return ret;
	}

};