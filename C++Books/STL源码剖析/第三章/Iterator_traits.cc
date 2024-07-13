#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <memory>
#include <cstddef>
using namespace std;
// 2024-7-11

#if 0
struct B {};             // 比拟 InputIterator

struct D1 : public B {}; // 比拟 ForwardIterator

struct D2 : public D1 {};// 比拟 BidirectionalIterator

template<class I>
void func(I& p, B)
{
	cout << "B version" << endl;
}

template<class I>
void func(I& p, D2)
{
	cout << "D2 version " << endl;
}

int main()
{
	int* p;
	func(p, B());  // B version.

	func(p, D1()); // B version.

	func(p, D2()); // D2 version.


	return 0;
}
#endif

#if 1
template <class I>
struct iterator_traits // traits 意为 "特性"
{
	typedef typename I::value_type value_type; 
};

template<class T>
struct iterator_traits<T*>
{
    typedef T value_type; // 迭代器是原生指针.
                          // 于是 原生指针 int* 虽然不是 class type 但是也可以通过 traits 取得 value type;
};

template <class T>
struct iterator_traits<const T *> // 偏特化版-当迭代器是个 pointer-to-const时. 萃取出来的型别应该是 T 而非 const T
{
    typedef T value_type;
}

template <class I>
struct Iterator_traits
{
	typedef typename I::iterator_category iterator_category;
	typedef typename I::value_type        value_type;
	typedef typename I::difference_type   difference_type;
	typedef typename I::pointer           pointer;
	typedef typename I::reference         reference;
};

int main()
{
    // 假如 "指向常数对象的指针" 下面得到什么?
    iterator_traits<const int *>::value_type a = 4;
    a += 1;
    cout << a << endl; // 5
}
#endif

#if 0
//Partial Specialization (偏特化)

// template<typename T>
// class C<T*>{}; //这个特化版本仅适用于 "T 为原生指针"的情况.


//Traits 编程技法.

//value type 必须用于函数的传回值.则必须要:> 声明内嵌
template<class T>
struct MyIter
{
	typedef T value_type;
	T* ptr;

	MyIter(T* p = 0)
		:ptr(p)
	{}

	T& operator* () const
	{
		return *ptr;
	}
};

template<class I>
typename I::value_type func(I ite)
{
	return *ite;
}


int main()
{
	MyIter<int> ite(new int(8));
	cout << *ite;      // 8
	cout << func(ite); // 8
}
#endif

#if 0
// 链表迭代器.

template <typename T>
class ListItem
{
public:
    T val() const
    {
        return _val;
    }

    ListItem *next() const
    {
        return _next;
    }

private:
    T _val;
    ListItem *_next; // 单向链表 (single Linked List).
};

template <typename T>
class List
{
public:
    void insert_front(T val);
    void insert_end(T val);
    void display(ostream &os = cout) const;

private:
    ListItem<T> *_end;
    ListItem<T> *_front;
    long _size;
};

template <class Item> // Item 可能是单向链表节点或者双向链表节点.此处这个迭代器特定只为链表服务.
struct ListIter
{
    Item *ptr; // 保持与容器之间的一个联系 (keep a reference to Container)

    ListIter(Item *p = 0)
        : ptr(p)
    {
    }

    // 不必实现 copy ctor 因为编译器提供的缺省行为已足够.
    // 不必实现 operator = 因为编译器提供的缺省行为已足够.

    Item &operator*() const
    {
        return *ptr;
    }

    Item *operator->() const
    {
        return ptr;
    }

    // pre-increment
    ListIter &operator++()
    {
        ptr = ptr->next();
        return *this;
    }

    // post-increment
    ListIter operator++(int)
    {
        Item tmp = *this;
        ++*this;
        return tmp;
    }

    bool operator=(const ListIter &i) const
    {
        return ptr = i.ptr;
    }

    bool operator!=(const ListIter &i) const
    {
        return ptr != i.ptr;
    }
};

#endif

#if 0
// 简化版 auto_ptr
template <class T>
class auto_Ptr
{
public:
    explicit auto_Ptr(T *p = 0)
        : pointee(p)
    {
    }

    template <class U>
    auto_Ptr(auto_Ptr<U> &rhs)
        : pointee(rhs.release())
    {
    }

    ~auto_Ptr()
    {
        delete pointee;
    }

    template <class U>
    auto_Ptr<T> &operator=(auto_Ptr<U> &rhs)
    {
        if (this != &rhs)
            reset(rhs.release());
        return *this;
    }

    T &operator*() const
    {
        return *pointee;
    }

    T *operator->() const
    {
        return pointee;
    }

    T *get() const
    {
        return pointee;
    }

private:
    T *pointee;
};

int main()
{
    auto_Ptr<string> ps1(new string("yuh"));
    cout << *ps1 << endl;
    cout << (*ps1.get()) << endl;

    auto_Ptr<string> ps(new string("jjhou"));
    cout << *ps << endl;        // jjhou
    cout << ps->size() << endl; // 5

    ps=ps1; // 没有 rhs.release() 函数..
    return 0;
}

#endif