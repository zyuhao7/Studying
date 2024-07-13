#include <iostream>
#include <memory>
#include <stdlib.h>
#include <cstring>
#include <vector>

using namespace std;

#if 0
class A
{
private:
    int val;

public:
    A(int n) { val = n; }
    A(const A &other) { val = other.val; } // 不加 & 会造成无穷递归.
    void Print() { cout << val << endl; }
};

int main()
{
    A a = 10;
    A b = a;
    b.Print();
    return 0;
}
#endif

#if 0
// 面试题 1: 赋值运算符函数
class CMyString
{
public:
    CMyString(char *pData = NULL)
    {
        if (!pData)
            m_pData = NULL;
        strcpy(m_pData, pData);
    }

    CMyString(const CMyString &str)
    {
    }

    ~CMyString(void)
    {
        m_pData = NULL;
    }

private:
    CMyString operator=(const CMyString &str);
    char *m_pData;
};

CMyString CMyString::operator=(const CMyString &str)
{
    if (this != &str)
    {
        delete[] m_pData; // 先置空啊! 有值怎么赋值. ******
        m_pData = NULL;
        m_pData = new char[strlen(str.m_pData) + 1];
        strcpy(m_pData, str.m_pData);
    }
    return *this;
}

// 上面没考虑出现异常情况处理.
CMyString CMyString::operator=(const CMyString &str)
{
    if (this != &str)
    {
        CMyString tmp(str);
        char *pTmp = tmp.m_pData;
        tmp.m_pData = m_pData;
        m_pData = pTmp;
    }
    return *this;
}

#endif

#if 0
// 面试题 2 实现 Singlton 模式
// 再 github上有总结的设计模式关于单例模式的详细说明.
class Singleton
{
public:
    static Singleton *get_instance()
    {
        static Singleton single;
        return &single;
    }

private:
    Singleton();
    ~Singleton();
    Singleton(const Singleton &);
    static Singleton *m_instance;
};
Singleton *Singleton::m_instance = nullptr;

#endif

#if 0
// 数组
int GetSize(int data[])
{
    return sizeof(data);
}

int main()
{
    int data1[] = {1, 2, 3, 4, 5};
    int size1 = sizeof(data1);

    int *data2 = data1;
    int size2 = sizeof data2;

    int size3 = GetSize(data1);

    cout << size1 << " " << size2 << " " << size3 << endl; // 20 8 8 //64位.

}

#endif

#if 0
// 面试题 3 二维数组中的查找

// 自解
void solve(int a[4][4], int row, int col, int n)
{

    int c, r;
    for (c = col - 1, r = 0; c >= 0 && r < row;)
    {
        if (n == a[r][c])
        {
            cout << "[" << r << "," << c << "]" << endl;
            break;
        }
        else if (n > a[r][c])
        {
            r++;
        }
        else
            --c;
    }

    if (c < 0 || r >= row)
        cout << "[" << -1 << "," << -1 << "]" << endl;
}

// 书解
bool Find(int *matrix, int rows, int columns, int number)
{
    bool found = false;
    if (matrix != NULL && rows > 0 && columns > 0)
    {
        int row = 0;
        int column = columns - 1;
        while (row < rows && columns >= 0)
        {
            if (matrix[row * columns + column] == number)
            {
                found = true;
                break;
            }
            else if (matrix[row * columns + column] > number)
            {
                --column;
            }
            else
                ++row;
        }
    }
    return found;
}
int main()
{
    int a[4][4] = {
        1, 2, 8, 9,
        2, 4, 9, 12,
        4, 7, 10, 13,
        6, 8, 11, 15};
    // solve(a, 4, 4, 5);
    cout << Find(*a, 4, 4, 5) << endl;
    return 0;
}

#endif

#if 1
// 字符串


int main()
{

    return 0;
}
#endif