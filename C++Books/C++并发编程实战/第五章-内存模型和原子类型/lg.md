# 第五章 内存模型与原子操作
 *  C++内存模型
 * 标准库中的原子类型
 * 如何使用原子类型
 * 使用原子操作同步线程

```c++
// 代码5.1 使用 std::atomic_flag 实现自旋锁
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

```

```c++
// std::atomic<T*>
// std::atomic<> 类模板
// 同步操作和强制排序
// 代码5.2 不同线程对数据的读写
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

```

```c++
// 现在，来看看 "先行" 和 "同发" 操作的真正意义，先从 "同步发生" 开始说起
// 