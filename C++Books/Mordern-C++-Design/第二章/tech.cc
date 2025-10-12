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

// template <typename T, bool isPolymorphic>
// class NiftyContainer
// {
//     typedef Select<isPolymorphic, T *, T>::Result ValueType;
// };

#include <vector>
template <class T, class U>
class Conversion
{
    typedef char Small;
    class Big
    {
        char dummy[2];
    };
    static Small Test(U);
    static Big Test(...);
    static T MakeT();

public:
    enum
    {
        exists = sizeof(Test(MakeT())) == sizeof(Small)
    };
};

class TypeInfo
{
public:
    TypeInfo();
    TypeInfo(const std::type_info &);
    TypeInfo(const TypeInfo &);
    TypeInfo &operator=(const TypeInfo &);
    bool before(const TypeInfo &) const;
    const char *name() const;

private:
    const std::type_info *pInfo_;
};
// 只是一个有声明但无定义的类
class NullType;

struct EmptyType
{
};

template <typename T>
class TypeTraits
{
private:
    template <class U>
    struct PointerTraits
    {
        enum
        {
            result = false
        };
        typedef NullType PointeeType;
    };

    template <class U>
    struct PointerTraits<U *>
    {
        enum
        {
            result = true
        };
        typedef U PointeeType;
    };

public:
    enum
    {
        isPointer = PointerTraits<T>::result
    };
    typedef typename PointerTraits<T>::PointeeType PointeeType;
};

int main()
{
    // void *somePtr = NULL;
    // char *c = safe_reinterpret_cast<char *>(somePtr);

    // cout << Conversion<double, int>::exists << " "
    //      << Conversion<char, char *>::exists << " "
    //      << Conversion<size_t, vector<int>>::exists << endl; // 100

    const bool iterIsPtr = TypeTraits<vector<int>::iterator>::isPointer;
    cout << "vector<int>::iterator is " << iterIsPtr << endl;
}
