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
