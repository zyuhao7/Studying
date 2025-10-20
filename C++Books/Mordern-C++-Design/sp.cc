#include <iostream>
using namespace std;

// day-2025-10-19
// 第七章 智能指针 smart pointer


template <class T>
class SmartPtr
{
public:
    explicit SmartPtr(T *pointee)
        : pointee_(pointee)
    {
    }
    SmartPtr &operator=(const SmartPtr &other);
    ~SmartPtr();
    T &operator*() const { return *pointee_; }
    T *operator->() const { return pointee_; }

private:
    T *pointee_;
};

class Widget
{
public:
    void Fun();
};

// class Concrete;
// class Base
// {
//     Base(Concrete c)
//         : con(c)
//     {
//         std::cout << "Baes() be called" << endl;
//     }
//     Concrete con;
// };

// class AbstractBase
// {
// public:
//     virtual Base *Clone();
// };

// class Concrete : public AbstractBase
// {
//     virtual Base *Clone()
//     {
//         return new Concrete(*this); // 这里需要拷贝构造函数
//     }
// };

int main()
{
    // SmartPtr<Widget> sp(new Widget);
    // sp->Fun();

    return 0;
}