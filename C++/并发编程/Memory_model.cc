#include <iostream>
#include <atomic>
#include <memory>
#include <mutex>
#include <thread>
#include <assert.h>
#include <vector>
using namespace std;
// day-2025-3-12
// review 2025-8-11
// 原子操作和内存模型

// 实现自旋锁
// 自旋锁是一种在多线程环境下保护共享资源的同步机制。
// 它的基本思想是，当一个线程尝试获取锁时，如果锁已经被其他线程持有，那么该线程就会不断地循环检查锁的状态，直到成功获取到锁为止。
class SpinLock
{
public:
    /**
     * @brief 获取锁的函数
     * 使用自旋锁实现，通过原子操作 test_and_set 来实现锁的获取
     * 当锁被占用时，线程会自旋等待直到锁被释放
     */
    void lock()
    {
        // 自旋等待，直到成功获取到锁
        // test_and_set 会将 flag 设置为 true，并返回 flag 之前的值
        // 如果之前的值是 false，表示锁未被占用，当前线程成功获取到锁
        // 如果之前的值是 true，表示锁已被占用，当前线程需要继续自旋等待
        while (flag.test_and_set(memory_order_acquire))
            ;
    }

    void unlock()
    {
        // 释放锁，将 flag 设置为 false
        flag.clear(memory_order_release);
    }

private:
    std::atomic_flag flag = ATOMIC_FLAG_INIT;
    /*
        `std::atomic_flag` 是 C++ 标准库中提供的一种简单的原子类型，主要用于实现低级别的同步操作。
        它是一个布尔类型的原子标志，只有两种状态：`true` 和 `false`。`atomic_flag` 通常用于实现锁、信号量等同步机制。
    */
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
/*
    在 C++ 的原子操作中，std::memory_order 是一个枚举类型，用于指定原子操作的内存顺序模型。
    它定义了线程间操作的可见性和同步规则，帮助开发者控制内存访问的顺序，从而避免数据竞争。

    常见的内存顺序选项
        std::memory_order_relaxed
            最弱的内存顺序模型。
            不保证操作的顺序，仅保证操作是原子的。
            适用于不需要线程间同步的场景，通常用于性能优化。

        std::memory_order_consume
            保证依赖关系的内存顺序。
            目前大多数实现将其视为 memory_order_acquire。

        std::memory_order_acquire
            保证当前线程对该原子变量的读取操作之前的所有操作都不会被重排序到读取之后。
            常用于加载操作，确保读取到的值是最新的。

        std::memory_order_release
            保证当前线程对该原子变量的写入操作之后的所有操作都不会被重排序到写入之前。
            常用于存储操作，确保写入的值对其他线程可见。

        std::memory_order_acq_rel
            结合了 memory_order_acquire 和 memory_order_release 的语义。
            常用于读-改-写操作（如 fetch_add）。

        std::memory_order_seq_cst
            最强的内存顺序模型。
            保证全局的顺序一致性，所有线程都以相同的顺序观察原子操作。
            默认的内存顺序，适用于需要严格同步的场景。
*/

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
                       yd.store(1, std::memory_order_release); // (2)
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
/*
  std::atomic::compare_exchange_strong 是 C++ 标准库中提供的一种原子操作，用于实现无锁编程中的比较和交换操作。
  它是 std::atomic 类型的成员函数，主要用于在多线程环境下安全地更新共享变量。

功能
    compare_exchange_strong 会比较原子变量的当前值与预期值（expected）。如果两者相等，
    则将原子变量更新为指定的新值（desired）；否则，将原子变量的当前值存储到 expected 中，并返回 false。

bool compare_exchange_strong(T& expected, T desired,
                             std::memory_order success,
                             std::memory_order failure) noexcept;

bool compare_exchange_strong(T& expected, T desired) noexcept;
    expected
    输入：表示期望的值。
    输出：如果比较失败，expected 会被更新为原子变量的当前值

    desired
    如果 expected 和原子变量的值相等，则将原子变量更新为 desired

    success 和 failure（可选）
    指定内存顺序模型：
    success：当比较成功时使用的内存顺序。
    failure：当比较失败时使用的内存顺序（不能是 memory_order_release 或 memory_order_acq_rel）。

    返回值
    true：比较成功，原子变量被更新为 desired。
    false：比较失败，expected 被更新为原子变量的当前值。


*/
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