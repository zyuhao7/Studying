#include <iostream>
#include <thread>
#include <mutex>
#include <memory>
using namespace std;
// 早期单例模式
// C++11 以前该方式存在风险，在多个线程初始化时存在开辟多个实例情况
// C++ 11以后大部分的单例都回归到这个模式了
class Single2
{
private:
    Single2()
    {
    }
    Single2(const Single2 &) = delete;
    Single2 &operator=(const Single2 &) = delete;

public:
    static Single2 &GetInst()
    {
        static Single2 single;
        return single;
    }
};

void test_single2()
{
    // 多线程情况下可能存在问题
    std::cout << "s1 addr is " << &Single2::GetInst() << std::endl;
    std::cout << "s2 addr is " << &Single2::GetInst() << std::endl;
}

class Single2Hungry
{
private:
    Single2Hungry() {}
    Single2Hungry(const Single2Hungry &) = delete;
    Single2Hungry &operator=(const Single2Hungry &) = delete;

public:
    static Single2Hungry *GetInstance()
    {
        if (single == nullptr)
        {
            single = new Single2Hungry;
        }
        return single;
    }

private:
    static Single2Hungry *single;
};
Single2Hungry *Single2Hungry::single = Single2Hungry::GetInstance();
void thread_func_s2(int i)
{
    cout << "this is thread " << i << endl;
    cout << "Inst is " << Single2Hungry::GetInstance() << endl;
}

void test_single2_hungry()
{
    cout << "s1 addr is " << Single2Hungry::GetInstance() << endl;
    cout << "s2 addr is " << Single2Hungry::GetInstance() << endl;
    for (int i = 0; i < 3; ++i)
    {
        thread tid(thread_func_s2, i);
        tid.join();
    }
}

class Single2Pointer
{
private:
    Single2Pointer() {}
    Single2Pointer(const Single2Pointer &) = delete;
    Single2Pointer &operator=(const Single2Pointer &) = delete;

public:
    static Single2Pointer *GetInstance()
    {
        if (single != nullptr)
            return single;
        mtx.lock();
        if (single != nullptr)
        {
            mtx.unlock();
            return single;
        }
        single = new Single2Pointer();
        mtx.unlock();
        return single;
    }

public:
private:
    static Single2Pointer *single;
    static std::mutex mtx;
};

Single2Pointer *Single2Pointer::single = nullptr;
std::mutex Single2Pointer::mtx;

void thread_func_lazy(int i)
{
    std::cout << "this is lazy thread " << i << std::endl;
    std::cout << "inst is " << Single2Pointer::GetInstance() << std::endl;
}
void test_single2_lazy()
{
    for (int i = 0; i < 3; i++)
    {
        std::thread tid(thread_func_lazy, i);
        tid.join();
    }
    // 何时释放new的对象？造成内存泄漏
}
// 可以利用智能指针完成自动回收
class SingleAuto
{
private:
    SingleAuto()
    {
    }
    SingleAuto(const SingleAuto &) = delete;
    SingleAuto &operator=(const SingleAuto &) = delete;

public:
    ~SingleAuto()
    {
        std::cout << "single auto delete success " << std::endl;
    }
    static std::shared_ptr<SingleAuto> GetInst()
    {
        if (single != nullptr)
        {
            return single;
        }
        s_mutex.lock();
        if (single != nullptr)
        {
            s_mutex.unlock();
            return single;
        }
        single = std::shared_ptr<SingleAuto>(new SingleAuto);
        s_mutex.unlock();
        return single;
    }

private:
    static std::shared_ptr<SingleAuto> single;
    static std::mutex s_mutex;
};
std::shared_ptr<SingleAuto> SingleAuto::single = nullptr;
std::mutex SingleAuto::s_mutex;
void test_singleauto()
{
    auto sp1 = SingleAuto::GetInst();
    auto sp2 = SingleAuto::GetInst();
    std::cout << "sp1  is  " << sp1 << std::endl;
    std::cout << "sp2  is  " << sp2 << std::endl;
    // 此时存在隐患，可以手动删除裸指针，造成崩溃
    //  delete sp1.get();
}

// 为了规避用户手动释放内存，可以提供一个辅助类帮忙回收内存
// 并将单例类的析构函数写为私有

class SingleAutoSafe;
class SafeDeletor
{
public:
    void operator()(SingleAutoSafe *sf)
    {
        std::cout << "this is safe deleter operator()" << std::endl;
        delete sf;
    }
};

class SingleAutoSafe
{
private:
    SingleAutoSafe() {}
    ~SingleAutoSafe()
    {
        std::cout << "this is single auto safe deletor" << std::endl;
    }
    SingleAutoSafe(const SingleAutoSafe &) = delete;
    SingleAutoSafe &operator=(const SingleAutoSafe &) = delete;
    // 定义友元类，通过友元类调用该类析构函数
    friend class SafeDeletor;

public:
    static std::shared_ptr<SingleAutoSafe> GetInst()
    {
        // 1处
        if (single != nullptr)
        {
            return single;
        }
        s_mutex.lock();
        // 2处
        if (single != nullptr)
        {
            s_mutex.unlock();
            return single;
        }
        // 额外指定删除器
        // 3 处
        single = std::shared_ptr<SingleAutoSafe>(new SingleAutoSafe, SafeDeletor());
        // 也可以指定删除函数
        //  single = std::shared_ptr<SingleAutoSafe>(new SingleAutoSafe, SafeDelFunc);
        s_mutex.unlock();
        return single;
    }

private:
    static std::shared_ptr<SingleAutoSafe> single;
    static std::mutex s_mutex;
};

std::shared_ptr<SingleAutoSafe> SingleAutoSafe::single = nullptr;
std::mutex SingleAutoSafe::s_mutex;

class SingletonOnce
{
private:
    SingletonOnce() = default;
    SingletonOnce(const SingletonOnce &) = delete;
    SingletonOnce &operator=(const SingletonOnce &) = delete;
    static std::shared_ptr<SingletonOnce> _instance;

public:
    static std::shared_ptr<SingletonOnce> GetInstance()
    {
        static std::once_flag s_flag;
        std::call_once(s_flag, [&]()
                       { _instance = std::shared_ptr<SingletonOnce>(new SingletonOnce); });
        return _instance;
    }
    void PrintAddress()
    {
        cout << _instance.get() << endl;
    }
    ~SingletonOnce()
    {
        cout << "this is singleton destruct" << endl;
    }
};

std::shared_ptr<SingletonOnce> SingletonOnce::_instance = nullptr;

void TestSingle()
{

    std::thread t1([]()
                   {
			std::this_thread::sleep_for(std::chrono::seconds(1));
			SingletonOnce::GetInstance()->PrintAddress(); });

    std::thread t2([]()
                   {
			std::this_thread::sleep_for(std::chrono::seconds(1));
			SingletonOnce::GetInstance()->PrintAddress(); });

    t1.join();
    t2.join();
}

template <typename T>
class Singleton
{
protected:
    Singleton() = default;
    Singleton(const Singleton<T> &) = delete;
    Singleton &operator=(const Singleton<T> &) = delete;
    static std::shared_ptr<T> _instance;

public:
    static shared_ptr<T> GetInstance()
    {
        std::once_flag s_flag;

        std::once_flag(s_flag, [&]()
                       { _instance = shared_ptr<T>(new T); });
        return _instance;
    }
    void PrintAddress()
    {
        std::cout << _instance.get() << std::endl;
    }

    ~SingletonOnce()
    {
        std::cout << "this is singleton destruct" << std::endl;
    }
};

template <typename T>
std::shared_ptr<T> Singleton<T>::_instance = nullptr;

// 想使用单例类，可以继承上面的模板，我们在网络编程中逻辑单例类用的就是这种方式
class LogicSystem : public Singleton<LogicSystem>
{
    friend class Singleton<LogicSystem>;

public:
    ~LogicSystem() {}

private:
    LogicSystem() {}
};

int main()
{
    // test_single2();
    // test_single2_hungry();
    // test_single2_lazy();
    // test_singleauto();
    TestSingle();
    return 0;
}