
# 第四章 同步操作
>   

```c++
// 在等待线程在检查间隙，使用 std::this_thread::sleep_for() 进行周期性的间歇
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

```
>   

```c++
 // 使用 std::condition_variable 处理数据等待
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

```
>

```c++
// 用简单的循环实现了一个“忙碌-等待”
template <typename Predicate>
void minimal_wait(std::unique_lock<std::mutex> &lk, Predicate pred)
{
    while (!pred())
    {
        lk.unlock();
        lk.lock();
    }
}

```
>

```c++
// std::queue 接口
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

```
>

```c++
// 线程安全队列的接口
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

```
>

```c++
// 从 line 25  中提取push()和wait_and_pop()
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

```
>

```c++
// 使用条件变量的线程安全队列(完整版)
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

```
```c++
// std::future 从异步任务中获取返回值
#include <future>
#include <iostream>

int find_the_answer_to_ltuae();

void do_other_stuff();

int main()

{
    std::future<int> the_answer = std::async(find_the_answer_to_ltuae);
    do_other_stuff();
    std::cout << "The answer is " << the_answer.get() << std::endl;
}

```

```c++
// 使用 std::async 向函数传递参数
#include <string>
#include <future>

struct X
{
    void foo(int, std::string const &);
    std::string bar(std::string const &);
};
X x;

auto f1 = std::async(&X::foo, &x, 42, "hello"); // 调用p->foo(42, "hello")，p是指向x的指针

auto f2 = std::async(&X::bar, x, "goodbye"); // 调用tmpx.bar("goodbye")， tmpx是x的拷贝副本

struct Y
{
    double operator()(double);
};
Y y;

auto f3 = std::async(Y(), 3.141); // 调用tmpy(3.141)，tmpy通过 Y 的移动构造函数得到

auto f4 = std::async(std::ref(y), 2.718); // 调用y(2.718)

X baz(X &);

auto t = std::async(baz, std::ref(x)); // 调用baz(x)

class move_only
{

public:
    move_only();
    move_only(move_only &&);
    move_only(move_only const &) = delete;
    move_only &operator=(move_only &&);
    move_only &operator=(move_only const &) = delete;

    void operator()();
};

auto f5 = std::async(move_only()); // 调用tmp()，tmp是通过std::move(move_only())构造得到
auto f6=std::async(std::launch::async,Y(),1.2); // 在新线程上执行
auto f7=std::async(std::launch::deferred,baz,std::ref(x)); // 在wait()或get()调用时执行

auto f8=std::async( 
 std::launch::deferred | std::launch::async, 
 baz,std::ref(x)); // 实现选择执行方式

auto f9=std::async(baz,std::ref(x)); 
f7.wait(); // 调用延迟函数

```


```c++
// std::packaged_task<> 的偏特化
template <>
class packaged_task<std::string(std::vector<char> *, int)>
{
public:
    template <typename Callable>
    explicit packaged_task(Callable &&f);

    std::future<std::string> get_future();
    void operator()(std::vector<char> *, int);
};

```

```c++
// 使用 std::packaged_task 执行一个图形界面线程
#include <deque>
#include <mutex>
#include <future>
#include <thread>
#include <utility>

std::mutex m;

std::deque<std::packaged_task<void()>> tasks;

bool gui_shutdown_message_received();

void get_and_process_gui_message();

void gui_thread() // 1

{
    while (!gui_shutdown_message_received()) // 2
    {
        get_and_process_gui_message(); // 3
        std::packaged_task<void()> task;
        {
            std::lock_guard<std::mutex> lk(m);
            if (tasks.empty()) // 4
                continue;
            task = std::move(tasks.front()); // 5
            tasks.pop_front();
        }
        task(); // 6
    }
}

std::thread gui_bg_thread(gui_thread);

template <typename Func>
std::future<void> post_task_for_gui_thread(Func f)
{
    std::packaged_task<void()> task(f);        // 7
    std::future<void> res = task.get_future(); // 8
    std::lock_guard<std::mutex> lk(m);
    tasks.push_back(std::move(task)); // 9
    return res;                       // 10
}

```

```c++
// 使用promise解决单线程多连接问题
#include <future>

void process_connections(connection_set &connections)
{
    while (!done(connections)) // 1
    {
        for (connection_iterator // 2
                 connection = connections.begin(),
                 end = connections.end();
             connection != end;
             ++connection)
        {
            if (connection->has_incoming_data()) // 3
            {
                data_packet data = connection->incoming();
                std::promise<payload_type> &p =
                    connection->get_promise(data.id); // 4
                p.set_value(data.payload);
            }
            if (connection->has_outgoing_data()) // 5
            {
                outgoing_packet data =
                    connection->top_of_outgoing_queue();
                connection->send(data.payload);
                data.promise.set_value(true); // 6
            }
        }
    }
}

```

```c++
// 限时等待
// 处理持续时间的变量以 _for 作为后缀,处理绝对时间的变量以 _until 作为后缀。

// 代码4.11 等待条件变量满足条件——有超时功能
#include <condition_variable>
#include <mutex>
#include <chrono>

std::condition_variable cv;

bool done;

std::mutex m;

bool wait_loop()
{
    auto const timeout = std::chrono::steady_clock::now() +
                         std::chrono::milliseconds(500);
    std::unique_lock<std::mutex> lk(m);
    while (!done)
    {
        if (cv.wait_until(lk, timeout) == std::cv_status::timeout)
            break;
    }
    return done;
}

```

```c++
// 4.3.4 使用超时
// 使用超时的最简单方式，就是对特定线程添加延迟处理。当线程无所事事时，就不会占用其他线程的处理时间.

```

```c++
// 4.4 简化代码
//  spawn_task的简单实现
template <typename F, typename A>
std::future<std::result_of<F(A &&)>::type>
spawn_task(F &&f, A &&a)
{
    typedef std::result_of<F(A &&)>::type result_type;
 std::packaged_task<result_type(A&&)> task(std::move(f)));
 std::future<result_type> res(task.get_future());
 std::thread t(std::move(task), std::move(a));
 t.detach();
 return res;
}
```

```c++
// 代码4.15 ATM逻辑类的简单实现
struct card_inserted
{
    std::string account;
};

class atm
{
    messaging::receiver incoming;
    messaging::sender bank;
    messaging::sender interface_hardware;
    void (atm::*state)();

    std::string account;
    std::string pin;

    void waiting_for_card() // 1
    {
        interface_hardware.send(display_enter_card()); // 2
        incoming.wait().                               // 3
            handle<card_inserted>(
                [&](card_inserted const &msg) // 4
                {
                    account = msg.account;
                    pin = "";
                    interface_hardware.send(display_enter_pin());
                    state = &atm::getting_pin;
                });
    }
    void getting_pin();

public:
    void run() // 5
    {
        state = &atm::waiting_for_card; // 6
        try
        {
            for (;;)
            {
                (this->*state)(); // 7
            }
        }
        catch (messaging::close_queue const &)
        {
        }
    }
};

/*
 这种程序设计的方式被称为参与者模式(Actor model)——在系统中有很多独立的(运行在一个独立的线程上)参与者，这些参与者会互相发送信息，去执行手头上的任务，并且不会共享状态，除非是通过信息直接传入的。
*/

// 代码4.16 简单ATM实现中的getting_pin状态函数
void atm::getting_pin()
{
    incoming.wait()
        .handle<digit_pressed>( // 1
            [&](digit_pressed const &msg)
            {
                unsigned const pin_length = 4;
                pin += msg.digit;
                if (pin.length() == pin_length)
                {
                    bank.send(verify_pin(account, pin, incoming));
                    state = &atm::verifying_pin;
                }
            })
        .handle<clear_last_pressed>( // 2
            [&](clear_last_pressed const &msg)
            {
                if (!pin.empty())
                {
                    pin.resize(pin.length() - 1);
                }
            })
        .handle<cancel_pressed>( // 3
            [&](cancel_pressed const &msg)
            {
                state = &atm::done_processing;
            });
}

```

```c++
// 代码4.17 使用并发技术扩展规范中的特性，实现与 std::async 等价的功能
template <typename Func>
std::experimental::future<decltype(std::declval<Func>()())>
spawn_async(Func &&func)
{
    std::experimental::promise<decltype(std::declval<Func>()())> p;
    auto res = p.get_future();
    std::thread t(
        [p = std::move(p), f = std::decay_t<Func>(func)]() mutable
        {
            try
            {
                p.set_value_at_thread_exit(f());
            }
            catch (...)
            {
                p.set_exception_at_thread_exit(std::current_exception());
            }
        });
    t.detach();
    return res;
}
```

```c++
// 4.4.4 持续性连接
// 代码4.18 处理用户登录——同步方式
void process_login(std::string const &username, std::string const &password)
{
    try
    {
        user_id const id = backend.authenticate_user(username, password);
        user_data const info_to_display = backend.request_current_info(id);
        update_display(info_to_display);
    }
    catch (std::exception &e)
    {
        display_error(e);
    }
}

// 代码4.19 处理用户登录——异步方式
std::future<void> process_login(std::string const &username, std::string const &password)
{
    return std::async(std::launch::async, [=]()
                      { 
        try{ 
            user_id consst id = backend.authenticate_user(username, password); 
            user_data const info_to_display = 
            backend.request_current_info(id); 
            update_display(info_to_display); 
        } 
        catch(std::exception& e){ 
        display_error(e); 
 } });
}

// 码4.20 处理用户登录——持续性方式
std::experimental::future<void> process_login(std::string const &username, std::string const &password)
{
    return spawn_async([=]()
                       { return backend.authenticate_user(username, password); })
        .then([](std::experimental::future<user_id> id)
              { return backend.request_current_info(id.get()); })
        .then([](std::experimental::future<user_data> info_to_display){ 
            try{ 
            update_display(info_to_display.get()); 
            } 
    
            catch(std::exception& e){ 
            display_error(e); 
            } });
    }

// 代码4.21 处理用户登录——全异步操作
std::experimental::future<void> process_login(std::string const &username, std::string const &password)
{
    return backend.async_authenticate_user(username, password).then([](std::experimental::future<user_id> id)
                                                                    { return backend.async_request_current_info(id.get()); })
        .then([](std::experimental::future<user_data> info_to_display)
              { 
                try{ 
                update_display(info_to_display.get()); 
                } 
                catch(std::exception& e){ 
                display_error(e); 
                } });
}

```

```c++
// std::experimental::latch：基础的锁存器类型
//构造 std::experimental::latch 时，将计数器的值作为构造函数的唯一参数。当等待的事件发生，就会调用锁存器count_down成员函数。当计数器为0时，锁存器状态变为就绪。可以调用wait成员函数对锁存器进行阻塞，直到等待的锁存器处于就绪状态。如果需要对锁存器是否就绪的状态进行检查，可调用is_ready成员函数。想要减少计数器1并阻塞直至0，则可以调用count_down_and_wait成员函数

// 代码4.25 使用 std::experimental::latch 等待所有事件
void foo()
{
    unsigned const thread_count = ...;
    latch done(thread_count); // 1
    my_data data[thread_count];
    std::vector<std::future<void>> threads;
    for (unsigned i = 0; i < thread_count; ++i)
        threads.push_back(std::async(std::launch::async, [&, i] { // 2 通过引用的方式对除了i之外的所有内容进行捕获
            data[i] = make_data(i);
            done.count_down(); // 3
            do_more_stuff();   // 4
        }));
    done.wait();                      // 5
    process_data(data, thread_count); // 6
} // 7

```


```c++
// std::experimental::barrier：简单的栅栏
//并发技术扩展规范提供了两种栅栏机制， <experimental/barrier> 头文件中，分别为： std::experimental::barrier 和 std::experimental::flex_barrier

// 当每个线程完成其处理任务时，都会到达栅栏处，并且通过调用栅栏对象的arrive_and_wait成员函数，等待小组的其他线程.

//代码4.26 std::experimental::barrier 的用法
result_chunk process(data_chunk);

std::vector<data_chunk> divide_into_chunks(data_block data, unsigned num_threads);

void process_data(data_source &source, data_sink &sink)
{
    unsigned const concurrency = std::thread::hardware_concurrency();
    unsigned const num_threads = (concurrency > 0) ? concurrency : 2;

    std::experimental::barrier sync(num_threads);
    std::vector<joining_thread> threads(num_threads);

    std::vector<data_chunk> chunks;
    result_block result;

    for (unsigned i = 0; i < num_threads; ++i)
    {
        threads[i] = joining_thread([&, i]
                                    { 
 while (!source.done()) { // 6 
    if (!i) { // 1 
    data_block current_block = 
         source.get_next_data_block(); 
    chunks = divide_into_chunks( 
    current_block, num_threads); 
    } 
    sync.arrive_and_wait(); // 2 
    result.set_chunk(i, num_threads, process(chunks[i])); // 3 
    sync.arrive_and_wait(); // 4 
    if (!i) { // 5 
    sink.write_data(std::move(result)); 
    } 
    } });
    }
} // 7


```

```c++
// 4.27 使用 std::experimental::flex_barrier 管理串行部分
   void process_data(data_source &source, data_sink &sink)
{
    unsigned const concurrency = std::thread::hardware_concurrency();
    unsigned const num_threads = (concurrency > 0) ? concurrency : 2;

    std::vector<data_chunk> chunks;

    auto split_source = [&] { // 1
        if (!source.done())
        {
            data_block current_block = source.get_next_data_block();
            chunks = divide_into_chunks(current_block, num_threads);
        }
    };

    split_source(); // 2

    result_block result;

    std::experimental::flex_barrier sync(num_threads, [&] { // 3
        sink.write_data(std::move(result));
        split_source(); // 4
        return -1;      // 5
    });
    std::vector<joining_thread> threads(num_threads);

    for (unsigned i = 0; i < num_threads; ++i)
    {
        threads[i] = joining_thread([&, i]
                                    { 
    while (!source.done()) { // 6 
    result.set_chunk(i, num_threads, process(chunks[i])); 
    sync.arrive_and_wait(); // 7 
    } });
    }
} 

```

```c++
// 本章总结
// 同步操作对于用并发编程来说是很重要的一部分.如果没有同步，线程基本上就是独立的，因其任务之间的相关性，才可作为一个整体直接执行.
// 本章讨论了各式各样的同步操作，有条件变量、future、promise、打包任务、锁存器和栅栏
// 替代同步的解决方案：函数式编程，完全独立执行的函数，不会受到外部环境的影响，以及消息传递模式，以消息子系统为中介，向线程异步的发送消息和持续性方式，其指定了操作的后续任务，并由系统负责调度

```