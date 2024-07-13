## 单例模式

### 单例模式简介
>  单例模式指的是, 无论怎么获取, 永远只能得到该类类型的唯一实例对象.

```bash
# 一般遇到的 写进程池类、日志类、内存池(用来缓存数据的结构,在一处写或者多处读)的话就会用到 单例模式.

```

```c++
// 设计单例必须满足下面三个条件:
1. 全局只有一个实例，用 static 特性实现，构造函数设为私有
2. 通过公有接口获得实例.
3. 线程安全
```

```c++
// 饿汉单例模式
class CSingleton
{
public:
    static CSingleton *getInstance()
    {
        return &single;
    }

private:
    static CSingleton single;
    CSingleton()
    {
        cout << "CSingleton()" << endl;
    }
    ~CSingleton()
    {
        cout << "~CSingleton()" << endl;
    }
    CSingleton(const CSingleton &); // 防止外部拷贝构造.
};

CSingleton CSingleton::single;

```


```c++
// 懒汉单例模式
1.
class CSingleton
{
public:
    static CSingleton *getInstance()
    {
        if (single == nullptr)
        {
            single = new CSingleton(); // 没有 delete.
        }
        return single;
    }

private:
    static CSingleton *single;
    CSingleton() { cout << " CSingleton()" << endl; }
    ~CSingleton() { cout << " ~CSingleton()" << endl; }
    CSingleton(const CSingleton &);
};
CSingleton *CSingleton::single = nullptr;

2.
// 资源没释放,内存泄漏问题.. 嵌套类.
class CSingleton
{
public:
    static CSingleton *getInstance()
    {
        if (single == nullptr)
        {
            single = new CSingleton();
        }
        return single;
    }

private:
    static CSingleton *single;
    CSingleton() { cout << " CSingleton()" << endl; }
    ~CSingleton() { cout << " ~CSingleton()" << endl; }
    CSingleton(const CSingleton &);

    // 定义一个嵌套类, 在该类的析构函数中, 自动释放外层类的资源.
    class CRelease
    {
    public:
        ~CRelease()
        {
            delete single;
        }
    };
    // 通过该静态对象在程序结束时自动析构的特点,来释放外层类的对象资源.
    static CRelease release;
};
CSingleton *CSingleton::single = nullptr;
CSingleton::CRelease CSingleton::release;

```

```c++
// 线程安全的单例模式
// 1. 饿汉单例模式的线程安全特性.
// 饿汉单例模式中, 单例对象定义成了一个 static 静态对象,他是在程序启动时, main 函数运行之前就初始化好的, 因此不存在线程安全问题,可以在多线程运行.

// 2. 懒汉单例模式的线程安全特性
// 懒汉单例模式获取单例对象方法如下:
static CSingleton* getInstance()
{
    if(single == nullptr)
    {
        single = new CSingleton();
    }
    return single;
}
// 显然, getInstance 是个 不可重入函数, 在多线程中会出现竞态条件问题, single = new CSingleton() 会做三件事, 开辟内存,调用构造函数, 给 single 指针赋值, 在多线程中, 可能出现如下可能:

1. 线程 A 先调用 getInstance 函数,由于 single 为 nullptr, 进入 if 语句.
2. new 操作先开辟内存, 此时 A 现成的 CPU 时间片到了, 切换到 B 线程. 
3. B 线程由于 single 为 nullptr 也进入 if 语句了, 开始 new 操作.

//  使用，pthread库中提供的线程互斥操作方法 mutex 互斥锁 线程安全的懒汉单例模式.
class CSingleton
{
public:
    static CSingleton *getInstance1()
    {
        // 效率太低, 每次获取实例, 第一次加锁有必要, 后面都没必要. 
        // 获取互斥锁 
        pthread_mutex_lock(&mutex);
        if (nullptr == single)
        {
            single = new CSingleton();
        }
        // 释放互斥锁
        pthread_mutex_unlock(&mutex);
        return single;
    }

     static CSingleton *getInstance2()
     {
        if(single == nullptr)
        {
            // 获取互斥锁.
            pthread_mutex_lock(&mutex);
            // 锁 + 双重判断 
            if(single == nullptr)
            {
                single = new CSingleton();
            }
            // 释放互斥锁.
            pthread_mutex_unlock(&mutex);
        }
        return single;
     }

private:
    static CSingleton *single;
    CSingleton() { cout << "CSingleton()" << endl; }
    ~CSingleton()
    {
        pthread_mutex_destroy(&mutex); // 释放锁
        cout << "~CSingleton()" << endl;
    }
    CSingleton(const CSingleton &);

    class CRelease
    {
    public:
        ~CRelease() { delete single; }
    };
    static CRelease release;

    // 定义线程间的互斥锁
    static pthread_mutex_t mutex;
};
CSingleton *CSingleton::single = nullptr;
CSingleton::CRelease CSingleton::release;
// 互斥锁的初始化
pthread_mutex_t CSingleton::mutex = PTHREAD_MUTEX_INITIALIZER;

```


```c++
// 封装互斥锁的线程安全懒汉单例模式.
class CMutex
{
public:
    CMutex() { pthread_mutex_init(&mutex, NULL); };  // 初始化锁.
    ~CMutex() { pthread_mutex_destroy(&mutex); };    // 摧毁锁.
    void lock() { pthread_mutex_lock(&mutex); };     // 获取锁.
    void unlock() { pthread_mutex_unlock(&mutex); }; // 释放锁.

private:
    pthread_mutex_t mutex;
};

class CSingleton
{
public:
    static CSingleton *getInstance1()
    {
        if (single == nullptr)
        {
            mutex.lock();
            if (single == nullptr)
            {
                single = new CSingleton();
            }
            mutex.unlock();
        }
        return single;
    }

    // 以下代码是否线程安全？
     static CSingleton *getInstance2()
     {
        static CSingleton single;
        return &single;
     }
     // 对于 static 静态局部变量的初始化, 编译器会自动对它的初始化进行加锁和解锁控制, 使静态局部变量的初始化成为
     // 线程安全的操作, 不用担心多线程都会初始化静态局部变量!

private:
    CSingleton() { cout << "CSingleton()" << endl; }
    ~CSingleton() { cout << "~CSingleton()" << endl; }
    CSingleton(const CSingleton &);
    class CRelease
    {
    public:
        ~CRelease()
        {
            delete single;
        }
    };

    static CRelease release;
    static CSingleton *single;
    // 线程间的静态互斥锁.
    static CMutex mutex;
};
CSingleton *CSingleton::single = nullptr;
CSingleton::CRelease CSingleton::release;
// 定义互斥锁静态对象.
CMutex CSingleton::mutex;
```

```c++
// 单例对象为什么是 static ?

1. 唯一性：static 变量属于类，而不是类的某个实例。因此，static 变量在类的所有实例之间共享。通过将单例实例声明为 static，我们确保无论创建了多少对象引用，它们都指向同一个实例.

2. 全局访问：static 变量和方法可以通过类名直接访问,而不需要实例化类。这使得访问单例对象变得更简单和直观.

3. 生命周期控制：static 变量的生命周期与类加载和卸载一致，这通常贯穿这于整个应用程序的生命周期。确保了单例对象的持久性和全局可用性。

// 如何初始化？
    懒汉式 和 饿汉式
// 饿汉式. 在类加载时就创建单例对象，这种方式线程安全，因为类加载时对象已经被创建。
优点: 1. 实现简单. 2. 类加载时即完成实例化, 避免线程同步问题.
缺点: 类加载即创建对象, 可能导致资源浪费.

// 懒汉式. 只有在需要时才创建单例对象，通常使用双重检查锁定来确保线程安全。
优点: 延迟加载,节省资源.
缺点: 实现复杂, 需要处理线程同步问题. 


// 如何销毁？

1. 手动销毁
提供销毁单例对象的方法.

2. 使用智能指针
std::unique_ptr 自动管理内存,当程序结束时会自动销毁单例对象,避免内存泄漏。

3. 使用静态局部变量
 static Singleton& getInstance() {
        static Singleton instance;
        return instance;
    }
优点: 实现简洁，使用 static 关键字确保对象在第一次使用时初始化。线程安全,C++11标准确保了静态局部变量的初始化是线程安全的.

缺点: 无法手动控制对象的销毁，单例对象会在程序结束时自动销毁.

```
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
```C++
// Double-Checked Locking thesis (DCLP)

// from the header file
class Singleton
{
public:
    static Singleton* instance();

private:
    static Singleton* pInstance;
};

// from the implementation file
Singleton* Singleton::instance()
{
    if(pInstance == 0)
    {
        pInstance = new Singleton();
    }
    return pInstance;
} // 不安全
// 采用锁可实现安全获取单例对象.
Singleton* Singleton::instance()
{
    Lock lock;  //acquire lock.
    if(pInstance == 0)
    {
        pInstance = new Singleton();
    }
    return pInstance;
}// release lock
// 这种方法能做到线程安全, 缺点就是资源耗费严重, 每次获取实例都需要获取锁,实际上只需要在第一次获取对象时需要加锁.

// The Double-Checked Locking Pattern (DCLP) 实现.
Singleton* Singleton::instance()
{
    if(pInstance == 0)      // 1st
    {
        Lock lock;
        if(pInstance == 0)  // 2st
          {
              pInstance = new Singleton();
          }
    }
    return pInstance;
}

// This statement causes three things to happen:
1.  Allocate memory to hold a Singleton object.            (分配内存以保存 Singleton 对象).
2.  Construct a Singleton object in the allocated memory.  (在分配的内存中构造一个 Singleton 对象).
3.  Make pInstance point to the allocated memory.          (使 pInstance 指向分配的内存).

// 有时编译器交换步骤 2和 3. 如下:
Singleton* Singleton::instance()
{
    if(pInstance == 0)
    {
        Lock lock;
        if(pInstance == 0)
        {
            pInstance =                         // Step 3.
              opeartor new (sizeof(Singleton)); // Step 1.
              new (pInstance) Singleton;       //  Step 2.
        }
    }
    return pInstance;
}

// volatile 关键字
class Singleton
{
public:
    static Singleton* instance();

private:    
    static Singleton* volatile pInstance; // volatile added.
    int x;
    Singleton()
        :x(5)
    {}
};

// from the implementation file
Singleton* volatile Singleton::pInstance = 0;

Singleton* Singleton::instance()
{
    if(pInstance == 0)
    {
        Lock lock;
        if(pInstance == 0)
        {
            Singleton* volatile temp = new Singleton(); //volatile added
            pInstance = temp;
        }
    }
    return pInstance;
}
// 内联函数展开之后...
// After inlining the constructor, the code looks like this:
if(pInstance == 0)
{
    Lock lock;
    if(pInstance == 0)
    {
        Singleton* volatile temp =
            static_cast<Singleton*>(operator new (sizeof(Singleton)));
            temp->x = 5;     // inlined Single constructor
        pInstance = temp;
    }
}

// problem:
//编译器可以对 temp->x 的赋值重新排序，以重新排序对 pInstance 的赋值。如果这样做，pInstance 将在它指向的数据初始化之前分配，这再次导致其他线程读取未初始化的 x 的可能性.
// 可能解决的方法:
class Singleton
{   
public:
    static volatile Singleton* volatile instance();

private:
    static volatile Singleton* volatile pInstance;

};

volatile Singleton* volatile Singleton::pInstance = 0;
volatile Singleton* volatile Singleton::instance1()
{
    if(pInstance == 0)
    {
        Lock lock;
        if(pInstance == 0)
        {
            volatile Singleton* volatile temp =
                new volatile Singleton();
            pInstance = temp;
        }
    }
    return pInstance;
}

volatile Singleton* volatile Singleton::instance2()
{
    if(pInstance == 0)
    {
        Lock lock;
        if(pInstance == 0)
        {
             Singleton* volatile temp =
               static_cast<Singleton*> (operator new (sizeof(Singleton)));
            static_cast<volatile int&>(temp->x) = 5;
            pInstance = temp;
        }
    }
    return pInstance;
}

// 缓存一致性问题的一般解决方案是使用内存屏障
Singleton* Singleton::instance()
{
    Singleton* tmp = pInstance;
    //....               insert memory barrier.
    if(tmp == 0)
    {
        Lock lock;
        tmp = pInstance;
        if(tmp == 0)
        {
            tmp = new Singleton();
            //...        insert memory barrier.
            pInstance = tmp;
        }
    }
    return tmp;
}
```