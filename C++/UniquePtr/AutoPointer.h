#pragma once
template<typename T>
struct  DefaultDeleter
{
	void operator()(T* p)
	{
		delete p;
	}
};
template<typename T, typename Deleter = DefaultDeleter<T>>
class AutoPtr
{
	T* m_ptr{};
	Deleter m_deleter{};
public:
	AutoPtr() = default;
	AutoPtr(T* ptr, Deleter deleter) : m_ptr{ ptr }, m_deleter{ deleter } {

	}
	explicit AutoPtr(T* ptr) noexcept : AutoPtr{ptr ,{} } {
	
	}
	AutoPtr(AutoPtr&& other)noexcept
		: m_ptr{ std::exchange(other.m_ptr, nullptr) } {

	}
	AutoPtr& operator=(AutoPtr&& other) noexcept
	{
		if (this != &other)
		{
			reset(other.release());
			m_ptr = std::exchange(other.m_ptr, nullptr);
		}
		return *this;
	}

	~AutoPtr()
	{	
		reset(m_ptr);
	}
	T* get() const noexcept
	{
		return m_ptr;
	}

	T* operator->() const noexcept
	{
		return m_ptr;
	}
	T& operator*() const noexcept
	{
		return *m_ptr;
	}
	explicit operator bool() const noexcept
	{
		return m_ptr != nullptr;
	}
	T* release() noexcept
	{
		auto ptr = m_ptr;
		m_ptr = nullptr;
		return ptr;
	}

	void reset(T* p = nullptr) noexcept
	{
		if (m_ptr)
		{
			m_deleter(m_ptr);
		}
		m_ptr = p;
	}
};


template<typename T>
bool operator==(const AutoPtr<T>& p, std::nullptr_t) noexcept
{
	return p.get() == nullptr;
}

template<typename T>
bool operator!=(const AutoPtr<T>& p, std::nullptr_t) noexcept
{
	return !(p == nullptr);
}