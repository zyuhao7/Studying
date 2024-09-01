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

// 2024-8-30
// 面试题 25 二叉树中和为某一值的路径
// 输入一颗二叉树和一个整数, 打印出二叉树中节点值的和为输入整数的所有路径.
//       10
//    5    12
//  4  7                      --> 22   10 + 5 + 7  |  10 + 22
// 先进入 10, 把值 求和, 和 22 比较, 大于则返回, 小于进入左右子树, 先进入左子树, 求路径和, 然后比较,如果大于 则 返回, 小于
// 则继续进入左子树, 求路径和 然后比较,小于则进入左子树, 如果左子树为空, 则 减掉此节点值返回上一节点,然后继续进入右子树, 直到
// 遍历完整棵树. 需要保存遍历的路径.
/*
class Solution
{
public:
    vector<vector<int>> pathSum(BinaryTreeNode *root, int targetSum)
    {
        dfs(root, targetSum);
        return res;
    }

private:
    vector<vector<int>> res;
    vector<int> path;
    void dfs(BinaryTreeNode *root, int targetSum)
    {
        if (root == nullptr)
            return;
        path.push_back(root->_val);
        targetSum -= root->_val;
        if (root->_left == nullptr && root->_right == nullptr && targetSum == 0)
            res.push_back(path);
        dfs(root->_left, targetSum);
        dfs(root->_right, targetSum);
        path.pop_back();
    }
};

int main()
{
    BinaryTreeNode *b1 = new BinaryTreeNode(10);
    BinaryTreeNode *b2 = new BinaryTreeNode(5);
    BinaryTreeNode *b3 = new BinaryTreeNode(12);
    BinaryTreeNode *b4 = new BinaryTreeNode(4);
    BinaryTreeNode *b5 = new BinaryTreeNode(7);
    b1->_left = b2;
    b1->_right = b3;
    b2->_left = b4;
    b2->_right = b5;
    vector<vector<int>> res = Solution().pathSum(b1, 22);
    for (int i = 0; i < res.size(); ++i)
    {
        for (int j = 0; j < res[i].size(); ++j)
        {
            cout << res[i][j] << " "; // 10 5 7
                                      // 10 12
        }
        cout << endl;
    }

    return 0;
}
*/

// 面试题 26 复杂链表的复制
// 1、 直接复制, 然后每个节点找在链表什么位置, 置 random 指针, 时间复杂度 O(N^2)
// 2、 存个哈希, <R,R`>, 直接找对应节点的 random指针, 空间换时间, 空间复杂度 O(N), 时间复杂度 O(N).
// 3、 将节点复制到本节点的后面 A A` B B` 这种, 然后遍历一遍, 存一下奇数节点的 random 指针, 然后偶数节点指向 存的技术节点的下一
// 位置就行, 然后根据奇偶将两个链表分开.
/*
class Solution
{
public:
    void copyNode(Node *head)
    {
        if (head == NULL)
            return;

        Node *node = new Node(head->val);
        node->random = NULL;
        node->next = head->next;
        head->next = node;
        copyNode(node->next);
    }

    void setRandomPtr(Node *head)
    {
        Node *cur = head;
        while (cur)
        {
            Node *copy = cur->next;
            if (cur->random == NULL)
                copy->random = NULL;
            else
                copy->random = cur->random->next;
            cur = copy->next;
        }
    }
    Node *detachList(Node *head)
    {
        Node *copyHead = NULL, *copyTail = NULL;
        Node *cur = head;
        while (cur)
        {
            Node *copy = cur->next;
            Node *next = copy->next;
            if (copyTail == NULL)
            {
                copyHead = copyTail = copy;
            }
            else
            {
                copyTail->next = copy;
                copyTail = copy;
            }
            cur->next = next;
            cur = next;
        }
        return copyHead;
    }

    Node *copyRandomList(Node *head)
    {
        if (head == NULL)
            return NULL;
        // 1、 复制节点.
        copyNode(head);

        // 2、 设置 random 指针.
        setRandomPtr(head);

        // 3、 分离链表
        Node *res = detachList(head);
        return res;
    }
};
*/

// 2024-9-1
// 面试题 27 二叉搜索树与双向链表
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
class Solution
{
public:
    Node *treeToDoublyList(Node *root)
    {
        if (root == nullptr)
            return nullptr;
        dfs(root);
        head->left = prev;
        prev->right = head;
        return head;
    }

private:
    Node *prev, *head;

    void dfs(Node *cur)
    {
        if (cur == nullptr)
            return;
        dfs(cur->left);
        if (prev != nullptr)
            prev->right = cur;
        else
            head = cur;
        cur->left = prev;
        prev = cur;
        dfs(cur->right);
    }
};
*/

// 面试题 28 字符串的排列
// 输入一个字符串, 打印该字符串中字符的所有排列, 例如输入字符串 abc 则打印出 abc、acb、bac、bca、cab、cba.
/*
void StringPermutation(string &s, vector<bool> &used, string str)
{
    if (str.size() == s.size())
    {
        cout << str << endl;
        return;
    }

    for (int i = 0; i < s.size(); ++i)
    {
        if (used[i])
            continue;

        used[i] = true;
        str += s[i];

        StringPermutation(s, used, str);

        str.pop_back();
        used[i] = false;
    }
}

// 交换两个字符的辅助函数
void swap(char &a, char &b)
{
    char temp = a;
    a = b;
    b = temp;
}

// 生成排列的递归函数
void Permutation(string &s, int left, int right)
{
    if (left == right)
    {
        cout << s << endl;
    }
    else
    {
        for (int i = left; i <= right; i++)
        {
            swap(s[left], s[i]);             // 交换当前字符与后续字符
            Permutation(s, left + 1, right); // 递归调用
            swap(s[left], s[i]);             // 回溯：恢复原有字符顺序
        }
    }
}

int main()
{
    string s = "abc";
    vector<bool> used(s.size(), false);
    StringPermutation(s, used, "");
    cout << "--------------------" << endl;
    Permutation(s, 0, 2);

    return 0;
}
// 画图 、 举例子、 分解
*/

// 面试题 29 数组中出现次数超过一半的数字
// 例如 输入一个长度为 9 的数组 {1,2,3,2,2,2,5,4,2} 由于数字 2 在数组中出现了五次, 超过数组长度的一半, 因此输出 2.

/*
int Partition(int data[], int length, int start, int end)
{
    if (data == NULL || length <= 0 || start < 0 || end >= length)
        return;
    int index = RandomInRange(start, end);
    swap(&data[index], &data[end]);

    int small = start - 1;
    for (index = start; index < end; ++index)
    {
        ++small;
        if (small != index)
            swap(&data[index], &data[small]);
    }
    ++small;
    swap(&data[small], &data[end]);
}

bool state = false;
bool CheckInvalidArray(int *numbers, int length)
{
    state = false;
    if (numbers == NULL && length <= 0)
        state = true;
    return state;
}

bool CheckMoreThanHalf(int *numbers, int length, int number)
{
    int times = 0;
    for (int i = 0; i < length; ++i)
    {
        if (numbers[i] == number)
            times++;
    }
    bool isMoreThanHalf = true;
    if (time * 2 <= length)
    {
        state = true;
        isMoreThanHalf = false;
    }
    return isMoreThanHalf;
}

int MoreThanHalfNum(int *numbers, int length)
{
    if (CheckInvalidArray(numbers, length))
        return 0;
    int mid = length >> 1;
    int start = 0;
    int end = length - 1;
    int index = Partition(numbers, length, start, end);
    while (index != mid)
    {
        if (index > mid)
        {
            end = index - 1;
            index = Partition(numbers, length, start, end);
        }
        else
        {
            start = index + 1;
            index = Partition(numbers, length, start, end);
        }
    }
    int result = numbers[mid];
    if (!CheckMoreThanHalf(numbers, length, result))
        result = 0;
    return result;
}
*/