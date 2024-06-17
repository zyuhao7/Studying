#include <mutex>
#include <iostream>
#include <thread>
#include <condition_variable>
#include <memory>
#include <queue>
#include <future>
#include <vector>
#include <functional>
#include <chrono>

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
auto f7=std::async(std::launch::deferred, baz, std::ref(x)); // 在wait()或get()调用时执行

auto f8=std::async( 
 std::launch::deferred | std::launch::async, 
 baz,std::ref(x)); // 实现选择执行方式

auto f9=std::async(baz,std::ref(x)); 
f7.wait(); // 调用延迟函数

template <>
class packaged_task<std::string(std::vector<char> *, int)>
{
public:
    template <typename Callable>
    explicit packaged_task(Callable &&f);

    std::future<std::string> get_future();
    void operator()(std::vector<char> *, int);
};

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



void do_something()
{
    unsigned long long s = 0;
    for (int i = 0; i < 10000000; ++i)
    {
        s += i;
    }
    std::cout << s << endl;
};

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

std::experimental::future<void> process_login(std::string const &username, std::string const &password)
{
    return spawn_async([=]()
                       { return backend.authenticate_user(username, password); })
        .then([](std::experimental::future<user_id> id)
              { return backend.request_current_info(id.get()); })
        .then([](std::experimental::future<user_data> info_to_display)
              { 
    try
    { 
    update_display(info_to_display.get()); 
    } 
    catch(std::exception& e){ 
    display_error(e); 
    } });
}

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
#endif


int main()
{

    // auto start = std::chrono::high_resolution_clock::now();
    // do_something();
    // auto stop = std::chrono::high_resolution_clock::now();

    // std::cout << "do_something() took " << std::chrono::duration<double, std::chrono::seconds>(stop - start).count()
    //           << "seconds" << std::endl;
    return 0;
}