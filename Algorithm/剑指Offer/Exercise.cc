#include <iostream>
#include <memory>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

// class A
// {
// private:
//     int val;

// public:
//     A(int n) { val = n; }
//     A(const A &other) { val = other.val; } // 不加 & 会造成无穷递归.
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
// class CMyString
// {
// public:
//     CMyString(char *pData = NULL)
//     {
//         if (!pData)
//             m_pData = NULL;
//         strcpy(m_pData, pData);
//     }

//     CMyString(const CMyString &str)
//     {
//     }

//     ~CMyString(void)
//     {
//         m_pData = NULL;
//     }

// private:
//     CMyString operator=(const CMyString &str);
//     char *m_pData;
// };

// CMyString CMyString::operator=(const CMyString &str)
// {
//     if (this != &str)
//     {
//         delete[] m_pData; // 先置空啊! 有值怎么赋值. ******
//         m_pData = NULL;
//         m_pData = new char[strlen(str.m_pData) + 1];
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

// 面试题 2 实现 Singlton 模式
// 再 github上有总结的设计模式关于单例模式的详细说明.
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
// int GetSize(int data[])
// {
//     return sizeof(data);
// }

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
//     for (c = col - 1, r = 0; c >= 0 && r < row;)
//     {
//         if (n == a[r][c])
//         {
//             cout << "[" << r << "," << c << "]" << endl;
//             break;
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
//                 break;
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
// 尾插.
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
//         while (*pHead != nullptr)
//         {
//             pNode = pNode->next;
//         }
//         pNode->next = pNew;
//     }
// }

// 面试题 5 从尾到头打印链表
// 节点定义如下:
// struct ListNode
// {
//     int m_nKey;
//     ListNode *m_pNext;
// };

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
//         cout << pNode->m_nKey << " ";
//         nodes.pop();
//     }
// }

// 既然栈可以实现, 那么本质来说递归就是栈结构, 我们可以访问节点的时候, 递归的输出它后面的节点, 在输出节点本身.

// void PrintListFromTailToHead(ListNode *pHead)
// {
//     if (pHead != nullptr)
//     {
//         if (pHead->m_pNext != nullptr)
//         {
//             PrintListFromTailToHead(pHead->next);
//         }
//     }
//     cout << pHead->m_nKey << " ";
// }

int main()
{

    return 0;
}