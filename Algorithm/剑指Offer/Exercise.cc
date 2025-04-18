#include <iostream>
#include <memory>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>
#include <string>
#include <unordered_map>
#include <time.h>
using namespace std;

// class A
// {
// private:
//     int val;

// public:
//     A(int n) { val = n; }
//     A(const A &other) { val = other.val; } // 不加 & 会造成无穷递归.  invalid constructor; you probably meant 'A (const A&)'
//     void Print() { cout << val << endl; }
// };

// int main()
// {
//     A a = 10;
//     A b = a;
//     b.Print();
//     return 0;
// }

// 面试题 1: 赋值运算符函数
class CMyString
{
public:
    CMyString(const char *str)
    {
        if (str)
        {
            _data = new char[strlen(str) + 1];
            strcpy(_data, str);
        }
        else
        {
            _data = new char[1];
            _data[0] = '\0';
        }
    }

    CMyString(const CMyString &other)
    {
        _data = new char[strlen(other._data) + 1];
        strcpy(_data, other._data);
    }

    ~CMyString()
    {
        delete[] _data;
    }

private:
    CMyString operator=(const CMyString &str);
    char *_data;
};

// CMyString CMyString::operator=(const CMyString &str)
// {
//     if (this != &str)
//     {
//         delete[] m_pData; // 先置空啊! 有值怎么赋值. ******
//         m_pData = NULL;
//         m_pData = new char[strlen(str._data) + 1];
//         strcpy(m_pData, str.m_pData);
//     }
//     return *this;
// }

// // 上面没考虑出现异常情况处理.
// CMyString CMyString::operator=(const CMyString &str)
// {
//     if (this != &str)
//     {
//         CMyString tmp(str);
//         char *pTmp = tmp.m_pData;
//         tmp.m_pData = m_pData;
//         m_pData = pTmp;
//     }
//     return *this;
// }

// 面试题 2 实现 Singleton 模式
// 再 github 上有总结的设计模式关于单例模式的详细说明.
// class Singleton
// {
// public:
//     static Singleton *get_instance()
//     {
//         static Singleton single;
//         return &single;
//     }

// private:
//     Singleton();
//     ~Singleton();
//     Singleton(const Singleton &);
//     static Singleton *m_instance;
// };
// Singleton *Singleton::m_instance = nullptr;

// 数组
int GetSize(int data[])
{
    return sizeof(data);
}

// int main()
// {
//     int data1[] = {1, 2, 3, 4, 5};
//     int size1 = sizeof(data1);

//     int *data2 = data1;
//     int size2 = sizeof data2;

//     int size3 = GetSize(data1);

//     cout << size1 << " " << size2 << " " << size3 << endl; // 20 8 8 //64位.
// }

// 面试题 3 二维数组中的查找

// 自解
// void solve(int a[4][4], int row, int col, int n)
// {

//     int c, r;
//     for (c = col - 1, r = 0; c >= 0 && r < row)
//     {
//         if (n == a[r][c])
//         {
//             cout << "[" << r << "," << c << "]" << endl;
//             bream;
//         }
//         else if (n > a[r][c])
//         {
//             r++;
//         }
//         else
//             --c;
//     }

//     if (c < 0 || r >= row)
//         cout << "[" << -1 << "," << -1 << "]" << endl;
// }

// // 书解
// bool Find(int *matrix, int rows, int columns, int number)
// {
//     bool found = false;
//     if (matrix != NULL && rows > 0 && columns > 0)
//     {
//         int row = 0;
//         int column = columns - 1;
//         while (row < rows && columns >= 0)
//         {
//             if (matrix[row * columns + column] == number)
//             {
//                 found = true;
//                 bream;
//             }
//             else if (matrix[row * columns + column] > number)
//             {
//                 --column;
//             }
//             else
//                 ++row;
//         }
//     }
//     return found;
// }
// int main()
// {
//     int a[4][4] = {
//         1, 2, 8, 9,
//         2, 4, 9, 12,
//         4, 7, 10, 13,
//         6, 8, 11, 15};
//     // solve(a, 4, 4, 5);
//     cout << Find(*a, 4, 4, 5) << endl;
//     return 0;
// }

// 字符串

// int main()
// {
//     char str1[] = "hello world";
//     char str2[] = "hello world";

//     char *str3 = "hello world";
//     char *str4 = "hello world";

//     if (str1 == str2)
//     {
//         cout << "str1 == str2" << endl;
//     }
//     else
//         cout << "str1 != str2" << endl; // √ str1 和 str2是数组地址

//     if (str3 == str4)
//     {
//         cout << "str3 == str4" << endl; // √ 同一 常量字符串  指向同一内存地址
//     }
//     else
//     {
//         cout << "str3 != str4" << endl;
//     }
//     return 0;
// }

// 面试题 4 替换空格
// 实现一个函数, 把字符串中的每个空格替换成 "%20".
// 自解
// void solve(string s)
// {
//     string res = "";
//     for (int i = 0; i < s.size(); ++i)
//     {
//         if (s[i] != ' ')
//         {
//             res += s[i];
//         }
//         else
//             res += "%20";
//     }
//     cout << res << endl;
// }

// 书解
// string replaceSpace(string s)
// {
//     int cnt = 0;
//     for (int i = 0; i < s.size(); ++i)
//     {
//         if (s[i] == ' ')
//             cnt++;
//     }

//     s.resize(s.size() + 2 * cnt, 0);
//     for (int i = s.size() - 1; i >= 0; --i)
//     {
//         if (s[i] != ' ')
//         {
//             s[i + 2 * cnt] = s[i];
//         }
//         else
//         {
//             cnt--;
//             s[i + 2 * cnt] = '%';
//             s[i + 2 * cnt + 1] = '2';
//             s[i + 2 * cnt + 2] = '0';
//         }
//     }
//     return s;
// }

// int main()
// {
//     string s = "we are happy";
//     cout << s << endl;
//     solve(s);
//     string r = replaceSpace(s);
//     cout << r << endl;
// }

// 链表
// 单向链表的节点定义为:

// struct Listnode
// {
//     int val;
//     Listnode *next;
// };
// // 尾插.
// void AddToTail(Listnode **pHead, int v)
// {
//     Listnode *pNew = new Listnode();
//     pNew->val = v;
//     pNew->next = nullptr;
//     if (*pHead == nullptr)
//     {
//         *pHead = pNew;
//     }
//     else
//     {
//         Listnode *pNode = *pHead;
//         while (pNode->next != nullptr)
//         {
//             pNode = pNode->next;
//         }
//         pNode->next = pNew;
//     }
// }

//////////////////////////////
// 面试题 5 从尾到头打印链表
// 节点定义如下:
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// 书解
// 思路:  从头到尾遍历一遍节点, 将值存到栈中, 然后在从栈取出来即可.
// void PrintListFromTailToHead(ListNode *pHead)
// {
//     std::stack<ListNode *> nodes;
//     ListNode *pNode = pHead;
//     while (pNode != nullptr)
//     {
//         nodes.push(pNode);
//         pNode = pNode->m_pNext;
//     }
//     while (!nodes.empty())
//     {
//         pNode = nodes.top();
//         cout << pNode->m_nmey << " ";
//         nodes.pop();
//     }
// }

// 既然栈可以实现, 那么本质来说递归就是栈结构, 我们可以访问节点的时候, 递归的输出它后面的节点, 在输出节点本身.

// 创建链表的函数
ListNode *createLinkedList(int arr[], int n)
{
    if (n == 0)
        return nullptr;

    ListNode *head = new ListNode(arr[0]);
    ListNode *current = head;

    for (int i = 1; i < n; i++)
    {
        current->next = new ListNode(arr[i]);
        current = current->next;
    }

    return head;
}

void PrintListFromTailToHead(ListNode *root)
{
    if (root == nullptr)
        return;
    PrintListFromTailToHead(root->next);
    cout << root->val << " ";
}

// int main()
// {
//     int arr[] = {1, 2, 3, 4, 5};
//     int n = sizeof(arr) / sizeof(arr[0]);

//     ListNode *head = createLinkedList(arr, n);
//     PrintListFromTailToHead(head);
//     return 0;
// }

// 树
// 面试题 6 重建二叉树
// 输入前序遍历 {1,2,4,7,3,5,6,8} 和中序遍历 {4,7,2,1,5,3,8,6}, 重建出二叉树并输出头结点.

// struct BinaryTreeNode
// {
//     int value_;
//     BinaryTreeNode *Left_;
//     BinaryTreeNode *Right_;
// };

/*
                   1
               2       3
            4       5     6
               7        8
*/
// string Prev, Inorder;
// 首先在中序中找到根节点, 然后在前序中找到根节点, 左边是左子树, 右边是右子树.
// 递归的构建左子树.
// 递归的构建右子树.

// void build(int l1, int r1, int l2, int r2)
// {
//     int m = Inorder.find(Prev[l1]); // 找到中序的根在哪?
//     if (m > l2)
//         build(l1 + 1, l1 + m - l2, l2, m - 1); // 左孩子.
//     if (m < r2)
//         build(l1 + m - l2 + 1, r1, m + 1, r2); // 右孩子.
//     cout << Prev[l1];
// }

// int main()
// {
//     while (cin >> Prev >> Inorder)
//     {
//         build(0, Prev.size() - 1, 0, Inorder.size() - 1);
//         cout << endl;
//     }
// }

// 二叉树节点定义
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 重建二叉树的递归函数
TreeNode *buildTreeHelper(const vector<int> &preorder, int preStart, int preEnd,
                          const vector<int> &inorder, int inStart, int inEnd,
                          unordered_map<int, int> &inorderMap)
{
    if (preStart > preEnd || inStart > inEnd)
    {
        return nullptr;
    }

    // 前序遍历的第一个节点是根节点
    int rootVal = preorder[preStart];
    TreeNode *root = new TreeNode(rootVal);

    // 找到根节点在中序遍历中的位置
    int inRootIndex = inorderMap[rootVal];
    int leftSubtreeSize = inRootIndex - inStart;

    // 递归构建左子树
    root->left = buildTreeHelper(preorder, preStart + 1, preStart + leftSubtreeSize,
                                 inorder, inStart, inRootIndex - 1, inorderMap);

    // 递归构建右子树
    root->right = buildTreeHelper(preorder, preStart + leftSubtreeSize + 1, preEnd,
                                  inorder, inRootIndex + 1, inEnd, inorderMap);

    return root;
}

// 重建二叉树的主函数
TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
{
    // 构建中序遍历的值到索引的映射，方便快速查找
    unordered_map<int, int> inorderMap;
    for (int i = 0; i < inorder.size(); i++)
    {
        inorderMap[inorder[i]] = i;
    }

    return buildTreeHelper(preorder, 0, preorder.size() - 1,
                           inorder, 0, inorder.size() - 1, inorderMap);
}

// 打印二叉树的前序遍历（验证结果）
void printPreOrder(TreeNode *root)
{
    if (root == nullptr)
    {
        return;
    }
    cout << root->val << " ";
    printPreOrder(root->left);
    printPreOrder(root->right);
}

// int main()
// {
//     vector<int> preorder = {1, 2, 4, 7, 3, 5, 6, 8};
//     vector<int> inorder = {4, 7, 2, 1, 5, 3, 8, 6};

//     TreeNode *root = buildTree(preorder, inorder);

//     // 打印前序遍历结果，验证重建是否正确
//     cout << "Result PreOrder: ";
//     printPreOrder(root);
//     cout << endl;

//     return 0;
// }

// 栈与队列
// 用两个栈实现队列.
class MyQueue
{
public:
    stack<int> st1;
    stack<int> st2;
    MyQueue() {}

    void push(int x)
    {
        st1.push(x);
    }

    int pop()
    {
        // st2 是出栈的栈, 如果为空, 那么将 st1 的元素全部压入 st2.
        if (st2.empty())
        {
            while (!st1.empty())
            {
                int top = st1.top();
                st1.pop();
                st2.push(top);
            }
        }
        int t = st2.top();
        st2.pop();
        return t;
    }

    int peek()
    {
        if (st2.empty())
        {
            while (!st1.empty())
            {
                st2.push(st1.top());
                st1.pop();
            }
        }
        return st2.top();
    }

    bool empty()
    {
        return st1.empty() && st2.empty();
    }
};

// int main()
// {
//     MyQueue q;

//     // 测试 1: 入队操作
//     q.push(1);
//     q.push(2);
//     q.push(3);

//     // 测试 2: 查看队首元素
//     cout << "que front: " << q.peek() << endl; // 应输出 1

//     // 测试 3: 出队操作
//     cout << "pop element: " << q.pop() << endl; // 应输出 1

//     // 测试 4: 再次查看队首元素
//     cout << "que front: " << q.peek() << endl; // 应输出 2

//     // 测试 5: 再次出队
//     cout << "pop element: " << q.pop() << endl; // 应输出 2

//     // 测试 6: 检查队列是否为空
//     cout << "isEmpty ? : " << (q.empty() ? "yes" : "no") << endl; // 应输出 no

//     // 测试 7: 继续出队
//     cout << "pop element: " << q.pop() << endl; // 应输出 3

//     // 测试 8: 检查队列是否为空
//     cout << "isEmpty ? : " << (q.empty() ? "yes" : "no") << endl; // 应输出  yes
// }
