#include <iostream>
#include <utility>
#include <boost/atomic.hpp>
#include <boost/memory_order.hpp>
#include <boost/smart_ptr/intrusive_ptr.hpp>

using namespace boost;

// 第十二章-并发编程
// day-2025-6-28
// atomic
// atomic库定义了基本模板类atomic<T>，其简化的类摘要如下:

//template<typename T>
//class Atomic : public atomics::detail::base_atomic<T>
//{
//public:
//	Atomic() = default;
//	explicit Atomic(T v);
//	Atomic(const Atomic&) = delete;
//	Atomic& operator=(const Atomic&) = delete;
//
//public:
//	bool is_lock_free(); //是否无锁
//	void store(T v);    //存值
//	T load();			//取值
//	
//	T operator=(T v) volatile; //赋值, 相等于 store
//	operator T() volatile const; //隐式类型转换, 相当于 load
//
//	T exchange(T new_value); // 存值, 然后返回原值
//	bool comare_exchange_weak(T& expected, T desired);  
//	bool comare_exchange_strong(T& expected, T desired);  
//
//	T& storage();	//获取内部的值
//	T const& storage() const;
//};
//
//// atomic<T> 还针对整数类型和指针类型进行了特化，增加了一些特殊的操作:
//template<>
//class Atomic<int>
//{
//public:
//	//... 同 Atomic<T>
//public:
//	int fetch_add(int i); // 加法, 返回原值
//	int fetch_sub(int i); // 减法, 返回原值
//	int fetch_and(int i); // &, 返回原值
//	int fetch_or(int i); // |, 返回原值
//	int fetch_xor(int i); // ^, 返回原值
//
//	int operator++();
//	int operator--();
//};
//
//template<typename T>
//class Atomic<T*>
//{
//public:
//	// ...
//public:
//	T* fecth_add(ptrdiff_t v); // 指针加偏移, 返回原值
//	T* fecth_sub(ptrdiff_t v);
//
//};

//enum Memory_order
//{
//	memory_order_relaxed = 0, // 不做任何顺序要求
//	memory_order_consume = 1,
//	memory_order_acquire = 2,
//	memory_order_release = 4,
//	memory_order_acq_rel = 6, // acquire | release
//
//	memory_order_seq_cst = 14 // acq_rel | 8   顺序一致性约束
//};

// 下面的代码使用atomic 结合恰当的内存访问顺序，实现了一个高效的引用计数适配器 ref_count:
//template<typename T>
//class Ref_count
//{	
//private:
//	typedef boost::atomic<int> atomic_type; // 定义 atomic 类型
//	mutable atomic_type m_count{ 0 };
//
//protected:
//	Ref_count(){}
//	~Ref_count() {}
//public:
//	typedef boost::intrusive_ptr<T> counted_ptr; // 定义 intrusive_ptr
//	
//	void add_ref() const
//	{
//		m_count.fetch_add(
//			1, boost::memory_order_relaxed); // 不做任何顺序要求
//	}
//
//	void sub_ref() const
//	{
//		if (m_count.fetch_sub(
//			1, boost::memory_order_release) == 1)
//		{
//			boost::atomic_thread_fence(      // 原子级别的线程保护
//				boost::memory_order_acquire); 
//			delete static_cast<const T*>(this); // 删除指针, 需要转型
//		}
//	}
//
//	decltype(m_count.load()) count() const
//	{
//		return m_count.load();
//	}
//
//public:
//	template<typename... Args>	// 可变参数模板
//	static counted_ptr make_ptr(Args&& ... args) // 工厂函数
//	{
//		return counted_ptr(new T(std::forward<Args>(args)...));
//	}
//
//private:
//	friend void intrusive_ptr_add_ref(const T* p) // intrusive_ptr 要求函数
//	{
//		p->add_ref();
//	}
//	friend void intrusive_ptr_release(const T* p) // intrusive_ptr 要求函数
//	{
//		p->sub_ref();
//	}
//};
//
//class demo : public Ref_count<demo>
//{
//public:
//	demo() = default;
//	~demo() = default;
//	int x;
//};

//int main()
//{
//	auto p = demo::make_ptr();
//	p->x = 10;
//	assert(p->x == 10);
//	assert(p->count() == 1);


	//atomic<int> n(100);
	//assert(n.fetch_add(10) == 100);
	//assert(n == 110);

	//assert(++n == 111);
	//assert(n++ == 111);
	//assert(n == 112);
	//assert((n -= 10) == 102);

	//atomic<long> l(100);
	//long v = 100;
	//if (l.compare_exchange_weak(v, 313))
	//{
	//	assert(l == 313 && v == 100);
	//}
	//v = 200;
	//std::cout << v << " ";
	//auto b = l.compare_exchange_strong(v, 99);
	//std::cout << v << " ";

	//assert(!b && v == 313);

	//l.compare_exchange_weak(v, 99);
	//assert(l == 99 && v == 313);

	//atomic<int> a(10);
	//assert(a == 10);

	//atomic<long> l; 
	//std::cout << l << std::endl; // 0

	//atomic<bool> b(false);
	//assert(!b.load());

	//b.store(true);
	//assert(b);

	//atomic<int> n(100);
	//assert(n.exchange(200) == 100);
	//assert(n == 200); // 隐式类型转换, 等于 load
//}