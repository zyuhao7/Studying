### 第二章 线程管理
>   
### 本章主要内容
 1. 启动新线程
 2. 等待线程与线程分离
 3. 线程唯一标识

 ```bash
 # 启动线程
 
 #1.可调用函数
void do_some_work();
std::thread	my_thread(do_some_work);

#2. 带有函数调用符类型的实例
class background_task
{
public:
		void	operator()()	const
		{
				do_something();
				do_something_else();
		}
};
background_task	f;
std::thread	my_thread(f);
 ```

```bash
# 当某个对象转移了线程的所有权，就不能对线程进行汇入或分离。为了确保线程在程序退出前完成，定义了scoped_thread类。

# scoped_thread的用法
class scoped_thread
{
    std::thread t;

public:
    explicit scoped_thread(std::thread t_) : // 1
                                             t(std::move(t_))
    {
        if (!t.joinable()) // 2
            throw std::logic_error("No Thread");
    }
    ~scoped_thread()
    {
        t.join(); // 3
    }
    scoped_thread(scoped_thread const &) = delete;
    scoped_thread &operator=(scoped_thread const &) = delete;
};

struct func; // 定义在代码2.1中

void f()
{
    int some_local_state;
    scoped_thread t(std::thread(func(some_local_state))); // 4
    do_something_in_current_thread();
} // 5
```

```bash
# joining_thread类的实现
class joining_thread
{
    std::thread t;

public:
    joining_thread() noexcept = default;

    template <typename Callable, typename... Args>
    explicit joining_thread(Callable &&func, Args &&...args)
        : t(std::forward<Callable>(func), std::forward<Args>(args)...)
    {
    }

    explicit joining_thread(std::thread t_) noexcept
        : t(std::move(t_))
    {
    }

    joining_thread(joining_thread &&other) noexcept
        : t(std::move(other.t))
    {
    }

    joining_thread &operator=(joining_thread &&other) noexcept
    {
        if (joinable())
        {
            join();
        }
        t = std::move(other.t);
        return *this;
    }

    joining_thread &operator=(std::thread other) noexcept
    {
        if (joinable())
            join();
        t = std::move(other);
        return *this;
    }

    ~joining_thread() noexcept
    {
        if (joinable())
            join();
    }

    void swap(joining_thread &other) noexcept
    {
        t.swap(other.t);
    }

    std::thread::id get_id() const noexcept
    {
        return t.get_id();
    }

    bool joinable() const noexcept
    {
        return t.joinable();
    }

    void join()
    {
        t.join();
    }

    void detach()
    {
        t.detach();
    }
    
    std::thread &as_thread() noexcept
    {
        return t;
    }
    const std::thread &as_thread() const noexcept
    {
        return t;
    }
};
```

```bash
# 并行版的 std::accumulate
# 每个线程有唯一标识符.
template <typename Iterator, typename T>
struct accumulate_block
{
    void operator()(Iterator first, Iterator last, T &result)
    {
        result = std::accumulate(first, last, result);
    }
};

template <typename Iterator, typename T>

T parallel_accumulate(Iterator first, Iterator last, T init)

{
    unsigned long const length = std::distance(first, last);

    if (!length) // 1
        return init;

    unsigned long const min_per_thread = 25;
    unsigned long const max_threads =
        (length + min_per_thread - 1) / min_per_thread; // 2

    unsigned long const hardware_threads =
        std::thread::hardware_concurrency();

    unsigned long const num_threads = // 3
        std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);

    unsigned long const block_size = length / num_threads; // 4

    std::vector<T> results(num_threads);
    std::vector<std::thread> threads(num_threads - 1); // 5

    Iterator block_start = first;
    for (unsigned long i = 0; i < (num_threads - 1); ++i)
    {
        Iterator block_end = block_start;
        std::advance(block_end, block_size); // 6
        threads[i] = std::thread(            // 7
            accumulate_block<Iterator, T>(),
            block_start, block_end, std::ref(results[i]));
        block_start = block_end; // 8
    }
    accumulate_block<Iterator, T>()(
        block_start, last, results[num_threads - 1]); // 9

    for (auto &entry : threads)
        entry.join();                                             // 10
    return std::accumulate(results.begin(), results.end(), init); // 11
}
```

```bash
# 线程标识
# std::thread::id 实例常用作检测线程是否需要进行一些操作。比如：当用线程来分割一项工作。
# 主线程可能要做一些与其他线程不同的工作，启动其他线程前,可以通过std::this_thread::get_id() 得到自己的线程ID。每个线程都要检查一下，其拥有的线程ID是否与初始线程的ID相同。

std::thread::id master_thread;

void some_core_part_of_algorithm()

{
    if (std::this_thread::get_id() == master_thread)
    {
        // do_master_thread_work();
    }
    // do_common_work();
}

```

```C++
// 本章总结
/*
 本章讨论了C++标准库中线程的管理方式：启动线程，等待结束和不等待结束。并了解应该如何在线程启动前，向线程函数中传递参数，如何转移线程的所有权，如何使用线程组来分割任务。
*/

/*
最后，讨论了使用线程标识来确定关联数据，以及特殊线程的特殊解决方案。虽然，现在已经可以依赖线程，使用独立的数据，做独立的任务，但在某些情况下，线程间确实需要有共享数据。
*/

// 第3章会讨论共享数据和线程的直接关系。
// 第4章会讨论在有/没有共享数据情况下的线程同步。

```