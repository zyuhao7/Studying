#include <iostream>
#include <assert.h>
using namespace std;
// day-2025-10-11
// 第二章-技术
// template <class To, class From>
// To safe_reinterpret_cast(From from)
// {
//     assert(sizeof(From) <= sizeof(To));
//     return reinterpret_cast<To>(from);
// }
#define STATIC_CHECK(expr)            \
    {                                 \
        char unnamed[(expr) ? 1 : 0]; \
    }
// template <class To, class From>
// To safe_reinterpret_cast(From from)
// {
//     STATIC_CHECK(sizeof(From) <= sizeof(To));
//     return reinterpret_cast<To>(from);
// }

template <bool>
struct CompileTimeChecker
{
    CompileTimeChecker(...);
};

template <>
struct CompileTimeChecker<false>
{
};

#define STATIC_CHECK(expr, msg)                  \
    {                                            \
        class ERROR_##msg                        \
        {                                        \
        };                                       \
        (void)sizeof(CompileTimeChecker<(expr)>{ERROR_##msg()));\
}

// 局部类
void Fun()
{
    class Local
    {
    };
}

class Interface
{
public:
    virtual void Fun() = 0;
};

template <class T, class P>
Interface *MakeAdapter(const T &obj, const P &arg)
{
    class Local : public Interface
    {
    public:
        Local(const T &obj, const P &arg)
            : obj_(obj),
              arg_(arg)
        {
        }

        virtual void Fun()
        {
            obj_.Call(arg_);
        }

    private:
        T obj_;
        P arg_;
    };
}

// 常整数映射为型别
template <int v>
struct Int2Type
{
    enum
    {
        value = v
    };
};

template <typename T, bool isPolymorphic>
class NiftyContainer
{
private:
    void DoSomething(T *pt, Int2Type<true>)
    {
        T *pnt = pt->Clone();
        // 多态算法
    }

    void DoSomething(T *pt, Int2Type<false>)
    {
        T *pnt = new T(*pt);
        // 非多态算法
    }

public:
    void DoSomething(T *pt)
    {
        DoSomething(pt, Int2Type<isPolymorphic>());
    }
};

// 类型对类型的映射
// template <class T, class U>
// T *Create(const U &arg)
// {
//     return new T(arg);
// }
// class Widget
// {
// };
// template <class T, class U>
// T *Create(const U &arg, T)
// {
//     return new T(arg);
// }

// template <class U>
// Widget *Create(const U &arg, Widget)
// {
//     return Widget(arg, -1);
// }

template <typename T, bool isPolymorphic>
struct NiftyContainerValueTraits
{
    typedef T *ValueType;
};
template <typename T>
struct NiftyContainerValueTraits<T, false>
{
    typedef T ValueType;
};

// template <typename T, bool isPolymorphic>
// class NiftyContainer
// {

//     typedef NiftyContainerValueTraits<T, isPolymorphic> Traits;
//     typedef typename ::Traits::ValueType ValueType;
// };

template <bool flag, typename T, typename U>
struct Select
{
    typedef T Result;
};

template <typename T, typename U>
struct Select<false, T, U>
{
    typedef U Result;
};

template <typename T, bool isPolymorphic>
class NiftyContainer
{
    typedef Select<isPolymorphic, T *, T>::Result ValueType;
};

int main()
{
    // void *somePtr = NULL;
    // char *c = safe_reinterpret_cast<char *>(somePtr);
}