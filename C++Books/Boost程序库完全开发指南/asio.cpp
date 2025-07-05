#define BOOST_THREAD_VERSION 5
#define BOOST_ASIO_ENABLE_HANDLER_TRACKINIG // 追踪日志
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
// 定时器
/*
	在异步IO里，定时器是一个非常重要的功能，它可以在指定时刻调用函数，实现异步操作.
	asio库提供4个定时器，分别是 deadline_timer、steady_timer、system_timer 和 high_resolution_timer。
	类摘要:

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

		time_point expires_at() const;			// 获得过期时间点
		std::size_t expires_at(const time_point& expiry_time);

		duration expires_from_now() const; //获得过期时间长度
		std::size_t expires_from_now(const duration& expiry_time) const; //获得过期时间长度

		void wait();	//同步等待
		void async_wait(WaitHandler handler); // 异步等待

		std::size_t cancel();
		std::size_t cancel_one();
	};

	steady_timer、system_timer 和 high_resolution_timer 是 basic_waitable_timer 的模板特化typedef：

	typedef basic_waitable_timer<steady_clock> steady_timer;
	typedef basic_waitable_timer<system_clock> steady_timer;
	typedef basic_waitable_timer<high_resolution_clock> high_resolution_timer;

	定时器有3种形式的构造函数，它同signal_set一样要求必须有一个io_service对象，用于提交IO请求.
	第二个参数是定时器的终止时间，可以是绝对时间点或是相对于当前时间点的一段时间长度.
	一旦定时器对象被创建，它就会立即开始计时，可以使用成员函数wait() 来同步等待定时器终止,
	或者使用async_wait() 异步等待定时器终止，当定时器终止时会调用 handler 函数

	2.同步定时器

	int main()
	{
		io_service ioc;
		steady_timer t(ioc, milliseconds(500));
		cout << t.expires_at() << endl;	// 查看终止的时间点
		cout << t.expires_from_now() << endl;	//查看终止的时间长度
		t.wait();

	}

	读者可以把上述代码与thread库的sleep() 函数对比研究一下，虽然两者都是等待，但它们的内部机制完全不同:
	thread库的sleep() 使用了互斥量和条件变量，在线程中等待，而asio则调用了操作系统的异步机制，如epoll、kqueue等，没有多线程的竞争。

	3.异步定时器
	接下来介绍异步定时器，其代码与同步定时器的代码大致相同，但异步定时器使用async_wait() 方法增加了回调函数：
	int main()
	{
		io_service ioc;
		steady_timer t(ioc, milliseconds(500));
		t.async_wait([](const error_code& ec) {
			cout << "hello world" << endl;
			});
		ioc.run();
	}
	当定时器时间到终止时, io_service将调用被注册的 lambda 函数，输出一条消息，然后程序结束

	4.使用bind
	定时器非常有用，我们可以用它增加回调函数的参数，使它能够做更多的事情。虽然async_wait() 接收的回调函数类型是固定的，
	但可以使用 bind 配合占位符 placeholders::error 来绑定参数来适配 bind 的接口:

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

	5.使用lambda
	bind 表达式的解法很通用，用bind表达式搭配占位符 placeholders::error 可以把任意的函数或成员函数适配为 asio 要求的 handler，
	但 bind 的写法稍显麻烦，而且当参数比较多时不易阅读。


	 网络通信
	 类 ip::tcp 是asio网络通信（TCP）部分主要的类，表示TCP协议.

	 1.address

	ip::address addr;

	addr = addr.from_string("127.0.0.1");
	assert(addr.is_v4());
	cout << addr.to_string() << endl;
	cout << typeid(addr).name() << endl;

	addr = addr.from_string("ab::12:34:56");
	assert(addr.is_v6());

	2.endpoint
	有了IP 地址，再加上通信用的端口号就构成了一个 socket 端点，在asio库中用 ip::tcp::endpoint 来表示。

	int main()
	{
		ip::address addr;
		addr = addr.from_string("127.0.0.1");

		ip::tcp::endpoint ep(addr, 6680);
		assert(ep.address() == addr);
		assert(ep.port() == 6680);
	}

	3. socket
	socket 可以在构造时就指定使用的协议或 endpoint，或者稍后调用成员函数connect() 

	socket 读写函数的参数都是buffer 类型，可以用buffer() 函数包装各种容器适配，区别在于send() /write_some() 的参数应该是一个可读buffer，
	而receive() /read_some() 要求参数是可写buffer。

	4.acceptor
	acceptor类对应Socket API的accept() 函数功能，它用于服务器端，在指定的端口号接收连接，acceptor必须配合socket类才能完成通信

	 同步通信
	 本节我们使用socket和acceptor来实现一对同步通信的服务器端和客户端程序
	 1.服务器端
	 首先我们来实现服务器端程序，它使用一个acceptor 对象在6688 端口接收连接，当有连接时使用socket对象发送一个字符串.
*/






















// day-2025-7-3
/*
	asio库基于操作系统提供的异步机制,采用前摄器设计模式（Proactor）实现了可移植的异步（或同步）IO操作,
	而且 asio并不要求使用多线程和锁,有效地避免了多线程编程带来的诸多有害的副作用（如条件竞争、死锁等）
	目前asio主要关注于网络通信方面,使用大量的类和函数封装了Socket API,提供了一个现代 C++ 风格的网络编程接口,
	支持TCP、UDP、ICMP等网络通信协议. 但asio的异步操作并不局限于网络编程,它还支持UNIX信号、定时器、串口读写、SSL等功能,
	而且asio是一个很好的、富有弹性的框架,可以将它扩展到其他有异步操作需要的领域。
*/

// 概述
/*
	asio库基于前摄器模式封装了操作系统的select、poll、epoll、kqueue等机制,实现了异步 IO模型。
	它的核心类是io_service,相当于前摄器模式中的Proactor角色,asio的任何操作都需要有io_service的参与。

	在同步模式下,程序发起一个IO操作,向io_service提交请求,io_service把操作转交给操作系统,同步等待。
	当 IO 操作完成时,操作系统通知 io_service,然后io_service再把结果返回给程序,完成整个同步流程。
	这个处理流程与多线程的join() 等待方式类似。

	在异步模式下,程序除了要发起IO操作,还要定义一个用于“回调”的完成处理函数 complete handler。
	io_service同样把IO操作转交给操作系统执行,但它不同步等待,而是立即返回。
	调用io_service 的run() 成员函数可以等待异步操作完成,当异步操作完成时,io_service从操作系统获取结果,再调用handler执行后续逻辑(回调)。
	 
	 1.handler
	 handler 是asio库里的重要概念,它是符合某种函数签名的回调函数。
	 handler 必须是可拷贝的,io_service 会存储 handler 的拷贝,当某种异步事件发生时,io_service 就会调用事件对应 的handler。
	 handler并不一定是函数或函数指针,函数对象、function对象、bind/lambda 表达式等可调用物都可以用于 io_service 调用。
	 但要小心,由于operator() 是异步发生的,时机不确定,必须保证它们引用的外部变量可用,否则就会发生未定义行为。

	 在asio库里,handler主要有以下三种:
	 ■ 只有一个 error_code 参数,标志某个异步事件完成了,是最基本的handler。
	 ■ 有 error_code 和 signal_number 两个参数,标志发生了一个UNIX信号事件。
	 ■ 有 error_code 和 bytes_transferred 两个参数,标志某个读写操作完成了,可读写的数据字节数是bytes_transferred,通常用于socket回调。

	 void handle(const error_codde& ec);
	 void handle(const error_codde& ec, int signal_number);
	 void handle(const error_codde& ec, std::size_t bytes_transferred);

	 可以使用bind把任意函数适配为asio要求的handler形式,asio库在子名字空间 boost::asio::placeholders里定义了几个新的占位符,
	 这些新占位符比 bind自己的 _1、_2 等占位符的含义更清晰。

	 2.io_service

	 class io_service : public noncopyable
	{
	public:
		std::size_t run();			// 阻塞执行事件循环
		std::size_t run_one();		// 至少阻塞执行一个 handler

		std::size_t poll();			// 非阻塞, 执行 ready的handler
		std::size_t poll_one();		// 至少执行一个 ready 的handler

		void stop();				// 停止事件循环
		bool stopped() const;		// 是否停止
		bool reset() const;			// 重启事件循环

		unsepecified dispatch(Hanler handler); // 要求异步执行一个 handler
		unsepecified post(Hanler handler); // 要求异步执行一个 handler

		class strand;			// 内部的线程类
		class work;				// 表示有工作进行
	};

	io_service类代表了系统里的异步处理机制(如epoll),必须在asio库里的其他对象之前初始化,其他对象则向 io_service 提交异步操作的handler。
	我们最常用的成员函数是run(),它启动事件循环,阻塞等待所有注册到io_service的事件完成.

	3.strand
	asio 库基于操作系统的异步 IO 模型,不直接使用系统线程,而是定义了一个自己的线程概念:
		strand,strand 可以序列化异步操作,保证异步代码在多线程的环境中可以正确执行,无须使用互斥量。
	strand的类摘要如下:

	class io_service::strand
	{
	public:
		explicit strand(io_service& ios);

		io_service& get_io_service();

		unspecified dispatch(Handler handler);
		unspecified post(Handler handler);
		unspecified wrap(Handler handler);	//包装一个 handler

		bool running_in_this_thread() const;
	};

	strand 常用的成员函数是wrap(),它可以包装一个函数,返回一个相同签名的函数对象,保证线程安全地在 strand 中执行。
	我们可以把 strand 理解为对一组 handler 的锁,加入线程保护后,这一组里的handler不会存在线程并发访问的问题。
	在一个线程里使用io_service是没有竞争的,它本身就是线程安全的,不需要使用strand 进行保护.
	但如果多个线程对一个 io_service 对象执行 run(),那么同一个 handler 就有可能存在线程竞争,需要使用 strand 进行保护.

	4.work
	当 io_service 里注册的所有事件都完成时,它就会退出事件循环,我们并不希望这样,有时我们想让io_service继续运行,
	以处理将来可能发生的异步事件,这时就需要让io_service始终 "有事可做"。
	io_service 的内部类 work 恰好可以达成这样的目的,它的功能很简单,只是在构造函数里启动了一个可用的 "工作",
	而在析构函数中停止 "工作",它像是一个guard,在work的生命周期里,io_service 永远不会因其他异步事件完成而结束事件循环.
	work的类摘要如下：

	class io_service::work
	{
	public:
		explicit work(io_service& ioc);
		~work();
		boost::asio::io_service& get_io_service();
	};
	如果想要停止工作,那么可以显式地调用它的析构函数,或者使用智能指针持有它,停止工作时reset智能指针进而析构.

	5.mutable_buffer 和 const_buffer
	IO 操作会经常使用数据缓冲区, 相当于一片指定的内存区域,asio库专门用两个类 mutable_buffer 和 const_buffer 来表示这个概念：

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
	mutable_buffer和const_buffer的结构很简单, 它们保存了void*的内存地址和数据长度, 其实现方式与boost.string_ref（5.3节）类似。

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
	我们通常使用工厂函数 buffer() 来生产 buffer 对象, 它能够包装常用的C++容器类型, 
	如原始数组、array、vector、string等, 返回mutable_buffers_1或const_buffers_1对象。

	buffer() 有多种重载形式, 适用于各种类型。例如:
	unspecified buffer(void* data, std::size_t size_in_bytes);
	unspecified buffer(std::vector<int>& data);

	asio库还提供了几个自由函数可以操作buffer:
	 ■ buffer_size(): 获取缓冲区的长度。
	 ■ buffer_cast<T*>(): 转换指针类型。
	 ■ buffer_copy(): 拷贝缓冲区数据, 类似memcpy。

	 std::size_t buffer_size(const buffer_type& b);
	 T* buffer_cast(const buffer_type& b);
	 std::size_t buffer_copy(const mutable_buffer& dest, const const_buffer& src);

	 6.错误处理
	 asio库使用system库的 error_code 和 system_error 来表示程序运行时的错误。
	 基本上所有的异步操作函数都有两种重载形式：一种形式是有一个 error_code& 的输出参数, 调用后可以检查这个参数验证是否发生了错误, 
	 或者简单地忽略它:另一种形式没有 error_code 参数,如果发生错误会抛出 system_error 异常, 调用代码必须使用 try-catch 块来捕获错误, 无法忽略。

	 7.跟踪日志
	 异步代码的执行是非线性的，运行异步代码时的流程很难调试。asio库为此特别提供了handler 跟踪机制，只要在头文件<boost/asio.hpp>前定义宏 
	 BOOST_ASIO_ENABLE_HANDLER_TRACKING, 它就会向标准流cerr 输出运行日志，使用操作系统的重定向功能也可以写入指定的日志文件。

	 跟踪日志以 "|" 分为4个字段，格式如下:
	 tag|timestamp|action|description
	 第一个字段是标记字符串，目前总是"@asio". 第二个字段是UNIX 时间戳，精确到毫秒分辨率。
	 最后两个字段很重要，它们记录了异步代码的具体动作，具体含义如下。

	 ■ n: n号handler正在执行某些操作。
	 ■ >n: 进入n号handler，description表示入口参数。
	 ■ <n: 离开n号handler，无description。
	 ■ !n: 发生异常，离开n号handler。
	 ■ ~n: n号handler未被调用就被销毁。
 	 ■ n*m: n号handler创建了一个新的m号handler。

	 asio 还提供了一个脚本 handlerviz.pl，它位于 Boost 源码包的libs/asio/tools/，它可以把日志可视化，生成 png 或 pdf 文件，方便我们更清晰地看出异步操作的调用顺序。

*/

/*
	  信号
	  信号(signal) 是UNIX系统里一种常用的进程间异步通信手段，成熟的UNIX程序几乎都以某种方式支持它.
	  asio库提供了类 signal_set，利用异步IO的方式很好地处理了UNIX信号。我们可以通过信号快速熟悉asio的基本使用方法。
	  类摘要:

	class signal_set
	{
	public:
		explicit signal_set(io_service& ioc);
		signal_set(io_service& ioc, int number, ...);

		void add(int signal_number);		//添加信号量
		void remove(int signal_number);		//添加信号量
		void clear();						//清空信号量集合

		void cancel();						// 取消所有异步操作

		void async_wait(SignalHandler handler); // 添加处理 handler, 非阻塞
	};

	signal_set的构造函数要求必须传入 io_service 对象，用于提交异步操作.
	第二种形式的构造函数最多可以传入三个整数信号值，在构造的同时加入信号集.

	用法
	在使用 signal_set 前我们必须先声明 io_service 对象，只有这样才能把信号处理加入事件处理循环异步等待信号的发生.
	之后可以用构造函数或add() 向 signal_set 添加要捕获的信号，如SIGINT、SIGUSR1等，再用async_wait() 添加与之对应的信号处理函数，
	注意函数必须符合async_wait() 对 handler 的要求，否则会导致编译错误。

	最后，我们需要调用io_service对象的run() 方法，启动事件循环等待信号。
	当进程收到信号时, signal_set 就会把 error_code 和信号值传递给所有注册的回调函数 handler, handler需要根据入口参数决定具体的处理逻辑。


	
	
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
//	typedef void(handler_type)(const error_code& ec, int); // 定义 handler 类型
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
				定时器	

*/