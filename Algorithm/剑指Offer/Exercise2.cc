#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 2024-8-24
// 面试题 15 链表倒数第 k 个节点
// 输入一个链表, 输出该链表的倒数第 K 个节点, 为符合大多数人的习惯, 本题从 1 开始, 即 链表的尾部是倒数第一个节点.
// 例如一个链表有六个节点, 从头结点开始它们的值依次是 1 2 3 4 5 6 这个链表的倒数第三个节点是 值为 4 的节点.

/*
struct ListNode
{
    ListNode(int val)
        : _val(val), _next(NULL)
    {
    }
    int _val;
    ListNode *_next;
};

void CountBackwardsOfKNode(ListNode **pListHead, int k)
{
    // 考虑特殊情况: 1. k > 链表长度 ? 该如何取？ 模链表长度然后去倒数第 k % countNode ? 还是什么应该询问面试官.
    // 2. 长度为 负数? ...
    if (pListHead == NULL || *pListHead == NULL || k <= 0)
        return;
    int cnt = 1;
    ListNode *node = *pListHead;
    while (node->_next != NULL)
    {
        node = node->_next;
        cnt++;
    }
    if (k > cnt)
        k %= cnt;
    cnt -= k;

    node = *pListHead;
    while (cnt)
    {
        cnt--;
        node = node->_next;
    }
    cout << node->_val << endl;
    return;
}

int main()
{
    ListNode *p1 = new ListNode(1);
    ListNode *p2 = new ListNode(2);
    ListNode *p3 = new ListNode(3);
    ListNode *p4 = new ListNode(4);
    ListNode *p5 = new ListNode(5);
    ListNode *p6 = new ListNode(6);
    p1->_next = p2;
    p2->_next = p3;
    p3->_next = p4;
    p4->_next = p5;
    p5->_next = p6;
    ListNode **phead = &p1;
    CountBackwardsOfKNode(phead, 8);

    return 0;
}
*/

// 面试题 16 反转链表
/*
struct ListNode
{
    ListNode(int val)
        : _val(val), _next(NULL)
    {
    }
    int _val;
    ListNode *_next;
};

ListNode *ReverseList(ListNode *pListHead)
{

    ListNode *pReverseHead = NULL;
    ListNode *node = pListHead;
    ListNode *prev = NULL;
    while (node != NULL)
    {
        ListNode *next = node->_next;
        if (next == NULL)
            pReverseHead = node;
        node->_next = prev;
        prev = node;
        node = next;
    }
    return pReverseHead;
}

int main()
{
    ListNode *p1 = new ListNode(1);
    ListNode *p2 = new ListNode(2);
    ListNode *p3 = new ListNode(3);
    ListNode *p4 = new ListNode(4);
    ListNode *p5 = new ListNode(5);
    ListNode *p6 = new ListNode(6);
    p1->_next = p2;
    p2->_next = p3;
    p3->_next = p4;
    p4->_next = p5;
    p5->_next = p6;

    ListNode *head = ReverseList(p1);
    while (head->_next != NULL)
    {
        cout << head->_val << "->";
        head = head->_next;
        if (head->_next == NULL)
            cout << head->_val;
    }
    return 0;
}
*/