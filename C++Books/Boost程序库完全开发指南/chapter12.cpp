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
#include <stack>
using namespace boost;
// ��ʮ����-�������

// day-2025-7-2
// future
/*
	�ܶ�����£��̲߳���Ҫִ��һЩ�����������ܻ᷵��һЩ��������thread��ʹ��future��ʽ�ṩ���첽�����̷߳���ֵ�ķ�����
	��Ϊ�������ֵ���߳̿�ʼִ��ʱ�ǲ����õģ��÷���ֵ��һ����δ�����ġ��ڴ�ֵ��������������Ϊfuture���ڻ�����
*/
// future �����洢�첽����õ���ֵ, ��ֻ�ܳ��н����Ψһ��һ�����ã� ��ժҪ:
//enum class Future_status
//{
//	ready,
//	timeout,
//	deferred
//};
//
//template<typename T>
//class Future
//{
//public:
//	T get();				//��ȡ future��ֵ.
//	void wait() const;     // �ȴ��߳���ɼ���
//	Future_status wait_for(const boost::chrono::duration& rel_time) const;
//	Future_status wait_until(const boost::chrono::time_point& abs_time) const;
//
//	bool valid() const;	   // �Ƿ�Ϊ��Чֵ
//
//	bool is_ready() const; // �Ƿ���ɼ���
//	bool has_exception() const; // �Ƿ����쳣
//	bool has_value() const;
//
//	shared_future share();  //����һ�� shared_future ����
//};

// async
/*
	async() �������ڲ��� future �������첽����һ���߳����к��������� future ��������������ǾͿ�������future��ȡ��������
*/
//enum class Lanch {
//	none = 0,					// ��Ϊδ����
//	async = 1,					// ���������߳�
//	defferred = 2,			    // ֮����Ҫʱ�������߳�
//	any = async | defferred     // ��������Ҫʱ�����߳�
//};
//
//future async(Function&& f, Args&&... args); //Ĭ�ϲ����� any
//future async(launch policy, Function&& f, Args&&... args);

//void dummy(int n)
//{
//	for (int i = 0; i < n; ++i)
//	{
//		std::cout << n << std::endl;
//	}
//}
//
//int main()
//{
	//async(bind(dummy, 10));

	//auto f = boost::async([] {std::cout << "hello" << std::endl;}); //�߳����� lambda���ʽ.
	//f.wait();

	// ����Ĵ����൱��:
	//thread(dummy, 10).detach();
	//thread t([] {std::cout << "hello" << std::endl;});
	//t.join();

	//return 0;
//}
 
// future �� async ��ͬ���� 쳲��������� 
int fib(int n)
{
	if (n <= 1) return n;
	return fib(n - 1) + fib(n - 2);
}
//
//int main()
//{
//	auto f5 = async(fib, 5);				// ���� fib(5) ʱ����ȷ��
//	auto f7 = async(launch::async, fib, 7); // �������� fib(7)
//
//	std::cout << f5.get() + f7.get() << std::endl;
//	assert(!f5.valid() && !f7.valid());
//
//	auto f10 = async(fib, 10);
//	auto s = f10.wait_for(boost::chrono::microseconds(100));
//	if (f10.valid())
//	{
//		assert(s == future_status::ready);
//		std::cout << f10.get() << std::endl;
//	}
//}

//int main()
//{
//	std::vector<boost::future<int>> vec;
//	for (int i = 0; i < 5; ++i)
//	{
//		vec.push_back(async(fib, i + 11));
//	}
	//wait_for_all(vec.begin(), vec.end());
	//for (auto& x : vec)
	//{
	//	std::cout << x.get() << " ";
	//}

//	wait_for_any(vec[3], vec[4], vec[2]);
//	for (auto& x : vec)
//	{
//		if (x.valid())
//		{
//			std::cout << x.get() << std::endl;
//		}
//	}
//}

// shared_future
// ��ժҪ
//template<typename T>
//class Shared_future
//{
//public:
//	T get();				//��ȡ future��ֵ.
//	void wait() const;     // �ȴ��߳���ɼ���
//	Future_status wait_for(const boost::chrono::duration& rel_time) const;
//	Future_status wait_until(const boost::chrono::time_point& abs_time) const;
//
//	bool valid() const;	   // �Ƿ�Ϊ��Чֵ
//
//	bool is_ready() const; // �Ƿ���ɼ���
//	bool has_exception() const; // �Ƿ����쳣
//	bool has_value() const;
//};

//int main()
//{
//	// async() �������Է��� shared_future ���󣬵���Ҫ������ȷ����������:
//	shared_future<int> f5 = async(fib, 5);
//
//	//future ��share() ����Ҳ���Բ��� shared_future ���������Ϳ�������auto���Զ��Ƶ����ͣ���������д���鷳.
//	auto f6 = async(fib, 6).share();	//ʹ�ù�������
//	auto func = [](decltype(f5) f) {
//		std::cout << "[" << f.get() << "]";
//		};
//	async(func, f5);
//	async(func, f6);
//
//	this_thread::sleep_for(boost::chrono::microseconds(100));
//	assert(f5.valid());
//
//}

// �߼�����
// 1.����lock()
//int main()
//{
//	mutex m1, m2;
//	{
//		auto g1 = make_unique_lock(m1, adopt_lock);
//		auto g2 = make_unique_lock(m2, adopt_lock);
//		lock(m1, m2);		//�������� mutex
//	}
//	{
//		auto g1 = make_unique_lock(m1, defer_lock);
//		auto g2 = make_unique_lock(m2, defer_lock);
//		try_lock(g1, g2);   // ��������unique_lock
//	}
//}

// 2.promise
/*
	promise�� future ���ڲ�ʵ�֣�Ҳ���ڴ����첽���÷���ֵ��������Ҫ��� thread ʹ�ã�������Ϊ������������������÷�������
	promise ��Ҫ���߳����� set_value() ����Ҫ���ص�ֵ���ó�Ա���� get_future() ����future����
*/

//int main()
//{
//	auto func = [](int n, promise<int>& p) { // ʹ�� promise��Ϊ�������
//		p.set_value(fib(n));
//		};
//	promise<int> p;
//	thread(func, 10, boost::ref(p)).detach();
//	auto f = p.get_future();
//	std::cout << f.get() << std::endl;
//}

//3. barrier
/*
	barrier�� thread ��������������ṩ����һ��ͬ�����ƣ������ڶ���߳�ͬ�������߳�ִ�е� barrier ʱ����ȴ���
	ֱ�����е��̶߳����������ʱ���ܼ���ִ���̡߳�barrier ����һ������rendezvous��Լ��ص㣩�������������������Ϊ.
*/

//int main()
//{
//	atomic<int> x;
//	barrier br(5); // 5���̵߳� barrier
//
//	auto func = [&]() {
//		std::cout << "thread: " << ++x << "arrived barrier! " << std::endl;
//		br.wait();		//�� barrier���ȴ�, ����ȵ�����̶߳�����������ܼ���ִ��.
//		std::cout << "thread run." << std::endl;
//		};
//
//	thread_group tg;
//	for (int i = 0; i < 5; ++i) tg.create_thread(func);
//	tg.join_all();
//}

// 4.�̱߳��ش洢
/*
	��ʱ����ʹ���� �ֲ���̬���� �� ȫ�־�̬�������������ڶ��̻߳�������Ϊ�޷���֤��̬�����ڶ��̻߳���������ʱ����ȷ������
	C++�������µĹؼ���thread_local���� thread�� ʹ�� thread_specific_ptr ʵ���˿���ֲ���̱߳��ش洢����(thread local storage����thread specific storage�����tss)
	ʹ�����ı���������������ÿ���̶߳���ӵ�еģ��Ӷ��򻯶��߳�Ӧ��.
	thread_specific_ptr��һ������ָ�룬������Ľӿ���shared_ptr���ƣ���������operator*�� operator->,
	������ get() �����ʵ��ָ�룬��Ҳ��reset() ��release() ����.
	thread_specific_ptr �ĳ�ʼֵͨ���ǿ�ָ�루nullptr���������Ҫʹ��get() �����м��.
	thread_specific_ptr û�ж�����ʽ��boolת�������Բ���ֱ����bool�ﾳ�м���Ƿ�Ϊ��.

*/

//int main()
//{
//	thread_specific_ptr<int> pi; // �̱߳��ش洢һ������
//	auto func = [&] {
//		pi.reset(new int());
//		++(*pi);
//		std::cout << "thread v = " << *pi << std::endl;
//		};
//	async(func);
//	async(func);
//
//	this_thread::sleep_for(boost::chrono::microseconds(100));
//}
// 
// 5.�߳̽���ʱִ�в���

/*
	this_thread���ֿռ��ṩ��һ��at_thread_exit��func���������������Ǽǡ�һ���߳��ڽ�����ʱ��ִ�пɵ�����func�������߳��Ƿ��жϡ�
*/
//void end_msg(const std::string& msg)
//{
//	std::cout << msg << std::endl;
//}
//void printing()
//{
//	this_thread::at_thread_exit(bind(end_msg, "end"));
//}


// day-2025-7-1
// condition_variable
/*
	������������һ�����ڵȴ���ͬ�����ƣ�������ʵ���̼߳��ͨ�ţ��������뻥�������ʹ�ã�
	�ȴ���һ���߳���ĳ���¼�����������ĳ����������Ȼ���̲߳��ܼ���ִ�С�
*/
// ��ժҪ
//enum class Cv_status {  // names for wait returns
//	no_timeout,
//	timeout
//};
//
//class Condition_variable_any
//{
//public:
//	void notify_one();				// ֪ͨһ���ȴ��е��߳�
//	void notify_all();				// ֪ͨ���еȴ��е��߳�
//
//	
//	template<typename lock_type>
//	void wait(lock_type& m);		// �ȴ�
//	template<typename lock_type, typename predicate_type>
//	void wait(lock_type& m, predicate_type pred);			// �ȴ�����
//
//	template<typename lock_type>
//	Cv_status wait_for(										// �ȴ����ʱ��
//		lock_type& lock, const boost::chrono::duration& d);
//	template<typename lock_type, typename predicate_type>
//	Cv_status wait_for(										// �����ȴ����ʱ��
//		lock_type& lock, const boost::chrono::duration& d, predicate_type pred);
//
//	template<typename lock_type>
//	Cv_status wait_until(									// �ȴ�����ʱ���
//		lock_type& lock, const boost::chrono::time_point& t);  
//	template<typename lock_type, typename predicate_type>
//	Cv_status wait_until(									// �����ȴ�����ʱ���
//		lock_type& lock, const boost::chrono::time_point& t, predicate_type pred);
//};

/*
* ����ʹ�ñ�׼������������� stack ��ʵ��һ������������ - ������ģʽ�ĺ���ȳ��ͻ�����:
* ������bufferʹ����������������cond_put ��cond_get���ֱ����ڴ���put������get������
* �������������cond_put�����ȴ�����cond_put�õ�֪ͨ��������������ʱ�߳�д�����ݣ�
* Ȼ��֪ͨ cond_get �����������Զ�ȡ���ݡ�cond_get �Ĵ���������cond_put���ƣ�����������£�
*/ 

//class Buffer
//{
//private:
//	mutex mtx;
//	condition_variable_any cond_put;
//	condition_variable_any cond_get;
//
//	std::stack<int> st;
//	int un_read, capacity;
//
//	bool is_full() { return un_read == capacity; }
//	bool is_empty() { return un_read == 0; }
//public:
//	Buffer(size_t n)
//		: un_read(0),
//		capacity(n)
//	{
//	}
//	void put(int x)
//	{
//		{
//			auto lock = make_unique_lock(mtx);  //����������
//			while(is_full())
//			{
//				std::cout << "full_wait..." << std::endl;
//				cond_put.wait(lock);
//			}
//			st.push(x);
//			un_read++;
//		}
//		cond_get.notify_one();
//	}
//
//	void get(int* x)
//	{
//		{
//			auto lock = make_unique_lock(mtx);
//			while (is_empty())
//			{
//				std::cout << "empty_wait..." << std::endl;
//				cond_get.wait(lock);
//			}
//			*x = st.top();
//			st.pop();
//			un_read--;
//		}
//		cond_put.notify_one();
//	}
//};
//
//
//Buffer buf(5);
//void producer(int n)
//{
//	for (int i = 0; i < n; ++i)
//	{
//		std::cout << "put " << i << std::endl;
//		buf.put(i);
//	}
//}
//
//
//void consumer(int n)
//{
//	int x;
//	for (int i = 0; i < n; ++i)
//	{
//		buf.get(&x);
//
//		std::cout << "get " << x << std::endl;
//	}
//}
//
//int main()
//{
//	thread_group tg;
//	tg.create_thread(bind(producer, 20));
//	tg.create_thread(bind(consumer, 10));
//	tg.create_thread(bind(consumer, 10));
//
//	tg.join_all();
//}

// shared_mutex
/*
* ��������shared_mutex��ͬ��mutex��recursive_mutex���������̻߳�ȡ�����������Ȩ��һ��ר������Ȩ��
* ʵ���˶�д���Ļ��ƣ���������߳�һ��д�̡߳�
*/

//class Shared_mutex
//{
//public:
//	Shared_mutex();
//	~Shared_mutex();
//
//	void lock();
//	bool try_lock();
//	void unlock();
//
//	bool try_lock_for(const boost::chrono::duration& rel_time);
//	bool try_lock_until(const boost::chrono::time_point& abs_time);
//
//	// shared_mutex ר�еĺ���
//	bool lock_shared();
//	bool try_lock_shared();
//	void unlock_shared();
//
//	bool try_lock_shared_for(const boost::chrono::duration& rel_time);
//	bool try_lock_shared_until(const boost::chrono::time_point& abs_time);
//};

//class rw_data
//{
//private:
//	int m_x;
//	shared_mutex rw_mtx;
//
//public:
//	rw_data()
//		:m_x(0)
//	{}
//
//	void write()
//	{
//		unique_lock<shared_mutex> g(rw_mtx);
//		++m_x;
//	}
//	void read(int* x)
//	{
//		shared_lock<shared_mutex> g(rw_mtx);
//		*x = m_x;
//	}
//};
//
//void writer(rw_data& d)
//{
//	for (int i = 0; i < 20; ++i)
//	{
//		this_thread::sleep_for(boost::chrono::milliseconds(3));
//		d.write();
//	}
//}
//
//void reader(rw_data& d)
//{
//	int x;
//	for (int i = 0; i < 10; ++i)
//	{
//		this_thread::sleep_for(boost::chrono::milliseconds(5));
//		d.read(&x);
//		std::cout << "reader: " << x << std::endl;
//	}
//}
//
//int main()
//{
//	rw_data d;
//	thread_group pool;
//
//	pool.create_thread(bind(writer, ref(d)));
//	pool.create_thread(bind(writer, ref(d)));
//
//
//	pool.create_thread(bind(reader, ref(d)));
//	pool.create_thread(bind(reader, ref(d)));
//	pool.create_thread(bind(reader, ref(d)));
//	pool.create_thread(bind(reader, ref(d)));
//
//	pool.join_all();
//}

// day-2025-6-30
// thread
// ժҪ:
//class Thread
//{
//public:
//	Thread();	
//	explicit Thread(F f);					// ���ݿɵ��ö���
//	Thread(F f, A1 a1, A2 a2, ...);		    // ���ݿɵ��ö��������
//
//	Thread(Thread&&) noexcept;				// �ƶ����캯��
//	Thread& operator=(Thread&&) noexcept;   // �ƶ���ֵ����
//
//	bool joinable() const;					// �Ƿ� join
//	void join();							// �ȴ��߳�
//
//	void detach();							// �����߳�
//
//	bool try_join_for(const boost::chrono::duration& rel_time); // ��ʱ�ȴ�
//	bool try_join_until(const boost::chrono::time_point& t);    // ��ʱ�ȴ�
//
//	void interrupt();	//�ж��߳�
//	bool interruption_requested() const; //�Ƿ��ж�
//	
//	class id;			// �ڲ����߳� id
//	id get_id() const;  // ����߳� id ����
//	native_handle_type native_handle(); //���ϵͳ��صĲ��� handle
//
//	static unsigned hardware_concurrency();	// ��ȡ�ɲ����ĺ�����
//	static unsigned physical_concurrency();	// ��ȡ��ʵ CPU ������
//};
//
//namespace This_thread
//{
//	Thread::id get_id();
//	void yield();										  // �����ص����߳�
//	void sleep_until(const boost::chrono::time_point& t);
//	void sleep_for(const boost::chrono::duration& d);
//}

//void dummy(int n)
//{
//	for (int i = 0; i < n; ++i)
//	{
//		std::cout << n << std::endl;
//	}
//}

//int main()
//{

	//thread t1, t2;
	//std::cout << t1.get_id() << std::endl; // {Not-any-thread}
	//assert(t1.get_id() == t2.get_id());

	//std::cout << thread::hardware_concurrency() << std::endl; // 16
	//std::cout << thread::physical_concurrency() << std::endl; // 8

	//this_thread::sleep_for(boost::chrono::milliseconds(2));
	//std::cout << this_thread::get_id(); // 6adc
	//this_thread::yield();

	//thread t1(dummy, 100);
	//thread t2([] {dummy(500);});

	//t1.try_join_for(boost::chrono::milliseconds(100));  //���ȴ� 100ms �󷵻�
	//t2.join();											//�ȴ� t2 �߳̽������ٷ���, ���� t2 �߳�ִ�ж���ʱ��

	//thread t3(dummy, 300);
	//t3.detach();
	//assert(!t3.joinable());
	// ��ʱ����
	//thread(dummy, 100).detach();
	//this_thread::sleep_for(boost::chrono::milliseconds(2));
//}

// thread_guard

//struct detach;			 //����ʱִ�� detach
//struct join_if_joinable;   // ����ʱִ�� join
//template<class CallableThread = join_if_joinable>
//class Thread_guard
//{
//	thread& _t;
//public:
//	explicit Thread_guard(thread& t);
//	~Thread_guard();
//};

//void dummy(int n)
//{
//	for (int i = 0; i < n; ++i)
//	{
//		std::cout << n << std::endl;
//	}
//}
//
//int main()
//{
//	thread t1(dummy, 200);
//	thread t2(dummy, 300);
//
//	thread_guard<boost::detach> g1(t1);	// �������̼߳�������
//	thread_guard<> g2(t2);				// ����ʱ�ȴ��߳̽���
//}

// scoped_thread
//template<class CallableThread = join_if_joinable>
//class Scoped_thread
//{};
//
//void dummy(int n)
//{
//	for (int i = 0; i < n; ++i)
//	{
//		std::cout << n << std::endl;
//	}
//}
//
//int main()
//{
//	scoped_thread<boost::detach> t1(dummy, 100); // �������̼߳�������
//	scoped_thread<> t2(dummy, 200);				 // ����ʱ�ȴ��߳̽���
//}

//void to_interrupt(int x)
//{
//	try
//	{
//		for (int i = 0; i < x; ++i)
//		{
//			this_thread::sleep_for(boost::chrono::microseconds(400));
//			std::cout << i << std::endl;
//		}
//	}
//	catch (const boost::thread_interrupted&)
//	{
//		std::cout << "thread_interrupted " << std::endl;
//	}
//}
//
//int main()
//{
//	thread t(to_interrupt, 10);
//	//this_thread::sleep_for(boost::chrono::milliseconds(10));
//
//	t.interrupt();
//	assert(t.interruption_requested());
//
//	t.join();
//}

// �߳���
//class Thread_group
//{
//public:
//	thread* create_thread(F threadfunc); // �������߳�
//	void add_thread(thread* thrd);		 // ��������߳�
//	void remove_thread(thread* thrd);    // ɾ���߳�
//
//	bool is_this_thread_in();			 // ��ǰ�߳��Ƿ�������
//	bool is_thread_in(thread* thrd);	 // ָ���߳��Ƿ�������
//
//	void join_all();					 // �ȴ������߳�
//	void interrupt_all();				 // �ж������߳�
//
//	int size() const;					 // ��ȡ�߳�����
//};

//int main()
//{
//	thread_group tg;
//
//	tg.create_thread(bind(dummy, 100));
//	tg.create_thread(bind(dummy, 200));
//
//	tg.join_all();
//}

// call_once
/*
		Ϊ�˱�֤��ʼ�������ڶ��̻߳����б���ȷ���ã�thread ���ṩ�˽�����һ�εĻ��� call_once��
		ʹ����߳��ڲ�������ʱֻ����һ���̳߳ɹ�ִ�У�������ִ���̵߳��´���
		�������������Ҫʹ��һ��once_flag ����,������Ϊ��ʼ���ı�־��Ȼ��ʹ�� call_once() �����ú�������ɽ�ִ��һ���̵߳ĳ�ʼ����
*/

// call_once() ��������������:
//template<class Callable, class ...Args>
//void call_once(once_flag& flag, Callable&& func, Args&&... args);
//// �������������µ�ȫ�ֱ�����һ����ʼ������:
//
//int g_count;
//void init_count(int x)
//{
//	std::cout << "should call once~" << std::endl;
//	g_count = x;
//}
//
//void call_func()
//{
//	static once_flag once;			 // һ�γ�ʼ����־
//	call_once(once, init_count, 10); // ִ��һ�γ�ʼ��
//}
//
//int main()
//{
//	((scoped_thread<>(call_func)));
//	((scoped_thread<>(call_func)));
//}


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