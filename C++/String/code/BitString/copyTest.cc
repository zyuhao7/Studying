#include <iostream>

#if 0
class ShallowCopy
{
public:
    int *data;

    ShallowCopy(int value)
    {
        data = new int(value);
    }

    // 默认的拷贝构造函数实现浅拷贝
    ShallowCopy(const ShallowCopy &other)
        : data(other.data) {}

    ~ShallowCopy()
    {
        delete data;
    }
};

int main()
{
    ShallowCopy obj1(1);
    ShallowCopy obj2 = obj1; // 浅拷贝

    std::cout << "obj1 data: " << *obj1.data << std::endl;
    std::cout << "obj2 data: " << *obj2.data << std::endl;

    *obj1.data = 100; // 修改obj1的数据

    std::cout << "After modification:" << std::endl;
    std::cout << "obj1 data: " << *obj1.data << std::endl;
    std::cout << "obj2 data: " << *obj2.data << std::endl;

    return 0;
}
#endif

#if 0
class DeepCopy
{
public:
    int *data;

    DeepCopy(int value)
    {
        data = new int(value);
    }

    // 自定义的拷贝构造函数实现深拷贝
    DeepCopy(const DeepCopy &other)
    {
        data = new int(*other.data);
    }

    ~DeepCopy()
    {
        delete data;
    }
};

int main()
{
    DeepCopy obj1(1);
    DeepCopy obj2 = obj1; // 深拷贝

    std::cout << "obj1 data: " << *obj1.data << std::endl;
    std::cout << "obj2 data: " << *obj2.data << std::endl;

    *obj1.data = 100; // 修改obj1的数据

    std::cout << "After modification:" << std::endl;
    std::cout << "obj1 data: " << *obj1.data << std::endl;
    std::cout << "obj2 data: " << *obj2.data << std::endl;

    return 0;
}
#endif

#if 0
#include <utility>

class MoveExample
{
public:
    int *data;

    // 构造函数
    MoveExample(int value)
    {
        data = new int(value);
        std::cout << "Constructor: allocated memory at " << data << std::endl;
    }

    // 移动构造函数
    MoveExample(MoveExample &&other) noexcept
        : data(other.data)
    {
        other.data = nullptr; // 防止被释放
        std::cout << "Move Constructor: moved memory at " << data << std::endl;
    }

    // 移动赋值运算符
    MoveExample &operator=(MoveExample &&other) noexcept
    {
        if (this == &other)
        {
            return *this; // 防止自赋值
        }

        delete data; // 释放旧的内存

        data = other.data;
        other.data = nullptr; // 防止被释放

        std::cout << "Move Assignment: moved memory at " << data << std::endl;

        return *this;
    }

    // 析构函数
    ~MoveExample()
    {
        if (data)
        {
            std::cout << "Destructor: deallocated memory at " << data << std::endl;
            delete data;
        }
    }
};

int main()
{
    MoveExample obj1(2);
    MoveExample obj2 = std::move(obj1); // 调用移动构造函数

    MoveExample obj3(0);
    obj3 = std::move(obj2); // 调用移动赋值运算符

    return 0;
}
#endif