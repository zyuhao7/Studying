#include <iostream>
#include <thread>
#include <vector>
#include <list>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <iterator>
#include <functional>
#include <algorithm>
#include <map>
#include <set>

using namespace std;
// day-2025-8-23
// 线程安全 哈希表 (hash table)
class MyClass
{
public:
    MyClass(int i) : _data(i) {}

    friend std::ostream &operator<<(std::ostream &os, const MyClass &mc)
    {
        os << mc._data;
        return os;
    }

private:
    int _data;
};

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class threadsafe_hash_table
{
private:
    // 桶类型
    class bucket_type
    {
        friend class threadsafe_hash_table;

    private:
        typedef std::pair<Key, Value> bucket_value; // key,val
        typedef std::list<bucket_value> bucket_list;
        typedef typename bucket_list::iterator bucket_iterator;

        bucket_list data;                    // 存储数据
        mutable std::shared_timed_mutex mtx; // 读写锁

        bucket_iterator find_entry_for(const Key &key)
        {
            return std::find_if(data.begin(), data.end(), [&](const bucket_value &entry)
                                { return entry.first == key; });
        }

    public:
        // 查找 key 值, 找到对应的 value, 未找到则返回默认值
        Value value_for(Key const &key, Value const &default_value)
        {
            std::shared_lock<std::shared_timed_mutex> lock(mtx);
            bucket_iterator found = find_entry_for(key);
            return (found == data.end()) ? default_value : found->second;
        }
        // 添加key和value，找到则更新，没找到则添加
        void add_or_update_mapping(Key const &key, Value const &value)
        {
            std::shared_lock<std::shared_timed_mutex> lock(mtx);
            auto it = find_entry_for(key);
            if (it == data.end())
            {
                data.push_back(bucket_value(key, value));
            }
            else
            {
                it->second = value;
            }
        }
        // 删除对应的key
        void remove_mapping(Key const &key)
        {
            std::unique_lock<std::shared_timed_mutex> lock(mtx);
            bucket_iterator const it = find_entry_for(key);
            if (it != data.end())
            {
                data.erase(it);
            }
        }
    };

public:
    // 用 vector 存储桶类型
    std::vector<std::unique_ptr<bucket_type>> buckets;
    // hash(key) 根据 key 生成 哈希值
    Hash hasher;

    // //根据key生成数字，并对桶的大小取余得到下标，根据下标返回对应的桶智能指针
    bucket_type &get_bucket(Key const &key) const
    {
        std::size_t const bucket_index = hasher(key) % buckets.size();
        return *buckets[bucket_index];
    }

public:
    threadsafe_hash_table(unsigned int num_buckets = 19, Hash const &hasher_ = Hash())
        : buckets(num_buckets), hasher(hasher_)
    {
        for (unsigned int i = 0; i < num_buckets; ++i)
        {
            buckets[i] = std::make_unique<bucket_type>();
        }
    }

    threadsafe_hash_table(threadsafe_hash_table const &) = delete;
    threadsafe_hash_table &operator=(threadsafe_hash_table const &) = delete;

    Value value_for(Key const &key, Value const &default_value) const
    {
        return get_bucket(key).value_for(key, default_value);
    }

    void add_or_update_mapping(Key const &key, Value const &value)
    {
        get_bucket(key).add_or_update_mapping(key, value);
    }

    void remove_mapping(Key const &key)
    {
        get_bucket(key).remove_mapping(key);
    }

    std::map<Key, Value> get_map()
    {
        std::vector<std::unique_lock<std::shared_timed_mutex>> locks;
        for (auto &bucket : buckets)
        {
            locks.push_back(std::unique_lock<std::shared_timed_mutex>(bucket->mtx, std::defer_lock));
        }

        std::map<Key, Value> res;
        for (auto &bucket : buckets)
        {
            for (auto &entry : bucket->data)
            {
                res.insert(entry);
            }
        }
        return res;
    }
};

void TestThreadSafeHash()
{
    std::set<int> removeSet;
    threadsafe_hash_table<int, std::shared_ptr<MyClass>> table;
    std::thread t1([&]()
                   {
    	for(int i = 0; i < 100; i++)
    	{
           auto class_ptr =  std::make_shared<MyClass>(i); 
            table.add_or_update_mapping(i, class_ptr);
    	} });

    std::thread t2([&]()
                   {
        for (int i = 0; i < 100; )
        {
            auto find_res = table.value_for(i, nullptr);
            if(find_res)
            {
                table.remove_mapping(i);
                removeSet.insert(i);
                i++;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        } });

    std::thread t3([&]()
                   {
        for (int i = 100; i < 200; i++)
        {
            auto class_ptr = std::make_shared<MyClass>(i);
            table.add_or_update_mapping(i, class_ptr);
        } });

    t1.join();
    t2.join();
    t3.join();

    for (auto &i : removeSet)
    {
        std::cout << "remove data is " << i << std::endl;
    }

    auto copy_map = table.get_map();
    for (auto &i : copy_map)
    {
        std::cout << "copy data is " << *(i.second) << std::endl;
    }
}

int main()
{
    TestThreadSafeHash();
    return 0;
}
