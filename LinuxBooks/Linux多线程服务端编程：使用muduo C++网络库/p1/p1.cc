#include <iostream>
#include <boost/noncopyable.hpp>
#include <vector>
#include <memory>
#include <boost/base/mutex.hpp>

using namespace std;
using namespace boost;
// day-2025-10-30
// 第一章 线程安全的对象生命期管理

// 线程安全的类应该满足的条件:
// 1. 多个线程同时访问时, 其表现出正确的行为
// 2. 无论操作系统如何调度这些线程, 无论这些线程的执行顺序如何交织
// 3. 调用端代码无需额外的同步或者其他协调动作

// A thread-safe counter
/*
class Counter : public noncopyable
{
public:
public:
    Counter() : value_(0) {}
    int64_t value() const;
    int64_t getAndIncrease();

private:
    int64_t value_;
    mutable MutexLock mutex_;
};

int64_t Counter::value() const
{
    MutexLockGuard lock(mutex_);
    return value_;
}

int64_t Counter::getAndIncrease()
{
    MutexLockGuard lock(mutex_);
    int64_t ret = value_++;
    return ret;
}
*/

// Observer 模式
/*
class Observer : public noncopyable
{
    void observe(Observable *s)
    {
        s->register_(this);
        subject_ = s;
    }

    virtual ~Observer()
    {
        subject_->unregister(this);
    }
    virtual void update() = 0;

    Observable *subject_;
};

class Observable : public noncopyable
{
public:
    void register_(Observer *x);
    void unregister(Observer *x);
    void notifyObservers()
    {
        for (Observer *x : observers_)
        {
            x->update();
        }
    }

private:
    std::vector<Observer *> observers_;
};
*/

// C++ 可能出现的内存问题大致的几个方面：
// 1. 缓冲区溢出
// 用 std::vector<char>/ std::string 或自己编写的 Buffer class 来管理缓冲区, 自动记住缓冲区的长度并通过成员函数而不是裸指针.
// 2. 空悬指针/野指针
// 用 shared_ptr/weak_ptr
// 3. 重复释放
// 用 scoped_ptr
// 4. 内存泄漏
// 用 scoped_ptr
// 5. 不配对的 new[]/ delete
// 把 new[] 统一换成 std::vector/ scoped_array
// 6. 内存碎片

// 将 weak_ptr 应用到 Observer上
/*
class Observable // not 100% thread safe！
{
public:
    void register_(weak_ptr<Observer> x);
    void notifyObservers();

private:
    mutable MutexLock mutex_;
    std::vector<weak_ptr<Observer>> observers_;
    typedef std::vector<weak_ptr<Observer>>::iterator Iterator;
};

void Observable::notifyObservers()
{
    MutexLockGuard lock(mutex_);
    Iterator it = observers_.begin();
    while (it != observers_.end())
    {
        shared_ptr<Observer> obj(it->lock());
        if (obj)
        {
            // 提升成功
            obj->update();
            ++it;
        }
        else
        {
            // 提升失败，删除
            it = observers_.erase(it);
        }
    }
}
*/

