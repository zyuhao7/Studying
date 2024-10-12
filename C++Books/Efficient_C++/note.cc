#include <iostream>
#include <string>
#include <mutex>
#include <chrono>
using namespace std;
// day-2024-10-10
// 第一章 跟踪实例
// 第二章 构造函数和析构函数

// 线程同步的方式:
// 1. 信号量(semaphore)、 2. 互斥(mutex) 3. 临界区 (critical section)

// 临界区是指某一时间只能由一个线程执行的一个代码段.
/*
    get_the_lock(CSLock);
    {   // 临界区开始
        // 被保护的计算
    }   // 临界区结束
    release_the_lock(CSLock);

class Lock
{
public:
    Lock(pthread_mutex_t &key)
        : theKey(key)
    {
        pthread_mutex_lock(&theKey);
    }
    ~Lock()
    {
        pthread_mutex_unlock(&theKey);
    }

private:
    pthread_mutex_t &theKey;
};



#include <unistd.h>
#include <pthread.h>

class BaseLock
{
public:
    // LogSource 对象在下文解释
    BaseLock(pthread_mutex_t &key, LogSource &lsrc) {}
    virtual ~BaseLock() {}
};

class MutexLock : public BaseLock
{
public:
    MutexLock(pthread_mutex_t &key, LogSource &lsrc);
    ~MutexLock();

private:
    pthread_mutex_t &theKey;
    LogSource &src;
};

MutexLock::MutexLock(pthread_mutex_t &akey, LogSource &source)
    : BaseLock(aKey, source),
      theKey(aKey),
      src(source)
{
    pthread_mutex_lock(&theKey);
#if defined(DEBUG)
    cout << "MutexLock " << &aKey << "created at " << src.file() << "line" << src.line() << endl;
#endif
}

MutexLock::~MutexLock()
{
    pthread_mutex_unlock(&theKey);
#if defined(DEBUG)
    cout << "MutexLock " << &aKey << "destroyed at " << src.file() << "line" << src.line() << endl;
#endif
}

// LogSource
class BaseLogSource
{
public:
    BaseLogSource() {}
    virtual ~BaseLogSource() {}
};

class LogSource : public BaseLogSource
{
public:
    LogSource(const char *name, int num)
        : filename(name),
          lineNum(num)
    {
    }
    ~LogSource() {}

private:
    char *filename;
    int lineNum;
};

    // 假设 sharedCounter 是一个可以由多个线程访问且需要序列化的整数变量.
    {
        MutexLock myLock(theKey, LogSource(__FILE__, __LINE__));
        sharedCounter++;
        // 这个版本涉及到四个构造和析构, BaseLock、MutexLock、BaseLogSource、LogSource.

        pthread_mutex_lock(&theKey);
        sharedCounter++;
        pthread_mutex_unlock(&theKey);

    }
*/

// day-2024-10-12
// 第三章 虚函数

// 无法内联虚函数对性能造成的损失最大.
// 模板比继承提供更好的性能.

// 第四章 返回值优化 (Return Value Optimization RVO)

// class Complex
// {
//     friend Complex operator+(const Complex &, const Complex &);

// public:
//     Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}
//     Complex(const Complex &c) : real(c.real), imag(c.imag) {}
//     Complex(const Complex &x, const Complex &y)
//         : real(x.real + y.real),
//           imag(x.imag + y.imag)
//     {
//     }

//     Complex &operator=(const Complex &c)
//     {
//         real = c.real;
//         imag = c.imag;
//         return *this;
//     }
//     ~Complex() {}

// private:
//     double real;
//     double imag;
// };

// // 按值返回.
// Complex operator+(const Complex &a, const Complex &b)
// {
//     // 版本一
//     Complex res;
//     res.real = a.real + b.real;
//     res.imag = a.imag + b.imag;
//     return res;

//     // 版本二
//     // double r = a.real + b.real;
//     // double i = a.imag + b.imag;
//     // return Complex(r, i);

//     // 版本三
//     // Complex retVal(a.real + b.real, a.imag + b.imag);
//     // return retVal;

//     // 版本四
//     // return Complex(a.real + b.real, a.imag + b.imag);

//     // 版本五
//     return Complex(a, b);
// }

// int main()
// {

//     Complex a(1, 0);
//     Complex b(2, 0);
//     Complex c;
//     auto start = std::chrono::high_resolution_clock::now();

//     for (int i = 0; i < 100000000; ++i) // 一亿次.
//     {
//         // c = a + b; // 版本 1 593 mil
//         // c = a + b; // 版本 2 756 mil
//         // c = a + b; // 版本 3 615 mil
//         // c = a + b; // 版本 4 594 mil
//         // c = a + b; // 版本 5 820 mil
//     }
//     auto end = std::chrono::high_resolution_clock::now();

//     auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

//     std::cout << "spends: " << duration.count() << " milliseconds" << std::endl;

//     return 0;
// }

// 如果必须按值返回对象, 通过 RVO 可以省去创建和销毁局部对象的步骤, 从而改善性能.
// RVO 的应用要遵循编译器的实现而定, 这需要考虑编译器文档或实验来判断是否使用 RVO 以及何时使用.
// 通过编写计算性构造函数可以更好滴使用 RVO.