#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <memory>
#include <queue>
using namespace std;

// Day-2025-3-7
std::mutex mtx;
int num = 1;
void PoorImpleman()
{
    std::thread t1([]()
                   { 
                for (;;)
                {
                    {
                        std::lock_guard<std::mutex> lock(mtx);
                        if(num == 1)
                        {
                            cout << "Thread A print 1! " << endl;
                            num++;
                            continue;
                        }
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                } });

    std::thread t2([]()
                   { 
             for (;;)
             {
                 {
                     std::lock_guard<std::mutex> lock(mtx);
                     if(num == 2)
                     {
                         cout << "Thread B print 2! " << endl;
                         num--;
                         continue;
                     }
                 }
                 std::this_thread::sleep_for(std::chrono::milliseconds(500));
             } });
    t1.join();
    t2.join();
}

std::condition_variable cvA;
std::condition_variable cvB;

// 用条件变量唤醒等待执行的线程
void ResonableImplemention()
{
    std::thread t1([]()
                   { 
                    for(;;)
                    {
                        std::unique_lock<std::mutex> lock(mtx);
                        cvA.wait(lock, []()
                                 { 
                                    return num == 1;
                                 }
                            );
                        num++;
                        cout << "Thread A print 1!" << endl;
                        cvB.notify_one();
                    } });

    std::thread t2([]()
                   { 
                    for(;;)
                    {
                        std::unique_lock<std::mutex> lock(mtx);
                        cvB.wait(lock, []()
                                 { 
                                    return num == 2;
                                 }
                            );
                        num--;
                        cout << "Thread B print 2!" << endl;
                        cvA.notify_one();
                    } });
    t1.join();
    t2.join();
}

// 线程安全队列
template <typename T>
class threadsafe_queue
{
private:
    std::mutex mtx;
    queue<T> que;
    condition_variable data_cond;

public:
    void push(T new_value)
    {
        std::lock_guard<std::mutex> lock(mtx);
        que.push(new_value);
        data_cond.notify_one();
    }
    void wait_and_pop(T &val)
    {
        std::unique_lock<std::mutex> lock(mtx);
        data_cond.wait(lock, [this]()
                       { return !que.empty(); });
        val = que.front();
        que.pop();
    }
};

// 我们可以启动三个线程，一个producer 线程用来向队列中放入数据。一个consumer1线程用来阻塞等待pop队列中的元素。
// 另一个consumer2尝试从队列中pop元素，如果队列为空则直接返回，如果非空则pop元素。
// 打印时为了保证线程输出在屏幕上不会乱掉，所以加了锁保证互斥输出。
void test_safe_que()
{
    threadsafe_queue<int> safe_que;
    std::mutex mtx;
    // 生产者线程
    std::thread producer([&]()
                         { 
                            for (int i = 0;; i ++)
                            {
                                safe_que.push(i);
                                {
                                    std::lock_guard<std::mutex> lock(mtx);
                                    cout << "Producer push data is " << i << endl;
                                }
                                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                            } });
    // 消费者线程1
    std::thread consumer1([&]()
                          { 
                        for (;;)
                        {
                            int data = 0;
                            safe_que.wait_and_pop(data);
                            {
                                std::lock_guard<std::mutex> lock(mtx);
                                cout << "Consumer1 wait and pop data is " << data << endl;
                            }
                            std::this_thread::sleep_for(std::chrono::milliseconds(500));
                        } });

    std::thread consumer2([&]()
                          { 
                      for (;;)
                      {
                          int data = 0;
                          safe_que.wait_and_pop(data);
                          {
                              std::lock_guard<std::mutex> lock(mtx);
                              cout << "Consumer2 wait and pop data is " << data << endl;
                          }
                          std::this_thread::sleep_for(std::chrono::milliseconds(500));
                      } });
    producer.join();
    consumer1.join();
    consumer2.join();
}

int main()
{
    // PoorImpleman();
    // ResonableImplemention();
    test_safe_que();
    return 0;
}