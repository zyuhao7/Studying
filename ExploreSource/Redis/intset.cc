#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <iostream>
#include <memory>
using namespace std;
// day-2025-7-26
/*
    intset（整数集合）是 Redis 中的一种底层数据结构，用于实现集合类型 Set 的一种优化存储形式。
    它专门用于保存 所有元素都是整数 的集合，具有 节省内存、快速查找 的优势。

    |    整数范围                         |   编码类型    |
        | ------------------------------  | ------------- |
        | -32,768 到 32,767               | `int16_t`     |
        | -2,147,483,648 到 2,147,483,647 | `int32_t`     |
        | 其它范围                        | `int64_t`     |
    编码类型：
        | `int16_t`  | 2 字节 |
        | `int32_t`  | 4 字节 |
        | `int64_t`  | 8 字节 |
    操作效率:
        插入（SADD）：O(n)，因为要保持排序
        查询（SISMEMBER）：O(log n)，使用二分查找
        删除（SREM）：O(n)
        内存占用：远小于 hashtable，尤其在元素较少时

    内存布局：
        +----------+----------+----------+----------+---------------+
        | encoding | length   | contents (连续整数数组，按升序排列) |
        +----------+----------+----------+----------+---------------+
    假设内容为：{3, 5, 7}，encoding 为 int16_t，内存大致如下：
        [encoding=2][length=3][0x0003][0x0005][0x0007]
*/

/* Toggle the 32 bit unsigned integer pointed by *p from little endian to
 * big endian 切换32位无符号整数的字节序
 */
void memrev32(void *p)
{
    unsigned char *x = (unsigned char *)p, t;
    /*
    字节序：
        小端序（little-endian）：低地址存放低字节，高地址存放高字节
        大端序（big-endian）：低地址存放高字节，高地址存放低字节
    */

    t = x[0];
    x[0] = x[3];
    x[3] = t;
    t = x[1];
    x[1] = x[2];
    x[2] = t;
}

/* Toggle the 64 bit unsigned integer pointed by *p from little endian to
 * big endian 切换64位无符号整数的字节序
 */
void memrev64(void *p)
{
    unsigned char *x = (unsigned char *)p, t;

    t = x[0];
    x[0] = x[7];
    x[7] = t;
    t = x[1];
    x[1] = x[6];
    x[6] = t;
    t = x[2];
    x[2] = x[5];
    x[5] = t;
    t = x[3];
    x[3] = x[4];
    x[4] = t;
}

/* Toggle the 16 bit unsigned integer pointed by *p from little endian to
 * big endian */
void memrev16(void *p)
{
    unsigned char *x = (unsigned char *)p, t;

    t = x[0];
    x[0] = x[1];
    x[1] = t;
}

#define INTSET_ENC_INT16 (sizeof(int16_t))
#define INTSET_ENC_INT32 (sizeof(int32_t))
#define INTSET_ENC_INT64 (sizeof(int64_t))
#define intrev32ifbe(v) v
#define intrev64ifbe(v) v
#define memrev16ifbe(p) memrev16(p)
#define memrev32ifbe(p) memrev32(p)
#define memrev64ifbe(p) memrev64(p)

typedef struct intset
{
    uint32_t encoding; // 编码方式
    uint32_t length;   // 集合中的元素数量
    int8_t contents[]; //  	存储整数元素的数组，按升序排列，便于二分查找
} intset;

/* Return the value at pos, given an encoding. 给定编码返回指定位置的值
 */
static int64_t _intsetGetEncoded(intset *is, int pos, uint8_t enc)
{
    int64_t v64;
    int32_t v32;
    int16_t v16;

    if (enc == INTSET_ENC_INT64)
    {
        memcpy(&v64, ((int64_t *)is->contents) + pos, sizeof(v64));
        memrev64ifbe(&v64);
        return v64;
    }
    else if (enc == INTSET_ENC_INT32)
    {
        memcpy(&v32, ((int32_t *)is->contents) + pos, sizeof(v32));
        memrev32ifbe(&v32);
        return v32;
    }
    else
    {
        memcpy(&v16, ((int16_t *)is->contents) + pos, sizeof(v16));
        memrev16ifbe(&v16);
        return v16;
    }
}

/* Return the required encoding for the provided value. 给定值返回所需的编码*/
static uint8_t _intsetValueEncoding(int64_t v)
{
    if (v < INT32_MIN || v > INT32_MAX)
        return INTSET_ENC_INT64;
    else if (v < INT16_MIN || v > INT16_MAX)
        return INTSET_ENC_INT32;
    else
        return INTSET_ENC_INT16;
}

/* Return the value at pos, using the configured encoding. 给定位置返回值*/
static int64_t _intsetGet(intset *is, int pos)
{
    return _intsetGetEncoded(is, pos, intrev32ifbe(is->encoding));
}

/* Set the value at pos, using the configured encoding. 给定位置设置值*/
static void _intsetSet(intset *is, int pos, int64_t value)
{
    uint32_t encoding = intrev32ifbe(is->encoding);

    if (encoding == INTSET_ENC_INT64)
    {
        ((int64_t *)is->contents)[pos] = value;
        memrev64ifbe(((int64_t *)is->contents) + pos);
    }
    else if (encoding == INTSET_ENC_INT32)
    {
        ((int32_t *)is->contents)[pos] = (int32_t)value;
        memrev32ifbe(((int32_t *)is->contents) + pos);
    }
    else
    {
        ((int16_t *)is->contents)[pos] = (int16_t)value;
        memrev16ifbe(((int16_t *)is->contents) + pos);
    }
}

/* Resize the intset */
static intset *intsetResize(intset *is, uint32_t len)
{
    uint32_t size = len * intrev32ifbe(is->encoding);
    is = (intset *)realloc(is, sizeof(intset) + size);
    return is;
}

/* Search for the position of "value". Return 1 when the value was found and
 * sets "pos" to the position of the value within the intset. Return 0 when
 * the value is not present in the intset and sets "pos" to the position
 * where "value" can be inserted. */
/**
 * @brief 在整数集合中搜索指定值的位置
 *
 * 此函数使用二分查找算法在整数集合中查找指定的值。
 * 如果找到该值，返回 1 并将其位置存储在 pos 指针指向的变量中；
 * 如果未找到，返回 0 并将该值可插入的位置存储在 pos 指针指向的变量中。
 *
 * @param is 指向整数集合的指针
 * @param value 需要搜索的整数值
 * @param pos 用于存储值的位置或可插入位置的指针，可为 nullptr
 * @return uint8_t 找到值返回 1，未找到返回 0
 */
static uint8_t intsetSearch(intset *is, int64_t value, uint32_t *pos)
{
    // 初始化二分查找的左右边界和中间位置
    int min = 0, max = is->length - 1, mid = -1;
    // 用于存储中间位置的值
    int64_t cur = -1;

    /* 集合为空时，值肯定找不到 */
    if (is->length == 0)
    {
        // 如果 pos 指针不为空，设置插入位置为 0
        if (pos)
            *pos = 0;
        return 0;
    }
    else
    {
        /* 检查可以确定找不到值，但能确定插入位置的情况 */
        // 如果值大于集合中的最大值
        if (value > _intsetGet(is, is->length - 1))
        {
            // 如果 pos 指针不为空，设置插入位置为集合长度
            if (pos)
                *pos = intrev32ifbe(is->length);
            return 0;
        }
        // 如果值小于集合中的最小值
        else if (value < _intsetGet(is, 0))
        {
            // 如果 pos 指针不为空，设置插入位置为 0
            if (pos)
                *pos = 0;
            return 0;
        }
    }

    // 二分查找循环
    while (max >= min)
    {
        // 计算中间位置，使用无符号整数加法避免溢出
        mid = ((unsigned int)min + (unsigned int)max) >> 1;
        // 获取中间位置的值
        cur = _intsetGet(is, mid);
        if (value > cur)
        {
            // 值大于中间值，调整左边界
            min = mid + 1;
        }
        else if (value < cur)
        {
            // 值小于中间值，调整右边界
            max = mid - 1;
        }
        else
        {
            // 找到值，跳出循环
            break;
        }
    }

    if (value == cur)
    {
        // 找到值，将位置存储到 pos 指针指向的变量中
        if (pos)
            *pos = mid;
        return 1;
    }
    else
    {
        // 未找到值，将可插入位置存储到 pos 指针指向的变量中
        if (pos)
            *pos = min; // 此时 min 和 max + 1 相等，使用 min 表示元素可插入的位置
        return 0;
    }
}

/* Create an empty intset. */
intset *intsetNew(void)
{
    intset *is = (intset *)malloc(sizeof(intset));
    is->encoding = INTSET_ENC_INT16;
    is->length = 0;
    return is;
}

/**
 * @brief 升级整数集合的编码类型并插入给定值
 *
 * 此函数会将整数集合升级到更大的编码类型，以容纳当前编码无法表示的给定值。
 * 升级过程中会将集合中的所有元素转换为新的编码类型，并保持集合的有序性，
 * 最后将新值插入到集合中的合适位置。
 *
 * @param is 指向整数集合的指针
 * @param value 要插入的整数值
 * @return intset* 升级并插入值后的整数集合指针
 */
static intset *intsetUpgradeAndAdd(intset *is, int64_t value)
{
    // 获取当前集合的编码类型
    uint8_t curenc = intrev32ifbe(is->encoding);
    // 获取能表示新值所需的编码类型
    uint8_t newenc = _intsetValueEncoding(value);
    // 获取当前集合的元素数量
    int length = intrev32ifbe(is->length);
    // 判断新值是否为负数，若为负数则需要将其插入到集合开头
    int prepend = value < 0 ? 1 : 0;

    /* 首先设置新的编码类型并调整集合大小 */
    // 设置集合的新编码类型
    is->encoding = intrev32ifbe(newenc);
    // 调整集合大小以容纳新元素
    is = intsetResize(is, intrev32ifbe(is->length) + 1);

    /* 从后向前升级元素编码，避免覆盖原有值。
     * 注意，"prepend" 变量用于确保在集合开头或结尾留出空位。 */
    // 将原集合中的元素逐个转换为新编码类型并移动到新位置
    while (length--)
        _intsetSet(is, length + prepend, _intsetGetEncoded(is, length, curenc));

    /* 在集合开头或结尾设置新值 */
    if (prepend)
        // 若新值为负数，将其插入到集合开头
        _intsetSet(is, 0, value);
    else
        // 若新值为非负数，将其插入到集合结尾
        _intsetSet(is, intrev32ifbe(is->length), value);
    // 更新集合的元素数量
    is->length = intrev32ifbe(intrev32ifbe(is->length) + 1);
    return is;
}

static void intsetMoveTail(intset *is, uint32_t from, uint32_t to)
{
    void *src, *dst;
    uint32_t bytes = intrev32ifbe(is->length) - from;
    uint32_t encoding = intrev32ifbe(is->encoding);

    if (encoding == INTSET_ENC_INT64)
    {
        src = (int64_t *)is->contents + from;
        dst = (int64_t *)is->contents + to;
        bytes *= sizeof(int64_t);
    }
    else if (encoding == INTSET_ENC_INT32)
    {
        src = (int32_t *)is->contents + from;
        dst = (int32_t *)is->contents + to;
        bytes *= sizeof(int32_t);
    }
    else
    {
        src = (int16_t *)is->contents + from;
        dst = (int16_t *)is->contents + to;
        bytes *= sizeof(int16_t);
    }
    memmove(dst, src, bytes);
}

/* Insert an integer in the intset */
/**
 * @brief 向整数集合中插入一个整数值
 *
 * 此函数尝试将指定的整数值插入到整数集合中。如果值已存在，则不插入；
 * 如果值需要更大的编码类型，则会升级集合编码。插入结果会通过 success 指针返回。
 *
 * @param is 指向整数集合的指针
 * @param value 要插入的整数值
 * @param success 用于返回插入是否成功的指针，成功为 1，值已存在为 0，可为 nullptr
 * @return intset* 插入值后的整数集合指针
 */
intset *intsetAdd(intset *is, int64_t value, uint8_t *success)
{
    // 获取能表示新值所需的编码类型
    uint8_t valenc = _intsetValueEncoding(value);
    // 用于存储值的位置或可插入位置
    uint32_t pos;

    // 初始化插入结果为成功
    if (success)
        *success = 1;

    // 如果新值所需的编码类型大于当前集合的编码类型，需要升级集合编码
    if (valenc > is->encoding)
    {
        // 调用升级并插入函数
        return intsetUpgradeAndAdd(is, value);
    }
    else
    {
        // 在集合中搜索值的位置
        if (intsetSearch(is, value, &pos))
        {
            // 值已存在，插入失败
            if (success)
                *success = 0;
            return is;
        }

        // 调整集合大小以容纳新元素
        is = intsetResize(is, intrev32ifbe(is->length) + 1);

        // 如果插入位置小于集合当前长度，需要移动元素腾出位置
        if (pos < intrev32ifbe(is->length))
            intsetMoveTail(is, pos, pos + 1);
    }

    // 在指定位置设置新值
    _intsetSet(is, pos, value);

    // 更新集合的元素数量
    is->length = intrev32ifbe(intrev32ifbe(is->length) + 1);

    return is;
}

intset *intsetRemove(intset *is, int64_t value, int *success)
{
    uint8_t valenc = _intsetValueEncoding(value);
    uint32_t pos;
    if (success)
        *success = 0;

    if (valenc <= intrev32ifbe(is->encoding) && intsetSearch(is, value, &pos))
    {
        uint32_t len = intrev32ifbe(is->length);

        /* We know we can delete */
        if (success)
            *success = 1;

        /* Overwrite value with tail and update length */
        if (pos < (len - 1))
            intsetMoveTail(is, pos + 1, pos);
        is = intsetResize(is, len - 1);
        is->length = intrev32ifbe(len - 1);
    }
    return is;
}
uint8_t intsetFind(intset *is, int64_t value)
{
    uint8_t valenc = _intsetValueEncoding(value);
    return valenc <= intrev32ifbe(is->encoding) && intsetSearch(is, value, NULL);
}
int64_t intsetRandom(intset *is)
{
    uint32_t len = intrev32ifbe(is->length);
    assert(len); /* avoid division by zero on corrupt intset payload. */
    return _intsetGet(is, rand() % len);
}

uint8_t intsetGet(intset *is, uint32_t pos, int64_t *value)
{
    if (pos < intrev32ifbe(is->length))
    {
        *value = _intsetGet(is, pos);
        return 1;
    }
    return 0;
}
uint32_t intsetLen(intset *is)
{
    return intrev32ifbe(is->length);
}
size_t intsetBlobLen(intset *is)
{
    return sizeof(intset) + (size_t)intrev32ifbe(is->length) * intrev32ifbe(is->encoding);
}

// int main()
// {
//     cout << INTSET_ENC_INT16 << endl; // 2
//     cout << INTSET_ENC_INT32 << endl; // 4
//     cout << INTSET_ENC_INT64 << endl; // 8

//     intset *is = intsetNew();
//     is = intsetAdd(is, 1, nullptr);
//     is = intsetAdd(is, 2, nullptr);
//     is = intsetAdd(is, 3, nullptr);
//     is = intsetAdd(is, 4, nullptr);
//     is = intsetAdd(is, 5, nullptr);
//     is = intsetAdd(is, 6, nullptr);
//     is = intsetAdd(is, 7, nullptr);
//     is = intsetAdd(is, 8, nullptr);
//     cout << is->encoding << endl; // 2
//     is = intsetAdd(is, 1000000, nullptr);
//     cout << is->encoding << endl; // 4

//     cout << intsetLen(is) << endl;
//     cout << intsetBlobLen(is) << endl;
//     int64_t value;
//     intsetGet(is, 0, &value);
//     cout << value << endl;

//     cout << intsetFind(is, 1000000) << endl;
// }