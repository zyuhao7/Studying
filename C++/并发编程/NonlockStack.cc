#include <iostream>
#include <atomic>
#include <memory>
#include <thread>
// 无锁栈
// day-2025-9-2
using namespace std;

// template <typename T>
// class lock_free_stack
// {
// private:
//     struct node
//     {
//         T data;
//         node *next;

//         node(const T &data_)
//             : data(data_) {}
//     };

//     std::atomic<node *> head;

// public:
//     void push(T const &data)
//     {
//         node *const new_node = new node(data);                        // 2
//         new_node->next = head.load();                                 // 3
//         while (!head.compare_exchange_weak(new_node->next, new_node)) // 4
//             ;
//     }
//     void pop(T &result)
//     {
//         node *old_head = head.load();
//         while (!head.compare_exchange_weak(old_head, old_head->next))
//             ;
//         result = old_head->data;
//     }
// };

// 带有节点泄露的无锁栈
// template <typename T>
// class lock_free_stack
// {
// private:
//     struct node
//     {
//         std::shared_ptr<T> data; // 1.指针获取数据
//         node *next;

//         node(const T &data_) // 2 让std::shared_ptr指向新分配出来的T
//             : data(make_shared<T>(data_)), next(nullptr)
//         {
//         }
//     };

//     std::atomic<node *> head;

// public:
//     void push(T const &data)
//     {
//         node *const new_node = new node(data);
//         new_node->next = head.load();
//         while (!head.compare_exchange_weak(new_node->next, new_node))
//             ;
//     }
//     std::shared_ptr<T> pop()
//     {
//         node *old_head = head.load();
//         while (old_head && !head.compare_exchange_weak(old_head, old_head->next)) // 3 在解引用前检查old_head是否为空指针
//             ;
//         return old_head ? old_head->data : std::make_shared<T>(); // 4
//     }
// };

// 没有线程通过pop()访问节点时，就对节点进行回收, 采用引用计数的回收机制
template <typename T>
class lock_free_stack
{
private:
    struct node
    {
        std::shared_ptr<T> data; // 1.指针获取数据
        node *next;

        node(const T &data_) // 2 让std::shared_ptr指向新分配出来的T
            : data(make_shared<T>(data_)), next(nullptr)
        {
        }
    };

private:
    std::atomic<node *> head;
    std::atomic<unsigned> threads_in_pop; // 1 原子变量
    std::atomic<node *> to_be_deleted;

    static void delete_nodes(node *nodes)
    {
        while (nodes)
        {
            node *next = nodes->next;
            delete nodes;
            nodes = next;
        }
    }

    void try_reclaim(node *old_head)
    {
        if (threads_in_pop == 1) // 1
        {
            node *nodes_to_delete = to_be_deleted.exchange(nullptr); // 2 声明 "可删除" 列表
            if(! --threads_in_pop) // 3 是否只有一个线程调用 pop()
            {
                delete_nodes(nodes_to_delete); // 4
            }
            else if(nodes_to_delete) // 5
            {
                chain_pending_nodes(nodes_to_delete); // 6
            }
            delete old_head; // 7
        }
        else
        {
            chain_pending_nodes(old_head); // 8
            ++threads_in_pop; 
        }
    }

    void chain_pending_nodes(node *nodes)
    {
        node* last = nodes;
        while(node* const next = last->next) // 9 让next指针指向链表的末尾
        {
            last = next;
        }
        chain_pending_nodes(nodes, last); 
    }
    void chain_pending_nodes(node *first, node *last)
    {
        last->next = to_be_deleted; // 10
        while(!to_be_deleted.compare_exchange_weak(last->next, first)) // 11 
            ;
    }
    void chain_pending_node(node* n)
    {
        chain_pending_nodes(n, n); // 12
    }

public:
    std::shared_ptr<T> pop()
    {
        ++threads_in_pop; // 2 在做事之前, 计数器加1
        node *old_head = head.load();
        while (old_head && !head.compare_exchange_weak(old_head, old_head->next))
            ;
        std::shared_ptr<T> res;
        if (old_head)
        {
            res.swap(old_head->data); // 3 回收删除的节点
        }
        try_reclaim(old_head); // 4 从节点中直接提取数据, 而非拷贝指针
        return res;
    }
};

// 检测使用风险指针(不可回收)的节点
// std::shared_ptr<T> pop()
// {
//   std::atomic<void*>& hp=get_hazard_pointer_for_current_thread();
//   node* old_head=head.load();  // 1
//   node* temp;
//   do
//   {
//     temp=old_head;
//     hp.store(old_head);  // 2
//     old_head=head.load();
//   } while(old_head!=temp); // 3
//   // ...
// }

// 使用风险指针实现的pop()
// std::shared_ptr<T> pop()
// {
//   std::atomic<void*>& hp=get_hazard_pointer_for_current_thread();
//   node* old_head=head.load();
//   do
//   {
//     node* temp;
//     do  // 1 直到将风险指针设为head指针
//     {
//       temp=old_head;
//       hp.store(old_head);
//       old_head=head.load();
//     } while(old_head!=temp);
//   }
//   while(old_head &&
//     !head.compare_exchange_strong(old_head,old_head->next));
//   hp.store(nullptr);  // 2 当声明完成，清除风险指针
//   std::shared_ptr<T> res;
//   if(old_head)
//   {
//     res.swap(old_head->data);
//     if(outstanding_hazard_pointers_for(old_head))  // 3 在删除之前对风险指针引用的节点进行检查
//     {
//       reclaim_later(old_head);  // 4
//     }
//     else
//     {
//       delete old_head;  // 5
//     }
//     delete_nodes_with_no_hazards();  // 6
//   }
//   return res;
// }

// get_hazard_pointer_for_current_thread()函数的简单实现
unsigned const max_hazard_pointers = 100;
struct hazard_pointer
{
    std::atomic<std::thread::id> id;
    std::atomic<void*> pointer;
};

hazard_pointer hazard_pointers[max_hazard_pointers];
    



int main()
{

}