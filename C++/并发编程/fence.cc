#include <iostream>
#include <mutex>
#include <memory>
#include <assert.h>
#include <atomic>
#include <thread>

using namespace std;

// 利用栅栏实现同步
// day-2025-3-14
std::atomic<bool> x, y;
std::atomic<int> z;

void write_x()
{
    x.store(true, std::memory_order_release);
}

void write_y()
{
    y.store(true, std::memory_order_release);
}

void read_x_then_y()
{
    while (!x.load(std::memory_order_acquire))
        ;
    if (y.load(std::memory_order_acquire))
        z++;
}

void read_y_then_x()
{
    while (!y.load(std::memory_order_acquire))
        ;
    if (x.load(std::memory_order_acquire))
        z++;
}

void TestAR()
{
    x = false;
    y = false;
    z = 0;
    std::thread a(write_x);
    std::thread b(write_y);
    std::thread c(read_x_then_y);
    std::thread d(read_y_then_x);
    a.join();
    b.join();
    c.join();
    d.join();
    assert(z.load() != 0); // 5
    std::cout << "z value is " << z.load() << std::endl;
}

//其实我们可以通过栅栏机制保证指令的写入顺序。栅栏的机制和memory_order_release类似

void write_x_then_y_fence()
{
    x.store(true, std::memory_order_relaxed);  //1
    std::atomic_thread_fence(std::memory_order_release);  //2
    y.store(true, std::memory_order_relaxed);  //3
}

void read_y_then_x_fence()
{
    while (!y.load(std::memory_order_relaxed));  //4
    std::atomic_thread_fence(std::memory_order_acquire); //5
    if (x.load(std::memory_order_relaxed))  //6
        ++z;
}

void TestFence()
{
    x = false;
    y = false;
    z = 0;
    std::thread a(write_x_then_y_fence);
    std::thread b(read_y_then_x_fence);
    a.join();
    b.join();
    assert(z.load() != 0);   //7
}

int main()
{
   // TestAR();
    TestFence();
    return 0;
}
