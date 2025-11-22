#include <bit>
#include <functional>
#include <map>
#include <iostream>
#include <memory>
#include <typeinfo>
// day-2025-11-18
/*
    static_cast<T>(x)：编译时转换，用于：相关类型间、上/下转、算术类型转换、隐式构造/转换函数的显式调用。无运行时类型检查。
    dynamic_cast<T>(x)：运行时受检的转换，主要用于 多态类 的指针/引用上下转换，依赖 RTTI；失败时返回 nullptr或抛 std::bad_cast。
    const_cast<T>(x)：移除或添加 const/volatile 限定。不改变对象本身的存储；若原对象实为 const，修改后写入会导致未定义行为.
    reinterpret_cast<T>(x)：按位重新解释，几乎把类型当作 "位模式" 搬来搬去。非常低级、易错、实现定义/未定义行为多。
    C 风格 cast (T)x 或 T(x)：尝试一系列 cast（const_cast→static_cast→reinterpret_cast 等组合），危险且可读性差。优先使用四种显式 cast.
*/

// static_cast
// struct Base
// {
//     virtual ~Base() = default;
// };

// struct Derived : Base
// {
//     int j;
//     Derived(int x) : j(x)
//     {
//     }
//     void foo()
//     {
//         std::cout << "Derived::foo\n";
//     }
// };

// struct Derived2 : Base
// {

//     void foo()
//     {
//         std::cout << "Derived2::foo\n";
//     }
// };
/*
    static_cast 在编译期根据类型信息决定如何转换（可能生成指针算术来做基类/派生类指针偏移调整），没有运行时类型检查。
    如果把指向 Base 的指针静态转换为 Derived*，而实际对象是另一个派生（或不是 Derived），则行为未定义。
    对多个继承、虚继承，编译器会在生成代码里插入指针偏移调整（pointer adjustment），但仍不做类型安全检查。
*/
// int main()
// {
//     Derived d(5);
//     // Base *b = static_cast<Base *>(&d); // upcast 安全
//     Base *b = new Derived2;

//     // 下转, 不检查
//     Derived *pd = static_cast<Derived *>(b);
//     pd->foo(); // OK, 因为这个 b 实际指向 Derived
//     std::cout << pd->j << std::endl;

//     double x = 3.14;
//     int n = static_cast<int>(x); // 显式截断
//     std::cout << n << std::endl;
//     delete b;
//     delete pd;
// }

// dynamic_cast
// struct Base
// {
//     virtual ~Base() {}
// };
// struct Derived : Base
// {
//     void f() { std::cout << "Derived\n"; }
// };
// struct Other : Base
// {
// };

/*
    dynamic_cast 以来 RTTI, 编译器在类对象中通过 vptr 和 vtable 保存动态类型信息, dynamic_cast 在运行时检查类型是否兼容,
    并在多继承/虚继承场景下做复杂的指针调整.
    基类必须要是多态的, 否则对指针/引用做 dynamic_cast 是编译错误.
    运行时开销(查表、比较、指针调整), 但是在需要类型安全的场景(例如插件、序列化、访问可变子类行为)十分重要
    如果启用了 RTTI, typeid 和 dynamic_cast 可用.
*/

// int main()
// {
//     Base *b1 = new Derived;
//     Derived *d1 = dynamic_cast<Derived *>(b1); // 成功 -> 非空
//     if (d1)
//         d1->f();

//     Base *b2 = new Other;
//     Derived *d2 = dynamic_cast<Derived *>(b2); // 失败 -> 返回 nullptr
//     if (!d2)
//         std::cout << "cast failed\n";

//     try
//     {
//         Base &br = *b2;
//         Derived &dr = dynamic_cast<Derived &>(br); // 失败 -> 抛 std::bad_cast
//     }
//     catch (const std::bad_cast &e)
//     {
//         std::cout << "bad_cast: " << e.what() << "\n";
//     }
//     delete b1;
//     delete b2;
// }

// const_cast
// 去除 const 或 volatile 以调用旧的 C 风格 API, 或添加 const

// void legacy_api(char *s) { s[0] = 'X'; }

/*
    const_cast 并不改变对象的存储或内存布局，仅改变编译器如何看待类型限定。
    若原对象实际上是 const（例如字符串字面量或 const 定义），修改后写入就是未定义行为。
    用途应尽量受限：最好仅用于调用确实不会修改对象的 legacy API（但 API 签名错误），或从 void* 恢复到 const T* 等场景。
*/
// int main()
// {
//     const char *msg = "hello"; // 字面量通常在只读区
//     // const_cast 去掉 const, 但是如果修改字面量会造成未定义行为

//     // legacy_api(const_cast<char *>(msg)); // 未定义行为 段错误

//     char buf[] = "hello";
//     const char *p = buf;
//     legacy_api(const_cast<char *>(p)); // 合法,原对象是 非 const
//     std::cout << buf << std::endl;     // Xello
// }

// reinterpret_cast
#include <cstdint>

/*
    reinterpret_cast 通常不改变位模式，只改变编译器如何解释这些位；
    许多转换结果是实现定义或未定义的（例如把指针转换为整数然后再转换回去不一定能保证原样恢复，除非使用 uintptr_t/intptr_t 并满足平台保证）。
    在多平台代码中，避免用 reinterpret_cast 做跨类型指针转换。
    若需要读取对象的字节，优先使用 std::memcpy（严格别名规则 safety）或 std::byte/unsigned char 视图。
*/

// int main()
// {
//     uintptr_t v = 0x12345678;
//     void *p = reinterpret_cast<void *>(v); // 把整数看成指针
//     std::cout << "pointer val: " << p << std::endl;

//     int x = 0x01020304;
//     unsigned char *bytes = reinterpret_cast<unsigned char *>(&x);
//     std::cout << "first byte: " << +bytes[0] << std::endl;
// }

#include <iostream>
#include <string>

struct TypeTag
{
    virtual const char *tag() const = 0;
};

struct Base : TypeTag
{
    virtual ~Base() = default;
    const char *tag() const override { return "Base"; }
};

struct Derived : Base
{
    const char *tag() const override { return "Derived"; }
};

Base *safe_downcast(Base *b)
{
    if (!b)
        return nullptr;
    if (std::string(b->tag()) == "Derived")
    {
        return b; // caller 再 static_cast<Derived*>(b)
    }
    return nullptr;
}

int main()
{
    Base *b = new Derived;
    if (safe_downcast(b))
    {
        Derived *d = static_cast<Derived *>(b);
        std::cout << "It's Derived\n";
    }
    delete b;
}
