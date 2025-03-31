#include <iostream>
#include <vector>
#include <mutex>
using namespace std;
// template <typename T>
// class SmartPtr
// {
// public:
//     SmartPtr(T *ptr = nullptr)
//         : _ptr(ptr)
//     {
//     }
//     ~SmartPtr()
//     {
//         if (_ptr)
//             delete _ptr;
//     }

// private:
//     T *_ptr;
// };

// int div()
// {
//     int a, b;
//     cin >> a >> b;
//     if (b == 0)
//         throw invalid_argument("除零错误");
//     return a / b;
// }
// void Func()
// {
//     SmartPtr<int> sp1(new int);
//     SmartPtr<int> sp2(new int);

//     cout << div() << endl;
// }
// int main()
// {
//     try
//     {
//         Func();
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << e.what() << '\n';
//     }

//     return 0;
// }

template <typename T>
class SmartPtr
{
public:
    SmartPtr(T *ptr = nullptr)
        : _ptr(ptr)
    {
    }
    ~SmartPtr()
    {
        if (_ptr)
            delete _ptr;
    }
    T &operator*()
    {
        return *_ptr;
    }
    T *operator->()
    {
        return _ptr;
    }

private:
    T *_ptr;
};

struct Date
{
    int _year;
    int _month;
    int _day;
};

// int main()
// {
//     SmartPtr<int> sp1(new int);
//     *sp1 = 10;
//     cout << *sp1 << endl;

//     SmartPtr<Date> sparray(new Date);
//     sparray->_year = 2018;
//     sparray->_month = 1;

//     return 0;
// }

template <typename T>
class auto_ptr
{
public:
    auto_ptr(T *ptr)
        : _ptr(ptr)
    {
    }
    auto_ptr(auto_ptr<T> &ap)
        : _ptr(ap._ptr)
    {
        ap._ptr = nullptr;
    }

    auto_ptr<T> operator=(auto_ptr<T> &ap)
    {
        if (this != &ap)
        {
            if (_ptr)
                delete _ptr;
            _ptr = ap._ptr;
            ap._ptr = nullptr;
        }
        return *this;
    }
    T &operator*()
    {
        return *_ptr;
    }
    ~auto_ptr()
    {
        if (_ptr)
        {
            cout << "delete: " << _ptr << endl;
            delete _ptr;
        }
    }

private:
    T *_ptr;
};

// int main()
// {
//     auto_ptr<int> sp1(new int);
//     auto_ptr<int> sp2(sp1);
//     *sp2 = 10;
//     cout << *sp2 << endl;
//     cout << *sp1 << endl;

//     return 0;
// }

template <typename T>
class unique_ptr
{
public:
    unique_ptr(T *ptr)
        : _ptr(ptr)
    {
    }

    ~unique_ptr()
    {
        if (_ptr)
        {
            cout << "delete : " << _ptr << endl;
            delete _ptr;
        }
    }

    T &operator*()
    {
        return *_ptr;
    }
    T *operator->()
    {
        return _ptr;
    }
    unique_ptr(const unique_ptr<T> &sp) = delete;
    unique_ptr<T> &operator=(const unique_ptr<T> &sp) = delete;

private:
    T *_ptr;
};

#include <mutex>

template <typename T>
class shared_ptr
{
public:
    shared_ptr(T *ptr = nullptr)
        : _ptr(ptr),
          _pRefCount(new int(1)),
          _mtx(new std::mutex)
    {
    }
    shared_ptr(const shared_ptr<T> &sp)
        : _ptr(sp._ptr),
          _pRefCount(sp._pRefCount),
          _mtx(sp._mtx)
    {
        AddRef();
    }

    void Release()
    {
        _mtx->lock();
        bool flag = false;
        if (--(*_pRefCount) == 0 && _ptr)
        {
            cout << "delete : " << _ptr << endl;
            delete _ptr;
            delete _pRefCount;
            flag = true;
        }
        _mtx->unlock();
        if (flag)
        {
            delete _mtx;
        }
    }
    void AddRef()
    {
        _mtx->lock();
        ++(*_pRefCount);
        _mtx->unlock();
    }

    shared_ptr<T> &operator=(const shared_ptr<T> &sp)
    {
        if (this != &sp)
        {
            Release();
            _ptr = sp._ptr;
            _pRefCount = sp._pRefCount;
            _mtx = sp._mtx;
            AddRef();
        }
        return *this;
    }
    int use_count()
    {
        return *_pRefCount;
    }
    ~shared_ptr()
    {
        Release();
    }
    T &operator*()
    {
        return *_ptr;
    }
    T *operator=()
    {
        return _ptr;
    }
    T *get() const
    {
        return _ptr;
    }

private:
    T *_ptr;
    int *_pRefCount;
    std::mutex *_mtx;
};
