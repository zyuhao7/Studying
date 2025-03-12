#include <iostream>
#include <atomic>
#include <memory>
#include <mutex>
#include <thread>
#include <assert.h>
#include <vector>
using namespace std;
// day-2025-3-12
// 原子操作和内存模型

// 实现自旋锁
// 自旋锁是一种在多线程环境下保护共享资源的同步机制。
// 它的基本思想是，当一个线程尝试获取锁时，如果锁已经被其他线程持有，那么该线程就会不断地循环检查锁的状态，直到成功获取到锁为止。
class SpinLock
{
public:
    void lock()
    {
        // 自旋等待，直到成功获取到锁
        while (flag.test_and_set(memory_order_acquire))
            ;
    }

    void unlock()
    {
        flag.clear(memory_order_release);
    }

private:
    std::atomic_flag flag = ATOMIC_FLAG_INIT;
};

void TestSpinLock()
{
    SpinLock spinlock;
    std::thread t1([&spinlock]()
                   {  
                    spinlock.lock();
                    for (int i = 0; i < 3; ++i)
                    {
                        cout << "*";
                    }
                    cout<<endl;
                    spinlock.unlock(); });

    std::thread t2([&spinlock]()
                   {  
                     spinlock.lock();
                     for (int i = 0; i < 3; ++i)
                     {
                         cout << "?";
                     }
                     cout<<endl;
                     spinlock.unlock(); });
    t1.join();
    t2.join();
}

// std::memory_order_relaxed
// std::atomic<bool> x, y;
// std::atomic<int> z;
// void write_x_then_y()
// {
//     x.store(true, std::memory_order_relaxed);
//     y.store(true, std::memory_order_relaxed);
// }

// void read_y_then_x()
// {
//     while (!y.load(std::memory_order_relaxed))
//     {
//         cout << "y load false" << endl;
//     }
//     if (x.load(std::memory_order_relaxed))
//     {
//         ++z;
//     }
// }

// void TestOrderRelaxed()
// {
//     std::thread t1(write_x_then_y);
//     std::thread t2(read_y_then_x);
//     t1.join();
//     t2.join();
//     assert(z.load() != 0);
// }

void TestOrderRelaxed2()
{
    std::atomic<int> a{0};
    std::vector<int> v3, v4;
    std::thread t1([&a]()
                   { 
                    for (int i = 0; i < 10; i+= 2)
                        a.store(i, std::memory_order_relaxed); });

    std::thread t2([&a]()
                   {
                        for (int i = 1; i < 10; i += 2)
                            a.store(i, std::memory_order_relaxed); });
    std::thread t3([&v3, &a]()
                   {
                                for (int i = 0; i < 10; ++i)
                                    v3.push_back(a.load(std::memory_order_relaxed)); });

    std::thread t4([&v4, &a]()
                   {
                                for (int i = 0; i < 10; ++i)
                                    v4.push_back(a.load(std::memory_order_relaxed)); });

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    for (auto &v : v3)
        cout << v << " ";
    cout << endl;
    for (auto &v : v4)
        cout << v << " ";
    cout << endl;
}

void TestDependency()
{
    // 1 处
    std::string str = "hello world!";
    // 2 处
    int i = 3;
    // 3 处
    std::cout << str[i] << std::endl;
}

// 通过内存顺序实现内存模型
// memory_order_seq_cst 全局一致性顺序
std::atomic<bool> x, y;
std::atomic<int> z;
void write_x_then_y()
{
    x.store(true, std::memory_order_seq_cst);
    y.store(true, std::memory_order_seq_cst);
}

void read_y_then_x()
{
    while (!y.load(std::memory_order_seq_cst))
    {
        cout << "y load false" << endl;
    }
    if (x.load(std::memory_order_seq_cst))
    {
        ++z;
    }
}

void TestOrderSeqCst()
{
    std::thread t1(write_x_then_y);
    std::thread t2(read_y_then_x);
    t1.join();
    t2.join();
    assert(z.load() != 0);
}

void TestOrderRelaxed()
{
    std::atomic<bool> rx, ry;

    std::thread t1([&]()
                   {
                       rx.store(true, std::memory_order_relaxed); // 1
                       ry.store(true, std::memory_order_relaxed); // 2
                   });

    std::thread t2([&]()
                   {
                       while (!ry.load(std::memory_order_relaxed))
                           ;                                       // 3
                       assert(rx.load(std::memory_order_relaxed)); // 4
                   });

    t1.join();
    t2.join();
}

// Acquire-Release
void TestReleaseAcquire()
{
    std::atomic<bool> rx, ry;

    std::thread t1([&]()
                   {
                       rx.store(true, std::memory_order_relaxed); // 1
                       ry.store(true, std::memory_order_release); // 2
                   });

    std::thread t2([&]()
                   {
                       while (!ry.load(std::memory_order_acquire))
                           ; // 3

                       assert(rx.load(std::memory_order_relaxed)); // 4
                   });

    t1.join();
    t2.join();
}

// Release sequences
void ReleasAcquireDanger2()
{
    std::atomic<int> xd{0}, yd{0};
    std::atomic<int> zd;

    std::thread t1([&]()
                   {
                       xd.store(1, std::memory_order_release); // (1)
                       yd.store(1, std::memory_order_release); //  (2)
                   });

    std::thread t2([&]()
                   {
                       yd.store(2, std::memory_order_release); // (3)
                   });

    std::thread t3([&]()
                   {
                       while (!yd.load(std::memory_order_acquire))
                           ;                                            // （4）
                       assert(xd.load(std::memory_order_acquire) == 1); // (5)
                   });

    t1.join();
    t2.join();
    t3.join();
}

void ReleaseSequence()
{
    std::vector<int> data;
    std::atomic<int> flag{0};

    std::thread t1([&]()
                   {
                       data.push_back(42);                       //(1)
                       flag.store(1, std::memory_order_release); //(2)
                   });

    std::thread t2([&]()
                   {
        int expected = 1;
        while (!flag.compare_exchange_strong(expected, 2, std::memory_order_relaxed)) // (3)
            expected = 1; });

    std::thread t3([&]()
                   {
                       while (flag.load(std::memory_order_acquire) < 2)
                           ;                     // (4)
                       assert(data.at(0) == 42); // (5)
                   });

    t1.join();
    t2.join();
    t3.join();
}

// 利用智能指针解决释放问题
class SingleMemoryModel
{
private:
    SingleMemoryModel()
    {
    }
    SingleMemoryModel(const SingleMemoryModel &) = delete;
    SingleMemoryModel &operator=(const SingleMemoryModel &) = delete;

public:
    ~SingleMemoryModel()
    {
        std::cout << "single auto delete success " << std::endl;
    }
    static std::shared_ptr<SingleMemoryModel> GetInst()
    {
        // 1 处
        if (_b_init.load(std::memory_order_acquire))
        {
            return single;
        }
        // 2 处
        s_mutex.lock();
        // 3 处
        if (_b_init.load(std::memory_order_relaxed))
        {
            s_mutex.unlock();
            return single;
        }
        // 4处
        single = std::shared_ptr<SingleMemoryModel>(new SingleMemoryModel);
        _b_init.store(true, std::memory_order_release);
        s_mutex.unlock();
        return single;
    }

private:
    static std::shared_ptr<SingleMemoryModel> single;
    static std::mutex s_mutex;
    static std::atomic<bool> _b_init;
};

std::shared_ptr<SingleMemoryModel> SingleMemoryModel::single = nullptr;
std::mutex SingleMemoryModel::s_mutex;
std::atomic<bool> SingleMemoryModel::_b_init(false);

void TestSingleMemory()
{
    std::thread t1([]()
                   { std::cout << "thread t1 singleton address is 0x: " << SingleMemoryModel::GetInst() << std::endl; });

    std::thread t2([]()
                   { std::cout << "thread t2 singleton address is 0x: " << SingleMemoryModel::GetInst() << std::endl; });

    t2.join();
    t1.join();
}
int main()
{
    // TestSpinLock();
    // TestOrderRelaxed();
    // TestOrderRelaxed2();
    // TestDependency();
    // TestOrderSeqCst();
    // TestReleaseAcquire();
    // ReleasAcquireDanger2();
    // ReleaseSequence();
    // TestSingleMemory();
    return 0;
}