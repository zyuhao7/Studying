#include <iostream>
using namespace std;
// day-2025-2-23
// class A1
// {
// public:
//     void f1() {}

// private:
//     int _a;
// };
// class A2
// {
// public:
//     void f2() {}
// };

// class A3
// {
// };
// int main()
// {
//     cout << sizeof(A1) << " "; // 4
//     cout << sizeof(A2) << " "; // 1
//     cout << sizeof(A3) << " "; // 1

//     return 0;
// }

// class A

// {
// public:
//     void Print()
//     {
//         cout << "Print()" << endl;
//     }
//     void PrintA()
//     {
//         cout << _a << endl;
//     }

// private:
//     int _a;
// };

// int main()
// {
//     A *p = nullptr;
//     p->Print();  // 正常运行
//     p->PrintA(); //  运行崩溃
//     return 0;
// }

// day-2025-2-24
// class Date
// {
// public:
//     Date()
//     {
//         _year = 1900;
//         _month = 1;
//         _day = 1;
//     }
//     Date(int year = 1900, int month = 1, int day = 1)
//     {
//         _year = year;
//         _month = month;
//         _day = day;
//     }

// private:
//     int _year;
//     int _month;
//     int _day;
// };

// // 以下测试函数能通过编译吗？

// void Test()
// {
//     Date d1;
// }

// int main()
// {
//     Test(); // 编译出错, call of overloaded 'Date()' is ambiguous
//     return 0;
// }

// class Date
// {
// public:
//     Date(int year, int month, int day)
//     {
//         _year = year;
//         _month = month;
//         _day = day;
//     }
//     void Print()
//     {
//         cout << "Print()" << endl;
//         cout << "year:" << _year << endl;
//         cout << "month:" << _month << endl;
//         cout << "day:" << _day << endl
//              << endl;
//     }
//     void Print() const

//     {
//         cout << "Print()const" << endl;
//         cout << "year:" << _year << endl;
//         cout << "month:" << _month << endl;
//         cout << "day:" << _day << endl
//              << endl;
//     }

// private:
//     int _year;  // 年
//     int _month; // 月
//     int _day;   // 日
// };

// void Test()
// {
//     Date d1(2022, 1, 13);
//     d1.Print(1); // 调用Print()
//     const Date d2(2022, 1, 13);
//     d2.Print(); // 调用Print()const
// }

// int main()
// {
//     Test();
//     return 0;
// }

