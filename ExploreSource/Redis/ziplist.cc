#include <iostream>
#include "common.h"

// day-2025-7-28
/* The ziplist is a specially encoded dually linked list that is designed
 * to be very memory efficient. It stores both strings and integer values,
 * where integers are encoded as actual integers instead of a series of
 * characters. It allows push and pop operations on either side of the list
 * in O(1) time. However, because every operation requires a reallocation of
 * the memory used by the ziplist, the actual complexity is related to the
 * amount of memory used by the ziplist.
 *
 * ----------------------------------------------------------------------------
 *
 * ZIPLIST OVERALL LAYOUT
 * ======================
 *
 * The general layout of the ziplist is as follows:
 *
 * <zlbytes> <zltail> <zllen> <entry> <entry> ... <entry> <zlend>
 *
 * NOTE: all fields are stored in little endian, if not specified otherwise.
 *
 * <uint32_t zlbytes> is an unsigned integer to hold the number of bytes that
 * the ziplist occupies, including the four bytes of the zlbytes field itself.
 * This value needs to be stored to be able to resize the entire structure
 * without the need to traverse it first.
 *
 * <uint32_t zltail> is the offset to the last entry in the list. This allows
 * a pop operation on the far side of the list without the need for full
 * traversal.
 *
 * <uint16_t zllen> is the number of entries. When there are more than
 * 2^16-2 entries, this value is set to 2^16-1 and we need to traverse the
 * entire list to know how many items it holds.
 *
 * <uint8_t zlend> is a special entry representing the end of the ziplist.
 * Is encoded as a single byte equal to 255. No other normal entry starts
 * with a byte set to the value of 255.
 *
 * ZIPLIST ENTRIES
 * ===============
 *
 * Every entry in the ziplist is prefixed by metadata that contains two pieces
 * of information. First, the length of the previous entry is stored to be
 * able to traverse the list from back to front. Second, the entry encoding is
 * provided. It represents the entry type, integer or string, and in the case
 * of strings it also represents the length of the string payload.
 * So a complete entry is stored like this:
 *
 * <prevlen> <encoding> <entry-data>
 *
 * Sometimes the encoding represents the entry itself, like for small integers
 * as we'll see later. In such a case the <entry-data> part is missing, and we
 * could have just:
 *
 * <prevlen> <encoding>
 *
 * The length of the previous entry, <prevlen>, is encoded in the following way:
 * If this length is smaller than 254 bytes, it will only consume a single
 * byte representing the length as an unsigned 8 bit integer. When the length
 * is greater than or equal to 254, it will consume 5 bytes. The first byte is
 * set to 254 (FE) to indicate a larger value is following. The remaining 4
 * bytes take the length of the previous entry as value.
 *
 * So practically an entry is encoded in the following way:
 *
 * <prevlen from 0 to 253> <encoding> <entry>
 *
 * Or alternatively if the previous entry length is greater than 253 bytes
 * the following encoding is used:
 *
 * 0xFE <4 bytes unsigned little endian prevlen> <encoding> <entry>
 *
 * The encoding field of the entry depends on the content of the
 * entry. When the entry is a string, the first 2 bits of the encoding first
 * byte will hold the type of encoding used to store the length of the string,
 * followed by the actual length of the string. When the entry is an integer
 * the first 2 bits are both set to 1. The following 2 bits are used to specify
 * what kind of integer will be stored after this header. An overview of the
 * different types and encodings is as follows. The first byte is always enough
 * to determine the kind of entry.
 *
 * |00pppppp| - 1 byte
 *      String value with length less than or equal to 63 bytes (6 bits).
 *      "pppppp" represents the unsigned 6 bit length.
 * |01pppppp|qqqqqqqq| - 2 bytes
 *      String value with length less than or equal to 16383 bytes (14 bits).
 *      IMPORTANT: The 14 bit number is stored in big endian.
 * |10000000|qqqqqqqq|rrrrrrrr|ssssssss|tttttttt| - 5 bytes
 *      String value with length greater than or equal to 16384 bytes.
 *      Only the 4 bytes following the first byte represents the length
 *      up to 2^32-1. The 6 lower bits of the first byte are not used and
 *      are set to zero.
 *      IMPORTANT: The 32 bit number is stored in big endian.
 * |11000000| - 3 bytes
 *      Integer encoded as int16_t (2 bytes).
 * |11010000| - 5 bytes
 *      Integer encoded as int32_t (4 bytes).
 * |11100000| - 9 bytes
 *      Integer encoded as int64_t (8 bytes).
 * |11110000| - 4 bytes
 *      Integer encoded as 24 bit signed (3 bytes).
 * |11111110| - 2 bytes
 *      Integer encoded as 8 bit signed (1 byte).
 * |1111xxxx| - (with xxxx between 0001 and 1101) immediate 4 bit integer.
 *      Unsigned integer from 0 to 12. The encoded value is actually from
 *      1 to 13 because 0000 and 1111 can not be used, so 1 should be
 *      subtracted from the encoded 4 bit value to obtain the right value.
 * |11111111| - End of ziplist special entry.
 *
 * Like for the ziplist header, all the integers are represented in little
 * endian byte order, even when this code is compiled in big endian systems.
 *
 * EXAMPLES OF ACTUAL ZIPLISTS
 * ===========================
 *
 * The following is a ziplist containing the two elements representing
 * the strings "2" and "5". It is composed of 15 bytes, that we visually
 * split into sections:
 *
 *  [0f 00 00 00] [0c 00 00 00] [02 00] [00 f3] [02 f6] [ff]
 *        |             |          |       |       |     |
 *     zlbytes        zltail     zllen    "2"     "5"   end
 *
 * The first 4 bytes represent the number 15, that is the number of bytes
 * the whole ziplist is composed of. The second 4 bytes are the offset
 * at which the last ziplist entry is found, that is 12, in fact the
 * last entry, that is "5", is at offset 12 inside the ziplist.
 * The next 16 bit integer represents the number of elements inside the
 * ziplist, its value is 2 since there are just two elements inside.
 * Finally "00 f3" is the first entry representing the number 2. It is
 * composed of the previous entry length, which is zero because this is
 * our first entry, and the byte F3 which corresponds to the encoding
 * |1111xxxx| with xxxx between 0001 and 1101. We need to remove the "F"
 * higher order bits 1111, and subtract 1 from the "3", so the entry value
 * is "2". The next entry has a prevlen of 02, since the first entry is
 * composed of exactly two bytes. The entry itself, F6, is encoded exactly
 * like the first entry, and 6-1 = 5, so the value of the entry is 5.
 * Finally the special entry FF signals the end of the ziplist.
 *
 * Adding another element to the above string with the value "Hello World"
 * allows us to show how the ziplist encodes small strings. We'll just show
 * the hex dump of the entry itself. Imagine the bytes as following the
 * entry that stores "5" in the ziplist above:
 *
 * [02] [0b] [48 65 6c 6c 6f 20 57 6f 72 6c 64]
 *
 * The first byte, 02, is the length of the previous entry. The next
 * byte represents the encoding in the pattern |00pppppp| that means
 * that the entry is a string of length <pppppp>, so 0B means that
 * an 11 bytes string follows. From the third byte (48) to the last (64)
 * there are just the ASCII characters for "Hello World".
 *
 * ----------------------------------------------------------------------------
 */

/* 特殊常量定义 */
#define ZIP_END 255         /* ziplist的结束标记 */
#define ZIP_BIG_PREVLEN 254 /* 大前项长度的标记值 */

/* ziplist中的每个条目结构，可以存储字符串或整数 */
typedef struct
{
    /* 当存储字符串时，sval指向字符串内容，slen为长度 */
    unsigned char *sval;
    unsigned int slen;
    /* 当存储整数时，sval为NULL，lval存储整数值 */
    long long lval;
} ziplistEntry;

/* ziplist头部结构定义 */
typedef struct
{
    unsigned int zlbytes;   /* ziplist总字节数（包括自身） */
    unsigned int zltail;    /* 最后一个条目的偏移量，用于快速尾部访问 */
    unsigned int zllen;     /* 条目数量，当超过2^16-2时需要遍历获取实际数量 */
    unsigned char *entries; /* 条目数据起始位置 */
    unsigned char zlend;    /* 结束标记，固定为ZIP_END(255) */
} ziplist;

/*
 * 创建一个新的空ziplist
 * 返回值：指向新创建ziplist的指针，内存不足时返回NULL
 */
ziplist *ziplistNew(void)
{
    unsigned int bytes = sizeof(ziplist);
    ziplist *zl = (ziplist *)malloc(bytes);
    if (!zl)
        return NULL;

    zl->zlbytes = bytes;          /* 初始大小为头部结构大小 */
    zl->zltail = sizeof(ziplist); /* 初始时没有条目，尾部偏移指向结束标记位置 */
    zl->zllen = 0;                /* 条目数量为0 */
    zl->entries = NULL;           /* 没有条目数据 */
    zl->zlend = ZIP_END;          /* 设置结束标记 */
    return zl;
}

/*
 * 计算前项长度的编码方式
 * prevlen：前一个条目的实际长度
 * 编码结果存储在buf中，返回编码后的字节数
 */
unsigned int zipStorePrevEntryLength(unsigned char *buf, unsigned int prevlen)
{
    if (prevlen < ZIP_BIG_PREVLEN)
    {
        /* 小长度：1字节直接存储 */
        buf[0] = prevlen;
        return 1;
    }
    else
    {
        /* 大长度：1字节标记(ZIP_BIG_PREVLEN) + 4字节实际长度 */
        buf[0] = ZIP_BIG_PREVLEN;
        memcpy(buf + 1, &prevlen, 4);
        return 1 + 4;
    }
}

/*
 * 向ziplist中插入新条目
 * zl：目标ziplist
 * p：插入位置（NULL表示尾部插入）
 * entry：要插入的条目数据
 * 返回值：插入后的ziplist（可能因内存重分配而变化）
 */
ziplist *ziplistInsert(ziplist *zl, unsigned char *p, ziplistEntry *entry)
{
    /* 1. 计算新条目的大小 */
    unsigned int entrylen = 0;
    if (entry->sval)
    {
        /* 字符串类型：需要存储长度和内容 */
        entrylen = zipStorePrevEntryLength(NULL, 0); /* 前项长度占位 */
        entrylen += 1;                               /* 编码类型占位 */
        entrylen += entry->slen;                     /* 字符串内容长度 */
    }
    else
    {
        /* 整数类型：根据值大小选择不同编码 */
        entrylen = zipStorePrevEntryLength(NULL, 0) + 1; /* 前项长度+编码类型 */
        /* 实际实现中会根据lval大小进一步优化编码 */
    }

    /* 2. 重新分配内存 */
    unsigned int new_zlbytes = zl->zlbytes + entrylen;
    zl = (ziplist *)realloc(zl, new_zlbytes);
    if (!zl)
        return NULL;
    zl->zlbytes = new_zlbytes;

    /* 3. 移动现有数据（如果不是尾部插入） */
    if (p != NULL)
    {
        memmove(p + entrylen, p, zl->zlbytes - (p - (unsigned char *)zl) - entrylen);
    }

    /* 4. 更新尾部偏移和条目计数 */
    if (p == NULL || p == (unsigned char *)zl + zl->zltail)
    {
        zl->zltail = (unsigned char *)&zl->zlend - (unsigned char *)zl - entrylen;
    }
    zl->zllen++;

    /* 5. 存储新条目数据（实际实现中需要处理前项长度编码、值编码等细节） */
    /* ... 条目数据存储逻辑 ... */

    return zl;
}

/*
 * 释放ziplist及其所有资源
 * zl：要释放的ziplist
 */
void ziplistFree(ziplist *zl)
{
    if (zl->entries)
    {
        /* 释放所有条目数据（实际实现中需要逐个释放条目） */
        /* ... 条目释放逻辑 ... */
    }
    free(zl);
}
