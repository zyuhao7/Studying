#include <iostream>
#include <utility>
#include <boost/atomic.hpp>
#include <boost/memory_order.hpp>
#include <boost/smart_ptr/intrusive_ptr.hpp>

using namespace boost;

// ��ʮ����-�������
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