#include "common.h"
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <cassert>
#include <cmath>
#include <stdio.h>
using namespace std;

typedef char robj;
const int ZSKIPLIST_MAXLEVEL = 32;
typedef struct zskiplistNode // size: 24
{
    robj *obj;
    double score;
    struct zskiplistNode *backward;
    struct zskiplistLevel // size: 16
    {
        struct zskiplistNode *forward;
        unsigned int span;
    } level[]; // 柔性数组
} zskiplistNode;

typedef struct zskiplist
{
    struct zskiplistNode *header, *tail;
    PORT_ULONG length;
    int level;
} zskiplist;

// 创建一个新的跳跃表节点
// 参数:
// level: 节点的层数
// score: 节点的分数
// obj: 节点存储的对象指针
// 返回值:
// 指向新创建的跳跃表节点的指针
zskiplistNode *zslCreateNode(int level, double score, robj *obj)
{
    // 分配内存，sizeof(*zn) 为节点基本结构的大小，level * sizeof(struct zskiplistNode::zskiplistLevel) 为所有层的大小
    zskiplistNode *zn = (zskiplistNode *)malloc(sizeof(*zn) + level * sizeof(struct zskiplistNode::zskiplistLevel));
    // 设置节点的分数
    zn->score = score;
    // 设置节点存储的对象指针
    zn->obj = obj;
    // 返回新创建的节点指针
    return zn;
}

// 创建一个新的跳跃表
// 参数: 无
// 返回值: 指向新创建的跳跃表的指针
zskiplist *zslCreate(void)
{
    int j;
    zskiplist *zsl;

    // 为跳跃表分配内存
    zsl = (zskiplist *)malloc(sizeof(*zsl));
    // 初始化跳跃表的最大层数为 1
    zsl->level = 1;
    // 初始化跳跃表的节点数量为 0
    zsl->length = 0;
    // 创建跳跃表的头节点，层数为 1，分数为 0，不存储对象
    zsl->header = zslCreateNode(1, 0, NULL);
    // 初始化头节点每一层的 forward 指针为 NULL，span 为 0
    for (j = 0; j < 1; j++)
    {
        zsl->header->level[j].forward = NULL;
        zsl->header->level[j].span = 0;
    }
    // 初始化头节点的 backward 指针为 NULL
    zsl->header->backward = NULL;
    // 初始化跳跃表的尾节点为 NULL
    zsl->tail = NULL;
    // 返回新创建的跳跃表指针
    return zsl;
}

// 释放跳跃表节点的内存
// 参数:
// node: 指向要释放的跳跃表节点的指针
// 返回值:
// 无
void zslFreeNode(zskiplistNode *node)
{
    // 释放节点存储的对象指针
    free(node->obj);
    // 释放节点内存
    free(node);
}

// 释放跳跃表的内存
// 参数:
// zsl: 指向要释放的跳跃表的指针
// 返回值:
// 无
void zslFree(zskiplist *zsl)
{
    // 获取跳跃表中第一个数据节点（头节点之后的节点）
    zskiplistNode *node = zsl->header->level[0].forward, *next;
    // 释放跳跃表的头节点
    free(zsl->header);
    // 遍历跳跃表中的所有数据节点
    while (node)
    {
        // 保存下一个节点的指针
        next = node->level[0].forward;
        // 释放当前节点的内存
        zslFreeNode(node);
        // 移动到下一个节点
        node = next;
    }
    // 释放跳跃表本身的内存
    free(zsl);
}

// 随机生成跳跃表节点的层数
// 返回值: 生成的节点层数
int zslRandomLevel(void)
{
    // 初始化节点层数为 1
    int level = 1;
    // 以 25% 的概率增加节点层数
    while ((rand() & 0xFFFF) < (0.25 * 0xFFFF))
        level += 1;
    // 确保节点层数不超过最大层数
    return (level < ZSKIPLIST_MAXLEVEL) ? level : ZSKIPLIST_MAXLEVEL;
}

// 向跳跃表中插入一个新节点
// 参数:
// zsl: 指向跳跃表的指针
// score: 节点的分数
// obj: 节点存储的对象指针
// 返回值:
// 指向新插入的跳跃表节点的指针
zskiplistNode *zslInsert(zskiplist *zsl, double score, robj *obj)
{
    // 1. 初始化辅助结构
    zskiplistNode *update[ZSKIPLIST_MAXLEVEL], *x; // update[i]存储第i层插入位置的前驱节点
    unsigned int rank[ZSKIPLIST_MAXLEVEL];         // rank[i]存储第i层前驱节点的排名
    int i, level;

    // 输入校验：确保分数不是NaN
    assert(std::isfinite(score));
    x = zsl->header; // 从表头开始遍历

    // 2. 查找插入位置（核心遍历逻辑）
    // 从最高层向下逐层查找
    for (i = zsl->level - 1; i >= 0; i--)
    {
        // 初始化排名：最高层从0开始，低层继承高层结果
        rank[i] = i == (zsl->level - 1) ? 0 : rank[i + 1];

        // 遍历当前层，找到第一个 >=score 的节点
        // 条件1：当前层有后续节点
        // 条件2：后续节点分数<当前分数 或 分数相等但对象指针较小
        while (x->level[i].forward &&
               (x->level[i].forward->score < score ||
                (x->level[i].forward->score == score &&
                 (x->level[i].forward->obj < obj))))
        {
            rank[i] += x->level[i].span; // 累加跨度计算排名
            x = x->level[i].forward;     // 移动到下一个节点
        }
        update[i] = x; // 记录当前层的前驱节点
    }

    // 3. 随机生成新节点层数（Redis的幂次定律实现）
    level = zslRandomLevel();

    // 4. 处理新节点层数超过跳跃表现有层数的情况
    if (level > zsl->level)
    {
        // 初始化新增层的前驱节点为头节点
        for (i = zsl->level; i < level; i++)
        {
            rank[i] = 0;
            update[i] = zsl->header;
            update[i]->level[i].span = (unsigned int)zsl->length; // 跨度设为当前表长
        }
        zsl->level = level; // 更新跳跃表最大层数
    }

    // 5. 创建新节点（含柔性数组内存分配）
    x = zslCreateNode(level, score, obj);

    // 6. 插入新节点并更新各层指针和跨度（核心修改操作）
    for (i = 0; i < level; i++)
    {
        x->level[i].forward = update[i]->level[i].forward; // 新节点forward指向原后继
        update[i]->level[i].forward = x;                   // 前驱节点forward指向新节点

        // 计算新节点跨度：原前驱跨度 - (底层排名差)
        x->level[i].span = update[i]->level[i].span - (rank[0] - rank[i]);
        // 更新前驱节点跨度：底层排名差 + 1（新节点本身）
        update[i]->level[i].span = (rank[0] - rank[i]) + 1;
    }

    // 7. 更新未修改层的跨度（高于新节点层数的那些层）
    for (i = level; i < zsl->level; i++)
    {
        update[i]->level[i].span++; // 这些层只需简单+1（新节点在其下方）
    }

    // 8. 设置反向指针（backward）
    x->backward = (update[0] == zsl->header) ? NULL : update[0];
    if (x->level[0].forward)
        x->level[0].forward->backward = x; // 若有后继节点，更新其backward
    else
        zsl->tail = x; // 若无后继，新节点成为尾节点

    // 9. 更新跳跃表节点计数
    zsl->length++;
    return x;
}

// 删除跳跃表中的指定节点
// 参数:
// zsl: 指向跳跃表的指针
// x: 指向要删除的跳跃表节点的指针
// update: 存储各层插入/删除位置的前驱节点指针数组
// 返回值:
// 无
void zslDeleteNode(zskiplist *zsl, zskiplistNode *x, zskiplistNode **update)
{
    int i;
    // 遍历跳跃表的每一层，更新各层的指针和跨度
    for (i = 0; i < zsl->level; i++)
    {
        // 如果当前层的前驱节点的 forward 指针指向要删除的节点
        if (update[i]->level[i].forward == x)
        {
            // 更新前驱节点的跨度：加上被删除节点的跨度并减1（减去被删除节点本身）
            update[i]->level[i].span += x->level[i].span - 1;
            // 将前驱节点的 forward 指针指向被删除节点的后继节点
            update[i]->level[i].forward = x->level[i].forward;
        }
        else
        {
            // 如果当前层的前驱节点的 forward 指针不指向要删除的节点，跨度减1
            update[i]->level[i].span -= 1;
        }
    }

    // 如果被删除节点有后继节点
    if (x->level[0].forward)
    {
        // 将后继节点的 backward 指针指向被删除节点的前驱节点
        x->level[0].forward->backward = x->backward;
    }
    else
    {
        // 如果被删除节点没有后继节点，说明它是尾节点，更新跳跃表的尾节点为其前驱节点
        zsl->tail = x->backward;
    }

    // 如果跳跃表的层数大于1，且最高层的头节点的 forward 指针为 NULL
    while (zsl->level > 1 && zsl->header->level[zsl->level - 1].forward == NULL)
    {
        // 降低跳跃表的层数
        zsl->level--;
    }

    // 减少跳跃表的节点数量
    zsl->length--;
}

// 从跳跃表中删除指定分数和对象的节点
// 参数:
// zsl: 指向跳跃表的指针
// score: 要删除节点的分数
// obj: 要删除节点存储的对象指针
// 返回值:
// 1: 成功删除节点
// 0: 未找到匹配的节点
int zslDelete(zskiplist *zsl, double score, robj *obj)
{
    // 用于记录各层插入/删除位置的前驱节点指针数组
    zskiplistNode *update[ZSKIPLIST_MAXLEVEL], *x;
    int i;

    // 从跳跃表的头节点开始遍历
    x = zsl->header;
    // 从最高层向下逐层查找
    for (i = zsl->level - 1; i >= 0; i--)
    {
        // 遍历当前层，找到第一个 >=score 的节点
        // 条件1：当前层有后续节点
        // 条件2：后续节点分数<当前分数 或 分数相等但对象指针较小
        while (x->level[i].forward &&
               (x->level[i].forward->score < score ||
                (x->level[i].forward->score == score &&
                 (x->level[i].forward->obj < obj))))
            // 移动到下一个节点
            x = x->level[i].forward;
        // 记录当前层的前驱节点
        update[i] = x;
    }
    /* 可能存在多个具有相同分数的元素，我们需要找到分数和对象都匹配的元素 */
    // 获取当前层的下一个节点，即可能要删除的节点
    x = x->level[0].forward;
    // 检查该节点是否存在，且分数和对象都匹配
    if (x && score == x->score && x->obj == obj)
    {
        // 调用 zslDeleteNode 函数删除该节点
        zslDeleteNode(zsl, x, update);
        // 释放该节点的内存
        zslFreeNode(x);
        // 返回 1 表示成功删除节点
        return 1;
    }
    // 返回 0 表示未找到匹配的节点
    return 0; /* not found */
}

// int main()
// {

//     zskiplistNode *node = zslCreateNode(3, 3.14, NULL);
//     printf("Node Size: %lu\n", sizeof(*node));
//     // 打印节点的分数
//     printf("Node score: %.2f\n", node->score);
//     zskiplist *zsl = zslCreate();
//     char *key = (char *)malloc(sizeof(char) * 4);
//     std::strcpy(key, "a");
//     zslInsert(zsl, 3.14, key);
//     printf("Node score: %.2f\n", node->score);
//     printf("Node key: %s\n", zsl->header->level[0].forward->obj);

//     // 释放节点内存
//     zslFreeNode(node);
//     return 0;
// }