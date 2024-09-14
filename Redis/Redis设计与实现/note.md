# Redis 设计与实现
` day-2024-9-8`

## 第二章 简单动态字符串
        1、 Redis 只会使用 C 字符串作为字面量, 在大多数情况下, Redis 使用 SDS(Simple Dynamic String, 简单动态字符串) 作为字符串表示.

        2、 比起 C 字符串, SDS 具有如下优点:
            1) 常数复杂度获取字符串长度
            2) 杜绝缓冲区溢出
            3) 减少修改字符串长度时所需的内存重分配次数
            4) 二进制安全
            5) 兼容部分 C 字符串函数

`day-2024-9-10`
## 第三章 链表
```c++
    1. 链表被广泛用于实现 Redis的各种功能,比如列表键、 发布与订阅、慢查询、监视器等
    2. 每个链表节点由一个 listNode 结构来表示, 每个节点都有一个指向前置节点和后置节点的指针, 所以 Redis 的链表实现是双端链表.
    3. 每个链表使用一个 list 结构来表示, 这个结构带有表头节点指针、 表尾节点指针以及链表长度等信息
    4. 因为链表表头节点的前置节点和表尾节点的后置节点都指向 NULL, 所以Redis的链表实现是无环链表
    5. 通过为链表设置不同的类型特定函数, Redis链表可以用于保存各种不同类型的值. 
```
`day-2024-9-11`
## 第四章 字典
![alt text](./Pic/image.png)
![alt text](./Pic/image1.png)

```c++
    哈希表的负载因子可以通过公式:
    //负载因子 = 哈希表已保存节点数量 / 哈希表大小
    load_factor = ht[0].used / ht[0].size

    typedef struct dictht{
        // 哈希表数组
        dictEntry** table;

        // 哈希表大小
        unsigned long size;

        // 哈希表大小掩码, 用于计算所以, 总是等于 size - 1
        unsigned long sizemask;

        // 该哈希表已有节点的数量
        unsigned long used;
    } dictht;

    typedef struct dictEntry{
        // 键
        void* key;

        // 值
        union{
            void* val;
            uint64_t u64;
            int64_t s64;
        } v;

        // 指向下个哈希表节点, 形成链表
        struct dictEntry* next;
    }dictEntry;

    typedef struct dict{
        // 类型特定函数
        dictType* type;

        // 私有数据
        void* privdata;

        // 哈希表
        dictht ht[2];

        // rehash 索引
        // 当 rehash 不再进行时, 值为 -1
        // in trehashidx;
    } dict;

    typedef struct dictType{
        // 计算哈希值的函数
        unsigned int (* hashFunction)(const void* key);

        // 复制键的函数
        void* (*keyDup) (void* privdata, const void* key);

        // 复制值的函数
        void* (*valDup) (void* privdata, const void* obj);

        // 对比键的函数
        int (*keyCompare)(void* privdata, const void* key1, const void* key2);

        // 销毁键的函数
        void (*keyDestructor)(void* privdata, void* key);

        //销毁值的函数
        void (*valDestructor)(void* privdata, void* obj);
    } dictType;

    1. 字典被广泛用于实现 Redis 的各种功能, 其中包括数据库和哈希键.
    2. Redis 中的字典使用哈希表作为底层实现, 每个字典带有两个哈希表, 一个平时使用, 另一个在进行rehash 时使用.
    3. 当字典被用作数据库的底层实现时, 或者哈希键的底层实现时, Redis 使用 MurmurHash2 算法来计算键的哈希值.
    4. 哈希表使用链地址法来解决键冲突, 被分配到同一个索引上的多个键值对会连成一个单向链表.
    5. 在对哈希表进行扩展或收缩操作时, 程序需要将现有哈希表包含的所有键值对 rehash 到新哈希表中, 并且这个 rehash 过程并不是一次性完成的, 而是渐进式地完成的.
```

## 第五章 跳跃表
![alt text](./Pic/image2.png)
```c++
    跳跃表 skiplist 是一个有序的数据结构, 它通过在每个节点中维持多个指向其他节点的指针, 从而达到快速访问节点的目的.
    跳表支持平均 O(lgN) 最快 O(N) 复杂度的节点查找, 还可以通过顺序性操作来批量处理节点.
    大多数情况下, 跳表的效率可以和平衡树相媲美, 并且因为跳表的实现比平衡树要来的更简单, 所以不少程序使用跳表来代替平衡树.
    Redis 使用跳表作为有序集合的底层实现之一, 如果一个有序集合包含的元素数量比较多, 又或者有序集合元素的成员(member) 是比较长的字符串时, Redis 就会使用跳表来作为有序集合键的底层实现.

    typedef struct zskiplistNode{
        //层
        struct zskiplistLevel{
            // 前进指针
            struct zskiplistNode* forward;

            // 跨度
            unsigned int span;
        }level[];

        // 后退指针
        struct zskiplistNode* backward;

        // 分值
        double score;

        // 成员对象
        robj *obj;
    } zskiplistNode;

    typedef struct zskiplist{
        // 表头节点和表尾节点
        struct zskiplistNode* header, tail;

        //表中节点的数量
        unsigned long length;

        //表中层数最大的节点的层数
        int level;
    }zskiplist;

    1. 跳表是有序集合的底层实现之一
    2. Redis 的跳跃表实现由 zskiplist 和 zskiplistNode 两个结构组成, 其中 zskiplist 用于保存跳表信息(比如表头节点、表尾节点、 层数、长度), 而 zskiplistNode 则用于表示跳跃表节点
    3. 每个跳表的层高都是 1 至 32 之间的随机数
    4. 在同一个跳表中, 多个节点可以包含相同的分值, 但每个节点的成员对象必须是唯一的.
    5. 跳表中的节点按分值大小进行排序, 当分值相同时, 节点按照成员对象的大小进行排序.
```

## 第六章 整数集合
![alt text](./Pic/image3.png)
```c++
    整数集合(intset) 是集合键的底层实现之一, 当一个集合只包含整数值元素, 并且这个集合的元素数量不多时, Redis 就会使用整数集合作为集合键的底层实现.
    typedef struct intset{
         // 编码方式
         uint32_t encoding;
         // 集合包含的元素数量
         uint32_t length;
         // 保存元素的数组
         int8_t contents[];
    }intset;

    1.整数集合是集合键的底层实现之一
    2. 整数集合的底层实现为数组, 这个数组以有序、无重复的方式保存集合, 在有需要时,程序会根据新添加元素的类型,改变这个数组的类型
    3. 升级操作为整数集合带来了操作上的灵活性, 并且尽可能节约了内存
    4. 整数集合支持升级操作, 不支持降级操作.
```

`day-2024-9-14`
## 第七章 压缩列表
```c++
    压缩列表(ziplist) 是列表键和哈希键的底层实现之一. 当一个列表键只包含少量列表项, 并且每个列表项要么就是小整数值, 要么就是长度比较短字符串, 那么redis就会使用 压缩列表来做列表键的底层实现.

    1. 压缩列表是一种为节约内存而开发的顺序性数据结构.
    2. 压缩列表被用作列表键和哈希键的底层实现之一.
    3. 压缩列表可以包含多个节点, 每个节点可以保存一个字节数组或者整数值.
    4. 添加新节点到压缩队列, 或者从压缩队列中删除节点, 可能会引发连锁更新操作, 但这种操作出现的几率不高.
```