#include <iostream>
#include <mutex>
#include <memory>
#include <pthread.h>
#include <thread>
#include <shared_mutex>
using namespace std;

// day-2025-3-3
//  unique_lock、读写锁、递归锁

// unique_lock 基本用法
mutex mtx;
int shared_data = 0;
void use_unique()
{
    // 可手动也可自动
    unique_lock<mutex> lock(mtx);
    cout << "lock success" << endl;
    shared_data++;
    lock.unlock();
}

// 可判断是否占有锁
void owns_lock()
{
    // lock可自动解锁，也可手动解锁
    std::unique_lock<std::mutex> lock(mtx);
    shared_data++;
    if (lock.owns_lock())
    {
        std::cout << "owns lock" << std::endl;
    }
    else
    {
        std::cout << "doesn't own lock" << std::endl;
    }

    lock.unlock();
    if (lock.owns_lock())
    {
        std::cout << "owns lock" << std::endl;
    }
    else
    {
        std::cout << "doesn't own lock" << std::endl;
    }
}

void defer_lock()
{
    std::unique_lock<std::mutex> lock(mtx, std::defer_lock);
    lock.lock();

    // 可以自动析构解锁, 也可以手动解锁
    lock.unlock();
}

void use_own_defer()
{
    std::unique_lock<std::mutex> lock(mtx);
    if (lock.owns_lock())
    {
        cout << "Main thread  has the lock." << endl;
    }
    else
    {
        cout << "Main thread does not  have the lock. " << endl;
    }
    std::thread t([]()
                  { std::unique_lock<std::mutex> lock(mtx, std::defer_lock);
                    if(lock.owns_lock())
                    {
                        cout << "thread has the lock." << endl;
                    }
                    else
                    {
                        cout << "thread does not have the lock." << endl;
                    }
                    lock.lock();
                    if(lock.owns_lock())
                    {
                        cout << "thread has the lock." << endl;
                    }
                    else
                    {
                        cout << "thread does not have the lock." << endl;
                    }
                    lock.unlock(); });
    t.join();
}

void use_own_adopt()
{
    // mtx.lock();
    std::unique_lock<std::mutex> lock(mtx, std::adopt_lock);
    if (lock.owns_lock())
    {
        cout << " owns lock" << endl;
    }
    else
    {
        cout << "does not have the lock" << endl;
    }
    lock.unlock();
}

int a = 10;
int b = 99;
std::mutex mtx1;
std::mutex mtx2;
void safe_swap()
{
    cout << "a = " << a << " b = " << b << endl;
    std::lock(mtx1, mtx2);
    std::unique_lock<std::mutex> lock1(mtx1, adopt_lock);
    std::unique_lock<std::mutex> lock2(mtx2, adopt_lock);
    swap(a, b);
    cout << "a = " << a << " b = " << b << endl;
    // 错误用法.
    // lock1.unlock();
    // lock2.unlock();
}

void safe_swap2()
{
    cout << "a = " << a << " b = " << b << endl;
    std::unique_lock<std::mutex> lock1(mtx1, std::defer_lock);
    std::unique_lock<std::mutex> lock2(mtx2, std::defer_lock);
    // 需用lock1,lock2加锁
    std::lock(lock1, lock2);
    // 错误用法
    // std::lock(mtx1, mtx2);
    std::swap(a, b);
    cout << "a = " << a << " b = " << b << endl;
}

// int main()
// {
//     // use_unique();
//     // owns_lock();
//     // use_own_defer();
//     // use_own_adopt();
//     // safe_swap();
//     // safe_swap2();

//     return 0;
// }

// 共享锁
// 类DNService代表DNS服务，查询操作使用共享锁，而写操作使用独占锁
#include <map>
#include <string>

class DNService
{
public:
    DNService() {}
    // 读操作采取共享锁
    string QueryDNS(string dnsname)
    {
        std::shared_lock<std::shared_mutex> shared_lock(_shared_mutex);
        auto it = _dns_info.find(dnsname);
        if (it != _dns_info.end())
        {
            return it->second;
        }
        return "";
    }

    // 写操作采用独占锁
    void AddDNSInfo(string dnsname, string dnsentry)
    {
        std::lock_guard<std::shared_mutex> guard_lock(_shared_mutex);
        _dns_info.insert(std::make_pair(dnsname, dnsentry));
    }

private:
    std::map<string, string> _dns_info;
    mutable std::shared_mutex _shared_mutex;
};

// 递归锁
// 有时候我们在实现接口的时候内部加锁，接口内部调用完结束自动解锁。会出现一个接口调用另一个接口的情况，
// 如果用普通的std::mutex就会出现卡死，因为嵌套加锁导致卡死。但是我们可以使用递归锁
