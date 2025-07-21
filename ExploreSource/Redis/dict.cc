#include <iostream>
#include <assert.h>
#include <cstring>
#include <cstdint>
#include <cctype>

// 定义字典操作的返回状态
#define DICT_OK 0
#define DICT_ERR 1

// 类型定义，确保跨平台兼容性
typedef unsigned long PORT_ULONG;
typedef long PORT_LONG;
typedef long long PORT_LONGLONG;

/**
 * 字典条目结构体，存储键值对
 * [] => [key: void*, v: union, next: dictEntry*]
 */
typedef struct dictEntry
{
    void *key; // 键指针，指向任意类型的键数据
    union      // 值联合体，支持多种数据类型
    {
        void *val;    // 指针类型值
        uint64_t u64; // 无符号64位整数值
        int64_t s64;  // 有符号64位整数值
        double d;     // 双精度浮点数值
    } v;
    struct dictEntry *next; // 指向下一个条目，用于解决哈希冲突的链表
} dictEntry;

/**
 * 字典类型结构体，定义字典的操作函数
 * [] => [hashFunction: function, keyDup: function, valDup: function, keyCompare: function, keyDestructor: function, valDestructor: function]
 */
typedef struct dictType
{
    unsigned int (*hashFunction)(const void *key);                         // 哈希函数
    void *(*keyDup)(void *privdata, const void *key);                      // 键复制函数
    void *(*valDup)(void *privdata, const void *obj);                      // 值复制函数
    int (*keyCompare)(void *privdata, const void *key1, const void *key2); // 键比较函数
    void (*keyDestructor)(void *privdata, void *key);                      // 键销毁函数
    void (*valDestructor)(void *privdata, void *obj);                      // 值销毁函数
} dictType;

/**
 * 哈希表结构体
 * [] => [table: dictEntry**, size: PORT_ULONG, sizemask: PORT_ULONG, used: PORT_ULONG]
 */
typedef struct dictht
{
    dictEntry **table;   // 哈希表数组，每个元素是dictEntry指针
    PORT_ULONG size;     // 哈希表大小，即数组的容量
    PORT_ULONG sizemask; // 掩码，用于计算索引，值为size-1
    PORT_ULONG used;     // 已使用的条目数量
} dictht;

/**
 * 字典结构体，支持渐进式rehash
 * [] => [type: dictType*, privdata: void*, ht: dictht[2], rehashidx: PORT_LONG, iterators: int]
 */
typedef struct dict
{
    dictType *type;      // 字典类型，包含操作函数
    void *privdata;      // 私有数据，传递给操作函数
    dictht ht[2];        // 两个哈希表，用于渐进式rehash
    PORT_LONG rehashidx; // rehash索引，-1表示未进行rehash
    int iterators;       // 当前运行的迭代器数量
} dict;

/**
 * 字典迭代器结构体
 * [] => [d: dict*, index: PORT_LONG, table: int, safe: int, entry: dictEntry*, nextEntry: dictEntry*, fingerprint: PORT_LONGLONG]
 */
typedef struct dictIterator
{
    dict *d;                   // 指向要迭代的字典
    PORT_LONG index;           // 当前索引
    int table;                 // 当前哈希表（0或1）
    int safe;                  // 是否为安全迭代器
    dictEntry *entry;          // 当前条目
    dictEntry *nextEntry;      // 下一个条目
    PORT_LONGLONG fingerprint; // 迭代器指纹，用于检测误用
} dictIterator;

// 哈希表扫描函数类型
typedef void(dictScanFunction)(void *privdata, const dictEntry *de);

// 哈希表初始大小
#define DICT_HT_INITIAL_SIZE 4

// 调整大小相关的全局变量
static int dict_can_resize = 1;
static unsigned int dict_force_resize_ratio = 5;

/* -------------------------- 私有函数原型 ---------------------------- */
static int _dictExpandIfNeeded(dict *ht);
static PORT_ULONG _dictNextPower(PORT_ULONG size);
static int _dictKeyIndex(dict *d, const void *key);
static int _dictInit(dict *ht, dictType *type, void *privDataPtr);

/* -------------------------- 哈希函数实现 ---------------------------- */
/**
 * 整数哈希函数
 * @param key 要哈希的整数键
 * @return 哈希值
 */
unsigned int dictIntHashFunction(unsigned int key)
{
    key += ~(key << 15);
    key ^= (key >> 10);
    key += (key << 3);
    key ^= (key >> 6);
    key += ~(key << 11);
    key ^= (key >> 16);
    return key;
}

// 哈希函数种子
static uint32_t dict_hash_function_seed = 5381;

/**
 * 设置哈希函数种子
 * @param seed 新的种子值
 */
void dictSetHashFunctionSeed(uint32_t seed)
{
    dict_hash_function_seed = seed;
}

/**
 * 获取当前哈希函数种子
 * @return 当前种子值
 */
uint32_t dictGetHashFunctionSeed(void)
{
    return dict_hash_function_seed;
}

/**
 * 基于MurmurHash2算法的字符串哈希函数
 * @param key 要哈希的键
 * @param len 键的长度
 * @return 32位哈希值
 */
unsigned int dictGenHashFunction(const void *key, int len)
{
    const uint32_t m = 0x5bd1e995;
    const int r = 24;
    uint32_t h = dict_hash_function_seed ^ len;
    const unsigned char *data = (const unsigned char *)key;

    // 处理4字节块
    while (len >= 4)
    {
        uint32_t k = *(uint32_t *)data;
        k *= m;
        k ^= k >> r;
        k *= m;
        h *= m;
        h ^= k;
        data += 4;
        len -= 4;
    }

    // 处理剩余字节
    switch (len)
    {
    case 3:
        h ^= data[2] << 16;
    case 2:
        h ^= data[1] << 8;
    case 1:
        h ^= data[0];
        h *= m;
    };

    // 最后的混合操作
    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return (unsigned int)h;
}

/**
 * 大小写不敏感的字符串哈希函数
 * @param buf 要哈希的字符串
 * @param len 字符串长度
 * @return 哈希值
 */
unsigned int dictGenCaseHashFunction(const unsigned char *buf, int len)
{
    unsigned int hash = (unsigned int)dict_hash_function_seed;
    while (len--)
        hash = ((hash << 5) + hash) + (tolower(*buf++)); /* hash * 33 + tolower(c) */
    return hash;
}

/* ----------------------------- API实现 ----------------------------- */

/**
 * 重置哈希表
 * @param ht 要重置的哈希表
 */
static void _dictReset(dictht *ht)
{
    ht->table = NULL;
    ht->size = 0;
    ht->sizemask = 0;
    ht->used = 0;
}

/**
 * 创建新字典
 * @param type 字典类型
 * @param privDataPtr 私有数据指针
 * @return 新创建的字典
 */
dict *dictCreate(dictType *type, void *privDataPtr)
{
    dict *d = (dict *)malloc(sizeof(*d));
    _dictInit(d, type, privDataPtr);
    return d;
}

/**
 * 初始化字典
 * @param d 要初始化的字典
 * @param type 字典类型
 * @param privDataPtr 私有数据指针
 * @return 操作结果
 */
int _dictInit(dict *d, dictType *type, void *privDataPtr)
{
    _dictReset(&d->ht[0]);
    _dictReset(&d->ht[1]);
    d->type = type;
    d->privdata = privDataPtr;
    d->rehashidx = -1;
    d->iterators = 0;
    return DICT_OK;
}

// 字典操作宏定义
#define dictSetVal(d, entry, _val_)                                 \
    do                                                              \
    {                                                               \
        if ((d)->type->valDup)                                      \
            entry->v.val = (d)->type->valDup((d)->privdata, _val_); \
        else                                                        \
            entry->v.val = (_val_);                                 \
    } while (0)

#define dictSetKey(d, entry, _key_)                               \
    do                                                            \
    {                                                             \
        if ((d)->type->keyDup)                                    \
            entry->key = (d)->type->keyDup((d)->privdata, _key_); \
        else                                                      \
            entry->key = (_key_);                                 \
    } while (0)

#define dictFreeVal(d, entry)     \
    if ((d)->type->valDestructor) \
    (d)->type->valDestructor((d)->privdata, (entry)->v.val)

#define dictCompareKeys(d, key1, key2) \
    (((d)->type->keyCompare) ? (d)->type->keyCompare((d)->privdata, key1, key2) : (key1) == (key2))

#define dictFreeKey(d, entry)     \
    if ((d)->type->keyDestructor) \
    (d)->type->keyDestructor((d)->privdata, (entry)->key)

// 声明未实现的函数
static void
_dictRehashStep(dict *d);
int dictRehash(dict *d, int n);

/**
 * 执行一步rehash
 * @param d 要rehash的字典
 */
static void _dictRehashStep(dict *d)
{
    if (d->iterators == 0)
        dictRehash(d, 1);
}

// 字典操作宏定义
#define dictHashKey(d, key) (d)->type->hashFunction(key)
#define dictGetKey(he) ((he)->key)
#define dictGetVal(he) ((he)->v.val)
#define dictGetSignedIntegerVal(he) ((he)->v.s64)
#define dictGetUnsignedIntegerVal(he) ((he)->v.u64)
#define dictGetDoubleVal(he) ((he)->v.d)
#define dictSlots(d) ((d)->ht[0].size + (d)->ht[1].size)
#define dictSize(d) ((d)->ht[0].used + (d)->ht[1].used)
#define dictIsRehashing(d) ((d)->rehashidx != -1)

/**
 * 在字典中查找键
 * @param d 字典
 * @param key 要查找的键
 * @return 找到的条目，NULL表示未找到
 */
dictEntry *dictFind(dict *d, const void *key)
{
    dictEntry *he;
    unsigned int h, idx, table;

    if (d->ht[0].size == 0)
        return NULL; /* 哈希表不存在 */
    if (dictIsRehashing(d))
        _dictRehashStep(d);
    h = dictHashKey(d, key);

    // 在两个哈希表中查找
    for (table = 0; table <= 1; table++)
    {
        idx = h & d->ht[table].sizemask;
        he = d->ht[table].table[idx];
        while (he)
        {
            if (dictCompareKeys(d, key, he->key))
                return he;
            he = he->next;
        }
        if (!dictIsRehashing(d))
            break;
    }
    return NULL;
}

/**
 * 添加键到字典（仅添加键，不设置值）
 * @param d 字典
 * @param key 要添加的键
 * @return 新创建的条目，NULL表示失败
 */
dictEntry *dictAddRaw(dict *d, void *key)
{
    int index;
    dictEntry *entry;
    dictht *ht;

    if (_dictExpandIfNeeded(d) == DICT_ERR)
        return NULL; // 添加扩容检查
    if ((index = _dictKeyIndex(d, key)) == -1)
        return NULL;

    ht = dictIsRehashing(d) ? &d->ht[1] : &d->ht[0];
    entry = (dictEntry *)malloc(sizeof(*entry));
    entry->next = ht->table[index];
    ht->table[index] = entry;
    ht->used++;

    dictSetKey(d, entry, key);
    return entry;
}

/**
 * 添加键值对到字典
 * @param d 字典
 * @param key 键
 * @param val 值
 * @return 操作结果
 */
int dictAdd(dict *d, void *key, void *val)
{
    dictEntry *entry = dictAddRaw(d, key);
    if (!entry)
        return DICT_ERR;
    dictSetVal(d, entry, val);
    return DICT_OK;
}

/**
 * 添加或替换键值对
 * @param d 字典
 * @param key 键
 * @param val 值
 * @return 1表示新添加，0表示替换
 */
int dictReplace(dict *d, void *key, void *val)
{
    dictEntry *entry, auxentry;

    if (dictAdd(d, key, val) == DICT_OK)
        return 1;

    entry = dictFind(d, key);
    auxentry = *entry;
    dictSetVal(d, entry, val);
    dictFreeVal(d, &auxentry);
    return 0;
}

/**
 * 删除字典中的键
 * @param d 字典
 * @param key 要删除的键
 * @param nofree 是否不释放内存
 * @return 操作结果
 */
static int dictGenericDelete(dict *d, const void *key, int nofree)
{
    unsigned int h, idx;
    dictEntry *he, *prevHe;
    int table;

    if (d->ht[0].size == 0)
        return DICT_ERR; /* 哈希表不存在 */
    if (dictIsRehashing(d))
        _dictRehashStep(d);
    h = dictHashKey(d, key);

    for (table = 0; table <= 1; table++)
    {
        idx = h & d->ht[table].sizemask;
        he = d->ht[table].table[idx];
        prevHe = NULL;
        while (he)
        {
            if (dictCompareKeys(d, key, he->key))
            {
                // 从链表中移除条目
                if (prevHe)
                    prevHe->next = he->next;
                else
                    d->ht[table].table[idx] = he->next;
                if (!nofree)
                {
                    dictFreeKey(d, he);
                    dictFreeVal(d, he);
                }
                free(he);
                d->ht[table].used--;
                return DICT_OK;
            }
            prevHe = he;
            he = he->next;
        }
        if (!dictIsRehashing(d))
            break;
    }
    return DICT_ERR; /* 未找到 */
}

/**
 * 清空哈希表
 * @param d 字典
 * @param ht 要清空的哈希表
 * @param callback 回调函数
 * @return 操作结果
 */
int _dictClear(dict *d, dictht *ht, void(callback)(void *))
{
    PORT_ULONG i;

    // 释放所有条目
    for (i = 0; i < ht->size && ht->used > 0; i++)
    {
        dictEntry *he, *nextHe;

        if (callback && (i & 65535) == 0)
            callback(d->privdata);

        if ((he = ht->table[i]) == NULL)
            continue;
        while (he)
        {
            nextHe = he->next;
            dictFreeKey(d, he);
            dictFreeVal(d, he);
            free(he);
            ht->used--;
            he = nextHe;
        }
    }
    // 释放哈希表
    free(ht->table);
    // 重置哈希表
    _dictReset(ht);
    return DICT_OK;
}

/**
 * 释放字典
 * @param d 要释放的字典
 */
void dictRelease(dict *d)
{
    _dictClear(d, &d->ht[0], NULL);
    _dictClear(d, &d->ht[1], NULL);
    free(d);
}

/**
 * 执行rehash操作
 * @param d 字典
 * @param n 要rehash的桶数量
 * @return 1表示还有更多要rehash，0表示完成
 */
int dictRehash(dict *d, int n)
{
    int empty_visits = n * 10; /* 最大空桶访问次数 */
    if (!dictIsRehashing(d))
        return 0;

    while (n-- && d->ht[0].used != 0)
    {
        dictEntry *de, *nextde;

        assert(d->ht[0].size > (PORT_ULONG)d->rehashidx);
        while (d->ht[0].table[d->rehashidx] == NULL)
        {
            d->rehashidx++;
            if (--empty_visits == 0)
                return 1;
        }
        de = d->ht[0].table[d->rehashidx];
        // 将桶中的所有条目移动到新哈希表
        while (de)
        {
            unsigned int h;
            nextde = de->next;
            // 计算新哈希表中的索引
            h = dictHashKey(d, de->key) & d->ht[1].sizemask;
            de->next = d->ht[1].table[h];
            d->ht[1].table[h] = de;
            d->ht[0].used--;
            d->ht[1].used++;
            de = nextde;
        }
        d->ht[0].table[d->rehashidx] = NULL;
        d->rehashidx++;
    }

    // 检查是否已完成rehash
    if (d->ht[0].used == 0)
    {
        free(d->ht[0].table);
        d->ht[0] = d->ht[1];
        _dictReset(&d->ht[1]);
        d->rehashidx = -1;
        return 0;
    }

    // 还有更多要rehash
    return 1;
}

/**
 * 获取键对应的值
 * @param d 字典
 * @param key 键
 * @return 值，NULL表示未找到
 */
void *dictFetchValue(dict *d, const void *key)
{
    dictEntry *he = dictFind(d, key);
    return he ? dictGetVal(he) : NULL;
}

// 打印字典
void dictPrint(dict *d)
{
    if (d == nullptr)
        return;
    for (int i = 0; i < 2; i++)
    {
        std::cout << "Hash table " << i << " (size: " << d->ht[i].size << ", used: " << d->ht[i].used << ")" << std::endl;
        for (int j = 0; j < d->ht[i].size; j++)
        {
            dictEntry *he = d->ht[i].table[j];
            while (he)
            {
                // 正确：假设存储的是int*类型的键和值
                std::cout << "Index: " << j << ", Key: " << *(int *)he->key << ", Value: " << *(int *)he->v.val << std::endl;
                he = he->next;
            }
        }
    }
}

// 声明未实现的函数
static int _dictExpandIfNeeded(dict *ht) { return DICT_OK; }
static PORT_ULONG _dictNextPower(PORT_ULONG size)
{
    PORT_ULONG i = DICT_HT_INITIAL_SIZE;
    if (size >= (1UL << 30))
        return 1UL << 30;
    while (i < size)
        i *= 2;
    return i;
}

int dictExpand(dict *d, PORT_ULONG size)
{
    dictht nht;
    PORT_ULONG realsize = _dictNextPower(size);
    if (dictIsRehashing(d) || d->ht[0].used > size)
        return DICT_ERR;
    nht.size = realsize;
    nht.sizemask = realsize - 1;
    nht.table = (dictEntry **)calloc(realsize, sizeof(dictEntry *));
    nht.used = 0;
    if (d->ht[0].table == NULL)
    {
        d->ht[0] = nht;
        return DICT_OK;
    }
    d->ht[1] = nht;
    d->rehashidx = 0;
    return DICT_OK;
}

static int _dictKeyIndex(dict *d, const void *key)
{
    unsigned int h, idx, table;
    dictEntry *he;

    if (_dictExpandIfNeeded(d) == DICT_ERR)
        return -1;

    h = dictHashKey(d, key);
    for (table = 0; table <= 1; table++)
    {
        idx = h & d->ht[table].sizemask;
        he = d->ht[table].table[idx];
        while (he)
        {
            if (dictCompareKeys(d, key, he->key))
                return -1; /* Key already exists */
            he = he->next;
        }
        if (!dictIsRehashing(d))
            break;
    }
    return idx;
}
// 简化的字符串哈希函数
static unsigned int simpleHashFunction(const void *key)
{
    return dictGenHashFunction((const char *)key, strlen((const char *)key));
}

// 简化的键比较函数
static int simpleKeyCompare(void *privdata, const void *key1, const void *key2)
{
    return strcmp((const char *)key1, (const char *)key2) == 0;
}

// 简化的键销毁函数
static void simpleKeyDestructor(void *privdata, void *key)
{
    free(key);
}

// 简化的值销毁函数
static void simpleValDestructor(void *privdata, void *obj)
{
    free(obj);
}

// 默认dictType实例初始化
static dictType defaultDictType = {
    .hashFunction = simpleHashFunction,
    .keyDup = NULL, // 不复制键
    .valDup = NULL, // 不复制值
    .keyCompare = simpleKeyCompare,
    .keyDestructor = simpleKeyDestructor,
    .valDestructor = simpleValDestructor};

/**
 * 主函数，用于测试字典功能
 */
// int main()
// {
//     dictSetHashFunctionSeed(100);
//     std::cout << "Hash function seed: " << dictGetHashFunctionSeed() << std::endl;
//     std::cout << "Hash value for \"hello\": " << dictGenHashFunction("hello", 5) << std::endl;
//     dictType dictType;
//     dict *d = dictCreate(&defaultDictType, NULL);
//     dictPrint(d);
//     dictRelease(d);
//     return 0;
// }
