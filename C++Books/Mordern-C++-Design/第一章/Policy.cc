#include <iostream>
// day-2024-9-2
using namespace std;

template <class T>
struct OpNewCreator
{
    static T *Create()
    {
        return new T;
    }
};

// struct OpNewCreator
// {
//     template <class T>
//     static T *Create()
//     {
//         return new T;
//     }

// protected:
//     ~OpNewCreator() {}
// };

template <class T>
struct MallocCreator
{
    static T *Create()
    {
        void *buf = malloc(sizeof(T));
        if (!buf)
            return 0;
        return new (buf) T;
    }
};

template <class T>
struct PrototyCreator
{
    PrototyCreator(T *pObj = 0)
        : pPrototype_(pObj)
    {
    }

    T *Create()
    {
        return pPrototype_ ? pPrototype_->Clone() : 0;
    }

    T *GetPrototype()
    {
        return pPrototype_;
    }

    void SetPrototype(T *pObj)
    {
        pPrototype_ = pObj;
    }

private:
    T *pPrototype_;
};

class Widget
{
};

template <template <class Created> class CreationPolicy>
class WidgetManager : public CreationPolicy<Widget>
{
    void SwitchPrototype(Widget *pNewPrototype)
    {
        CreationPolicy<Widget> &myPolicy = *this;
        delete myPolicy.Getprototype();
        myPolicy.SetPrototype(pNewPrototype);
    }
};

// SmartPtr 这样使用 Checking policy:
// template <
//     class T,
//     template <class> class CheckingPolicy,
//     template <class> class ThreadingModel>
// class SmartPtr
//     : public CheckingPolicy<T>,
//       public ThreadingModel<SmartPtr>
// {
//     //...
//     T *operator->()
//     {
//         typename ThreadingModel<SmartPtr>::lock guard(*this);
//         CheckingPolicy<T>::Check(pointee_);
//         return pointee_;
//     }

// private:
//     T *pointee_;
// };

template <class T>
struct NoChecking
{
    static void Check(T *) {}
};

template <class T>
struct EnforceNotNull
{
    class NullPointerException : public std::exception
    {
    };
    static void Check(T *ptr)
    {
        if (!ptr)
            throw NullPointerException();
    }
};

template <class T>
struct EnsureNotNull
{
    static void Check(T *&ptr)
    {
        if (!ptr)
            ptr = GetDefaultValue();
    }
};

// smart pointer 的缺省存储形式是一个带有 Structure policy 接口的一般指针.
template <class T>
class DefaultSmartPtrStorage
{
public:
    typedef T *PointerType;
    typedef T &ReferenceType;

protected:
    PointerType GetPointer() { return ptr_; }
    void SetPointer(PointerType ptr) { ptr_ = ptr; }

private:
    PointerType ptr_;
};

// 实际指针的存储形式已经被完全隐藏于 Structure接口之内. 现在 SmartPtr 可以运用一个 Storage policy 来取代对 T*的聚合.
template <
    class T,
    template <class> class CheckingPolicy,
    template <class> class ThreadingModel,
    template <class> class Storage = DefaultSmartPtrStorage>
class SmartPtr;

// 当然为了内嵌所需要的结构, SP 必须继承自 Storage<T> 或 聚合一个 Storage<T> 对象.

// template <
//     class T,
//     template <class> class CheckingPolicy>
// class SmartPtr : public CheckingPolicy<T>
// {
//     template <
//         class T1,
//         template <class> class CP1>
//     SmartPtr(const SmartPtr<T1, CP1> &other)
//         : pointee_(other.pointee_),
//           CheckingPolicy<T>(other)
//     {
//     }
// };
