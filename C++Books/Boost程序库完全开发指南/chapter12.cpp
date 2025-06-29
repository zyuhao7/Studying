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

// ��ʮ����-�������
// day-2025-6-29
// thread
/*
										mutex
	��������mutex����һ�������߳�ͬ�����ֶΣ��������ڶ��̻߳������ֹ����߳�ͬʱ����������Դ��
	һ��һ���߳������˻���������ô�����̱߳���ȴ�����������������ܷ��ʹ�����Դ��
	thread�ṩ��6�ֻ���������:
	�� null_mutex�����κ��������ܵĻ����������ǿն���ģʽ��Ӧ�á�
	�� mutex����ռʽ�Ļ�����������򵥡���õĻ��������͡�
	�� timed_mutex����ռʽ�Ļ����������ṩ��ʱ�������ܡ�
	�� recursive_mutex���ݹ�ʽ�����������Զ����������Ӧ��Ҳ��Ҫ��ν�����
	�� recursive_timed_mutex���ݹ�ʽ��������ͬ�������˳�ʱ�������ܡ�
	�� shared_mutex��multiple-reader/single-writer�͵Ĺ�������(�ֳƶ�д��).
*/

// ��ժҪ
//class Mutex : public boost::noncopyable
//{
//public:
//	void lock();
//	void unlock();
//
//	bool try_lock();
//
//	bool try_lock_for(const  booost::chrono::duration & rel_time); // ��ʱ��������
//	bool try_lock_until(const boost::chrono::time_point& t);
//
//	some_type native_handle(); // ϵͳ��ص� handle
//};

//int main()
//{
//	mutex mtx;
//	try
//	{
//		mtx.lock();
//		std::cout << "some operations" << std::endl; // ����������Դ
//		mtx.unlock();
//	}
//	catch (const std::exception&)
//	{
//		mtx.unlock();
//	}
//	timed_mutex t_mtx;
//	bool b = t_mtx.try_lock_for(boost::chrono::milliseconds(100));
//	if (b) {
//		std::cout << "�ɹ���ȡ��" << std::endl;
//		t_mtx.unlock();
//	}
//	else {
//		std::cout << "��ȡ����ʱ" << std::endl;
//	}
//}

//lock_guard
/*
	thread���ṩ RAII�͵� lock_guard �����ڸ������������������ڹ���ʱ������������������ʱ�Զ�������
	�Ӷ���֤�˻���������ȷ��������������������������һ������ָ��.
*/

//template<typename Mutex>
//class Lock_guard : boost::noncopyable
//{
//private:
//	Mutex& m;
//
//public:
//	explicit Lock_guard(Mutex& m_);			    //�������� mutex
//	/*
//		lock_guard �ĵڶ�����ʽ�Ĺ��캯��ͨ����� timed_mutex ʹ�ã���������һ����־��������Ϊ adopt_lock_t ��Ԥ���峣��adopt_lock��
//		��ʱ lock_guard ��Ϊ�߳��Ѿ���ǰ��ĳ�ֲ��������� mutex��������ִ������������������ʱ��Ȼ�������
//	*/
//	Lock_guard(Mutex& m_, boost::adopt_lock_t); //��ִ�������������
//	~Lock_guard();								//�����ͷ� mutex
//};

// thread�⻹�ṩһ����ݺ��� with_lock_guard()��������ʹ�� lock_guard ����������ִ��һ����������lock_guard�ĵ��ã�����������:
//template<class Lockable, class Function, class... Args>
//auto with_lock_guard(Lockable& m, Function&& func, Args&&... args);

// with_lock_guard �൱��
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
//		lock_guard<timed_mutex> g(mu, adopt_lock); //�����ٴμ���
//		std::cout << "lock timed mutex" << std::endl;
//	}   // �Զ��ͷ���
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
//	Unique_lock(Mutex& m);	//����������
//	Unique_lock(Mutex& m, boost::adopt_lock_t); //������������, �������
//	Unique_lock(Mutex& m, boost::defer_lock_t); //������������
//	Unique_lock(Mutex& m, boost::try_to_lock_t);//��������������
//
//	Unique_lock(Mutex& m, const boost::chrono::time_point& t); // ��ʱ����
//	Unique_lock(Mutex& m, const boost::chrono::duration& t);   // ��ʱ����
//
//	void lock();
//	void unlock();
//	bool try_lock();
//	bool try_lock_for(const boost::chrono::duration& d);
//	bool try_lock_until(const boost::chrono::time_point& t);
//
//	bool owns_lock() const;  // �Ƿ������˻�����
//	explicit operator bool() const; // �ȼ��� owns_lock
//
//	Mutex* mutex() const noexcept; // ��������Ļ�����
//	Mutex* release();			   // ���ٹ�������
//};

// ����ѡ��
// thread������3������ѡ����Ƕ��ǿ��࣬����Ϊ����ʱ�ı�־������û����������
//struct defer_lock_t{};   //��ִ����������
//struct try_to_lock_t{};  // ִ�� try_lock
//struct adopt_lock_t {};  // ������, ��������Ȩ
//
//constexpr defer_lock_t defer_lock = {}; //������������־
//constexpr try_to_lock_t try_to_lock = {}; //������������־
//constexpr adopt_lock_t adopt_lock = {}; //������������־

// ��Ϊunique_lock֧��ת������,���������Դӹ�����������,����ģ�庯���Զ��Ƶ����͵����Կ��Բ���д��ģ�����,���һ�����˱�д����Ĺ���.
//��Щ������������������:
// ���ֲ�ͬ�Ĺ���������Ӧ��ͬ�Ĺ��캯��:
//unique_lock<Lockable> make_unique_lock(Lockable& mtx);
//unique_lock<Lockable> make_unique_lock(Lockable& mtx, adopt_lock_t);
//unique_lock<Lockable> make_unique_lock(Lockable& mtx, defer_lock_t);
//unique_lock<Lockable> make_unique_lock(Lockable& mtx, try_to_lock_t);

// һ���Բ������ unique_lock, �� std::tuple ����
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
//		auto g = make_unique_lock(mtx, defer_lock); // �ݲ�����������
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
	lock_guard �� unique_lock ������������Ҫ���� mutex ʹ�ã���������������������Ϊ������ģ���࣬
	����ֻҪ�Ƿ��� "Lockable" �����Ҳ������lock/unlock/try_lock�ӿڵ���(��һ���ǻ�����),
	���������� lock_guard �� unique_lock���������ܹ������׵�������������ʵ��ԭ���Ե����������

	thread�ⶨ���˼���lockable�������࣬��������ʵ��Lockable����:
	�� basic_lockable_adapter����򵥵Ľӿڣ��ṩlock/unlock��
	�� lockable_adapter�������Ľӿڣ����� try_lock ���ܡ�
	�� timed_lockable_adapter������try_lock_for/try_lock_until��
*/
//��Щ��������������:
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

// �������Ƕ���һ���򵥵Ĵ����˻��࣬��ʹ��atomic<int>��¼�����������Ϳ��Ա�֤���ʽ��׵�ԭ���ԣ�
// �����Ҫ��֤��ʽ���Ҳ����ԭ���ԣ������ʹ�û�����:
//class account final : public lockable_adapter<mutex>
//{
//private:
//	atomic<int> money{ 0 };
//public:
//	int sum() const
//	{
//		return money;
//	}
//	void withdraw(int x) // ȡ��
//	{
//		money -= x;
//	}
//	void deposit(int x) // ���
//	{
//		money += x;
//	}
//};

//int main()
//{
//	/*
//		account��ʹ��lockable_adapter<mutex> ��Ϊ���࣬�����������˺�mutex��ͬ�Ľӿڣ�������ʹ��һ������������ʹ������
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
// atomic�ⶨ���˻���ģ����atomic<T>����򻯵���ժҪ����:

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
//	bool is_lock_free(); //�Ƿ�����
//	void store(T v);    //��ֵ
//	T load();			//ȡֵ
//	
//	T operator=(T v) volatile; //��ֵ, ����� store
//	operator T() volatile const; //��ʽ����ת��, �൱�� load
//
//	T exchange(T new_value); // ��ֵ, Ȼ�󷵻�ԭֵ
//	bool comare_exchange_weak(T& expected, T desired);  
//	bool comare_exchange_strong(T& expected, T desired);  
//
//	T& storage();	//��ȡ�ڲ���ֵ
//	T const& storage() const;
//};
//
//// atomic<T> ������������ͺ�ָ�����ͽ������ػ���������һЩ����Ĳ���:
//template<>
//class Atomic<int>
//{
//public:
//	//... ͬ Atomic<T>
//public:
//	int fetch_add(int i); // �ӷ�, ����ԭֵ
//	int fetch_sub(int i); // ����, ����ԭֵ
//	int fetch_and(int i); // &, ����ԭֵ
//	int fetch_or(int i); // |, ����ԭֵ
//	int fetch_xor(int i); // ^, ����ԭֵ
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
//	T* fecth_add(ptrdiff_t v); // ָ���ƫ��, ����ԭֵ
//	T* fecth_sub(ptrdiff_t v);
//
//};

//enum Memory_order
//{
//	memory_order_relaxed = 0, // �����κ�˳��Ҫ��
//	memory_order_consume = 1,
//	memory_order_acquire = 2,
//	memory_order_release = 4,
//	memory_order_acq_rel = 6, // acquire | release
//
//	memory_order_seq_cst = 14 // acq_rel | 8   ˳��һ����Լ��
//};

// ����Ĵ���ʹ��atomic ���ǡ�����ڴ����˳��ʵ����һ����Ч�����ü��������� ref_count:
//template<typename T>
//class Ref_count
//{	
//private:
//	typedef boost::atomic<int> atomic_type; // ���� atomic ����
//	mutable atomic_type m_count{ 0 };
//
//protected:
//	Ref_count(){}
//	~Ref_count() {}
//public:
//	typedef boost::intrusive_ptr<T> counted_ptr; // ���� intrusive_ptr
//	
//	void add_ref() const
//	{
//		m_count.fetch_add(
//			1, boost::memory_order_relaxed); // �����κ�˳��Ҫ��
//	}
//
//	void sub_ref() const
//	{
//		if (m_count.fetch_sub(
//			1, boost::memory_order_release) == 1)
//		{
//			boost::atomic_thread_fence(      // ԭ�Ӽ�����̱߳���
//				boost::memory_order_acquire); 
//			delete static_cast<const T*>(this); // ɾ��ָ��, ��Ҫת��
//		}
//	}
//
//	decltype(m_count.load()) count() const
//	{
//		return m_count.load();
//	}
//
//public:
//	template<typename... Args>	// �ɱ����ģ��
//	static counted_ptr make_ptr(Args&& ... args) // ��������
//	{
//		return counted_ptr(new T(std::forward<Args>(args)...));
//	}
//
//private:
//	friend void intrusive_ptr_add_ref(const T* p) // intrusive_ptr Ҫ����
//	{
//		p->add_ref();
//	}
//	friend void intrusive_ptr_release(const T* p) // intrusive_ptr Ҫ����
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
	//assert(n == 200); // ��ʽ����ת��, ���� load
//}