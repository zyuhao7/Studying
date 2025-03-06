#include <iostream>
#include <thread>
#include <mutex>
#include <stack>
#include <chrono>

using namespace std;
// day-2025-2-28
// C++ 互斥与死锁
// std::mutex m1;
// int shared_data = 100;

// void use_lock()
// {
//     while (true)
//     {
//         m1.lock();
//         shared_data++;
//         cout << "current thread is " << std::this_thread::get_id() << ", shared data is " << shared_data << endl;
//         m1.unlock();
//         std::this_thread::sleep_for(std::chrono::seconds(1));
//     }
// }

// void test_lock()
// {
//     std::thread t1(use_lock);
//     std::thread t2([]()
//                    {
//         while(true)
//         {
//             m1.lock();
//             shared_data--;
//             cout<<"current thread is "<<std::this_thread::get_id()<<", shared data is "<<shared_data<<endl;
//             m1.unlock();
//             std::this_thread::sleep_for(std::chrono::seconds(1));
//         } });
//     t1.join();
//     t2.join();
// }

// int main()
// {
//     test_lock();
//     return 0;
// }

// lock_guard的使用
//  对 std::mutex 进行 RAII 封装，即构造时 lock，析构时 unlock

// 如何保证数据安全

// template <typename T>
// class threadsafe_stack1
// {
// private:
//     std::stack<T> data;
//     mutable std::mutex m;

// public:
//     threadsafe_stack1() {}
//     threadsafe_stack1(const threadsafe_stack1 &other)
//     {
//         std::lock_guard<std::mutex> lock(other.m);
//         data = other.data;
//     }
//     threadsafe_stack1 &operator=(const threadsafe_stack1 &) = delete;
//     void Push(T new_value)
//     {
//         std::lock_guard<std::mutex> lock(m);
//         data.push(std::move(new_value));
//     }
//     // to fix , have bug
//     T Pop()
//     {
//         std::lock_guard<std::mutex> lock(m);
//         if (data.empty())
//         {
//             throw empty_stack();
//         }
//         T top = data.top();
//         data.pop();
//         return top;
//     }

//     bool empty() const
//     {
//         std::lock_guard<std::mutex> lock(m);
//         return data.empty();
//     }
// };
// void test_threadsafe_stack1()
// {
//     threadsafe_stack1<int> safe_stack;
//     safe_stack.Push(1);

//     std::thread t1([&safe_stack]()
//                    {
//         if(!safe_stack.empty())
//         {
//             std::this_thread::sleep_for(std::chrono::seconds(1));
//             safe_stack.Pop();
//         } });

//     std::thread t2([&safe_stack]()
//                    {
//         if(!safe_stack.empty())
//         {
//             std::this_thread::sleep_for(std::chrono::seconds(1));
//             safe_stack.Pop();
//         } });
//     t1.join();
//     t2.join();
// }

// int main()
// {
//     test_threadsafe_stack1(); // 1 段错误
//     return 0;
// }

// struct empty_stack : std::exception
// {
//     const char *what() const throw();
// };

// const char *empty_stack::what() const throw()
// {
//     return "empty stack!";
// }

// template <typename T>
// class threadsafe_stack
// {
// private:
//     std::stack<T> data;
//     mutable std::mutex m;

// public:
//     threadsafe_stack() {}
//     threadsafe_stack(const threadsafe_stack &other)
//     {
//         std::lock_guard<std::mutex> lock(other.m);
//         data = other.data;
//     }
//     threadsafe_stack &operator=(const threadsafe_stack &) = delete;
//     void Push(T new_value)
//     {
//         std::lock_guard<std::mutex> lock(m);
//         data.push(std::move(new_value));
//     }

//     shared_ptr<T> Pop()
//     {
//         std::lock_guard<std::mutex> lock(m);
//         if (data.empty())
//         {
//             throw empty_stack();
//         }
//         std::shared_ptr<T> const result = std::make_shared<T>(data.top());
//         data.pop();
//         return result;
//     }

//     void pop(T &value)
//     {
//         std::lock_guard<std::mutex> lock(m);
//         if (data.empty())
//         {
//             throw empty_stack();
//         }
//         value = data.top();
//         data.pop();
//     }

//     bool empty() const
//     {
//         std::lock_guard<std::mutex> lock(m);
//         return data.empty();
//     }
// };
// void test_threadsafe_stack()
// {
//     threadsafe_stack<int> safe_stack;
//     safe_stack.Push(1);

//     std::thread t1([&safe_stack]()
//                    {
//         if(!safe_stack.empty())
//         {
//             std::this_thread::sleep_for(std::chrono::seconds(1));
//             safe_stack.Pop();
//         } });

//     std::thread t2([&safe_stack]()
//                    {
//         if(!safe_stack.empty())
//         {
//             std::this_thread::sleep_for(std::chrono::seconds(1));
//             safe_stack.Pop();
//         } });
//     t1.join();
//     t2.join();
// }

// int main()
// {
//     test_threadsafe_stack();
//     return 0;
// }

// std::mutex t_lock1;
// std::mutex t_lock2;

// int m_1 = 0;
// int m_2 = 0;

// void deal_lock1()
// {
//     while (true)
//     {
//         cout << "deal lock1 begin" << endl;
//         t_lock1.lock();
//         std::this_thread::sleep_for(std::chrono::seconds(6));

//         m_1 = 1024;
//         t_lock2.lock();
//         m_2 = 2028;
//         t_lock2.unlock();
//         t_lock1.unlock();
//         cout << "deal lock1 end" << endl;
//     }
// }

// void deal_lock2()
// {
//     while (true)
//     {
//         cout << "deal lock2 begin" << endl;
//         t_lock2.lock();
//         std::this_thread::sleep_for(std::chrono::seconds(6));

//         m_2 = 2028;

//         t_lock1.lock();
//         m_1 = 1024;

//         t_lock1.unlock();
//         t_lock2.unlock();

//         cout << "deal lock2 end" << endl;
//     }
// }

// void test_deal_lock()
// {
//     std::thread t1(deal_lock1);
//     std::thread t2(deal_lock2);
//     t1.join();
//     t2.join();
// }

// int main()
// {
//     test_deal_lock();
//     return 0;
// }

// 同时加锁
// class some_big_object
// {
// public:
//     some_big_object(int data) : _data(data) {}
//     some_big_object(const some_big_object &other) : _data(other._data) {}
//     some_big_object(const some_big_object &&other) : _data(std::move(other._data)) {}

//     friend std::ostream &operator<<(std::ostream &os, const some_big_object &obj)
//     {
//         os << obj._data;
//         return os;
//     }

//     some_big_object &operator=(const some_big_object &other)
//     {
//         if (this == &other)
//             return *this;
//         _data = other._data;
//         return *this;
//     }

//     // 交换数据
//     friend void swap(some_big_object &b1, some_big_object &b2)
//     {
//         some_big_object temp = std::move(b1);
//         b1 = std::move(b2);
//         b2 = std::move(temp);
//     }

// private:
//     int _data;
// };

// class big_object_mgr
// {
// public:
//     big_object_mgr(int data) : _obj(data) {}
//     void printinfo()
//     {
//         cout << "current obj  data is " << _obj << endl;
//     }
//     friend void danger_swap(big_object_mgr &objm1, big_object_mgr &objm2);
//     friend void safe_swap(big_object_mgr &objm1, big_object_mgr &objm2);
//     friend void safe_swap_scope(big_object_mgr &objm1, big_object_mgr &objm2);

// private:
//     std::mutex _m;
//     some_big_object _obj;
// };

// void danger_swap(big_object_mgr &objm1, big_object_mgr &objm2)
// {
//     cout << "thread [" << std::this_thread::get_id() << "] begin" << endl;
//     if (&objm1 == &objm2)
//         return;
//     std::lock_guard<std::mutex> guard1(objm1._m);
//     std::this_thread::sleep_for(std::chrono::seconds(1));
//     std::lock_guard<std::mutex> guard2(objm2._m);
//     swap(objm1._obj, objm2._obj);
//     cout << "thread [" << std::this_thread::get_id() << "] end" << endl;
// }

// void test_danger_swap()
// {
//     big_object_mgr objm1(5);
//     big_object_mgr objm2(100);

//     std::thread t1(danger_swap, std::ref(objm1), std::ref(objm2));
//     std::thread t2(danger_swap, std::ref(objm2), std::ref(objm1));
//     t1.join();
//     t2.join();

//     objm1.printinfo();
//     objm2.printinfo();
// }

// void safe_swap(big_object_mgr &objm1, big_object_mgr &objm2)
// {
//     cout << "thread [" << std::this_thread::get_id() << "] begin" << endl;
//     if (&objm1 == &objm2)
//         return;
//     std::lock(objm1._m, objm2._m);
//     std::lock_guard<std::mutex> guard1(objm1._m, adopt_lock);
//     std::this_thread::sleep_for(std::chrono::seconds(1));
//     std::lock_guard<std::mutex> guard2(objm2._m, adopt_lock);

//     swap(objm1._obj, objm1._obj);
//     cout << "thread [" << std::this_thread::get_id() << "] end" << endl;
// }

// void test_safe_swap()
// {
//     big_object_mgr objm1(5);
//     big_object_mgr objm2(100);

//     std::thread t1(safe_swap, std::ref(objm1), std::ref(objm2));
//     std::thread t2(safe_swap, std::ref(objm2), std::ref(objm1));
//     t1.join();
//     t2.join();

//     objm1.printinfo();
//     objm2.printinfo();
// }

// // 层级锁
// class hierarchical_mutex
// {
// public:
//     explicit hierarchical_mutex(unsigned long value) : _hierarchy_value(value),
//                                                        _previous_hierarchy_value(0) {}
//     hierarchical_mutex(const hierarchical_mutex &) = delete;
//     hierarchical_mutex &operator=(const hierarchical_mutex &) = delete;
//     void lock()
//     {
//         check_for_hierarchy_violation();
//         _internal_mutex.lock();
//         update_hierarchy_value();
//     }

//     void unlock()
//     {
//         if (_this_thread_hierarchy_value != _hierarchy_value)
//         {
//             throw std::logic_error("mutex hierarchy violated");
//         }

//         _this_thread_hierarchy_value = _previous_hierarchy_value;
//         _internal_mutex.unlock();
//     }

//     bool try_lock()
//     {
//         check_for_hierarchy_violation();
//         if (_internal_mutex.try_lock())
//         {
//             return false;
//         }

//         update_hierarchy_value();
//         return true;
//     }

// private:
//     std::mutex _internal_mutex;
//     // 当前层级值
//     unsigned long const _hierarchy_value;
//     // 上一次层级值
//     unsigned long _previous_hierarchy_value;
//     // 本线程记录的层级值
//     static thread_local unsigned long _this_thread_hierarchy_value;

//     void check_for_hierarchy_violation()
//     {
//         if (_this_thread_hierarchy_value <= _hierarchy_value)
//         {
//             throw std::logic_error("mutex  hierarchy violated");
//         }
//     }

//     void update_hierarchy_value()
//     {
//         _previous_hierarchy_value = _this_thread_hierarchy_value;
//         _this_thread_hierarchy_value = _hierarchy_value;
//     }
// };
// #include <climits>
// thread_local unsigned long hierarchical_mutex::_this_thread_hierarchy_value(ULONG_MAX);

// void test_hierarchy_lock()
// {
//     hierarchical_mutex hmtx1(1000);
//     hierarchical_mutex hmtx2(500);
//     std::thread t1([&hmtx1, &hmtx2]()
//                    {
//             hmtx1.lock();
//             hmtx2.lock();
//             hmtx2.unlock();
//             hmtx1.unlock(); });

//     std::thread t2([&hmtx1, &hmtx2]()
//                    {
//             hmtx2.lock();
//             hmtx1.lock();
//             hmtx1.unlock();
//             hmtx2.unlock(); });

//     t1.join();
//     t2.join();
// }

// int main()
// {
//     // test_hierarchy_lock();
//     // test_safe_swap();
//     // test_danger_swap();
//     return 0;
// }

// 死锁发生的四个条件?
//  互斥条件、 非抢占条件、 循环等待条件、 占有并等待条件.