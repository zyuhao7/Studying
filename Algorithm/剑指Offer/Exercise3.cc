#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;
// day-2024-8-29
// 面试题 23 从上到下打印二叉树

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

// 二叉树的层序遍历
//      8
//    6   10
//  5  7 9   11
//  取出 根节点 8 然后添加到队列, 打印节点值, 然后加入左右子节点,  6   10, 取出 6 节点, 然后打印, 假如 6 的左右子节点,  10 5 7,
// 然后打印 10, 假如 10 的左右子节点, 5 7 9 11.  一直处理到最后一层.
/*
void LevelOrderTraversal(BinaryTreeNode *pRoot)
{
    if (pRoot == NULL)
        return;
    queue<BinaryTreeNode *> que;
    que.push(pRoot);

    while (!que.empty())
    {
        BinaryTreeNode *node = que.front();
        cout << node->_val << " ";
        que.pop();
        if (node->_left != NULL)
        {
            que.push(node->_left);
        }
        if (node->_right != NULL)
        {
            que.push(node->_right);
        }
    }
}

int main()
{
    BinaryTreeNode *b1 = new BinaryTreeNode(8);
    BinaryTreeNode *b2 = new BinaryTreeNode(6);
    BinaryTreeNode *b3 = new BinaryTreeNode(10);
    BinaryTreeNode *b4 = new BinaryTreeNode(5);
    BinaryTreeNode *b5 = new BinaryTreeNode(7);
    BinaryTreeNode *b6 = new BinaryTreeNode(9);
    BinaryTreeNode *b7 = new BinaryTreeNode(11);
    b1->_left = b2;
    b1->_right = b3;
    b2->_left = b4;
    b2->_right = b5;
    b3->_left = b6;
    b3->_right = b7;
    LevelOrderTraversal(b1);

    return 0;
}
*/

// 面试题 24 二叉搜索树的后序遍历序列
//       8
//    6    10
//  5  7  9   11

// 5 7 6 9 11 10 8

/*
bool VerifySequenceOfBST(int sequence[], int length)
{
    if (sequence == NULL || length <= 0)
        return false;
    int root = sequence[length - 1];

    int i = 0;
    for (; i < length - 1; ++i)
    {
        if (sequence[i] > root)
            break;
    }

    // 在二叉搜索树中, 右子树的节点大于根节点.
    int j = i;
    for (; j < length - 1; ++j)
    {
        if (sequence[j] < root)
            return false;
    }

    // 判断左子树是否是二叉搜索树
    if (i > 0)
        bool left = VerifySequenceOfBST(sequence, i);

    // 判断右子树是否是二叉搜索树
    if (i < length - 1)
        bool right = VerifySequenceOfBST(sequence + i, length - i - 1);

    return (left && right);
}

int main()
{
    BinaryTreeNode *b1 = new BinaryTreeNode(8);
    BinaryTreeNode *b2 = new BinaryTreeNode(6);
    BinaryTreeNode *b3 = new BinaryTreeNode(10);
    BinaryTreeNode *b4 = new BinaryTreeNode(5);
    BinaryTreeNode *b5 = new BinaryTreeNode(7);
    BinaryTreeNode *b6 = new BinaryTreeNode(9);
    BinaryTreeNode *b7 = new BinaryTreeNode(11);
    b1->_left = b2;
    b1->_right = b3;
    b2->_left = b4;
    b2->_right = b5;
    b3->_left = b6;
    b3->_right = b7;
    int a[] = {5, 7, 6, 9, 11, 10, 8};
    cout << VerifySequenceOfBST(a, sizeof(a) / sizeof(a[0]));

    return 0;
}
*/