#include <iostream>
#include <thread>
#include <vector>
using namespace std;

#if 0
struct func
{
    int &i;
    func(int &i_)
        : i(i_)
    {
    }

    void operator()()
    {
        for (unsigned j = 0; j < 100000; ++j)
        {
            // do_something();
        }
    }
};

class thread_guard
{
    std::thread &t;

public:
    explicit thread_guard(std::thread &t_)
        : t(t_)
    {
    }

    ~thread_guard()
    {
        if (t.joinable()) // 1
        {
            t.join(); // 2
        }
    }

    thread_guard(thread_guard const &) = delete; // 3
    thread_guard &operator=(thread_guard const &) = delete;
};

void f()
{
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread t(my_func);
    thread_guard g(t);
    // do_something_in_current_thread();
} // 4

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::thread f()
{
    void some_function();
    return std::thread(some_function);
}

std::thread g()
{
    void some_other_function(int);
    std::thread t(some_other_function, 42);
    return t;
}

void f(std::thread t);

void g(int i)
{
    void some_function();
    f(std::thread(some_function));
    std::thread t(some_function);
    f(std::move(t));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class scoped_thread
{
    std::thread t;

public:
    explicit scoped_thread(std::thread t_) // 1
        : t(std::move(t_))
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

struct func;
void f()
{
    int some_local_state;
    scoped_thread t(std::thread(func(some_local_state))); // 4
    // do_something_in_current_thread();
} // 5

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void do_work(unsigned id)
{
    cout << "hello" << id << endl;
}

void f()
{
    std::vector<std::thread> threads;
    for (int i = 0; i < 20; ++i)
    {
        threads.emplace_back(do_work, i);
    }
    for (auto &entry : threads)
    {
        entry.join();
    }
    cout << threads.size() << endl;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::thread::id master_thread;

void some_core_part_of_algorithm()

{
    if (std::this_thread::get_id() == master_thread)
    {
        // do_master_thread_work();
    }
    // do_common_work();
}
#endif

int main()
{
    // f();
    return 0;
}