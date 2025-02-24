#include <iostream>
#include <thread>
#include <memory>
#include <string>

using namespace std;

// day-2024-2-24
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