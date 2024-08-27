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

// day-2024-8-26
// 面试题 17 合并两个排序的链表
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
// 两个链表是两个递增的链表: 如
// 1 -> 3 -> 5 -> 7
// 2 -> 4 -> 6 -> 8
// 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8

ListNode *merge(ListNode *pHead1, ListNode *pHead2)
{
    if (pHead1 == NULL)
        return pHead2;
    else if (pHead2 == NULL)
        return pHead1;

    ListNode *pMergeHead = NULL;
    if (pHead1->_val < pHead2->_val)
    {
        pMergeHead = pHead1;
        pMergeHead->_next = merge(pHead1->_next, pHead2);
    }
    else
    {
        pMergeHead = pHead2;
        pMergeHead->_next = merge(pHead1, pHead2->_next);
    }
    return pMergeHead;
}

int main()
{
    ListNode *p1 = new ListNode(1);
    ListNode *p2 = new ListNode(2);
    ListNode *p3 = new ListNode(3);
    ListNode *p4 = new ListNode(4);
    ListNode *p5 = new ListNode(5);
    ListNode *p6 = new ListNode(6);
    ListNode *p7 = new ListNode(7);
    ListNode *p8 = new ListNode(8);

    p1->_next = p3;
    p2->_next = p4;
    p3->_next = p5;
    p4->_next = p6;
    p5->_next = p7;
    p6->_next = p8;

    ListNode *head = merge(p1, p2);
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

// 面试题 18 树的子结构
// 输入两棵二叉树 A 和 B, 判断 B 是否是 A 的子树.
/*
struct BinaryTreeNode
{
    BinaryTreeNode(int val)
        : _val(val),
          _left(NULL),
          _right(NULL)
    {
    }
    int _val;
    BinaryTreeNode *_left;
    BinaryTreeNode *_right;
};
// 例如 :
//         A                           B
//         8                           8
//      8     7                     9     2
//    9   2
//      4   7
// B 树 是 A 树的子结构.

bool DoseTreeHaveTree2(BinaryTreeNode *pRoot1, BinaryTreeNode *pRoot2)
{
    if (pRoot2 == NULL)
        return true;
    if (pRoot1 == NULL)
        return false;
    if (pRoot1->_val != pRoot2->_val)
        return false;
    return DoseTreeHaveTree2(pRoot1->_left, pRoot2->_left) &&
           DoseTreeHaveTree2(pRoot1->_right, pRoot2->_right);
}

bool HasSubtree(BinaryTreeNode *pRoot1, BinaryTreeNode *pRoot2)
{
    bool result = false;
    if (pRoot1 != NULL && pRoot2 != NULL)
    {
        if (pRoot1->_val == pRoot2->_val)
        {
            result = DoseTreeHaveTree2(pRoot1, pRoot2);
        }
        if (!result)
        {
            result = HasSubtree(pRoot1->_left, pRoot2);
        }
        if (!result)
        {
            result = HasSubtree(pRoot1->_right, pRoot2);
        }
    }
    return result;
}

int main()
{
    BinaryTreeNode *b1 = new BinaryTreeNode(8);
    BinaryTreeNode *b2 = new BinaryTreeNode(8);
    BinaryTreeNode *b3 = new BinaryTreeNode(7);
    BinaryTreeNode *b4 = new BinaryTreeNode(9);
    BinaryTreeNode *b5 = new BinaryTreeNode(2);
    BinaryTreeNode *b6 = new BinaryTreeNode(4);
    BinaryTreeNode *b7 = new BinaryTreeNode(7);
    b1->_left = b2;
    b2->_right = b3;
    b2->_left = b4;
    b2->_right = b5;
    b5->_left = b6;
    b5->_right = b7;

    BinaryTreeNode *b8 = new BinaryTreeNode(8);
    BinaryTreeNode *b9 = new BinaryTreeNode(9);
    BinaryTreeNode *b10 = new BinaryTreeNode(2);
    BinaryTreeNode *b11 = new BinaryTreeNode(0);

    b8->_left = b9;
    b8->_right = b10;

    cout << HasSubtree(b1, b8); // 1
    return 0;
}
*/

// 2024-8-27
// 面试题 19   二叉树的镜像
/*
struct BinaryTreeNode
{
    BinaryTreeNode(int val)
        : _val(val),
          _left(NULL),
          _right(NULL)
    {
    }
    int _val;
    BinaryTreeNode *_left;
    BinaryTreeNode *_right;
};

//         A                           B
//         8                           8
//      6     10                   10     6
//    5   7  9   1               1   9   7  5
// A 与 B 树 互为镜像.
// 思路: 将根节点的左右指针交换, 然后递归左右子树.
void PreorderTraversal(BinaryTreeNode *root)
{
    if (root == NULL)
        return;
    cout << root->_val << " ";
    if (root->_left)
        PreorderTraversal(root->_left);
    if (root->_right)
        PreorderTraversal(root->_right);
}

void MirrorRecursively(BinaryTreeNode *pNode)
{
    if (pNode == NULL || (pNode->_left == NULL && pNode->_right == NULL))
        return;
    BinaryTreeNode *tmp = pNode->_left;
    pNode->_left = pNode->_right;
    pNode->_right = tmp;
    if (pNode->_left)
        MirrorRecursively(pNode->_left);
    if (pNode->_right)
        MirrorRecursively(pNode->_right);
}

int main()
{
    BinaryTreeNode *b1 = new BinaryTreeNode(8);
    BinaryTreeNode *b2 = new BinaryTreeNode(6);
    BinaryTreeNode *b3 = new BinaryTreeNode(10);
    BinaryTreeNode *b4 = new BinaryTreeNode(5);
    BinaryTreeNode *b5 = new BinaryTreeNode(7);
    BinaryTreeNode *b6 = new BinaryTreeNode(9);
    BinaryTreeNode *b7 = new BinaryTreeNode(1);
    b1->_left = b2, b1->_right = b3;
    b2->_left = b4, b2->_right = b5;
    b3->_left = b6, b3->_right = b7;
    PreorderTraversal(b1);
    cout << endl;
    MirrorRecursively(b1);

    PreorderTraversal(b1);

    return 0;
}
*/

// 面试题 20 顺时针打印矩阵
// 1 2 3
// 4 5 6
// 7 8 9   -> 1 2 3 6 9 8 7 4 5 这种顺序.
/*
class Solution
{
public:
    vector<int> spiralOrder(vector<vector<int>> &matrix)
    {
        vector<int> res;
        if (matrix.empty())
            return res;

        int rows = matrix.size();
        int cols = matrix[0].size();
        int l = 0, r = cols - 1, t = 0, b = rows - 1;
        while (l <= r && t <= b)
        {
            for (int i = l; i <= r; ++i)
                res.push_back(matrix[t][i]);
            for (int j = t + 1; j <= b; ++j)
                res.push_back(matrix[j][r]);
            if (l < r && t < b)
            {
                for (int i = r - 1; i >= l; --i)
                    res.push_back(matrix[b][i]);
                for (int j = b - 1; j > t; --j)
                    res.push_back(matrix[j][l]);
            }
            l++;
            r--;
            t++;
            b--;
        }
        return res;
    }
};
int main()
{
    vector<vector<int>> v{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    for (int i = 0; i < v.size(); ++i)
    {
        for (int j = 0; j < v[0].size(); ++j)
            cout << v[i][j] << " ";
        cout << endl;
    }
    Solution slt;
    vector<int> res = slt.spiralOrder(v);
    for (int i = 0; i < res.size(); ++i)
        cout << res[i] << " ";
    // 1 2 3
    // 4 5 6
    // 7 8 9
    // 1 2 3 6 9 8 7 4 5
}
*/