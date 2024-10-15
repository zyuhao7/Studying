#include <iostream>
#include <string>
#include <mutex>
#include <chrono>
#include <vector>
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

// day-2024-10-13
// 第五章 临时对象

// 临时对象会以构造函数和析构函数的形式降低一半的性能.
//  将构造函数声明为 explicit, 可以阻止编译器在幕后使用类型转换.
// 编译器尝尝创建临时对象来解决类型不匹配问题, 通过函数重载可以避免这种情况.
// 如果可能, 尽量避免使用对象拷贝, 按引用传递和返回对象.
// 在 <op> 可能是 "+ - * / " 的地方, 使用 <op> = 运算符消除临时对象.

// 第六章 单线程内存池
// 版本 0 全局函数 new() 和 delete()

// class Rational
// {
//     friend Rational operator+(const Rational &, const Rational &);

// public:
//     Rational(int a = 0, int b = 1)
//         : m(a),
//           n(b)
//     {
//     }

// private:
//     int m; // 分子
//     int n; // 分母
// };
// 版本 1 专用 Rational 内存管理器

// 将空闲列表声明为 Rational 类的静态成员, Rational的操作符 new() 和 delete() 可以管理该
// 静态列表.

// class NextOnFreeList
// {
// public:
//     NextOnFreeList *next;
// };

// class Rational
// {
//     friend Rational operator+(const Rational &, const Rational &);

// public:
//     Rational(int a = 0, int b = 1)
//         : m(a),
//           n(b) {}
//     inline void *operator new(size_t size);
//     inline void operator delete(void *doomed, size_t size);

//     static void newMemPool() { expandTheFreeList(); }
//     static void deleteMemPool();

// private:
//     static void expandTheFreeList();
//     enum
//     {
//         EXPANSION_SIZE = 32
//     };
//     int m;                           // 分子
//     int n;                           // 分母
//     static NextOnFreeList *freeList; // Rational 对象的空闲列表.
// };

// inline void *Rational::operator new(size_t size)
// {
//     if (0 == freeList) // 如果列表为空, 则将其填满.
//     {
//         expandTheFreeList();
//     }
//     NextOnFreeList *head = freeList;
//     freeList = head->next;
//     return head;
// }

// inline void Rational::operator delete(void *doomed, size_t size)
// {
//     NextOnFreeList *head = static_cast<NextOnFreeList *>(doomed);
//     head->next = freeList;
//     freeList = head;
// }

// void Rational::expandTheFreeList()
// {
//     // 我们必须分配足够大的对象以包含下一个指针.
//     size_t size = (sizeof(Rational) > sizeof(NextOnFreeList *)) ? sizeof(Rational) : sizeof(NextOnFreeList *);

//     NextOnFreeList *runner = reinterpret_cast<NextOnFreeList *>(new char[size]);
//     freeList = runner;
//     for (int i = 0; i < EXPANSION_SIZE; ++i)
//     {
//         runner->next = reinterpret_cast<NextOnFreeList *>(new char[size]);
//         runner = runner->next;
//     }
//     runner->next = nullptr;
// }

// void Rational::deleteMemPool()
// {
//     NextOnFreeList *nextPtr;
//     for (nextPtr = freeList; nextPtr != nullptr; nextPtr = freeList)
//     {
//         freeList = freeList->next;
//         delete[] nextPtr;
//     }
// }

// NextOnFreeList *Rational::freeList = nullptr;

// 版本 2 固定大小对象的内存池

// template <class T>
// class MemoryPool
// {
// public:
//     MemoryPool(size_t size = EXPANSION_SIZE);
//     ~MemoryPool();

//     // 从空闲列表中分配 T 元素.
//     inline void *alloc(size_t size);

//     // 返回 T 元素到空闲列表中
//     inline void free(void *someElement);

// private:
//     // 空闲列表的下一个元素.
//     MemoryPool<T> *next;

//     // 如果空闲列表为空, 按该大小扩展它
//     enum
//     {
//         EXPANSION_SIZE = 32
//     };
//     // 添加空闲元素到空闲列表
//     void expandTheFreeList(int howMany = EXPANSION_SIZE);
// };

// template <class T>
// MemoryPool<T>::MemoryPool(size_t size)
// {
//     expandTheFreeList(size);
// }

// // 析构函数遍历空闲列表并且删除所有元素
// template <class T>
// MemoryPool<T>::~MemoryPool()
// {
//     MemoryPool<T> *nextPtr = next;
//     for (nextPtr = next; nextPtr != NULL; nextPtr = next)
//     {
//         next = next->next;
//         delete nextPtr;
//     }
// }

// // 成员函数 alloc() 为 T 元素分配足够大的空间. 如果空闲列表用尽, 则调用 expandTheFreeList() 来扩充它.
// template <class T>
// inline void *MemoryPool<T>::alloc(size_t)
// {
//     if (!next)
//     {
//         expandTheFreeList();
//     }
//     MemoryPool<T> *head = next;
//     next = head->next;
//     return head;
// }

// template <class T>
// inline void MemoryPool<T>::free(void *doomed)
// {
//     MemoryPool<T> *head = static_cast<MemoryPool<T> *>(doomed);
//     head->next = next;
//     next = head;
// }

// // expandTheFreeList() 用来向空闲列表添加新元素. 首先从堆上分配新元素, 然后把他们连接到列表中.
// template <class T>
// void MemoryPool<T>::expandTheFreeList(int howMany)
// {
//     size_t size = (sizeof(T) > sizeof(MemoryPool<T> *)) ? sizeof(T) : sizeof(MemoryPool<T> *);

//     MemoryPool<T> *runner = reinterpret_cast<MemoryPool<T> *>(new char[size]);

//     next = runner;
//     for (int i = 0; i < howMany; ++i)
//     {
//         runner->next = reinterpret_cast<MemoryPool<T> *>(new char[size]);
//         runner = runner->next;
//     }
//     runner->next = nullptr;
// }
// class Rational
// {
// public:
//     Rational(int a = 0, int b = 1)
//         : n(a),
//           d(b)
//     {
//     }
//     void *operator new(size_t size)
//     {
//         return memPool->alloc(size);
//     }

//     void operator delete(void *doomed, size_t size)
//     {
//         memPool->free(doomed);
//     }

//     static void newMemPool() { memPool = new MemoryPool<Rational>; }
//     static void deleteMemPool() { delete memPool; }

// private:
//     int n; // 分子
//     int d; // 分母
//     static MemoryPool<Rational> *memPool;
// };

// MemoryPool<Rational> *Rational::memPool = nullptr;

// 版本 3 单线程可变大小内存管理器

// class MemoryChunk
// {
// public:
//     MemoryChunk(MemoryChunk *nextChunk, size_t ChunkSize);
//     ~MemoryChunk() { delete[] reinterpret_cast<char *>(mem); }

//     inline void *alloc(size_t size);
//     inline void free(void *someElement);

//     // 指向列表下一内存块的指针.
//     MemoryChunk *nextMemChunk() { return next; }

//     // 当前内存块剩余空间大小
//     size_t spaceAvailable()
//     {
//         return chunkSize - bytesAlreadyAllocated;
//     }

//     enum
//     {
//         DEFAULT_CHUNK_SIZE = 4096
//     };

// private:
//     MemoryChunk *next;
//     void *mem;

//     // 内存块大小
//     size_t chunkSize;

//     // 当前内存块已分配字节数
//     size_t bytesAlreadyAllocated;
// };

// MemoryChunk::MemoryChunk(MemoryChunk *nextChunk, size_t reqSize)
// {
//     chunkSize = (reqSize > DEFAULT_CHUNK_SIZE) ? reqSize : DEFAULT_CHUNK_SIZE;
//     next = nextChunk;
//     bytesAlreadyAllocated = 0;
//     mem = new char[chunkSize];
// }

// void *MemoryChunk::alloc(size_t reqSize)
// {
//     if (bytesAlreadyAllocated + reqSize > chunkSize)
//     {
//         return nullptr; // Not enough space
//     }
//     void *addr = reinterpret_cast<char *>(mem) + bytesAlreadyAllocated;
//     bytesAlreadyAllocated += reqSize;
//     return addr;
// }

// inline void MemoryChunk::free(void *doomed)
// {
//     // No-op (since we are using a pool, individual freeing is not needed)
// }

// class ByteMemoryPool
// {
// public:
//     ByteMemoryPool(size_t initSize = MemoryChunk::DEFAULT_CHUNK_SIZE);
//     ~ByteMemoryPool();

//     // 从私有内存池分配内存.
//     inline void *alloc(size_t size);

//     // 释放先前从内存池中分配的内存
//     inline void free(void *someElement);

// private:
//     // 内存块列表. 他是我们的私有存储空间
//     MemoryChunk *listOfMemoryChunks;

//     // 向我们的私有内存添加一个内存块
//     void expandStorage(size_t reqSize);
// };

// ByteMemoryPool::ByteMemoryPool(size_t initSize)
// {
//     listOfMemoryChunks = nullptr;
//     expandStorage(initSize);
// }

// ByteMemoryPool::~ByteMemoryPool()
// {
//     MemoryChunk *memChunk = listOfMemoryChunks;
//     while (memChunk)
//     {
//         listOfMemoryChunks = memChunk->nextMemChunk();
//         delete memChunk;
//         memChunk = listOfMemoryChunks;
//     }
// }

// void *ByteMemoryPool::alloc(size_t reqSize)
// {
//     size_t space = listOfMemoryChunks->spaceAvailable();
//     if (space < reqSize)
//     {
//         expandStorage(reqSize);
//     }
//     return listOfMemoryChunks->alloc(reqSize);
// }

// inline void ByteMemoryPool::free(void *doomed)
// {
//     listOfMemoryChunks->free(doomed);
// }

// void ByteMemoryPool::expandStorage(size_t reqSize)
// {
//     listOfMemoryChunks = new MemoryChunk(listOfMemoryChunks, reqSize);
// }

// class Rational
// {
// public:
//     Rational(int a = 0, int b = 1)
//         : n(a),
//           d(b)
//     {
//     }

//     void *operator new(size_t size) { return memPool->alloc(size); }
//     void operator delete(void *doomed, size_t size) { memPool->free(doomed); }

//     static void newMemPool() { memPool = new ByteMemoryPool; }
//     static void deleteMemPool() { delete memPool; }

// private:
//     int n;
//     int d;
//     static ByteMemoryPool *memPool;
// };

// ByteMemoryPool *Rational::memPool = nullptr;

// int main()
// {
// 测量全局函数 new() 和 delete() 的基准性能.
// Rational *array[1000];
// auto start = chrono::high_resolution_clock::now();
// for (int j = 0; j < 5000; j++)
// {
//     for (int i = 0; i < 1000; ++i)
//     {
//         array[i] = new Rational(i);
//     }
//     for (int i = 0; i < 1000; ++i)
//     {
//         delete array[i];
//     }
// }
// auto end = chrono::high_resolution_clock::now();
// auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
// std::cout << "spends: " << duration.count() << " milliseconds" << std::endl;
// 版本 0  212 mil

// Rational *array[1000];
// Rational::newMemPool();
// auto start = chrono::high_resolution_clock::now();
// for (int j = 0; j < 5000; j++)
// {
//     for (int i = 0; i < 1000; ++i)
//     {
//         array[i] = new Rational(i);
//     }
//     for (int i = 0; i < 1000; ++i)
//     {
//         delete array[i];
//     }
// }
// auto end = chrono::high_resolution_clock::now();
// auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
// std::cout << "spends: " << duration.count() << " milliseconds" << std::endl; // 版本 1 28 mil
// Rational::deleteMemPool();

// Rational *array[1000];
// Rational::newMemPool();
// auto start = chrono::high_resolution_clock::now();
// for (int j = 0; j < 5000; j++)
// {
//     for (int i = 0; i < 1000; ++i)
//     {
//         array[i] = new Rational(i);
//     }
//     for (int i = 0; i < 1000; ++i)
//     {
//         delete array[i];
//     }
// }
// auto end = chrono::high_resolution_clock::now();
// auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
// std::cout << "spends: " << duration.count() << " milliseconds" << std::endl; // 版本 2  41 mil
// Rational::deleteMemPool();

// Rational *array[1000];
// Rational::newMemPool();
// auto start = chrono::high_resolution_clock::now();
// for (int j = 0; j < 5000; j++)
// {
//     for (int i = 0; i < 1000; ++i)
//     {
//         array[i] = new Rational(i);
//     }
//     for (int i = 0; i < 1000; ++i)
//     {
//         delete array[i];
//     }
// }
// auto end = chrono::high_resolution_clock::now();
// auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
// std::cout << "spends: " << duration.count() << " milliseconds" << std::endl; // 版本 3  85 mil
// Rational::deleteMemPool();

//     return 0;
// }

// 要点:
// 1. 灵活性以速度的降低为代价. 随着内存管理的功能和灵活性的增强, 执行速度降低.
// 2. 全局内存管理器(new()和delete()) 是通用的, 代价高.
// 3. 专用内存管理器比全局内存管理器块一个数量级以上.
// 4. 如果主要分配固定大小的内存块, 专用的固定大小内存管理器将明显地提升性能.
// 5. 如果主要分配限于单线程的内存块, 那么内存管理器也会有类似的性能提高. 由于省去了全局函数 new()和delete()必须
// 处理的并发问题, 单线程内存管理器的性能有所提高.

// day-2024-10-15
//  第七章 多线程版本内存池
// 7.1 版本四 实现多线程版内存池

// template <class T>
// class MemoryPool
// {
// public:
//     MemoryPool(size_t size = EXPANSION_SIZE);
//     ~MemoryPool();

//     // From freeList allocate T element.
//     inline void *alloc(size_t size);

//     // Return T element to freeList
//     inline void free(void *someElement);

// private:
//     // Next element in freeList.
//     MemoryPool<T> *next;

//     // If freeList is empty, expand it by this size
//     enum
//     {
//         EXPANSION_SIZE = 32
//     };

//     // Add free elements to freeList
//     void expandTheFreeList(int howMany = EXPANSION_SIZE);

//     // Keep track of allocated memory to free it properly
//     std::vector<char *> allocatedBlocks;
// };

// template <class T>
// MemoryPool<T>::MemoryPool(size_t size)
// {
//     next = nullptr;
//     expandTheFreeList(size);
// }

// // Destructor traverses the freeList and deletes all elements
// template <class T>
// MemoryPool<T>::~MemoryPool()
// {
//     MemoryPool<T> *nextPtr = next;
//     while (nextPtr != nullptr)
//     {
//         MemoryPool<T> *curr = nextPtr;
//         nextPtr = nextPtr->next;
//         delete curr; // Delete each element from the pool
//     }

//     // Free the actual memory blocks
//     for (char *block : allocatedBlocks)
//     {
//         delete[] block; // Properly delete the allocated char array
//     }
// }

// // Alloc function allocates enough space for T elements.
// // If freeList is empty, it calls expandTheFreeList() to expand it.
// template <class T>
// inline void *MemoryPool<T>::alloc(size_t)
// {
//     if (!next)
//     {
//         expandTheFreeList();
//     }
//     MemoryPool<T> *head = next;
//     next = head->next;
//     return head;
// }

// template <class T>
// inline void MemoryPool<T>::free(void *doomed)
// {
//     MemoryPool<T> *head = static_cast<MemoryPool<T> *>(doomed);
//     head->next = next;
//     next = head;
// }

// // expandTheFreeList() is used to add new elements to the freeList.
// template <class T>
// void MemoryPool<T>::expandTheFreeList(int howMany)
// {
//     size_t size = (sizeof(T) > sizeof(MemoryPool<T> *)) ? sizeof(T) : sizeof(MemoryPool<T> *);

//     // Allocate a block of memory for the free list elements
//     char *newBlock = new char[size * howMany];
//     allocatedBlocks.push_back(newBlock); // Keep track of the allocated block

//     MemoryPool<T> *runner = reinterpret_cast<MemoryPool<T> *>(newBlock);

//     next = runner;
//     for (int i = 0; i < howMany - 1; ++i)
//     {
//         runner->next = reinterpret_cast<MemoryPool<T> *>(newBlock + (i + 1) * size);
//         runner = runner->next;
//     }
//     runner->next = nullptr;
// }

// template <class POOLTYPE, class LOCK>
// class MTMemoryPool
// {
// public:
//     // 从 freeList 里分配一个元素
//     inline void *alloc(size_t size);

//     // 返回一个元素给 freeList
//     inline void free(void *someElement);

// private:
//     POOLTYPE stPool; // 单线程池
//     LOCK theLock;
// };

// // 在具体实现时, alloc() 方法将分配任务委托给内存池成员, 而将锁定任务委托给锁成员.
// template <class M, class L>
// inline void *MTMemoryPool<M, L>::alloc(size_t size)
// {
//     void *mem;
//     theLock.lock();
//     mem = stPool.alloc(size);
//     theLock.unlock();
//     return mem;
// }

// template <class M, class L>
// inline void MTMemoryPool<M, L>::free(void *doomed)
// {
//     theLock.lock();
//     stPool.free(doomed);
//     theLock.unlock();
// }

// class ABCLock
// {
// public:
//     virtual ~ABCLock() {}
//     virtual void lock() = 0;
//     virtual void unlock() = 0;
// };

// class MutexLock : public ABCLock
// {
// public:
//     inline void lock() override
//     {
//         mtx.lock();
//     }

//     inline void unlock() override
//     {
//         mtx.unlock();
//     }

// private:
//     std::mutex mtx;
// };

// class Rational
// {
// public:
//     Rational(int a = 0, int b = 1)
//         : n(a),
//           d(b == 0 ? 1 : b) // 防止分母为零
//     {
//     }

//     void *operator new(size_t size) { return memPool->alloc(size); }
//     void operator delete(void *doomed, size_t size) { memPool->free(doomed); }

//     static void newMemPool() { memPool = new MTMemoryPool<MemoryPool<Rational>, MutexLock>; }
//     static void deleteMemPool() { delete memPool; }

// private:
//     int n;
//     int d;
//     static MTMemoryPool<MemoryPool<Rational>, MutexLock> *memPool;
// };

// // Corrected static member initialization
// MTMemoryPool<MemoryPool<Rational>, MutexLock> *Rational::memPool = nullptr;

// int main()
// {
//     Rational *array[1000];
//     Rational::newMemPool();
//     auto start = std::chrono::high_resolution_clock::now();
//     for (int j = 0; j < 5000; j++)
//     {
//         for (int i = 0; i < 1000; ++i)
//         {
//             array[i] = new Rational(i);
//         }
//         for (int i = 0; i < 1000; ++i)
//         {
//             delete array[i];
//         }
//     }
//     auto end = std::chrono::high_resolution_clock::now();
//     auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
//     std::cout << "spends: " << duration.count() << " milliseconds" << std::endl; // 版本 4 298 mil
//     Rational::deleteMemPool();
//     return 0;
// }

// 全局内存管理 是通用的, 不过开销也很大.
// 单线程内存管理器比多线程内存管理器快得多, 所以分配大多数内存块限于单线程, 明显可以提升性能.
// 如果开发一条有效的单线程分配器 那么通过模版可以方便地将它们扩展到多线程中.
