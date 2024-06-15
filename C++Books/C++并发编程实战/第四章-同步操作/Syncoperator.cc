#include <mutex>
#include <iostream>
#include <thread>
#include <condition_variable>
#include <memory>
#include <queue>
#include <vector>
using namespace std;

#if 0
bool flag;
std::mutex m;

void wait_for_flag()
{
    std::unique_lock<std::mutex> lk(m);
    while (!flag)
    {
        lk.unlock();                                                 // 1 解锁互斥量
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 2 休眠 100ms
        lk.lock();                                                   // 3 再锁互斥量
    }
}


std::mutex mut;
class data_chunk
{
};

std::queue<data_chunk> data_queue; // 1

std::condition_variable data_cond;

void data_preparation_thread()

{
    while (more_data_to_prepare())
    {
        data_chunk const data = prepare_data();
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(data);  // 2
        data_cond.notify_one(); // 3
    }
}
void data_processing_thread()

{
    while (true)
    {
        std::unique_lock<std::mutex> lk(mut); // 4
        data_cond.wait(
            lk, []
            { return !data_queue.empty(); }); // 5
        data_chunk data = data_queue.front();
        data_queue.pop();
        lk.unlock(); // 6
        process(data);
        if (is_last_chunk(data))
            break;
    }
}

template <typename Predicate>
void minimal_wait(std::unique_lock<std::mutex> &lk, Predicate pred)
{
    while (!pred())
    {
        lk.unlock();
        lk.lock();
    }
}


template <class T, class Container = std::deque<T>>
class queue
{
public:
    explicit queue(const Container &);
    explicit queue(Container && = Container());

    template <class Alloc>
    explicit queue(const Alloc &);

    template <class Alloc>
    queue(const Container &, const Alloc &);

    template <class Alloc>
    queue(Container &&, const Alloc &);

    template <class Alloc>
    queue(queue &&, const Alloc &);

    void swap(queue &q);

    bool empty() const;
    size_type size() const;

    T &front();
    const T &front() const;
    T &back();
    const T &back() const;

    void push(const T &x);
    void push(T &&x);
    void pop();
    template <class... Args>
    void emplace(Args &&...args);
};


template <typename T>
class threadsafe_queue
{

public:
    threadsafe_queue();
    threadsafe_queue(const threadsafe_queue &);
    threadsafe_queue &operator=(const threadsafe_queue &) = delete; // 不允许简单的赋值.

    void push(T new_value);

    bool try_pop(T &value);       // 1
    std::shared_ptr<T> try_pop(); // 2

    void wait_and_pop(T &value);
    std::shared_ptr<T> wait_and_pop();

    bool empty() const;
};

template <typename T>
class threadsafe_queue
{

private:
    std::mutex mut;
    std::queue<T> data_queue;
    std::condition_variable data_cond;

public:
    void push(T new_value)
    {
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(new_value);
        data_cond.notify_one();
    }

    void wait_and_pop(T &value)
    {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk, [this]
                       { return !data_queue.empty(); });
        value = data_queue.front();
        data_queue.pop();
    }
};

threadsafe_queue<data_chunk> data_queue; // 1

void data_preparation_thread()

{
    while (more_data_to_prepare())
    {
        data_chunk const data = prepare_data();
        data_queue.push(data); // 2
    }
}

void data_processing_thread()

{
    while (true)
    {
        data_chunk data;
        data_queue.wait_and_pop(data); // 3
        process(data);
        if (is_last_chunk(data))
            break;
    }
}


template <typename T>
class threadsafe_queue
{
private:
    mutable std::mutex mut; // 1 互斥量必须是可变的

    std::queue<T> data_queue;
    std::condition_variable data_cond;

public:
    threadsafe_queue()
    {
    }
    threadsafe_queue(threadsafe_queue const &other)
    {
        std::lock_guard<std::mutex> lk(other.mut);
        data_queue = other.data_queue;
    }

    void push(T new_value)
    {
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(new_value);
        data_cond.notify_one();
    }

    void wait_and_pop(T &value)
    {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk, [this]
                       { return !data_queue.empty(); });
        value = data_queue.front();
        data_queue.pop();
    }

    std::shared_ptr<T> wait_and_pop()
    {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk, [this]
                       { return !data_queue.empty(); });
        std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
        data_queue.pop();
        return res;
    }

    bool try_pop(T &value)
    {
        std::lock_guard<std::mutex> lk(mut);
        if (data_queue.empty())
            return false;
        value = data_queue.front();
        data_queue.pop();
        return true;
    }

    std::shared_ptr<T> try_pop()
    {
        std::lock_guard<std::mutex> lk(mut);
        if (data_queue.empty())
            return std::shared_ptr<T>();
        std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
        data_queue.pop();
        return res;
    }

    bool empty() const
    {
        std::lock_guard<std::mutex> lk(mut);
        return data_queue.empty();
    }
};

#endif

int main()
{
    return 0;
}