
#define LRU_BITS 24

typedef struct redisObject
{
    /*
        类型
        REDIS_TYPE_STRING: 字符串
        REDIS_TYPE_LIST: 列表
        REDIS_TYPE_SET: 集合
        REDIS_TYPE_ZSET: 有序集合
        REDIS_TYPE_HASH: 哈希表
        REDIS_TYPE_STREAM: 流
    */
    unsigned type : 4;
    /*
        编码
        REDIS_ENCODING_INT: 整数
        REDIS_ENCODING_EMBSTR: embstr编码的简单动态字符串
        REDIS_ENCODING_RAW: 简单动态字符串
        REDIS_ENCODING_LINKEDLIST: 链表
        REDIS_ENCODING_HT: 字典
        REDIS_ENCODING_ZIPLIST: 压缩列表
        REDIS_ENCODING_HASHMAP: 哈希表
        REDIS_ENCODING_SKIPLIST: 跳表和字典
    */
    unsigned encoding : 4;
    unsigned lru : LRU_BITS; /* LRU time (relative to global lru_clock) or
                              * LFU data (least significant 8 bits frequency
                              * and most significant 16 bits access time). */
    int refcount;
    void *ptr;
} robj;
