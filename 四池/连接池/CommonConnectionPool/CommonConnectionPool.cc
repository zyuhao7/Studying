#define _CRT_SECURE_NO_WARNINGS 
#include "CommonConnectionPool.h"
#include "public.h"

// 线程安全的懒汉单例函数接口.
ConnectionPool* ConnectionPool::getConnectionPool()
{
	static ConnectionPool pool; // lock、 unlock. 静态变量在产生对象时创建,出作用域自动销毁.
	return &pool;
}

// 从配置文件中加载配置项.
bool ConnectionPool::loadConfigFile()
{
	FILE* pf = fopen("mysql.ini", "r");
	if (pf == nullptr)
	{
		LOG("mysql.ini file is not exists!");
		return false;
	}

	while (!feof(pf))
	{
		char line[1024] = { 0 };
		fgets(line, 1024, pf);
		string str = line;
		int idx = str.find("=", 0);
		if (idx == -1) // 无效配置项.
		{
			continue;
		}
		// passwd=123456\n
		int endidx = str.find('\n', idx);
		string key = str.substr(0, idx);
		string value = str.substr(idx + 1, endidx - idx - 1);

		if (key == "ip")
		{
			ip_ = value;
		}

		else if (key == "port")
		{
			port_ = atoi(value.c_str());
		}
		else if (key == "username")
		{
			username_ = value;
		}
		else if (key == "password")
		{
			password_ = value;
		}
		else if (key == "dbname")
		{
			dbname_ = value;
		}
		else if (key == "initSize")
		{
			initSize_ = atoi(value.c_str());
		}
		else if (key == "maxSize")
		{
			maxSize_ = atoi(value.c_str());
		}
		else if (key == "maxIdleTime")
		{
			maxIdleTime_ = atoi(value.c_str());
		}
		else if (key == "connctionTimeOut")
		{
			connectionTimeOut_ = atoi(value.c_str());
		}
	}
	return true;
}

// 连接池的构造.
ConnectionPool::ConnectionPool()
{
	// 加载配置项.
	if (!loadConfigFile()) return;
	
	// 创建初始数量的连接.
	for (int i = 0; i < initSize_; ++i)
	{
		Connection* p = new Connection();
		p->connect(ip_, port_, username_, password_, dbname_);
		p->refreshAliveTime(); // 刷新一下开始空闲的起始时间.
		connQue_.push(p);
		connCnt_++;
	}

	//启动一个新的线程, 作为连接的生产者, linux thread 《=》 pthread_create
	thread produce(std::bind(&ConnectionPool::produceConnectionTask, this));
	produce.detach();

	// 启动一个新的定时线程, 扫描超过 maxIdleTime 的空闲连接, 进行多于的连接回收.
	thread scanner(std::bind(&ConnectionPool::scannerConnectionTask, this));
	scanner.detach();
}


//运行在独立的线程中, 专门负责生产新连接.
void ConnectionPool::produceConnectionTask()
{
	for (;;)
	{
		unique_lock<mutex> lock(queMutex_);
		while (!connQue_.empty())
		{
			cv.wait(lock); // 队列不为空, 生产者等待.
		}

		// 连接数量没有达到上限, 继续创建新的连接.
		if (connCnt_ < maxSize_)
		{
			Connection* p = new Connection();
			p->connect(ip_, port_, username_, password_, dbname_);
			p->refreshAliveTime(); // 刷新一下开始空闲的起始时间.
			connQue_.push(p);
			connCnt_++;
		}

		cv.notify_all();// 通知消费者线程, 有新连接到来了!
	}
}

// 给外部提供接口, 从连接池获取一个可用的空闲连接.
shared_ptr<Connection> ConnectionPool::getConnection()
{
	unique_lock<mutex> lock(queMutex_);
	while (connQue_.empty())
	{
		// sleep
		/*_EXPORT_STD enum class cv_status { // names for wait returns
			no_timeout,
			timeout
		};*/
		if (cv_status::timeout == cv.wait_for(lock, chrono::milliseconds(connectionTimeOut_)))
		{
			if (connQue_.empty())
			{
				LOG("获取空闲连接超时了..... 获取连接失败!");
				return nullptr;
			}
		}
	}
	/*
	* shared_ptr 智能指针析构时, 会把 connection 资源直接 delete 掉, 相当于
	* 调用 connection 的析构函数, connection 就被 close 掉了.
	* 这里需要自定义 shared_ptr 的释放资源的方式, 把 connection 直接归还到 queue 里.
	*/
	shared_ptr<Connection> sp(connQue_.front(),
		[&](Connection* pcon) {
			// 这里是在服务器应用线程中调用的, 所以一定要考虑 队列的线程安全操作.
			unique_lock<mutex> lock(queMutex_);
			pcon->refreshAliveTime(); // 刷新一下开始空闲的起始时间.
			connQue_.push(pcon);
		});

	connQue_.pop();
	cv.notify_all(); // 消费完连接以后, 通知生产者线程检查一下， 如果队列空了, 赶紧生产连接.
	return sp;

}

// 扫描超过 maxIdleTime 时间的空闲连接, 进行多于的连接回收.
void ConnectionPool::scannerConnectionTask()
{
	for (;;)
	{
		// 通过 sleep 模拟定时效果.
		this_thread::sleep_for(chrono::seconds(maxIdleTime_));

		// 扫描整个队列, 释放多于的连接.
		unique_lock<mutex> lock(queMutex_);
		while (connCnt_ > initSize_)
		{
			Connection* p = connQue_.front();
			if (p->getAliveTime() >= (maxIdleTime_ * 1000))
			{
				connQue_.pop();
				connCnt_--;
				delete p;
			}
			else
			{
				break; 
				// 对头的连接都没超过 maxIdleTime, 其余更没有可能.
			}
		}
	}

}