## C++新特性高效多线程线程池实现项目

> ​	项目地址: [zyuhao7/Studying(github.com)](https://github.com/zyuhao7/Studying
>
> ​	平台工具: VS 2022开发，centos 7 g++ 编译so库，gdb 调试多线程





### 项目描述：

1.  使用可变参模板编程和引用折叠原理， 实现线程池 **submitTask** 接口, 支持任意函数和任意参数的传递。
2.  使用 **future**类型定制 **submitTask** 提交任务的返回值。
3.  使用 **unordered_map** 和 **queue** 管理线程对象和任务。
4.  使用自动类型 **auto** 和 可变参数模板 **forward** 进行任务封装。
5.  基于条件变量 **condition_variable** 和 互斥锁 **mutex** 实现任务提交线程和任务执行线程间的通信机制。
6.  支持 **fixed** 和 **cached** 模式的线程池定制。



### 项目问题

1.  在 ThreadPool 资源回收时, 等待线程池所有线程退出时, 发生死锁问题, 导致进程无法退出
2. 在 **windows**平台运行正常, 在 **linux** 平台运行发生死锁问题







### 分析定位问题

#### 问题一:

```c++
 =============== main函数所在的主线程 ==============
 ThreadPool::~ThreadPool()
 {
     isPoolRunning = false;
     //notEmpty_.notify_all();
     // 等待线程池里面所有的线程返回(两种状态 阻塞 & 执行任务)
     std::unique_lock<std::mutex> lock(taskQueMtx_);
     notEmpty_.notify_all();
     exitCond_.wait(lock,[&]()->bool {return threads_.size() == 0;});
     // 进入 wait 状态, 并把 mutex 释放掉. 
 }

 =============== 线程池每个线程的线程函数 ==============

// 等待 notEmpty 条件
notEmpty_.wait(lock);									//  (1)

task->exec();											//  (2)

void ThreadPool::threadFunc(int threadid)
 {
     while(isPoolRunning_)
     {
         std::shared_ptr<Task> task;                    //  (3)
         // 先获取锁.
         std::unique_lock<std::mutex> lock(taskQueMtx_);
	 }
}
```



#### 问题二:

### Linux 测试线程池项目

> ​	**程序没法正常退出, why?**

![image-20240618224633941](C:\Users\徐浩\AppData\Roaming\Typora\typora-user-images\image-20240618224633941.png)

#### windows 下正常运行

![image-20240618224908760](C:\Users\徐浩\AppData\Roaming\Typora\typora-user-images\image-20240618224908760.png)

##### 原因分析



Linux 平台下，g++是由全世界程序员维护的。 Result 返回类型在任务执行时候睡眠几秒, 主函数退出, Result成员析构, sem 信号量析构,  mtx_ 和 cond_ 析构, 导致变量失效, 但是在 Result中 setVal时候调用 sem_.post(), cond_ 阻塞,条件变量析构不释放资源, 导致状态失效,无故阻塞了。

![image-20240618225944961](C:\Users\徐浩\AppData\Roaming\Typora\typora-user-images\image-20240618225944961.png)





微软工程师在条件变量析构时候,释放了互斥量资源, 任务正常结束。

![image-20240618225625071](C:\Users\徐浩\AppData\Roaming\Typora\typora-user-images\image-20240618225625071.png)



![image-20240618225643624](C:\Users\徐浩\AppData\Roaming\Typora\typora-user-images\image-20240618225643624.png)





##### Linux 平台对信号量更正

```c++
// 信号量类型.
class Semaphore
{
public:
    Semaphore(int limit = 0)
        : resLimit_(limit), isExit_(false)
    {
    }

    ~Semaphore()
    {
        isExit_ = true;
    }

    // 获取一个信号量资源.
    void wait()
    {
        if (isExit_)
            return;
        std::unique_lock<std::mutex> lock(mtx_);
        // 等待信号量有资源, 没有资源就阻塞着...
        cond_.wait(lock, [&]() -> bool
                   { return resLimit_ > 0; });
        resLimit_--;
    }

    // 增加一个信号量资源.
    void post()
    {
        if (isExit_)
            return;
        std::unique_lock<std::mutex> lock(mtx_);
        resLimit_++;
        cond_.notify_all();
    }

private:
    std::atomic_bool isExit_;
    int resLimit_;
    std::mutex mtx_;
    std::condition_variable cond_;
};
```

