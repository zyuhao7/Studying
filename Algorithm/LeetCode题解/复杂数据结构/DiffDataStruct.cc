#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 并查集
// 快速判断两个点是否连通.
// 分为 union 操作 和 find 操作.
// union : 合并两个集合.   find : 查找给定节点的祖先.

// LeetCode 684 冗余连接.
// 路径压缩 + 按秩合并.
// const int N = 1e5 + 10;
// int p[N];
// vector<int> size(N, 1);

// int find(int x)
// {
//     if (x == p[x])
//         return x;
//     return p[x] = find(p[x]);
// }

// void unionSet(int x, int y)
// {
//     x = find(x), int y = find(y);
//     if (x == y)
//         return;
//     if (size[x] > size[y])
//         swap(x, y);
//     p[x] = y;
//     size[y] += size[x];
// }

// bool isConnect(int x, int y)
// {
//     return find(x) == find(y);
// }

// 复合数据结构
// 这类问题通常采用 unordered_map 或 map 辅助记录,  从而加速寻址, 再配上 vector 或者 list 进行数据储存, 从而加速连续选址或删除值.
// LeetCode 146 LRU 缓存
// 最少最近使用缓存 (least recently used cache, LRU)
#if 0
class LRUCache
{
    unordered_map<int, list<pair<int, int>>::iterator> hash;
    list<pair<int, int>> cache;
    int size;

public:
    LRUCache(int capacity)
        : size(capacity) {}

    int get(int key)
    {
        auto it = hash.find(key);
        if (it == hash.end())
            return -1;
        cache.splice(cache.begin(), cache, it->second);
        return it->second->second;
    }

    void put(int key, int value)
    {
        auto it = hash.find(key);
        if (it != hash.end())
        {
            it->second->second = value;
            return cache.splice(cache.begin(), cache, it->second);
        }
        cache.insert(cache.begin(), make_pair(key, value));
        hash[key] = cache.begin();
        if (cache.size() > size)
        {
            hash.erase(cache.back().first);
            cache.pop_back();
        }
    }
};
int main()
{

    return 0;
}
#endif