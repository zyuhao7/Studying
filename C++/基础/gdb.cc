#include <iostream>
#include <thread>
#include <vector>
#include <unistd.h>

using namespace std;

// gdb 调试
/*
    命令	作用
    gdb                 ./a.out	载入可执行文件
    break 行号/函数名	设置断点
    run	                运行程序
    next（n）	        单步执行（不进入函数）
    step（s）	        单步进入函数
    continue（c）	    继续运行直到下一个断点
    print 变量名	    打印变量的值
    backtrace（bt）	    打印函数调用栈
    info locals	        查看当前函数局部变量
    info args	        查看当前函数参数
    list（l）	        查看源代码
    quit	            退出 GDB

    gdb ./a.out core    载入 core 文件 查看崩溃时的调用栈
    多线程调试（info threads、thread 线程号）
    查看内存 （x 命令）
*/

volatile int counter = 0; 

void worker()
{
    for (int i = 0; i < 100000; ++i)
    {
        counter++; 
    }
}

int main()
{
    std::thread t1(worker);
    std::thread t2(worker);

    t1.join();
    t2.join();

    std::cout << "Final counter: " << counter << std::endl;
}

// void safe_function()
// {
//     while (true)
//     {
//         std::this_thread::sleep_for(std::chrono::seconds(1));
//     }
// }

// void crash_function()
// {
//     sleep(2);
//     int *p = nullptr;
//     *p = 42;
// }

// int main()
// {
//     std::vector<std::thread> threads;
//     for (int i = 0; i < 3; ++i)
//     {
//         threads.emplace_back(safe_function);
//     }
//     threads.emplace_back(crash_function);
//     for (auto &t : threads)
//     {
//         t.join();
//     }

//     return 0;
// }
