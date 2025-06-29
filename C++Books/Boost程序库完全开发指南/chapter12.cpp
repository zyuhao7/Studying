#define BOOST_THREAD_VERSION 5
#include <iostream>
#include <utility>
#include <boost/atomic.hpp>
#include <boost/memory_order.hpp>
#include <boost/smart_ptr/intrusive_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/lock_factories.hpp>
#include <boost/thread/lockable_adapter.hpp>
#include <boost/thread/thread_guard.hpp>
#include <boost/thread/scoped_thread.hpp>
#include <boost/thread/shared_lock_guard.hpp>
#include <boost/noncopyable.hpp>
#include <boost/chrono.hpp>
#include <ctime>
using namespace boost;

// 第十二章-并发编程
// day-2025-6-29
// thread
/*
										mutex
	互斥量（mutex）是一种用于线程同步的手段，它可以在多线程环境里防止多个线程同时操作共享资源。
	一旦一个线程锁定了互斥量，那么其他线程必须等待它解锁互斥量后才能访问共享资源。
	thread提供了6种互斥量类型:
	■ null_mutex：无任何锁定功能的互斥量，它是空对象模式的应用。
	■ mutex：独占式的互斥量，是最简单、最常用的互斥量类型。
	■ timed_mutex：独占式的互斥量，但提供超时锁定功能。
	■ recursive_mutex：递归式互斥量，可以多次锁定，相应地也需要多次解锁。
	■ recursive_timed_mutex：递归式互斥量，同样增加了超时锁定功能。
	■ shared_mutex：multiple-reader/single-writer型的共享互斥量(又称读写锁).
*/

// 类摘要
//class Mutex : public boost::noncopyable
//{
//public:
//	void lock();
//	void unlock();
//
//	bool try_lock();
//
//	bool try_lock_for(const  booost::chrono::duration & rel_time); // 限时尝试锁定
//	bool try_lock_until(const boost::chrono::time_point& t);
//
//	some_type native_handle(); // 系统相关的 handle
//};

//int main()
//{
//	mutex mtx;
//	try
//	{
//		mtx.lock();
//		std::cout << "some operations" << std::endl; // 操作共享资源
//		mtx.unlock();
//	}
//	catch (const std::exception&)
//	{
//		mtx.unlock();
//	}
//	timed_mutex t_mtx;
//	bool b = t_mtx.try_lock_for(boost::chrono::milliseconds(100));
//	if (b) {
//		std::cout << "成功获取锁" << std::endl;
//		t_mtx.unlock();
//	}
//	else {
//		std::cout << "获取锁超时" << std::endl;
//	}
//}

//lock_guard
/*
	thread库提供 RAII型的 lock_guard 类用于辅助锁定互斥量。它在构造时锁定互斥量，在析构时自动解锁，
	从而保证了互斥量的正确操作，避免遗忘解锁，它就像一个智能指针.
*/

//template<typename Mutex>
//class Lock_guard : boost::noncopyable
//{
//private:
//	Mutex& m;
//
//public:
//	explicit Lock_guard(Mutex& m_);			    //构造锁定 mutex
//	/*
//		lock_guard 的第二种形式的构造函数通常配合 timed_mutex 使用，它允许传入一个标志——类型为 adopt_lock_t 的预定义常量adopt_lock，
//		这时 lock_guard 认为线程已经提前以某种操作锁定了 mutex，不会再执行锁定操作，但析构时仍然会解锁。
//	*/
//	Lock_guard(Mutex& m_, boost::adopt_lock_t); //不执行锁定但会解锁
//	~Lock_guard();								//析构释放 mutex
//};

// thread库还提供一个便捷函数 with_lock_guard()，它可以使用 lock_guard 锁定互斥量执行一个函数，简化lock_guard的调用，其声明如下:
//template<class Lockable, class Function, class... Args>
//auto with_lock_guard(Lockable& m, Function&& func, Args&&... args);

// with_lock_guard 相当于
//{
//	lock_guard<Lockable> g(m);
//	return func(args...);
//}


//int main()
//{
//	mutex mtx;
//	lock_guard<mutex> g(mtx); //RAII
//	std::cout << "some ops" << std::endl;
//	
//	timed_mutex mu;
//	if (mu.try_lock_for(boost::chrono::milliseconds(100)))
//	{
//		lock_guard<timed_mutex> g(mu, adopt_lock); //不会再次加锁
//		std::cout << "lock timed mutex" << std::endl;
//	}   // 自动释放锁
//}

//  unique_lock
//template<typename Mutex>
//class Unique_lock
//{
//private:
//	Mutex* m;
//	bool is_locked;
//public:
//	Unique_lock();
//	~Unique_lock();
//
//	Unique_lock(Mutex& m);	//锁定互斥量
//	Unique_lock(Mutex& m, boost::adopt_lock_t); //不锁定互斥量, 但会解锁
//	Unique_lock(Mutex& m, boost::defer_lock_t); //不锁定互斥量
//	Unique_lock(Mutex& m, boost::try_to_lock_t);//尝试锁定互斥量
//
//	Unique_lock(Mutex& m, const boost::chrono::time_point& t); // 超时锁定
//	Unique_lock(Mutex& m, const boost::chrono::duration& t);   // 超时锁定
//
//	void lock();
//	void unlock();
//	bool try_lock();
//	bool try_lock_for(const boost::chrono::duration& d);
//	bool try_lock_until(const boost::chrono::time_point& t);
//
//	bool owns_lock() const;  // 是否锁定了互斥量
//	explicit operator bool() const; // 等价于 owns_lock
//
//	Mutex* mutex() const noexcept; // 获得锁定的互斥量
//	Mutex* release();			   // 不再管理互斥量
//};

// 锁定选项
// thread库里有3个锁定选项，它们都是空类，仅作为运行时的标志，此外没有其他作用
//struct defer_lock_t{};   //不执行锁定操作
//struct try_to_lock_t{};  // 执行 try_lock
//struct adopt_lock_t {};  // 不锁定, 但有所有权
//
//constexpr defer_lock_t defer_lock = {}; //编译器常量标志
//constexpr try_to_lock_t try_to_lock = {}; //编译器常量标志
//constexpr adopt_lock_t adopt_lock = {}; //编译器常量标志

// 因为unique_lock支持转移语义,所以它可以从工厂函数产生,利用模板函数自动推导类型的特性可以不必写出模板参数,这进一步简化了编写代码的工作.
//这些工厂函数的声明如下:
// 四种不同的工厂函数对应不同的构造函数:
//unique_lock<Lockable> make_unique_lock(Lockable& mtx);
//unique_lock<Lockable> make_unique_lock(Lockable& mtx, adopt_lock_t);
//unique_lock<Lockable> make_unique_lock(Lockable& mtx, defer_lock_t);
//unique_lock<Lockable> make_unique_lock(Lockable& mtx, try_to_lock_t);

// 一次性产生多个 unique_lock, 以 std::tuple 返回
//std::tuple<unique_lock<Lockable> ...>
//make_unique_locks(Lockable&, ...mtx);

//int main()
//{
//	mutex mtx;
//	{
//		auto g = make_unique_lock(mtx);
//		assert(g.owns_lock());
//		std::cout << " some ops" << std::endl;
//	}
//	{
//		auto g = make_unique_lock(mtx, defer_lock); // 暂不锁定互斥量
//		assert(!g);
//
//		assert(g.try_lock());
//		assert(g);
//		std::cout << " some ops" << std::endl;
//	}
//
//	timed_mutex tm;
//	{
//		auto g = 
//	}
//}

// lock_adapter
/*
	lock_guard 和 unique_lock 大多数情况下需要搭配 mutex 使用，用于锁定互斥量，但因为它们是模板类，
	所以只要是符合 "Lockable" 概念——也就是有lock/unlock/try_lock接口的类(不一定是互斥量),
	都可以用于 lock_guard 和 unique_lock，这样就能够很容易地锁定整个对象，实现原子性的事务操作。

	thread库定义了几个lockable适配器类，方便我们实现Lockable概念:
	■ basic_lockable_adapter：最简单的接口，提供lock/unlock。
	■ lockable_adapter：基本的接口，增加 try_lock 功能。
	■ timed_lockable_adapter：增加try_lock_for/try_lock_until。
*/
//这些适配器声明如下:
//template<typename BasicLockable>
//class Basic_lockable_adapter
//{
//public:
//	void lock() const;
//	void unlock() const;
//};
//
//template<typename Lockable>
//class Lockable_adapter : public Basic_lockable_adapter<Lockable>
//{
//public:
//	bool try_lock() const;
//};
//
//template<typename TimedLock>
//class Timed_lockable_adapter : public Lockable_adapter<TimedLock>
//{
//public:
//	bool try_lock_for(boost::chrono::duration& rel_time) const;
//	bool try_lock_until(boost::chrono::time_point& t) const;
//};

// 下面我们定义一个简单的储蓄账户类，它使用atomic<int>记录金额，无须锁定就可以保证单笔交易的原子性，
// 但如果要保证多笔交易也具有原子性，则必须使用互斥量:
//class account final : public lockable_adapter<mutex>
//{
//private:
//	atomic<int> money{ 0 };
//public:
//	int sum() const
//	{
//		return money;
//	}
//	void withdraw(int x) // 取款
//	{
//		money -= x;
//	}
//	void deposit(int x) // 存款
//	{
//		money += x;
//	}
//};

//int main()
//{
//	/*
//		account类使用lockable_adapter<mutex> 作为基类，所以它具有了和mutex相同的接口，可以像使用一个互斥量那样使用它：
//	*/
//	account a;
//	{
//		auto g = make_unique_lock(a);
//		a.deposit(100);
//		a.withdraw(20);
//		assert(a.sum() == 80);
//	}
//	{
//		auto b = make_unique_lock(a, try_to_lock);
//		if (b)
//		{
//			a.withdraw(a.sum());
//			assert(a.sum() == 0);
//		}
//	}
//}

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