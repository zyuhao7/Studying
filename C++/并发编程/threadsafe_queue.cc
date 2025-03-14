#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <memory>
#include <string>
#include <condition_variable>
using namespace std;
// day-2025-3-14
// 线程安全队列

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

template <typename T>
class threadsafe_que
{
public:
    threadsafe_que() {}
    void push(T val)
    {
        std::lock_guard<std::mutex> lock(m);
        data.push(std::move(val));
        cv.notify_one();
    }

    void wait_and_pop(T &val)
    {
        std::unique_lock<std::mutex> lock(m);
        cv.wait(lock, [this]()
                { return !data.empty(); });
        val = std::move(data.front());
        data.pop();
    }

    std::shared_ptr<T> wait_and_pop()
    {
        std::unique_lock<std::mutex> lock(m);
        cv.wait(lock, [this]()
                { return !data.empty(); });
        std::shared_ptr<T> res(
            std::make_shared<T>(std::move(data.front())));
        data.pop();
        return res;
    }

    bool try_pop(T &val)
    {
        std::lock_guard<std::mutex> lock(m);
        if (data.empty())
            return false;
        val = std::move(data.front());
        data.pop();
        return true;
    }
    std::shared_ptr<T> try_pop()
    {
        std::lock_guard<std::mutex> lock(m);
        if (data.empty())
            return std::shared_ptr<T>();
        std::shared_ptr<T> res(
            std::make_shared<T>(std::move(data.front())));
        data.pop();
        return true;
    }

    bool empty() const
    {
        std::lock_guard<std::mutex> lock(m);
        return data.empty();
    }

private:
    std::queue<T> data;
    mutable std::mutex m;
    std::condition_variable cv;
};

template <typename T>
class threadsafe_queue_ptr
{
private:
    mutable std::mutex mut;
    std::queue<std::shared_ptr<T>> data_queue;
    std::condition_variable data_cond;

public:
    threadsafe_queue_ptr()
    {
    }
    void wait_and_pop(T &value)
    {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk, [this]
                       { return !data_queue.empty(); });
        value = std::move(*data_queue.front()); // ⇽-- - ①
        data_queue.pop();
    }
    bool try_pop(T &value)
    {
        std::lock_guard<std::mutex> lk(mut);
        if (data_queue.empty())
            return false;
        value = std::move(*data_queue.front()); // ⇽-- - ②
        data_queue.pop();
        return true;
    }
    std::shared_ptr<T> wait_and_pop()
    {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk, [this]
                       { return !data_queue.empty(); });
        std::shared_ptr<T> res = data_queue.front(); // ⇽-- - ③
        data_queue.pop();
        return res;
    }
    std::shared_ptr<T> try_pop()
    {
        std::lock_guard<std::mutex> lk(mut);
        if (data_queue.empty())
            return std::shared_ptr<T>();
        std::shared_ptr<T> res = data_queue.front(); // ⇽-- - ④
        data_queue.pop();
        return res;
    }
    void push(T new_value)
    {
        std::shared_ptr<T> data(
            std::make_shared<T>(std::move(new_value))); // ⇽-- - ⑤
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(data);
        data_cond.notify_one();
    }
    bool empty() const
    {
        std::lock_guard<std::mutex> lk(mut);
        return data_queue.empty();
    }
};

std::mutex mtx_cout;
void PrintMyClass(std::string consumer, std::shared_ptr<MyClass> data)
{
    std::lock_guard<std::mutex> lock(mtx_cout);
    std::cout << consumer << " pop data success , data is " << (*data) << std::endl;
}

void TestThreadSafeQue()
{
    threadsafe_queue_ptr<MyClass> safe_que;
    std::thread consumer1(
        [&]()
        {
            for (;;)
            {
                std::shared_ptr<MyClass> data = safe_que.wait_and_pop();
                PrintMyClass("consumer1", data);
            }
        });

    std::thread consumer2([&]()
                          {
			for (;;)
			{
				std::shared_ptr<MyClass> data = safe_que.wait_and_pop();
				PrintMyClass("consumer2", data);
			} });

    std::thread producer([&]()
                         {
			for (int i = 0; i < 100; i++)
			{
				MyClass mc(i);
				safe_que.push(std::move(mc));
			} });

    consumer1.join();
    consumer2.join();
    producer.join();
}
int main()
{
    TestThreadSafeQue();
    return 0;
}