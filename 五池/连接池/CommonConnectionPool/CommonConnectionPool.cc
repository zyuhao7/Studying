#define _CRT_SECURE_NO_WARNINGS 
#include "CommonConnectionPool.h"
#include "public.h"

// �̰߳�ȫ���������������ӿ�.
ConnectionPool* ConnectionPool::getConnectionPool()
{
	static ConnectionPool pool; // lock�� unlock. ��̬�����ڲ�������ʱ����,���������Զ�����.
	return &pool;
}

// �������ļ��м���������.
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
		if (idx == -1) // ��Ч������.
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

// ���ӳصĹ���.
ConnectionPool::ConnectionPool()
{
	// ����������.
	if (!loadConfigFile()) return;
	
	// ������ʼ����������.
	for (int i = 0; i < initSize_; ++i)
	{
		Connection* p = new Connection();
		p->connect(ip_, port_, username_, password_, dbname_);
		p->refreshAliveTime(); // ˢ��һ�¿�ʼ���е���ʼʱ��.
		connQue_.push(p);
		connCnt_++;
	}

	//����һ���µ��߳�, ��Ϊ���ӵ�������, linux thread ��=�� pthread_create
	thread produce(std::bind(&ConnectionPool::produceConnectionTask, this));
	produce.detach();

	// ����һ���µĶ�ʱ�߳�, ɨ�賬�� maxIdleTime �Ŀ�������, ���ж��ڵ����ӻ���.
	thread scanner(std::bind(&ConnectionPool::scannerConnectionTask, this));
	scanner.detach();
}


//�����ڶ������߳���, ר�Ÿ�������������.
void ConnectionPool::produceConnectionTask()
{
	for (;;)
	{
		unique_lock<mutex> lock(queMutex_);
		while (!connQue_.empty())
		{
			cv.wait(lock); // ���в�Ϊ��, �����ߵȴ�.
		}

		// ��������û�дﵽ����, ���������µ�����.
		if (connCnt_ < maxSize_)
		{
			Connection* p = new Connection();
			p->connect(ip_, port_, username_, password_, dbname_);
			p->refreshAliveTime(); // ˢ��һ�¿�ʼ���е���ʼʱ��.
			connQue_.push(p);
			connCnt_++;
		}

		cv.notify_all();// ֪ͨ�������߳�, �������ӵ�����!
	}
}

// ���ⲿ�ṩ�ӿ�, �����ӳػ�ȡһ�����õĿ�������.
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
				LOG("��ȡ�������ӳ�ʱ��..... ��ȡ����ʧ��!");
				return nullptr;
			}
		}
	}
	/*
	* shared_ptr ����ָ������ʱ, ��� connection ��Դֱ�� delete ��, �൱��
	* ���� connection ����������, connection �ͱ� close ����.
	* ������Ҫ�Զ��� shared_ptr ���ͷ���Դ�ķ�ʽ, �� connection ֱ�ӹ黹�� queue ��.
	*/
	shared_ptr<Connection> sp(connQue_.front(),
		[&](Connection* pcon) {
			// �������ڷ�����Ӧ���߳��е��õ�, ����һ��Ҫ���� ���е��̰߳�ȫ����.
			unique_lock<mutex> lock(queMutex_);
			pcon->refreshAliveTime(); // ˢ��һ�¿�ʼ���е���ʼʱ��.
			connQue_.push(pcon);
		});

	connQue_.pop();
	cv.notify_all(); // �����������Ժ�, ֪ͨ�������̼߳��һ�£� ������п���, �Ͻ���������.
	return sp;

}

// ɨ�賬�� maxIdleTime ʱ��Ŀ�������, ���ж��ڵ����ӻ���.
void ConnectionPool::scannerConnectionTask()
{
	for (;;)
	{
		// ͨ�� sleep ģ�ⶨʱЧ��.
		this_thread::sleep_for(chrono::seconds(maxIdleTime_));

		// ɨ����������, �ͷŶ��ڵ�����.
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
				// ��ͷ�����Ӷ�û���� maxIdleTime, �����û�п���.
			}
		}
	}

}