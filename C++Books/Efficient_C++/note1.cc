#include <iostream>
#include <string>
#include <mutex>
#include <cstring>
#include <chrono>
#include <algorithm>
#include <memory>
using namespace std;

// day-2024-10-15
// 第八章 内联基础

// 内联类似于宏,在调用方法内部展开被调用方法, 以此来代替方法的调用.

// class GateInt
// {
//     int x;

// public:
//     // 类内成员函数默认 内联. 或者类外定义加 inline.
//     int get()
//     {
//         return x;
//     }
//     void set(int arg)
//     {
//         x = arg;
//     }
// };

// int calc(int num1, int num2)
// {
//     return num1 + num2;
// }
// int main()
// {
//     int x[2000];
//     int y[2000];
//     int z[2000];
//     auto start = chrono::high_resolution_clock::now();
//     for (int i = 0; i < 2000; ++i)
//     {
//         for (int j = 0; j < 2000; ++j)
//         {
//             for (int k = 0; k < 2000; ++k)
//             {
//                 z[i] = calc(y[j], x[k]);
//             }
//         }
//     }
//     auto end = chrono::high_resolution_clock::now();
//     auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
//     std::cout << "spends: " << duration.count() << " seconds" << std::endl;
//     // 没内联 :  14 s
// 内联 : 14 s 估计优化了.

// GateInt gi;
// gi.set(12);
// cout << gi.get() << endl;
//     return 0;
// }

// 内联就是用方法的代码来替换对方法的调用.
// 内联通过消除调用开销来提升性能, 并且允许进行调用间优化.
// 内联的主要作用是对运行时间进行优化, 荡然它也可以使可执行映像变得更小.

// day-2024-10-17
//  第九章 内联

// inline bool is_hex(char c, int &val)
// {
//     switch (c)
//     {
//     case '0':
//         val = 0;
//         break;
//     case '1':
//         val = 1;
//         break;
//     case '2':
//         val = 2;
//         break;
//     case '3':
//         val = 3;
//         break;
//     case '4':
//         val = 4;
//         break;
//     case '5':
//         val = 5;
//         break;
//     case '6':
//         val = 6;
//         break;
//     case '7':
//         val = 7;
//         break;
//     case '8':
//         val = 8;
//         break;
//     case '9':
//         val = 9;
//         break;
//     case 'a':
//         val = 10;
//         break;
//     case 'A':
//         val = 10;
//         break;
//     case 'b':
//         val = 11;
//         break;
//     case 'B':
//         val = 11;
//         break;
//     case 'c':
//         val = 12;
//         break;
//     case 'C':
//         val = 12;
//         break;
//     case 'd':
//         val = 13;
//         break;
//     case 'D':
//         val = 13;
//         break;
//     case 'e':
//         val = 14;
//         break;
//     case 'E':
//         val = 14;
//         break;
//     case 'f':
//         val = 15;
//         break;
//     case 'F':
//         val = 15;
//         break;
//     default:
//         return false;
//     }
//     return true;
// }

// inline int parse_hex(char *cp)
// {
//     int ret = 0;
//     int tmp;
//     while (is_hex(*cp, tmp))
//     {
//         ret = (ret << 4) + tmp;
//         ++cp;
//     }
//     for (int i = 31; i >= 0; --i)
//     {
//         if ((ret >> i) & 1)
//             cout << 1;
//         else
//             cout << 0;
//     }
//     return ret;
// }

// int main()
// {
//     char *alpha_number = "78";
//     int bin_number = parse_hex(alpha_number);
//     cout << endl;
//     cout << bin_number << endl; // 十进制 305419896
// }

// 要点:
// 1. 直接量参数与内联结合使用, 为编译器性能的大幅提升开辟了更为广阔的空间.
// 2. 使用内联有时会适得其反, 尤其是滥用的情况下. 内联可能使得代码量变大, 而代码量增多后会较原先出现更多的缓存失败
// 和 换页问题.
// 3. 非精简方法的内联决策应根据样本执行的配置文件来制定, 不能主观臆断.
// 4. 对于那些调用频率高的方法, 如果其静态尺寸较大, 而动态尺寸较小, 可以考虑将其重写, 从而抽取其核心的动态特性,
// 并将动态组件内联.
// 5. 精简化与唯一化总是可以被内联.

// day-2024-10-18

// 第十章 内联技巧
// 1. 内联可以改善性能, 目标是找到程序的快速路径, 然后内联它, 尽管内联这个路径可能费点功夫.
// 2. 条件内联可以阻止内联的发生, 这样就减少了编译时间, 同时也简化了开发前期的调试工作.
// 3. 选择性内联是一种只在某些地方内联方法的技术. 在对方法进行内联时, 为了抵消可能的代码尺寸膨胀的影响, 选择性内联
// 只在对性能有重大影响的路径上对方法调用进行内联.
// 4. 递归内联是一种让人感觉别扭, 但对于改善递归方法性能却有效的技术.
// 5. 需要关注局部静态变量.
// 6. 内联的目标是消除调用开销. 在使用内联之前请弄清楚系统中真正的调用代价.

// day-2024-10-24

// 第十一章 标准模板库
// 要点: 1、 STL是抽象, 灵活性和效率的一种罕见的结合.
// 2、 对于特定的应用模式, 一些容器比其他的更加高效, 这都要随着实际应用而定.
// 3、除非了解一些相关领域内 STL 所忽略的问题, 否则您是不可能超过 STL 实现的.
// 4、不过, 在一些特定的情况下, 还是有可能超过 STL 实现的性能的.

// day-2024-10-31
//  第十一章 引用计数

class Widget
{
public:
    Widget(int size);
    Widget(const Widget &rhs);
    ~Widget();

    Widget &operator=(const Widget &rhs);

    void doThis();
    int showThat() const;

private:
    char *somePtr;
    int refCount;
};

class RCWidget
{
public:
    RCWidget(int size)
        : value(new Widget(size))
    {
    }

    // RCWidget(const RCWidget &rhs);
    // ~RCWidget();

    // RCWidget &operator=(const RCWidget &rhs);

    void doThis()
    {
        value->doThis();
    }

    int showThat() const
    {
        return value->showThat();
    }

private:
    Widget *value;
};

#include <iostream>
#include <cstring>
#include <algorithm>
#include <memory> // 仅用于 std::shared_ptr 的使用示例

// RCObject类
class RCObject
{
public:
    void addReference() { ++refCount; }
    void removeReference()
    {
        if (--refCount == 0)
            delete this;
    }

    void markUnshareable() { shareable = false; }
    bool isShareable() const { return shareable; }

protected:
    RCObject() : refCount(0), shareable(true) {}
    RCObject(const RCObject &rhs) : refCount(0), shareable(true) {}
    RCObject &operator=(const RCObject &rhs) { return *this; }
    virtual ~RCObject() {}

private:
    int refCount;
    bool shareable;
};

// BigInt类
class BigInt : public RCObject
{
    friend BigInt operator+(const BigInt &, const BigInt &);

public:
    BigInt(const char *);
    BigInt(unsigned = 0);
    BigInt(const BigInt &);
    BigInt &operator=(const BigInt &);
    BigInt &operator+=(const BigInt &);
    ~BigInt();

    void print() const;
    char *getDigits() const { return digits; }
    unsigned getNdigits() const { return ndigits; }

private:
    char *digits;
    unsigned ndigits;
    char fetch(unsigned i) const;
};

BigInt::BigInt(const char *str)
{
    ndigits = strlen(str);
    digits = new char[ndigits + 1];
    for (unsigned i = 0; i < ndigits; ++i)
        digits[ndigits - i - 1] = str[i] - '0'; // 倒序存储
}

BigInt::BigInt(unsigned num)
{
    ndigits = 0;
    unsigned temp = num;
    while (temp > 0)
    {
        temp /= 10;
        ++ndigits;
    }
    if (ndigits == 0)
        ndigits = 1;

    digits = new char[ndigits];
    for (unsigned i = 0; i < ndigits; ++i)
    {
        digits[i] = num % 10;
        num /= 10;
    }
}

BigInt::BigInt(const BigInt &other)
{
    ndigits = other.ndigits;
    digits = new char[ndigits];
    std::memcpy(digits, other.digits, ndigits);
}

BigInt &BigInt::operator=(const BigInt &other)
{
    if (this == &other)
        return *this;

    delete[] digits;

    ndigits = other.ndigits;
    digits = new char[ndigits];
    std::memcpy(digits, other.digits, ndigits);

    return *this;
}

BigInt::~BigInt()
{
    delete[] digits;
}

BigInt operator+(const BigInt &a, const BigInt &b)
{
    unsigned maxDigits = std::max(a.ndigits, b.ndigits);
    char *sumDigits = new char[maxDigits + 1];
    unsigned carry = 0;

    for (unsigned i = 0; i < maxDigits; ++i)
    {
        unsigned digitA = (i < a.ndigits) ? a.fetch(i) : 0;
        unsigned digitB = (i < b.ndigits) ? b.fetch(i) : 0;
        unsigned sum = digitA + digitB + carry;
        sumDigits[i] = sum % 10;
        carry = sum / 10;
    }

    if (carry > 0)
    {
        sumDigits[maxDigits] = carry;
        ++maxDigits;
    }

    BigInt result;
    delete[] result.digits;
    result.ndigits = maxDigits;
    result.digits = new char[maxDigits];
    std::memcpy(result.digits, sumDigits, maxDigits);

    delete[] sumDigits;
    return result;
}

BigInt &BigInt::operator+=(const BigInt &other)
{
    *this = *this + other;
    return *this;
}

char BigInt::fetch(unsigned i) const
{
    return (i < ndigits) ? digits[i] : 0;
}

void BigInt::print() const
{
    for (int i = ndigits - 1; i >= 0; --i)
        std::cout << static_cast<char>(digits[i] + '0');
    std::cout << std::endl;
}

// RCPtr类
template <class T>
class RCPtr
{
public:
    RCPtr(T *realPtr = nullptr) : pointee(realPtr)
    {
        init();
    }

    RCPtr(const RCPtr &rhs) : pointee(rhs.pointee)
    {
        init();
    }

    ~RCPtr()
    {
        if (pointee)
            pointee->removeReference();
    }

    RCPtr &operator=(const RCPtr &rhs)
    {
        if (pointee != rhs.pointee)
        {
            if (pointee)
                pointee->removeReference();
            pointee = rhs.pointee;
            init();
        }
        return *this;
    }

    T *operator->() const { return pointee; }
    T &operator*() const { return *pointee; }

private:
    T *pointee;

    void init()
    {
        if (!pointee)
            return;
        if (!pointee->isShareable())
            pointee = new T(*pointee);
        pointee->addReference();
    }
};

// RCBigInt类
class RCBigInt
{
    friend RCBigInt operator+(const RCBigInt &, const RCBigInt &);

public:
    RCBigInt(const char *p) : value(new BigInt(p)) {}
    RCBigInt(unsigned u = 0) : value(new BigInt(u)) {}
    RCBigInt(const BigInt &bi) : value(new BigInt(bi)) {}

    void print() const
    {
        value->print();
    }

private:
    RCPtr<BigInt> value;
};

inline RCBigInt operator+(const RCBigInt &left, const RCBigInt &right)
{
    return RCBigInt(*(left.value) + *(right.value));
}

void performanceComparison()
{
    const int iterations = 10000000; // 设置测试次数
    BigInt a("123456789012345678901234567890");
    BigInt b("987654321098765432109876543210");
    a.print();
    // --------------------
    // 加法性能比较
    // --------------------
    clock_t start = clock();
    for (int i = 0; i < iterations; ++i)
    {
        BigInt c = a + b;
    }
    clock_t end = clock();
    double bigIntAddTime = double(end - start) / CLOCKS_PER_SEC;

    RCBigInt ra("123456789012345678901234567890");
    RCBigInt rb("987654321098765432109876543210");

    start = clock();
    for (int i = 0; i < iterations; ++i)
    {
        RCBigInt rc = ra + rb;
    }
    end = clock();
    double rcBigIntAddTime = double(end - start) / CLOCKS_PER_SEC;

    std::cout << "BigInt addition time: " << bigIntAddTime << " seconds\n";
    std::cout << "RCBigInt addition time: " << rcBigIntAddTime << " seconds\n";

    // --------------------
    // 赋值性能比较
    // --------------------
    clock_t startAssign = clock();
    for (int i = 0; i < iterations; ++i)
    {
        BigInt c = a;
    }
    clock_t endAssign = clock();
    double bigIntAssignTime = double(endAssign - startAssign) / CLOCKS_PER_SEC;

    clock_t startRCAssign = clock();
    for (int i = 0; i < iterations; ++i)
    {
        RCBigInt rc = ra;
    }
    clock_t endRCAssign = clock();
    double rcBigIntAssignTime = double(endRCAssign - startRCAssign) / CLOCKS_PER_SEC;

    std::cout << "BigInt assignment time: " << bigIntAssignTime << " seconds\n";
    std::cout << "RCBigInt assignment time: " << rcBigIntAssignTime << " seconds\n";

    // --------------------
    // 拷贝构造性能比较
    // --------------------
    clock_t startCopy = clock();
    for (int i = 0; i < iterations; ++i)
    {
        BigInt c(a); // 拷贝构造
    }
    clock_t endCopy = clock();
    double bigIntCopyTime = double(endCopy - startCopy) / CLOCKS_PER_SEC;

    clock_t startRCCopy = clock();
    for (int i = 0; i < iterations; ++i)
    {
        RCBigInt rc(ra); // 拷贝构造
    }
    clock_t endRCCopy = clock();
    double rcBigIntCopyTime = double(endRCCopy - startRCCopy) / CLOCKS_PER_SEC;

    std::cout << "BigInt copy construction time: " << bigIntCopyTime << " seconds\n";
    std::cout << "RCBigInt copy construction time: " << rcBigIntCopyTime << " seconds\n";
}

int main()
{
    performanceComparison();
    return 0;
}

/*
    要点:
        下面任意一种情况都可以使引用计数变得更为有效:
            1. 目标对象是很大的资源消费者
            2. 资源分配和释放的代价很高
            3. 高度共享: 由于使用赋值操作符和拷贝构造函数, 引用计数的性能可能会很高
            4. 创建和销毁引用的代价低廉
*/