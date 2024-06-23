#include <iostream>
#include <atomic>
#include <thread>
#include <memory>
#include <functional>
using namespace std;

#if 0
template <typename T>
class lock_free_stack
{
private:
    struct node
    {
        T data;
        node *next;

        node(T const &data_) // 1
            : data(data_)
        {
        }
    };

    std::atomic<node *> head;

public:
    void push(T const &data)
    {
        node *const new_node = new node(data); // 2
        new_node->next = head.load();          // 3
        while (!head.compare_exchange_weak(new_node->next, new_node))
            ; // 4
    }
};
#endif

#if 0
template <typename T>
class lock_free_stack
{
private:
    struct node
    {
        std::shared_ptr<T> data; // 1 指针获取数据
        node *next;

        node(T const &data_)
            : data(std::make_shared<T>(data_)) // 2 让std::shared_ptr指向新分配出来的T
        {
        }
    };

    std::atomic<node *> head;

public:
    void push(T const &data)
    {
        node *const new_node = new node(data);
        new_node->next = head.load();
        while (!head.compare_exchange_weak(new_node->next, new_node))
            ;
    }
    std::shared_ptr<T> pop()
    {
        node *old_head = head.load();
        while (old_head && // 3 在解引用前检查old_head是否为空指针
               !head.compare_exchange_weak(old_head, old_head->next))
            ;
        return old_head ? old_head->data : std::shared_ptr<T>(); // 4
    }
};
#endif

#if 0
template <typename T>
class lock_free_stack
{
private:
    struct node
    {
        std::shared_ptr<T> data;
        node *next;

        node(T const &data_)
            : data(std::make_shared<T>(data_));
        {
        }
    };

private:
    std::atomic<unsigned> threads_in_pop; // 1 原子变量
    void try_reclaim(node *old_head);     // 尝试回收.

public:
    std::shared_ptr<T> pop()
    {
        ++threads_in_pop; // 2 在做事之前，计数值加1.
        node *old_head = head.load();
        while (old_head &&
               !head.compare_exchange_weak(old_head, old_head->next))
            ;
        std::shared_ptr<T> res;
        if (old_head)
        {
            res.swap(old_head->data); // 3 回收删除的节点
        }
        try_reclaim(old_head); // 4 从节点中直接提取数据，而非拷贝指针
        return res;
    }
};
#endif

#if 0
template <typename T>
class lock_free_stack
{
private:
    struct node
    {
        std::shared_ptr<T> data;
        node *next;

        node(T const &data_)
            : data(std::make_shared<T>(data_));
        {
        }
    };

private:
    std::atomic<node *> to_be_deleted;
    std::atomic<unsigned> threads_in_pop;

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
            node *nodes_to_delete = to_be_deleted.exchange(nullptr); // 2 声明“可删除”列表
            if (!--threads_in_pop)                                   // 3 是否只有一个线程调用pop()?
            {
                delete_nodes(nodes_to_delete); // 4
            }
            else if (nodes_to_delete) // 5
            {
                chain_pending_nodes(nodes_to_delete); // 6
            }
            delete old_head; // 7
        }
        else
        {
            chain_pending_node(old_head); // 8
            --threads_in_pop;
        }
    }
    void chain_pending_nodes(node *nodes)
    {
        node *last = nodes;
        while (node *const next = last->next) // 9 让next指针指向链表的末尾
        {
            last = next;
        }
        chain_pending_nodes(nodes, last);
    }

    void chain_pending_nodes(node *first, node *last)
    {
        last->next = to_be_deleted;                  // 10
        while (!to_be_deleted.compare_exchange_weak( // 11 用循环来保证last->next 的正确性
            last->next,
            first))
            ;
    }
    void chain_pending_node(node *n)
    {
        chain_pending_nodes(n, n); // 12
    }
};
#endif

#if 0
std::shared_ptr<T> pop()
{
    std::atomic<void *> &hp = get_hazard_pointer_for_current_thread();
    node *old_head = head.load();
    do
    {
        node *temp;
        do // 1 直到将风险指针设为head指针
        {
            temp = old_head;
            hp.store(old_head);
            old_head = head.load();
        } while (old_head != temp);
    } while (old_head &&
             !head.compare_exchange_strong(old_head, old_head->next));
    hp.store(nullptr); // 2 当声明完成，清除风险指针
    std::shared_ptr<T> res;
    if (old_head)
    {
        res.swap(old_head->data);
        if (outstanding_hazard_pointers_for(old_head)) // 3 在删除之前对风险指针引用 的节点进行检查
            {
                reclaim_later(old_head); // 4
            }
        else
        {
            delete old_head; // 5
        }
        delete_nodes_with_no_hazards(); // 6
    }
    return res;
}

#endif

#if 0
unsigned const max_hazard_pointers = 100;

struct hazard_pointer
{
    std::atomic<std::thread::id> id;
    std::atomic<void *> pointer;
};

hazard_pointer hazard_pointers[max_hazard_pointers];

class hp_owner
{
    hazard_pointer *hp;

public:
    hp_owner(hp_owner const &) = delete;
    hp_owner operator=(hp_owner const &) = delete;
    hp_owner() 
    : hp(nullptr)
    {
        for (unsigned i = 0; i < max_hazard_pointers; ++i)
        {
            std::thread::id old_id;
            if (hazard_pointers[i].id.compare_exchange_strong( // 6 尝试声明风险指针的所有权
                    old_id,
                    std::this_thread::get_id()))
            {
                hp = &hazard_pointers[i];
                break; // 7
            }
        }
        if (!hp) // 1
        {
            throw std::runtime_error("No hazard pointers available");
        }
    }

    std::atomic<void *> &get_pointer()
    {
        return hp->pointer;
    }

    ~hp_owner() // 2
    {
        hp->pointer.store(nullptr);      // 8
        hp->id.store(std::thread::id()); // 9
    }
};

std::atomic<void *> &get_hazard_pointer_for_current_thread() // 3 {
{
    thread_local static hp_owner hazard; // 4 每个线程都有自己的风险指针
    return hazard.get_pointer();         // 5
}
#endif

#if 0
template <typename T>
void do_delete(void *p)
{
    delete static_cast<T *>(p);
}

struct data_to_reclaim
{
    void *data;
    std::function<void(void *)> deleter;
    data_to_reclaim *next;

    template <typename T>
    data_to_reclaim(T *p) //  1
        : data(p),
          deleter(&do_delete<T>),
          next(0)
    {
    }

    ~data_to_reclaim()
    {
        deleter(data); // 2
    }
};

std::atomic<data_to_reclaim *> nodes_to_reclaim;

void add_to_reclaim_list(data_to_reclaim *node) // 3

{
    node->next = nodes_to_reclaim.load();
    while (!nodes_to_reclaim.compare_exchange_weak(node->next, node))
        ;
}

template <typename T>
void reclaim_later(T *data) // 4
{
    add_to_reclaim_list(new data_to_reclaim(data)); // 5
}

void delete_nodes_with_no_hazards()
{
    data_to_reclaim *current = nodes_to_reclaim.exchange(nullptr); // 6
    while (current)
    {
        data_to_reclaim *const next = current->next;
        if (!outstanding_hazard_pointers_for(current->data)) // 7
        {
            delete current; // 8  }
            else
            {
                add_to_reclaim_list(current); // 9
            }
            current = next;
        }
    }
};
#endif

#if 0

template <typename T>
class lock_free_stack
{
private:
    struct node
    {
        std::shared_ptr<T> data;
        std::shared_ptr<node> next;
        node(T const &data_)
            : data(std::make_shared<T>(data_))
        {
        }
    };

    std::shared_ptr<node> head;

public:
    void push(T const &data)
    {
        std::shared_ptr<node> const new_node = std::make_shared<node>(data);
        new_node->next = head.load();
        while (!std::atomic_compare_exchange_weak(&head, &new_node->next, new_node))
            ;
    }
    std::shared_ptr<T> pop()
    {
        std::shared_ptr<node> old_head = std::atomic_load(&head);
        while (old_head && !std::atomic_compare_exchange_weak(&head,
                                                              &old_head, old_head->next))
            ;
        if (old_head)
        {
            std::atomic_store(&old_head->next, std::shared_ptr<node>());
            return old_head->data;
        }
        return std::shared_ptr<T>();
    }
    ~lock_free_stack()
    {
        while (pop())
            ;
    }
};

#endif

#if 0

template <typename T>
class lock_free_stack
{
private:
    struct node
    {
        std::shared_ptr<T> data;
        std::experimental::atomic_shared_ptr<node> next;
        node(T const &data_) : data(std::make_shared<T>(data_))
        {
        }
    };
    std::experimental::atomic_shared_ptr<node> head;

public:
    void push(T const &data)
    {
        std::shared_ptr<node> const new_node = std::make_shared<node>(data);
        new_node->next = head.load();
        while (!head.compare_exchange_weak(new_node->next, new_node))
            ;
    }
    std::shared_ptr<T> pop()
    {
        std::shared_ptr<node> old_head = head.load();
        while (old_head && !head.compare_exchange_weak(
                               old_head, old_head->next.load()))
            ;
        if (old_head)
        {
            old_head->next = std::shared_ptr<node>();
            return old_head->data;
        }
        return std::shared_ptr<T>();
    }
    ~lock_free_stack()
    {
        while (pop())
            ;
    }
};

#endif

#if 0
template <typename T>
class lock_free_stack
{
private:
    struct node;

    struct counted_node_ptr // 1
    {
        int external_count;
        node *ptr;
    };

    struct node
    {
        std::shared_ptr<T> data;
        std::atomic<int> internal_count; // 2
        counted_node_ptr next;           // 3

        node(T const &data_)
            : data(std::make_shared<T>(data_)),
              internal_count(0)
        {
        }
    };

    std::atomic<counted_node_ptr> head; // 4

public:
    ~lock_free_stack()
    {
        while (pop())
            ;
    }

    void push(T const &data) // 5
    {
        counted_node_ptr new_node;
        new_node.ptr = new node(data);
        new_node.external_count = 1;
        new_node.ptr->next = head.load();
        while (!head.compare_exchange_weak(new_node.ptr->next, new_node))
            ;
    }
};

#endif

#if 0
template <typename T>
class lock_free_stack
{
private:
    void increase_head_count(counted_node_ptr &old_counter)
    {
        counted_node_ptr new_counter;

        do
        {
            new_counter = old_counter;
            ++new_counter.external_count;
        } while (!head.compare_exchange_strong(old_counter, new_counter)); // 1

        old_counter.external_count = new_counter.external_count;
    }

public:
    std::shared_ptr<T> pop()
    {
        counted_node_ptr old_head = head.load();
        for (;;)
        {
            increase_head_count(old_head);
            node *const ptr = old_head.ptr; // 2
            if (!ptr)
            {
                return std::shared_ptr<T>();
            }
            if (head.compare_exchange_strong(old_head, ptr->next)) // 3
            {
                std::shared_ptr<T> res;
                res.swap(ptr->data); // 4

                int const count_increase = old_head.external_count - 2; // 5

                if (ptr->internal_count.fetch_add(count_increase) == // 6
                    -count_increase)
                {
                    delete ptr;
                }

                return res; // 7
            }
            else if (ptr->internal_count.fetch_sub(1) == 1)
            {
                delete ptr; // 8
            }
        }
    }
};

#endif

#if 0
template <typename T>
class lock_free_stack
{
private:
    struct node;
    struct counted_node_ptr
    {
        int external_count;
        node *ptr;
    };

    struct node
    {
        std::shared_ptr<T> data;
        std::atomic<int> internal_count;
        counted_node_ptr next;

        node(T const &data_)
            : data(std::make_shared<T>(data_)),
              internal_count(0)
        {
        }
    };

    std::atomic<counted_node_ptr> head;

    void increase_head_count(counted_node_ptr &old_counter)
    {
        counted_node_ptr new_counter;

        do
        {
            new_counter = old_counter;
            ++new_counter.external_count;
        } while (!head.compare_exchange_strong(old_counter, new_counter,
                                               std::memory_order_acquire,
                                               std::memory_order_relaxed));
        old_counter.external_count = new_counter.external_count;
    }

public:
    ~lock_free_stack()
    {
        while (pop())
            ;
    }

    void push(T const &data)
    {
        counted_node_ptr new_node;
        new_node.ptr = new node(data);
        new_node.external_count = 1;
        new_node.ptr->next = head.load(std::memory_order_relaxed);
        while (!head.compare_exchange_weak(new_node.ptr->next, new_node,
                                           std::memory_order_release,
                                           std::memory_order_relaxed))
            ;
    }
    std::shared_ptr<T> pop()
    {
        counted_node_ptr old_head =
            head.load(std::memory_order_relaxed);
        for (;;)
        {
            increase_head_count(old_head);
            node *const ptr = old_head.ptr;
            if (!ptr)
            {
                return std::shared_ptr<T>();
            }
            if (head.compare_exchange_strong(old_head, ptr->next,
                                             std::memory_order_relaxed))
            {
                std::shared_ptr<T> res;
                res.swap(ptr->data);

                int const count_increase = old_head.external_count - 2;

                if (ptr->internal_count.fetch_add(count_increase,
                                                  std::memory_order_release) == -count_increase)
                {
                    delete ptr;
                }

                return res;
            }
            else if (ptr->internal_count.fetch_add(-1,
                                                   std::memory_order_relaxed) == 1)
            {
                ptr->internal_count.load(std::memory_order_acquire);
                delete ptr;
            }
        }
    }
};

#endif

#if 0
template <typename T>
class lock_free_queue
{
private:
    struct node
    {
        std::shared_ptr<T> data;
        node *next;

        node()
            : next(nullptr)
        {
        }
    };

    std::atomic<node *> head;
    std::atomic<node *> tail;

    node *pop_head()
    {
        node *const old_head = head.load();
        if (old_head == tail.load()) // 1
        {
            return nullptr;
        }
        head.store(old_head->next);
        return old_head;
    }

public:
    lock_free_queue()
        : head(new node), tail(head.load())
    {
    }

    lock_free_queue(const lock_free_queue &other) = delete;
    lock_free_queue &operator=(const lock_free_queue &other) = delete;

    ~lock_free_queue()
    {
        while (node *const old_head = head.load())
        {
            head.store(old_head->next);
            delete old_head;
        }
    }
    std::shared_ptr<T> pop()
    {
        node *old_head = pop_head();
        if (!old_head)
        {
            return std::shared_ptr<T>();
        }

        std::shared_ptr<T> const res(old_head->data); // 2
        delete old_head;
        return res;
    }

    void push1(T new_value)
    {
        std::shared_ptr<T> new_data(std::make_shared<T>(new_value));
        node *p = new node;                 // 3
        node *const old_tail = tail.load(); // 4
        old_tail->data.swap(new_data);      // 5
        old_tail->next = p;                 // 6
        tail.store(p);                      // 7
    }

    void push2(T new_value)

    {
        std::unique_ptr<T> new_data(new T(new_value));
        counted_node_ptr new_next;
        new_next.ptr = new node;
        new_next.external_count = 1;
        for (;;)
        {
            node *const old_tail = tail.load(); // 1
            T *old_data = nullptr;
            if (old_tail->data.compare_exchange_strong(
                    old_data, new_data.get())) // 2
            {
                old_tail->next = new_next;
                tail.store(new_next.ptr); // 3
                new_data.release();
                break;
            }
        }
    }
};

#endif

#if 0
template <typename T>
class lock_free_queue
{
private:
    struct node;
    struct counted_node_ptr
    {
        int external_count;
        node *ptr;
    };

    std::atomic<counted_node_ptr> head;
    std::atomic<counted_node_ptr> tail; // 1

    struct node_counter
    {
        unsigned internal_count : 30;
        unsigned external_counters : 2; // 2
    };

    struct node
    {
        std::atomic<T *> data;
        std::atomic<node_counter> count; // 3
        counted_node_ptr next;

        node()
        {
            node_counter new_count;
            new_count.internal_count = 0;
            new_count.external_counters = 2; // 4
            count.store(new_count);

            next.ptr = nullptr;
            next.external_count = 0;
        }
    };

public:
    void push(T new_value)
    {
        std::unique_ptr<T> new_data(new T(new_value));
        counted_node_ptr new_next;
        new_next.ptr = new node;
        new_next.external_count = 1;
        counted_node_ptr old_tail = tail.load();

        for (;;)
        {
            increase_external_count(tail, old_tail); // 5

            T *old_data = nullptr;
            if (old_tail.ptr->data.compare_exchange_strong( // 6
                    old_data, new_data.get()))
            {
                old_tail.ptr->next = new_next;
                old_tail = tail.exchange(new_next);
                free_external_counter(old_tail); // 7
                new_data.release();
                break;
            }
            old_tail.ptr->release_ref();
        }
    }
};

#endif

#if 0
template <typename T>

class lock_free_queue
{

private:
    struct node
    {
        void release_ref();
    };

public:
    std::unique_ptr<T> pop()
    {
        counted_node_ptr old_head = head.load(std::memory_order_relaxed); // 1
        for (;;)
        {
            increase_external_count(head, old_head); // 2
            node *const ptr = old_head.ptr;
            if (ptr == tail.load().ptr)
            {
                ptr->release_ref(); // 3
                return std::unique_ptr<T>();
            }
            if (head.compare_exchange_strong(old_head, ptr->next)) // 4
            {
                T *const res = ptr->data.exchange(nullptr);
                free_external_counter(old_head); // 5
                return std::unique_ptr<T>(res);
            }
            ptr->release_ref(); // 6
        }
    }
};

#endif

#if 0
template <typename T>
class lock_free_queue
{
private:
    struct node
    {
        void release_ref()
        {
            node_counter old_counter = count.load(std::memory_order_relaxed);
            node_counter new_counter;
            do
            {
                new_counter = old_counter;
                --new_counter.internal_count;        // 1
            } while (!count.compare_exchange_strong( // 2
                old_counter, new_counter,
                std::memory_order_acquire, std::memory_order_relaxed));
            if (!new_counter.internal_count &&
                !new_counter.external_counters)
            {
                delete this; // 3
            }
        }
    };
};

#endif

#if 0
template <typename T>
class lock_free_queue
{
private:
    static void increase_external_count(std::atomic<counted_node_ptr> &counter,
                                        counted_node_ptr &old_counter)
    {
        counted_node_ptr new_counter;
        do
        {
            new_counter = old_counter;
            ++new_counter.external_count;
        } while (!counter.compare_exchange_strong(
            old_counter, new_counter,
            std::memory_order_acquire, std::memory_order_relaxed));

        old_counter.external_count = new_counter.external_count;
    }
};

#endif

#if 0
template <typename T>
class lock_free_queue
{
private:
    static void free_external_counter(counted_node_ptr &old_node_ptr)
    {
        node *const ptr = old_node_ptr.ptr;
        int const count_increase = old_node_ptr.external_count - 2;

        node_counter old_counter =
            ptr->count.load(std::memory_order_relaxed);
        node_counter new_counter;
        do
        {
            new_counter = old_counter;
            --new_counter.external_counters;              // 1
            new_counter.internal_count += count_increase; // 2
        } while (!ptr->count.compare_exchange_strong(     // 3
            old_counter, new_counter,
            std::memory_order_acquire, std::memory_order_relaxed));

        if (!new_counter.internal_count &&
            !new_counter.external_counters)
        {
            delete ptr; // 4
        }
    }
};
#endif



int main()
{

    return 0;
}