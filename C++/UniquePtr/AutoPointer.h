#pragma once
template<typename T>
struct  DefaultDeleter
{
	void operator()(T* p)
	{
		delete p;
	}
};

template<typename Resource, typename Deleter, bool IsPointer = false>
class PointerInfo : public Deleter
{
	Resource m_ptr{};
public:
	PointerInfo(Resource ptr, Deleter): m_ptr{ptr}{
	}
	void setResource(Resource ptr)
	{
		m_ptr = ptr;
	}
	Resource getResource() const 
	{
		return m_ptr;
	}
	Deleter getDeleter() const
	{
		return *this;
	}
};

// Æ«ÌØ»¯
template<typename Resource, typename Deleter>
class PointerInfo<Resource, Deleter, true>
{
	Resource m_ptr{};
	Deleter m_Deleter{};
public:
	PointerInfo(Resource ptr, Deleter deleter)
		: m_ptr{ ptr },
		m_Deleter(deleter){
	
	}
	void setResource(Resource ptr)
	{
		m_ptr = ptr;
	}
	Resource getResource() const
	{
		return m_ptr;
	}
	Deleter getDeleter() const
	{
		return m_Deleter;
	}
};


template<typename T, typename Deleter = DefaultDeleter<T>>
class AutoPtr : Deleter
{
	T* m_ptr{};
	//[[msvc::no_unique_address]] Deleter m_deleter{};
public:
	AutoPtr() = default;
	AutoPtr(T* ptr, Deleter deleter) : Deleter(deleter), m_ptr{ptr} {

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
	AutoPtr(const AutoPtr&) = delete;
	AutoPtr& operator=(const AutoPtr&) = delete;

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
			(*this)(m_ptr);
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