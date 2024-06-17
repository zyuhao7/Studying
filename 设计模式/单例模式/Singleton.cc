#include <iostream>
#include <mutex>
#include <pthread.h>
using namespace std;

#if 0
// 饿汉单例模式
class CSingleton
{
public:
    static CSingleton *getInstance()
    {
        return &single;
    }

private:
    static CSingleton single;
    CSingleton()
    {
        cout << "CSingleton()" << endl;
    }
    ~CSingleton()
    {
        cout << "~CSingleton()" << endl;
    }
    CSingleton(const CSingleton &); // 防止外部拷贝构造.
};

CSingleton CSingleton::single;
#endif

#if 0
class CSingleton
{
public:
    static CSingleton *getInstance()
    {
        if (single == nullptr)
        {
            single = new CSingleton();
        }
        return single;
    }

private:
    static CSingleton *single;
    CSingleton() { cout << " CSingleton()" << endl; }
    ~CSingleton() { cout << " ~CSingleton()" << endl; }
    CSingleton(const CSingleton &);

    // 定义一个嵌套类, 在该类的析构函数中, 自动释放外层类的资源.
    class CRelease
    {
    public:
        ~CRelease()
        {
            delete single;
        }
    };
    // 通过该静态对象在程序结束时自动析构的特点,来释放外层类的对象资源.
    static CRelease release;
};
CSingleton *CSingleton::single = nullptr;
CSingleton::CRelease CSingleton::release;

#endif

#if 0
class CSingleton
{
public:
    static CSingleton *getInstance()
    {
        // 获取互斥锁
        pthread_mutex_lock(&mutex);
        if (nullptr == single)
        {
            single = new CSingleton();
        }
        // 释放互斥锁
        pthread_mutex_unlock(&mutex);
        return single;
    }

private:
    static CSingleton *single;
    CSingleton() { cout << "CSingleton()" << endl; }
    ~CSingleton()
    {
        pthread_mutex_destroy(&mutex); // 释放锁
        cout << "~CSingleton()" << endl;
    }
    CSingleton(const CSingleton &);

    class CRelease
    {
    public:
        ~CRelease() { delete single; }
    };
    static CRelease release;

    // 定义线程间的互斥锁
    static pthread_mutex_t mutex;
};
CSingleton *CSingleton::single = nullptr;
CSingleton::CRelease CSingleton::release;
// 互斥锁的初始化
pthread_mutex_t CSingleton::mutex = PTHREAD_MUTEX_INITIALIZER;

#endif

#if 0
// 封装互斥锁.
class CMutex
{
public:
    CMutex() { pthread_mutex_init(&mutex, NULL); };  // 初始化锁.
    ~CMutex() { pthread_mutex_destroy(&mutex); };    // 摧毁锁.
    void lock() { pthread_mutex_lock(&mutex); };     // 获取锁.
    void unlock() { pthread_mutex_unlock(&mutex); }; // 释放锁.

private:
    pthread_mutex_t mutex;
};

class CSingleton
{
public:
    static CSingleton *getInstance()
    {
        if (single == nullptr)
        {
            mutex.lock();
            if (single == nullptr)
            {
                single = new CSingleton();
            }
            mutex.unlock();
        }
        return single;
    }

private:
    CSingleton() { cout << "CSingleton()" << endl; }
    ~CSingleton() { cout << "~CSingleton()" << endl; }
    CSingleton(const CSingleton &);
    class CRelease
    {
    public:
        ~CRelease()
        {
            delete single;
        }
    };

    static CRelease release;
    static CSingleton *single;
    // 线程间的静态互斥锁.
    static CMutex mutex;
};
CSingleton *CSingleton::single = nullptr;
CSingleton::CRelease CSingleton::release;
// 定义互斥锁静态对象.
CMutex CSingleton::mutex;

#endif



int main()
{
    // CSingleton *p1 = CSingleton::getInstance();
    // CSingleton *p2 = CSingleton::getInstance();
    // CSingleton *p3 = CSingleton::getInstance();
    // cout << p1 << " " << p2 << " " << p3 << endl; // 0x601191 0x601191 0x601191
    return 0;
}