```bash
# 本章主要内容
        · 共享数据的问题
        · 用互斥保护数据
        · 保护数据的替代方案
```
___
```C++
// 使用互斥量保护列表
std::list<int> some_list; // 1

std::mutex some_mutex; // 2

void add_to_list(int new_value)
{
    std::lock_guard<std::mutex> guard(some_mutex); // 3
    some_list.push_back(new_value);
}

bool list_contains(int value_to_find)
{
    std::lock_guard<std::mutex> guard(some_mutex); // 4
    return std::find(some_list.begin(), some_list.end(), value_to_find) !=
           some_list.end();
}

// C++17中添加了一个新特性，称为模板类参数推导.
// 类似std::lock_guard 这样简单的模板类型，其模板参数列表可以省略

std::lock_guard guard(some_mutex);  // 3 4 可以简写.
std::scoped_lock guard(some_mutex); //加强版数据保护机制.

```
___
```C++
// 无意中传递了保护数据的引用
class some_data
{
    int a;
    std::string b;

public:
    void do_something()
    {
        cout << "do_something()" << endl;
    }
};

class data_wrapper
{

private:
    some_data data;
    std::mutex m;

public:
    template <typename Function>
    void process_data(Function func) // 过程数据.
    {
        std::lock_guard<std::mutex> l(m);
        func(data); // 1 传递“保护”数据给用户函数
    }
};

some_data *unprotected;

void malicious_function(some_data &protected_data)
{
    unprotected = &protected_data;
}

data_wrapper x;

void foo()
{
    x.process_data(malicious_function); // 2 传递一个恶意函数
    unprotected->do_something();        // 3 在无保护的情况下访问保护数据
}
```
___
```c++
// std::stack 容器的实现
template <typename T, typename Container = std::deque<T>>
class stack
{
public:
    explicit stack(const Container &);
    explicit stack(Container && = Container());

    template <class Alloc>
    explicit stack(const Alloc &);

    template <class Alloc>
    stack(const Container &, const Alloc &);

    template <class Alloc>
    stack(Container &&, const Alloc &);

    template <class Alloc>
    stack(stack &&, const Alloc &);

    bool empty() const;
    size_t size() const;
    T &top();
    T const &top() const;
    void push(T const &);
    void push(T &&);
    void pop();
    void swap(stack &&);

    template <class... Args>
    void emplace(Args &&...args); // C++14的新特性
};
```

```C++
// 线程安全的堆栈类定义
#include <exception>
#include <memory> // For std::shared_ptr<>

struct empty_stack : std::exception
{
    const char *what() const throw();
};

template <typename T>
class threadsafe_stack
{
public:
    threadsafe_stack();
    threadsafe_stack(const threadsafe_stack &);
    threadsafe_stack &operator=(const threadsafe_stack &) = delete; // 1 赋值操作被删除

    void push(T new_value);
    std::shared_ptr<T> pop();
    void pop(T &value);
    bool empty() const;
};
```
___

```C++
// 扩充(线程安全)堆栈
#include <exception>
#include <memory>
#include <mutex>
#include <stack>

struct empty_stack : std::exception
{
    const char *what() const throw()
    {
        return "empty stack!";
    };
};

template <typename T>
class threadsafe_stack
{
private:
    std::stack<T> data;
    mutable std::mutex m;

public:
    threadsafe_stack()
        : data(std::stack<T>()) {}

    threadsafe_stack(const threadsafe_stack &other)
    {
        std::lock_guard<std::mutex> lock(other.m);
        data = other.data; // 1 在构造函数体中的执行拷贝
    }

    threadsafe_stack &operator=(const threadsafe_stack &) = delete;

    void push(T new_value)
    {
        std::lock_guard<std::mutex> lock(m);
        data.push(new_value);
    }

    std::shared_ptr<T> pop()
    {
        std::lock_guard<std::mutex> lock(m);
        if (data.empty())
            throw empty_stack(); // 在调用pop前，检查栈是否为空

        std::shared_ptr<T> const res(std::make_shared<T>(data.top())); // 在修改堆栈前，分配出返回值
        data.pop();
        return res;
    }
    void pop(T &value)
    {
        std::lock_guard<std::mutex> lock(m);
        if (data.empty())
            throw empty_stack();

        value = data.top();
        data.pop();
    }

    bool empty() const
    {
        std::lock_guard<std::mutex> lock(m);
        return data.empty();
    }
};
```
___
```bash
# 死锁: 一对线程需要对他们所有的互斥量做一些操作，其中每个线程都有一个互斥量，且等待另一个解锁。因为他们都在等待对方释放互斥量，没有线程能工作。这种情况就是死锁，它的问题就是由两个或两个以上的互斥量进行锁定。

# 交换操作中使用 std::lock() 和 std::lock_guard 
class some_big_object
{
};

void swap(some_big_object &lhs, some_big_object &rhs);

class X
{

private:
    some_big_object some_detail;
    std::mutex m;

public:
    X(some_big_object const &sd)
        : some_detail(sd) {}

    friend void swap(X &lhs, X &rhs)
    {
        if (&lhs == &rhs)
            return;
        std::lock(lhs.m, rhs.m);                                    // 1
        std::lock_guard<std::mutex> lock_a(lhs.m, std::adopt_lock); // 2
        std::lock_guard<std::mutex> lock_b(rhs.m, std::adopt_lock); // 3
        swap(lhs.some_detail, rhs.some_detail);
    }

    
};
# C++17对这种情况提供了支持, std::scoped_lock<>  是一种新的RAII模板类型,与 std::lock_guard<> 的功能相同，这个新类型能接受不定数量的互斥量类型作为模板参数，以及相应的互斥量(数量和类型)作为构造参数。互斥量支持构造时上锁，与 std::lock 的用法相同，解锁在析构中进行。
```

```C++
// 交换操作中 std::lock() 和 std::unique_lock 的使用

class some_big_object
{
};

void swap(some_big_object &lhs, some_big_object &rhs);
class X
{
private:
    some_big_object some_detail;
    std::mutex m;

public:
    X(some_big_object const &sd)
        : some_detail(sd) {}
        
    friend void swap(X &lhs, X &rhs)
    {
        if (&lhs == &rhs)
            return;
        std::unique_lock<std::mutex> lock_a(lhs.m, std::defer_lock); // 1

        std::unique_lock<std::mutex> lock_b(rhs.m, std::defer_lock); // 1
                                                                     // 留下未上锁的互斥量 std::defer_lock
        std::lock(lock_a, lock_b);                                   // 2 互斥量在这里上锁
        swap(lhs.some_detail, rhs.some_detail);
    }
};
```

```c++
// std::call_once 的替代方案
class my_class
{
};

my_class &get_my_class_instance()
{
    static my_class instance; // 线程安全的初始化过程
    return instance;
}

```

```C++
/*              std::shared_mutex 的共享锁
  唯一的限制：当有线程拥有共享锁时，尝试获取独占锁的线程会被阻塞，直到所有其他线程放弃锁。当任一线程拥有一个独占锁时，其他线程就无法获得共享锁或独占锁，直到第一个线程放弃其拥有的锁。
*/

//           std::shared_mutex 对数据结构进行保护
#include <map>
#include <string>
#include <mutex>
#include <shared_mutex>
class dns_entry
{
};

class dns_cache
{
    std::map<std::string, dns_entry> entries;
    mutable std::shared_mutex entry_mutex;

public:
    dns_entry find_entry(std::string const &domain) const
    {
        std::shared_lock<std::shared_mutex> lk(entry_mutex); // 1
        std::map<std::string, dns_entry>::const_iterator const it =
            entries.find(domain);
        return (it == entries.end()) ? dns_entry() : it->second;
    }
    void update_or_add_entry(std::string const &domain,
                             dns_entry const &dns_details)
    {
        std::lock_guard<std::shared_mutex> lk(entry_mutex); // 2
        entries[domain] = dns_details;
    }
};
```

```bash
#                           总结
 本章讨论了当线程间的共享数据发生恶性条件竞争时，将会带来多么严重的灾难。还讨论了如何使用 std::mutex 和如何避免这些问题。虽然C++标准库提供了一些工具来避免这些问题，但互斥量并不是灵丹妙药，也还有自己的问题(比如：死锁)。还见识了一些用于避免死锁的技术，之后了解了锁的所有权转移，以及围绕如何选取适当粒度锁产生的问题。最后，在具体情况下讨论了其他数据保护的方案，例如: std::call_once() 和 std::shared_mutex.
还有一个方面没有涉及，那就是等待其他线程作为输入的情况。我们的线程安全栈，仅是在栈为空时，抛出一个异常，所以当一个线程要等待其他线程向栈压入一个值时(这是线程安全栈的主要用途之一)，它需要多次尝试去弹出一个值，当捕获抛出的异常时，再次进行尝试。这种消耗资源的检查，没有任何意义。并且，不断的检查会影响系统中其他线程的运行，这反而会妨碍程序的运行。我们需要一些方法让一个线程等待其他线程完成任务，但在等待过程中不占用CPU。

```