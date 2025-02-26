#include <iostream>
#include <thread>
#include <memory>
#include <string>

using namespace std;

// day-2025-2-24
// void thread_work1(std::string str)
// {
//     cout << "str is : " << str << endl;
// }

// struct func
// {
//     int &_i;
//     func(int &i)
//         : _i(i)
//     {
//     }

//     void operator()()
//     {
//         for (int i = 0; i < 3; ++i)
//         {
//             _i = i;
//             cout << "_i is " << _i << endl;
//             std::this_thread::sleep_for(std::chrono::seconds(1));
//         }
//     }
// };

// void oops()
// {
//     int some_local_state = 0;
//     func mf(some_local_state);
//     std::thread functhread(mf);
//     // //隐患，访问局部变量，局部变量可能会随着 } 结束而回收或随着主线程退出而回收
//     functhread.detach();
// }

// // int main()
// // {
// //     std::thread t1(thread_work1, "hello world!~");
// //     t1.join();

// //     oops();
// //     std::this_thread::sleep_for(std::chrono::seconds(1));

// //     return 0;
// // }

// // 线程守卫

// class thread_guard
// {
// private:
//     std::thread &_t;

// public:
//     explicit thread_guard(std::thread &t)
//         : _t(t)
//     {
//     }
//     ~thread_guard()
//     {
//         if (_t.joinable())
//         {
//             _t.join();
//         }
//     }
//     thread_guard(thread_guard const &) = delete;
//     thread_guard &operator=(thread_guard const &) = delete;
// };

// void auto_guard()
// {
//     int some_local_state = 0;
//     func mf(some_local_state);
//     std::thread t(mf);
//     thread_guard g(t);
//     cout << "auto guard finished" << endl;
// }

// void print_str(int i, std::string const &s)
// {
//     std::cout << "i is " << i << " str is " << s << std::endl;
// }

// void danger_oops(int some_param)
// {
//     char buf[1024];
//     sprintf(buf, "%i", some_param);
//     std::thread t(print_str, 3, buf);
//     t.detach();
// }
// void safe_oops(int some_param)
// {
//     char buffer[1024];
//     sprintf(buffer, "%i", some_param);
//     std::thread t(print_str, 3, std::string(buffer));
//     t.detach();
// }

// int main()
// {
//     // auto_guard();
//     // danger_oops(3);
//     safe_oops(3);
//     std::this_thread::sleep_for(std::chrono::seconds(1));
//     return 0;
// }

// void change_param(int &param)
// {
//     param++;
// }

// void ref_oops(int some_param)
// {
//     cout << "Before change, param is " << some_param << endl;
//     std::thread t2(change_param, std::ref(some_param));
//     t2.join();
//     cout << "After change, param is " << some_param << endl;
// }

// void deal_unique(std::unique_ptr<int> p)
// {
//     cout << "unique ptr data is " << *p << endl;
//     (*p)++;
//     cout << "unique ptr data is " << *p << endl;
// }

// void move_oops()
// {
//     auto p = std::make_unique<int>(100);
//     std::thread t(deal_unique, std::move(p));
//     t.join();

//     // 不能再使用p了，p已经被move废弃
//     // cout << "after shared ptr data is " << *p << endl;
// }
// int main()
// {
//     // ref_oops(3);
//     move_oops();
//     return 0;
// }

// day-2025-2-26
//  线程管控
void some_function()
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void some_other_function()
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

// int main()
// {
//     // t1 绑定some_function
//     std::thread t1(some_function);

//     // 2 转移t1管理的线程给t2，转移后t1无效
//     std::thread t2 = std::move(t1);

//     // 3 t1 可继续绑定其他线程,执行some_other_function
//     t1 = std::thread(some_other_function);

//     // 4  创建一个线程变量t3
//     std::thread t3;

//     // 5  转移t2管理的线程给t3
//     t3 = std::move(t2);

//     // 6  转移t3管理的线程给t1
//     t1 = std::move(t3);

//     std::this_thread::sleep_for(std::chrono::seconds(2000));
// }

class joining_thread
{
private:
    std::thread t;

public:
    joining_thread() noexcept = default;
    template <typename Callable, typename... Args>
    explicit joining_thread(Callable &&func, Args &&...args)
        : t(std::forward<Callable>(func), std::forward<Args>(args)...) {}
    explicit joining_thread(std::thread _t) noexcept
        : t(std::move(_t)) {}
    joining_thread(joining_thread &&other) noexcept
        : t(std::move(other.t)) {}

    joining_thread &operator=(joining_thread &&other) noexcept
    {
        // //如果当前线程可汇合，则汇合等待线程完成再赋值
        if (t.joinable())
        {
            t.join();
        }
        t = std::move(other.t);
        return *this;
    }
    // joining_thread &operator=(joining_thread other) noexcept
    // {
    //     // 如果当前线程可汇合，则汇合等待线程完成再赋值
    //     if (t.joinable())
    //     {
    //         t.join();
    //     }
    //     t = std::move(other.t);
    //     return *this;
    // }

    ~joining_thread() noexcept
    {
        if (t.joinable())
        {
            t.join();
        }
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

void use_jointhread()
{
    // 1 根据线程构造函数构造joiningthread
    joining_thread j1([](int maxindex)
                      {
        for (int i = 0; i < maxindex; i++) {
            std::cout << "in thread id " << std::this_thread::get_id()
                << " cur index is " << i << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        } }, 10);

    // 2 根据thread构造joiningthread
    joining_thread j2(std::thread([](int maxindex)
                                  {
        for (int i = 0; i < maxindex; i++) {
            std::cout << "in thread id " << std::this_thread::get_id()
                << " cur index is " << i << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        } }, 10));

    // 3 根据thread构造j3
    joining_thread j3(std::thread([](int maxindex)
                                  {
        for (int i = 0; i < maxindex; i++) {
            std::cout << "in thread id " << std::this_thread::get_id()
                << " cur index is " << i << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        } }, 10));

    // 4 把j3赋值给j1，joining_thread内部会等待j1汇合结束后
    // 再将j3赋值给j1
    j1 = std::move(j3);
}
// void use_vector()
// {
//     std::vector<std::thread> threads;
//     for (unsigned i = 0; i < 10; ++i)
//     {
//         threads.emplace_back(param_function, i);
//     }

//     for (auto &entry : threads)
//     {
//         entr y.join();
//     }
// }
// int main()
// {
//     // use_jointhread();
//     cout << std::thread::hardware_concurrency() << endl;

//     return 0;
// }