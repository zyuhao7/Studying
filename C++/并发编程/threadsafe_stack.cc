#include <iostream>
#include <vector>
#include <exception>
#include <thread>
#include <mutex>
#include <string>
#include <stack>
#include <condition_variable>
using namespace std;
// 线程安全栈
// day-2025-3-14
class MyClass
{

public:
    MyClass() : _data(0)
    {
    }

    MyClass(int data) : _data(data)
    {
    }

    MyClass(const MyClass &mc)
    {
        // std::cout << "called MyClass const MyClass& version " << std::endl;
        _data = mc._data;
    }

    MyClass(MyClass &&mc) noexcept
    {
        // std::cout << "called MyClass  MyClass&& version " << std::endl;
        _data = std::move(mc._data);
    }

    friend std::ostream &operator<<(std::ostream &os, const MyClass &my)
    {
        os << "MyClass Data is " << my._data;
        return os;
    }

    MyClass &operator=(const MyClass &other)
    {
        _data = other._data;
        return *this;
    }

private:
    int _data;
};

struct empty_stack : public std::exception
{
    const char *what() const throw();
};

template <typename T>
class threadsafe_stack
{
public:
    threadsafe_stack() {}
    threadsafe_stack(const threadsafe_stack &other)
    {
        std::lock_guard<std::mutex> lock(other.m);
        data = other.data;
    }

    threadsafe_stack operator=(const threadsafe_stack &) = delete;

    void push(T val)
    {
        std::lock_guard<std::mutex> lock(m);
        data.push(std::move(val));
    }
    std::shared_ptr<T> pop()
    {
        std::lock_guard<std::mutex> lock(m);
        if (data.empty())
            throw empty_stack();

        std::shared_ptr<T> const res(
            std::make_shared<T>(std::move(data.top())));
        data.pop();
        return res;
    }

    void pop(T &val)
    {
        std::lock_guard<std::mutex> lock(m);
        if (data.empty())
            throw empty_stack();
        val = std::move(data.top());
        data.pop();
    }
    bool empty() const
    {
        std::lock_guard<std::mutex> lock(m);
        return data.empty();
    }

private:
    std::stack<T> data;
    mutable std::mutex m;
};


// 为了解决栈为空就抛出异常的问题，我们可以做如下优化
template <typename T>
class threadsafe_stack_waitable
{
private:
    std::stack<T> data;
    std::mutex m;
    std::condition_variable cv;

public:
    threadsafe_stack_waitable() {}
    threadsafe_stack_waitable(const threadsafe_stack_waitable &other)
    {
        std::lock_guard<std::mutex> lock(m);
        data = other.data;
    }
    threadsafe_stack_waitable operator=(const threadsafe_stack_waitable &other) = delete;

    void push(T val)
    {
        std::lock_guard<std::mutex> lock(m);
        data.push(std::move(val));
        cv.notify_one();
    }

    std::shared_ptr<T> wait_and_pop()
    {
        std::unique_lock<std::mutex> lock(m);
        cv.wait(lock, [this]()
                { 
                    if(data.empty()) return false;
                return true; });

        std::shared_ptr<T> const res(
            std::make_shared<T>(std::move(data.top())));
        data.pop();
        return res;
    }

    void wait_and_pop(T &val)
    {
        std::unique_lock<std::mutex> lock(m);
        cv.wait(lock, [this]()
                { 
            if(data.empty()) return false;
        return true; });
        val = std::move(data.top());
        data.pop();
    }

    bool empty() const
    {
        std::lock_guard<std::mutex> lock(m);
        return data.empty();
    }

    bool try_pop(T &val)
    {
        std::lock_guard<std::mutex> lock(m);
        if (data.empty())
            return false;
        val = std::move(data.top());
        data.pop();
        return true;
    }
    std::shared_ptr<T> try_pop()
    {
        std::lock_guard<std::mutex> lock(m);
        if (data.empty())
            return shared_ptr<T>();
        std::shared_ptr<T> const res(std::make_shared<T>(std::move(data.top())));
        data.pop();
        return res;
    }
};

std::mutex mtx_cout;
void PrintMyClass(std::string consumer, std::shared_ptr<MyClass> data)
{
    std::lock_guard<std::mutex> lock(mtx_cout);
    std::cout << consumer << " pop data success , data is " << (*data) << std::endl;
}

std::mutex mtx_cout;
void PrintMyClass(std::string consumer, std::shared_ptr<MyClass> data)
{
    std::lock_guard<std::mutex> lock(mtx_cout);
    std::cout << consumer << " pop data success , data is " << (*data) << std::endl;
}

void TestThreadSafeStack()
{
    threadsafe_stack_waitable<MyClass> stack;

    std::thread consumer1(
        [&]()
        {
            for (;;)
            {
                std::shared_ptr<MyClass> data = stack.wait_and_pop();
                PrintMyClass("consumer1", data);
            }
        });

    std::thread consumer2([&]()
                          {
			for (;;)
			{
				std::shared_ptr<MyClass> data = stack.wait_and_pop();
				PrintMyClass("consumer2", data);
			} });

    std::thread producer([&]()
                         {
			for(int i = 0 ; i < 100; i++)
			{
				MyClass mc(i);
				stack.push(std::move(mc));
			} });

    consumer1.join();
    consumer2.join();
    producer.join();
}
int main()
{
    TestThreadSafeStack();
    return 0;
}