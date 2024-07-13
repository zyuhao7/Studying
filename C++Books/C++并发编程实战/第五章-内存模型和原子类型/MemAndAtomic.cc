#include <memory>
#include <atomic>
#include <iostream>
#include <vector>
#include <thread>
#include <assert.h>
#include <chrono>

using namespace std;

#if 0
class spinlock_mutex
{
    std::atomic_flag flag;

public:
    spinlock_mutex()
        : flag(ATOMIC_FLAG_INIT)
    {
    }
    void lock()
    {
        while (flag.test_and_set(std::memory_order_acquire))
            ;
    }
    void unlock()
    {
        flag.clear(std::memory_order_release);
    }
};
#endif

#if 0
class Foo
{
};
Foo some_array[5];

std::atomic<Foo *> p(some_array);
Foo *x = p.fetch_add(2); // p加2，并返回原始值

assert((x == some_array));
assert(p.load() == &some_array[2]);
x = (p -= 1); // p减1，并返回原始值
assert(x == &some_array[1]);
assert(p.load() == &some_array[1]);

#endif

#if 0
std::vector<int> data;

std::atomic<bool> data_ready(false);

void reader_thread()
{
    while (!data_ready.load()) // 1
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    std::cout << "The answer = " << data[0] << " \m " << endl; // 2
}

void writer_thread()

{
    data.push_back(42); // 3
    data_ready = true;  // 4
}
#endif



int main()
{
    // writer_thread();
    // reader_thread();

    return 0;
}