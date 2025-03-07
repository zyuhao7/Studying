#include <iostream>
#include <future>
#include <chrono>
#include <string>
using namespace std;

// 定义异步任务
// string fetchDataFromDB(string query)
// {
//     std::this_thread::sleep_for(std::chrono::seconds(5));
//     return "Data : " + query;
// }

// int main()
// {
//     std::future<std::string> reusltFromDB = std::async(std::launch::async, fetchDataFromDB, "Data");
//     // 在主线程做其他事情
//     cout << "Doing something else..." << endl;

//     // 从 future对象中获取数据
//     string dbData = reusltFromDB.get();
//     cout << dbData << endl;

//     return 0;
// }

// int my_task()
// {
//     std::this_thread::sleep_for(std::chrono::seconds(5));
//     cout << "My task run  5 s" << endl;
//     return 42;
// }

// void use_package()
// {
//     // 创建一个包装了任务的 package_task 对象
//     std::packaged_task<int()> task(my_task);

//     // 获取与任务管理的 std::future 对象
//     std::future<int> result = task.get_future();

//     // 在另一个线程上执行
//     std::thread t(std::move(task));
//     t.detach();

//     // 等待任务并获取结果
//     int value = result.get();
//     cout << "The value is : " << value << endl;
// }

// int main()
// {
//     use_package();
// }

// promise 用法
// std::promise用于在某一线程中设置某个值或异常，而std::future则用于在另一线程中获取这个值或异常。
// void set_promise(std::promise<int> prom)
// {
//     prom.set_value(10);
// }

// int main()
// {
//     // 创建一个 promise 对象
//     std::promise<int> prom;

//     // 获取与prom相关联的 future 对象
//     std::future<int> fut = prom.get_future();

//     // 在新线程中设置 prom 的值
//     std::thread t(set_promise, std::move(prom));

//     // 在主线程获取 future 的值
//     std::cout << "Waiting for the thread to set the value...\n";
//     std::cout << "Value set by the thread: " << fut.get() << '\n';
//     t.join();
// }

// void set_exception(std::promise<void> prom)
// {
//     try
//     {
//         // 抛出一个异常
//         throw std::runtime_error("An error occurred!");
//     }
//     catch (...)
//     {
//         // 设置 promise 的异常
//         prom.set_exception(std::current_exception());
//     }
// }

// int main()
// {
//     // 创建一个 promise 对象
//     std::promise<void> prom;

//     // 获取与 promise 相关联的 future 对象
//     std::future<void> fut = prom.get_future();

//     // 在新线程中设置 promise 的异常
//     std::thread t(set_exception, std::move(prom));

//     // 在主线程中获取 future 的异常
//     try
//     {
//         std::cout << "Waiting for the thread to set the exception...\n";
//         fut.get();
//     }
//     catch (const std::exception &e)
//     {
//         std::cout << "Exception set by the thread: " << e.what() << '\n';
//     }
//     t.join();
//     return 0;
// }

// void set_value(std::promise<int> prom)
// {
//     std::this_thread::sleep_for(std::chrono::microseconds(100000));
//     prom.set_value(120);
// }

// void use_promise_destruct()
// {
//     std::thread t;
//     std::future<int> fut;
//     {
//         // 创建一个 promise 对象
//         std::promise<int> prom;
//         // 获取与 promise 相关联的 future 对象
//         fut = prom.get_future();
//         // 在新线程中设置 promise 的值
//         t = std::thread(set_value, std::move(prom));
//     }
//     // 在主线程中获取 future 的值
//     std::cout << "Waiting for the thread to set the value...\n";
//     std::cout << "Value set by the thread: " << fut.get() << '\n';
//     t.join();
// }

// int main()
// {
//     use_promise_destruct();
// }

// void myFunction(std::promise<int> &&promise)
// {
//     // 模拟一些工作
//     std::this_thread::sleep_for(std::chrono::seconds(1));
//     promise.set_value(42); // 设置 promise 的值
// }

// void threadFunction(std::shared_future<int> future)
// {
//     try
//     {
//         int result = future.get();
//         std::cout << "Result: " << result << std::endl;
//     }
//     catch (const std::future_error &e)
//     {
//         std::cout << "Future error: " << e.what() << std::endl;
//     }
// }

// void use_shared_future()
// {
//     std::promise<int> promise;
//     std::shared_future<int> future = promise.get_future();

//     std::thread myThread1(myFunction, std::move(promise)); // 将 promise 移动到线程中

//     // 使用 share() 方法获取新的 shared_future 对象
//     std::thread myThread2(threadFunction, future);

//     std::thread myThread3(threadFunction, future);

//     myThread1.join();
//     myThread2.join();
//     myThread3.join();
// }

// int main()
// {
//     use_shared_future();
// }

// 线程池

