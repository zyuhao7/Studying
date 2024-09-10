#include <iostream>
using namespace std;

// 饿汉和懒汉两种模式

// 饿汉模式
// class CSingleton
// {
// public:
//     static CSingleton *getInstance()
//     {
//         return &single;
//     }

// private:
//     static CSingleton single;
//     CSingleton()
//     {
//         cout << "CSingleton()" << endl;
//     }
//     ~CSingleton()
//     {
//         cout << "~CSingleton()" << endl;
//     }
//     CSingleton(const CSingleton &) = delete; // 防止外部拷贝构造.
// };

// CSingleton CSingleton::single;

// 懒汉模式
// class CSingleton
// {
// public:
//     static CSingleton *getInstance()
//     {
//         static CSingleton single;
//         return &single;
//     }

// private:
//     static CSingleton single;
//     CSingleton()
//     {
//         cout << "CSingleton()" << endl;
//     }
//     ~CSingleton()
//     {
//         cout << "~CSingleton()" << endl;
//     }
//     CSingleton(const CSingleton &) = delete; // 防止外部拷贝构造.
// };

// CSingleton CSingleton::single;

// int main()
// {
//     CSingleton::getInstance();

//     return 0;
// }