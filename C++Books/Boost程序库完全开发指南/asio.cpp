#define BOOST_THREAD_VERSION 5
#define BOOST_ASIO_ENABLE_HANDLER_TRACKINIG // ׷����־
#include <iostream>
#include <utility>
#include <boost/atomic.hpp>
#include <boost/memory_order.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/smart_ptr/intrusive_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/lock_factories.hpp>
#include <boost/thread/lockable_adapter.hpp>
#include <boost/thread/thread_guard.hpp>
#include <boost/thread/scoped_thread.hpp>
#include <boost/thread/shared_lock_guard.hpp>
#include <boost/noncopyable.hpp>
#include <boost/chrono.hpp>
#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/system_timer.hpp>
#include <boost/asio/high_resolution_timer.hpp>
#include <ctime>
#include <stack>
using namespace boost::asio;
using namespace boost::chrono;
using namespace std;

// day-2025-7-4
// ��ʱ��
/*
	���첽IO���ʱ����һ���ǳ���Ҫ�Ĺ��ܣ���������ָ��ʱ�̵��ú�����ʵ���첽����.
	asio���ṩ4����ʱ�����ֱ��� deadline_timer��steady_timer��system_timer �� high_resolution_timer��
	��ժҪ:

	template<typename Clock>
	class basic_waitable_timer
	{
	public:
		typedef Clock clock_type;
		typedef typename clock_type::duration duration;
		typedef typename clock_type::time_point time_point;

		explicit basic_waitable_timer(io_service& ioc);
		basic_waitable_timer(io_service&, const time_point& expiry_time);
		basic_waitable_timer(io_service&, const duration& expiry_time);

		time_point expires_at() const;			// ��ù���ʱ���
		std::size_t expires_at(const time_point& expiry_time);

		duration expires_from_now() const; //��ù���ʱ�䳤��
		std::size_t expires_from_now(const duration& expiry_time) const; //��ù���ʱ�䳤��

		void wait();	//ͬ���ȴ�
		void async_wait(WaitHandler handler); // �첽�ȴ�

		std::size_t cancel();
		std::size_t cancel_one();
	};

	steady_timer��system_timer �� high_resolution_timer �� basic_waitable_timer ��ģ���ػ�typedef��

	typedef basic_waitable_timer<steady_clock> steady_timer;
	typedef basic_waitable_timer<system_clock> steady_timer;
	typedef basic_waitable_timer<high_resolution_clock> high_resolution_timer;

	��ʱ����3����ʽ�Ĺ��캯������ͬsignal_setһ��Ҫ�������һ��io_service���������ύIO����.
	�ڶ��������Ƕ�ʱ������ֹʱ�䣬�����Ǿ���ʱ����������ڵ�ǰʱ����һ��ʱ�䳤��.
	һ����ʱ�����󱻴��������ͻ�������ʼ��ʱ������ʹ�ó�Ա����wait() ��ͬ���ȴ���ʱ����ֹ,
	����ʹ��async_wait() �첽�ȴ���ʱ����ֹ������ʱ����ֹʱ����� handler ����

	2.ͬ����ʱ��

	int main()
	{
		io_service ioc;
		steady_timer t(ioc, milliseconds(500));
		cout << t.expires_at() << endl;	// �鿴��ֹ��ʱ���
		cout << t.expires_from_now() << endl;	//�鿴��ֹ��ʱ�䳤��
		t.wait();

	}

	���߿��԰�����������thread���sleep() �����Ա��о�һ�£���Ȼ���߶��ǵȴ��������ǵ��ڲ�������ȫ��ͬ:
	thread���sleep() ʹ���˻��������������������߳��еȴ�����asio������˲���ϵͳ���첽���ƣ���epoll��kqueue�ȣ�û�ж��̵߳ľ�����

	3.�첽��ʱ��
	�����������첽��ʱ�����������ͬ����ʱ���Ĵ��������ͬ�����첽��ʱ��ʹ��async_wait() ���������˻ص�������
	int main()
	{
		io_service ioc;
		steady_timer t(ioc, milliseconds(500));
		t.async_wait([](const error_code& ec) {
			cout << "hello world" << endl;
			});
		ioc.run();
	}
	����ʱ��ʱ�䵽��ֹʱ, io_service�����ñ�ע��� lambda ���������һ����Ϣ��Ȼ��������

	4.ʹ��bind
	��ʱ���ǳ����ã����ǿ����������ӻص������Ĳ�����ʹ���ܹ�����������顣��Ȼasync_wait() ���յĻص����������ǹ̶��ģ�
	������ʹ�� bind ���ռλ�� placeholders::error ���󶨲��������� bind �Ľӿ�:

	class timer_with_func
	{
	private:
		int m_count = 0;
		int m_count_Max = 0;
		function<void()> m_func;
		steady_timer m_t;

	public:
		template<typename F>
		timer_with_func(io_service& ioc, int x, F func)
			:m_count(x),
			m_func(func),
			m_t(ioc, milliseconds(200)
		{
			init();
		}

	private:
		typedef timer_with_func this_type;

		void init()
		{
			m_t.async_wait(bind(&this_type::handler, this,
				boost::asio::placeholders::error));
		}

		void handler()
		{
			if(m_count++ >= m_count_Max) return;
			m_func();

			m_t.expires_from_now(200_ms);
			m_t.async_wait(bind(&this_type::handler, this, boost::asio::placeholders::error));
		}
	};

	5.ʹ��lambda
	bind ���ʽ�Ľⷨ��ͨ�ã���bind���ʽ����ռλ�� placeholders::error ���԰�����ĺ������Ա��������Ϊ asio Ҫ��� handler��
	�� bind ��д�������鷳�����ҵ������Ƚ϶�ʱ�����Ķ���


	 ����ͨ��
	 �� ip::tcp ��asio����ͨ�ţ�TCP��������Ҫ���࣬��ʾTCPЭ��.

	 1.address

	ip::address addr;

	addr = addr.from_string("127.0.0.1");
	assert(addr.is_v4());
	cout << addr.to_string() << endl;
	cout << typeid(addr).name() << endl;

	addr = addr.from_string("ab::12:34:56");
	assert(addr.is_v6());

	2.endpoint
	����IP ��ַ���ټ���ͨ���õĶ˿ںž͹�����һ�� socket �˵㣬��asio������ ip::tcp::endpoint ����ʾ��

	int main()
	{
		ip::address addr;
		addr = addr.from_string("127.0.0.1");

		ip::tcp::endpoint ep(addr, 6680);
		assert(ep.address() == addr);
		assert(ep.port() == 6680);
	}

	3. socket
	socket �����ڹ���ʱ��ָ��ʹ�õ�Э��� endpoint�������Ժ���ó�Ա����connect() 

	socket ��д�����Ĳ�������buffer ���ͣ�������buffer() ������װ�����������䣬��������send() /write_some() �Ĳ���Ӧ����һ���ɶ�buffer��
	��receive() /read_some() Ҫ������ǿ�дbuffer��

	4.acceptor
	acceptor���ӦSocket API��accept() �������ܣ������ڷ������ˣ���ָ���Ķ˿ںŽ������ӣ�acceptor�������socket��������ͨ��

	 ͬ��ͨ��
	 ��������ʹ��socket��acceptor��ʵ��һ��ͬ��ͨ�ŵķ������˺Ϳͻ��˳���
	 1.��������
	 ����������ʵ�ַ������˳�����ʹ��һ��acceptor ������6688 �˿ڽ������ӣ���������ʱʹ��socket������һ���ַ���.
*/






















// day-2025-7-3
/*
	asio����ڲ���ϵͳ�ṩ���첽����,����ǰ�������ģʽ��Proactor��ʵ���˿���ֲ���첽����ͬ����IO����,
	���� asio����Ҫ��ʹ�ö��̺߳���,��Ч�ر����˶��̱߳�̴���������к��ĸ����ã������������������ȣ�
	Ŀǰasio��Ҫ��ע������ͨ�ŷ���,ʹ�ô�������ͺ�����װ��Socket API,�ṩ��һ���ִ� C++ ���������̽ӿ�,
	֧��TCP��UDP��ICMP������ͨ��Э��. ��asio���첽��������������������,����֧��UNIX�źš���ʱ�������ڶ�д��SSL�ȹ���,
	����asio��һ���ܺõġ����е��ԵĿ��,���Խ�����չ���������첽������Ҫ������
*/

// ����
/*
	asio�����ǰ����ģʽ��װ�˲���ϵͳ��select��poll��epoll��kqueue�Ȼ���,ʵ�����첽 IOģ�͡�
	���ĺ�������io_service,�൱��ǰ����ģʽ�е�Proactor��ɫ,asio���κβ�������Ҫ��io_service�Ĳ��롣

	��ͬ��ģʽ��,������һ��IO����,��io_service�ύ����,io_service�Ѳ���ת��������ϵͳ,ͬ���ȴ���
	�� IO �������ʱ,����ϵͳ֪ͨ io_service,Ȼ��io_service�ٰѽ�����ظ�����,�������ͬ�����̡�
	���������������̵߳�join() �ȴ���ʽ���ơ�

	���첽ģʽ��,�������Ҫ����IO����,��Ҫ����һ�����ڡ��ص�������ɴ����� complete handler��
	io_serviceͬ����IO����ת��������ϵͳִ��,������ͬ���ȴ�,�����������ء�
	����io_service ��run() ��Ա�������Եȴ��첽�������,���첽�������ʱ,io_service�Ӳ���ϵͳ��ȡ���,�ٵ���handlerִ�к����߼�(�ص�)��
	 
	 1.handler
	 handler ��asio�������Ҫ����,���Ƿ���ĳ�ֺ���ǩ���Ļص�������
	 handler �����ǿɿ�����,io_service ��洢 handler �Ŀ���,��ĳ���첽�¼�����ʱ,io_service �ͻ�����¼���Ӧ ��handler��
	 handler����һ���Ǻ�������ָ��,��������function����bind/lambda ���ʽ�ȿɵ����ﶼ�������� io_service ���á�
	 ��ҪС��,����operator() ���첽������,ʱ����ȷ��,���뱣֤�������õ��ⲿ��������,����ͻᷢ��δ������Ϊ��

	 ��asio����,handler��Ҫ����������:
	 �� ֻ��һ�� error_code ����,��־ĳ���첽�¼������,���������handler��
	 �� �� error_code �� signal_number ��������,��־������һ��UNIX�ź��¼���
	 �� �� error_code �� bytes_transferred ��������,��־ĳ����д���������,�ɶ�д�������ֽ�����bytes_transferred,ͨ������socket�ص���

	 void handle(const error_codde& ec);
	 void handle(const error_codde& ec, int signal_number);
	 void handle(const error_codde& ec, std::size_t bytes_transferred);

	 ����ʹ��bind�����⺯������ΪasioҪ���handler��ʽ,asio���������ֿռ� boost::asio::placeholders�ﶨ���˼����µ�ռλ��,
	 ��Щ��ռλ���� bind�Լ��� _1��_2 ��ռλ���ĺ����������

	 2.io_service

	 class io_service : public noncopyable
	{
	public:
		std::size_t run();			// ����ִ���¼�ѭ��
		std::size_t run_one();		// ��������ִ��һ�� handler

		std::size_t poll();			// ������, ִ�� ready��handler
		std::size_t poll_one();		// ����ִ��һ�� ready ��handler

		void stop();				// ֹͣ�¼�ѭ��
		bool stopped() const;		// �Ƿ�ֹͣ
		bool reset() const;			// �����¼�ѭ��

		unsepecified dispatch(Hanler handler); // Ҫ���첽ִ��һ�� handler
		unsepecified post(Hanler handler); // Ҫ���첽ִ��һ�� handler

		class strand;			// �ڲ����߳���
		class work;				// ��ʾ�й�������
	};

	io_service�������ϵͳ����첽�������(��epoll),������asio�������������֮ǰ��ʼ��,������������ io_service �ύ�첽������handler��
	������õĳ�Ա������run(),�������¼�ѭ��,�����ȴ�����ע�ᵽio_service���¼����.

	3.strand
	asio ����ڲ���ϵͳ���첽 IO ģ��,��ֱ��ʹ��ϵͳ�߳�,���Ƕ�����һ���Լ����̸߳���:
		strand,strand �������л��첽����,��֤�첽�����ڶ��̵߳Ļ����п�����ȷִ��,����ʹ�û�������
	strand����ժҪ����:

	class io_service::strand
	{
	public:
		explicit strand(io_service& ios);

		io_service& get_io_service();

		unspecified dispatch(Handler handler);
		unspecified post(Handler handler);
		unspecified wrap(Handler handler);	//��װһ�� handler

		bool running_in_this_thread() const;
	};

	strand ���õĳ�Ա������wrap(),�����԰�װһ������,����һ����ͬǩ���ĺ�������,��֤�̰߳�ȫ���� strand ��ִ�С�
	���ǿ��԰� strand ���Ϊ��һ�� handler ����,�����̱߳�����,��һ�����handler��������̲߳������ʵ����⡣
	��һ���߳���ʹ��io_service��û�о�����,����������̰߳�ȫ��,����Ҫʹ��strand ���б���.
	���������̶߳�һ�� io_service ����ִ�� run(),��ôͬһ�� handler ���п��ܴ����߳̾���,��Ҫʹ�� strand ���б���.

	4.work
	�� io_service ��ע��������¼������ʱ,���ͻ��˳��¼�ѭ��,���ǲ���ϣ������,��ʱ��������io_service��������,
	�Դ��������ܷ������첽�¼�,��ʱ����Ҫ��io_serviceʼ�� "���¿���"��
	io_service ���ڲ��� work ǡ�ÿ��Դ��������Ŀ��,���Ĺ��ܼܺ�,ֻ���ڹ��캯����������һ�����õ� "����",
	��������������ֹͣ "����",������һ��guard,��work������������,io_service ��Զ�����������첽�¼���ɶ������¼�ѭ��.
	work����ժҪ���£�

	class io_service::work
	{
	public:
		explicit work(io_service& ioc);
		~work();
		boost::asio::io_service& get_io_service();
	};
	�����Ҫֹͣ����,��ô������ʽ�ص���������������,����ʹ������ָ�������,ֹͣ����ʱreset����ָ���������.

	5.mutable_buffer �� const_buffer
	IO �����ᾭ��ʹ�����ݻ�����, �൱��һƬָ�����ڴ�����,asio��ר���������� mutable_buffer �� const_buffer ����ʾ������

	class mutable_buffer
	{
	public:
		mutable_buffer();
		mutable_buffer(void* data, std::size_t size);

	private:
		void* data_;
		std::size_t size_;
	};

	class const_buffer
	{
	public:
		const_buffer();
		const_buffer(const void* data, std::size_t size);
		const_buffer(const mutable_buffer& b);

	private:
		void* data_;
		std::size_t size_;
	};
	mutable_buffer��const_buffer�Ľṹ�ܼ�, ���Ǳ�����void*���ڴ��ַ�����ݳ���, ��ʵ�ַ�ʽ��boost.string_ref��5.3�ڣ����ơ�

	class mutable_buffer_1 : public mutable_buffer
	{
	public:
		const_iterator begin() const;
		const_iterator end() const;

	};

	class const_buffer_1 : public const_buffer
	{
	public:
		const_iterator begin() const;
		const_iterator end() const;
	};
	����ͨ��ʹ�ù������� buffer() ������ buffer ����, ���ܹ���װ���õ�C++��������, 
	��ԭʼ���顢array��vector��string��, ����mutable_buffers_1��const_buffers_1����

	buffer() �ж���������ʽ, �����ڸ������͡�����:
	unspecified buffer(void* data, std::size_t size_in_bytes);
	unspecified buffer(std::vector<int>& data);

	asio�⻹�ṩ�˼������ɺ������Բ���buffer:
	 �� buffer_size(): ��ȡ�������ĳ��ȡ�
	 �� buffer_cast<T*>(): ת��ָ�����͡�
	 �� buffer_copy(): ��������������, ����memcpy��

	 std::size_t buffer_size(const buffer_type& b);
	 T* buffer_cast(const buffer_type& b);
	 std::size_t buffer_copy(const mutable_buffer& dest, const const_buffer& src);

	 6.������
	 asio��ʹ��system��� error_code �� system_error ����ʾ��������ʱ�Ĵ���
	 ���������е��첽����������������������ʽ��һ����ʽ����һ�� error_code& ���������, ���ú���Լ�����������֤�Ƿ����˴���, 
	 ���߼򵥵غ�����:��һ����ʽû�� error_code ����,�������������׳� system_error �쳣, ���ô������ʹ�� try-catch �����������, �޷����ԡ�

	 7.������־
	 �첽�����ִ���Ƿ����Եģ������첽����ʱ�����̺��ѵ��ԡ�asio��Ϊ���ر��ṩ��handler ���ٻ��ƣ�ֻҪ��ͷ�ļ�<boost/asio.hpp>ǰ����� 
	 BOOST_ASIO_ENABLE_HANDLER_TRACKING, ���ͻ����׼��cerr ���������־��ʹ�ò���ϵͳ���ض�����Ҳ����д��ָ������־�ļ���

	 ������־�� "|" ��Ϊ4���ֶΣ���ʽ����:
	 tag|timestamp|action|description
	 ��һ���ֶ��Ǳ���ַ�����Ŀǰ����"@asio". �ڶ����ֶ���UNIX ʱ�������ȷ������ֱ��ʡ�
	 ��������ֶκ���Ҫ�����Ǽ�¼���첽����ľ��嶯�������庬�����¡�

	 �� n: n��handler����ִ��ĳЩ������
	 �� >n: ����n��handler��description��ʾ��ڲ�����
	 �� <n: �뿪n��handler����description��
	 �� !n: �����쳣���뿪n��handler��
	 �� ~n: n��handlerδ�����þͱ����١�
 	 �� n*m: n��handler������һ���µ�m��handler��

	 asio ���ṩ��һ���ű� handlerviz.pl����λ�� Boost Դ�����libs/asio/tools/�������԰���־���ӻ������� png �� pdf �ļ����������Ǹ������ؿ����첽�����ĵ���˳��

*/

/*
	  �ź�
	  �ź�(signal) ��UNIXϵͳ��һ�ֳ��õĽ��̼��첽ͨ���ֶΣ������UNIX���򼸺�����ĳ�ַ�ʽ֧����.
	  asio���ṩ���� signal_set�������첽IO�ķ�ʽ�ܺõش�����UNIX�źš����ǿ���ͨ���źſ�����Ϥasio�Ļ���ʹ�÷�����
	  ��ժҪ:

	class signal_set
	{
	public:
		explicit signal_set(io_service& ioc);
		signal_set(io_service& ioc, int number, ...);

		void add(int signal_number);		//����ź���
		void remove(int signal_number);		//����ź���
		void clear();						//����ź�������

		void cancel();						// ȡ�������첽����

		void async_wait(SignalHandler handler); // ��Ӵ��� handler, ������
	};

	signal_set�Ĺ��캯��Ҫ����봫�� io_service ���������ύ�첽����.
	�ڶ�����ʽ�Ĺ��캯�������Դ������������ź�ֵ���ڹ����ͬʱ�����źż�.

	�÷�
	��ʹ�� signal_set ǰ���Ǳ��������� io_service ����ֻ���������ܰ��źŴ�������¼�����ѭ���첽�ȴ��źŵķ���.
	֮������ù��캯����add() �� signal_set ���Ҫ������źţ���SIGINT��SIGUSR1�ȣ�����async_wait() �����֮��Ӧ���źŴ�������
	ע�⺯���������async_wait() �� handler ��Ҫ�󣬷���ᵼ�±������

	���������Ҫ����io_service�����run() �����������¼�ѭ���ȴ��źš�
	�������յ��ź�ʱ, signal_set �ͻ�� error_code ���ź�ֵ���ݸ�����ע��Ļص����� handler, handler��Ҫ������ڲ�����������Ĵ����߼���


	
	
	*/



//int main()
//{
//	io_service ioc;
//	signal_set sig(ioc, SIGINT, SIGABRT);
//
//	auto handler1 = [](const error_code& ec, int n)
//		{
//			if (ec)
//			{
//				cout << ec.message() << endl;
//				return;
//			}
//			if (n != SIGINT)
//				return;
//
//			cout << "handler1 recv = " << n << endl;
//			cout << "do somethings" << endl;
//		};
//
//	typedef void(handler_type)(const error_code& ec, int); // ���� handler ����
//
//	function<handler_type> handler2 = [](const error_code& ec, int n) {
//		if (n != SIGABRT)
//			return;
//		cout << "handler2 recv = " << n << endl;
//		};
//
//	sig.async_wait(handler1);
//	sig.async_wait(handler2);
//
//	ioc.run();
//	cout << "io stoped " << endl;
//}

/*
				��ʱ��	

*/