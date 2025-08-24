#include <iostream>
#include <list>
#include <vector>
#include <mutex>
#include <memory>
using namespace std;

// day-2025-8-24
// 线程安全 链表
// 链表的 node 节点
class MyClass
{
public:
    MyClass(int i) : _data(i) {}

    int GetData() const { return _data; }

    friend std::ostream &
    operator<<(std::ostream &os, const MyClass &mc)
    {
        os << mc._data;
        return os;
    }

private:
    int _data;
};

template <typename T>
class threadsafe_list
{
    struct node
    {
        std::mutex mtx;
        std::shared_ptr<T> data;
        std::unique_ptr<node> next;
        node()
            : next() {}
        node(T const &value)
            : data(std::make_shared<T>(value)) {}
    };

    node head; // 虚拟头结点

public:
    threadsafe_list() {}
    ~threadsafe_list()
    {
        remove_if([](node const &)
                  { return true; });
    }
    threadsafe_list(threadsafe_list const &) = delete;
    threadsafe_list &operator=(threadsafe_list const &) = delete;

    template <typename Pred>
    /**
     * 移除满足特定条件的节点
     * @param p 判断函数，用于决定是否移除某个节点
     */
    void remove_if(Pred p)
    {
        // 从头节点开始遍历
        node *cur = &head;
        // 对头节点加锁，确保线程安全
        std::unique_lock<std::mutex> lock(head.mtx);
        // 遍历链表
        while (node *const next = cur->next.get())
        {
            // 对下一个节点加锁
            std::unique_lock<std::mutex> next_lock(next->mtx);
            // 如果满足删除条件
            if (p(*next->data))
            {
                // 保存要删除的节点
                std::unique_ptr<node> old_next = std::move(cur->next);
                // 跳过要删除的节点，直接连接到下一个节点
                cur->next = std::move(next->next);
                // 解锁被删除节点的锁
                next_lock.unlock();
            }
            else
            {
                // 解锁当前节点的锁
                lock.unlock();
                // 移动到下一个节点
                cur = next;
                // 转移锁的所有权到当前节点
                lock = std::move(next_lock);
            }
        }
    }

    void push_front(T const &value)
    {
        std::unique_ptr<node> new_node(new node(value));
        std::unique_lock<std::mutex> lock(head.mtx);
        new_node->next = std::move(head.next);
        head.next = std::move(new_node);
    }

    template <typename Pred>
    std::shared_ptr<T> find_first_if(Pred p)
    {
        node *cur = &head;

        std::unique_lock<std::mutex> lock(head.mtx);

        while (node *const next = cur->next.get())
        {
            // 锁定下一个节点的互斥锁，确保线程安全
            std::unique_lock<std::mutex> next_lock(next->mtx);

            // 释放当前节点的锁，因为我们已经锁定了下一个节点
            lock.unlock();

            if (p(*next->data))
            {
                return next->data;
            }
            cur = next;
            lock = std::move(next_lock);
        }
        return std::shared_ptr<T>();
    }

    template <typename Function>
    void for_each(Function f)
    {
        node *cur = &head;
        std::unique_lock<std::mutex> lock(head.mtx);
        while (node *const next = cur->next.get())
        {
            std::unique_lock<std::mutex> next_lock(next->mtx);
            lock.unlock();
            f(*next->data);
            cur = next;
            lock = std::move(next_lock);
        }
    }
};
#include <set>
#include <thread>
std::set<int> removeSet;
void TestThreadSafeList()
{

    threadsafe_list<MyClass> thread_safe_list;
    std::thread t1([&]()
                   {
                       for (unsigned int i = 0; i < 100; i++)
                       {
                           MyClass mc(i);
                           thread_safe_list.push_front(mc);
                       } });

    std::thread t2([&]()
                   {
        for (unsigned int i = 0; i < 100; )
        {

            auto find_res = thread_safe_list.find_first_if([&]( auto & mc)
            {
                    return mc.GetData() == i;
            });

            if(find_res == nullptr)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                continue;
            }

            removeSet.insert(i);
            i++;
        } });

    t1.join();
    t2.join();
}

int main()
{
    TestThreadSafeList();
}