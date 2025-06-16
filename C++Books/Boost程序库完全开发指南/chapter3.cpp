#define BOOST_POOL_NO_MT
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <boost/version.hpp>
#include <boost/config.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/smart_ptr/make_unique.hpp>
#include <boost/smart_ptr/owner_less.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/pool/pool.hpp>
#include <boost/pool/object_pool.hpp>
#include <boost/pool/singleton_pool.hpp>
using namespace boost;
using std::endl;
using std::cin;
using std::cout;


//day-2025-6-13
// 第三章-内存管理
// 
//day-2025-6-16
// singleton_pool
//template<typename Tag, unsigned RequestedSize>
//class Singleton_pool
//{
//public:
//    static bool is_from(void* ptr);
//
//    void* malloc();
//    void* ordered_malloc();
//    void* ordered_malloc(size_t n);
//
//    void free(void* ptr);
//    void ordered_free(void* ptr);
//    void free(void* chunk, size_t n);
//    void ordered_free(void* ptr, size_t n);
//
//    bool release_memory();
//    bool purge_memory();
//};

//struct pool_tag{};
//typedef singleton_pool<pool_tag, sizeof(int)> sp1;
//
//int main()
//{
//    int* p = (int*)sp1::malloc();
//    assert(sp1::is_from(p));
//    sp1::release_memory();
//}

// object_pool
//template<typename T, typename UserAllocator>
//class Object_pool : protected pool<UserAllocator>
//{
//public:
//    typedef T element_type;
//public:
//    Object_pool();
//    ~Object_pool();
//
//    element_type* malloc();
//    void free(element_type* p);
//    bool is_from(element_type* p) const;
//
//    element_type* construct(...);
//    void destroy(element_type* p);
//};
 

//template<typename P, typename... Args>
//inline typename P::element_type* construct(P& p, Args&& ... args)
//{
//    typename P::element_type* mem = p.malloc();
//
//    assert(mem != 0);
//    new (mem) typename P::element_type(
//        std::forward<Args>(args)...);
//    return mem;
//}
//
//struct demo_class
//{
//public:
//    int a, b, c;
//    demo_class(int x = 1, int y = 2, int z = 3)
//        :a(x),
//        b(y),
//        c(z)
//    {}
//    demo_class(int, int, int, int)
//    {
//        cout << "demo_class ctor" << endl;
//    }
//    ~demo_class()
//    {
//        cout << "demo_class dtor" << endl;
//    }
//};

//int main()
//{
    //object_pool<demo_class> p1;
    //auto p = p1.malloc();
    //assert(p1.is_from(p));

    //// p指向的内存未经过初始化
    //assert(p->a != 1 || p->b != 2 || p->c != 3);


    //p = p1.construct(7, 8, 9);
    //assert(p->a == 7);

    //object_pool<std::string> pls;
    //for (int i = 0; i < 10; ++i)
    //{
    //    std::string* ps  = pls.construct("hello object_pool");
    //    cout << *ps << endl;
    //}

//    object_pool<demo_class> pd;
//    auto d = construct(pd, 1, 2, 3, 5);
//}


// pool
//template<typename UserAllocator = default_user_allocator_new_delete>
//class Pool
//{
//public:
//    explicit pool(size_t requested_size);
//    ~Pool();
//
//    size_t get_requested_size() const;
//
//    void* malloc();
//    void* ordered_malloc();
//    void* ordered_malloc(size_t n);
//    bool is_from(void* chunk) const;
//
//    void free(void* chunk);
//    void ordered_free(void* chunk);
//    void free(void* chunk, size_t n);
//    void ordered_free(void* chunks, size_t n);
//
//    bool release_memory();
//    bool purge_memory();
//};

//int main()
//{
//    pool<> p1(sizeof(int));
//    int* p = static_cast<int*>(p1.malloc());
//    assert(p1.is_from(p));
//    p1.free(p);
//    for (int i = 0; i < 100; ++i)
//    {
//        p1.ordered_malloc(10);
//    }
//}


// day-2025-6-15
// weak_ptr

// 引用计数
//class node // 一个用于链表节点的类
//{
//public:
//    ~node()
//    {
//        cout << "deleted" << endl;
//    }
//    typedef shared_ptr<node> ptr_type;
//    ptr_type next;
//};
//
//int main()
//{
//    auto p1 = make_shared<node>();
//    auto p2 = make_shared<node>();
//
//    p1->next = p2;
//    p2->next = p1;
//    assert(p1.use_count() == 2);;
//    assert(p2.use_count() == 2);
//}

//class node // 一个用于链表节点的类
//{
//public:
//    ~node()
//    {
//        cout << "deleted" << endl;
//    }
//    typedef weak_ptr<node> ptr_type;
//    ptr_type next;
//};
//
//int main()
//{
//    auto p1 = make_shared<node>();
//    auto p2 = make_shared<node>();
//    p1->next = p2;
//    p2->next = p1;
//
//    assert(p1.use_count() == 1);
//    assert(p2.use_count() == 1);
//    if (!p1->next.expired())
//    {
//        auto p3 = p1->next.lock();
//    }
//}

//<boost/enable_shared_from_this.hpp>
// enable_shared_from_this<T>
//template<typename T>
//class Enable_shared_from_this
//{
//public:
//    shared_ptr<T> shared_from_this(); // 工厂函数, 产生 this 指针的shared_ptr
//};

// 使用 weak_ptr的时候只需要让想被 shared_ptr 管理的类继承它即可, 成员函数 shared_from_this() 会返回 this指针的 shared_ptr.
//class Self_shared : public enable_shared_from_this<Self_shared>
//{
//public:
//    Self_shared(int n)
//        :x(n){}
//    int x;
//    void print()
//    {
//        cout << "Self_shared: " << x << endl;
//    }
//    
//};
//
//int main()
//{
//    auto sp = make_shared<Self_shared>(313);
//    sp->print();
//
//    auto p = sp->shared_from_this();
//    p->x = 1000;
//    p->print();
//    cout << p.use_count() << endl;
//
//    Self_shared ss;
//    auto p = ss.shared_from_this(); // err
//}


/*
    weak_ptr 被设计为与shared_ptr 协同工作，可以从一个shared_ptr 或另一个weak_ptr 对象构造以获得资源的观测权。
    但 weak_ptr 没有共享资源，它的构造不会引起指针引用计数的增加。同样，weak_ptr 析构时也不会导致引用计数减少
*/
//template<typename T>
//class Weak_ptr
//{
//public:
//    Weak_ptr();
//    template<typename Y>
//    Weak_ptr(boost::shared_ptr<Y> const& r);
//    Weak_ptr(Weak_ptr const& r);
//    ~Weak_ptr();
//    Weak_ptr& operator=(Weak_ptr const& r);
//
//    long use_count() const;
//    bool expired() const; //是否为失效指针
//    bool empty() const;   // 是否为空指针
//    boost::shared_ptr<T> lock() const; // 获取 shared_ptr 
//    
//    void reset();
//    void swap(Weak_ptr<T>& b);
//};

//int main()
//{
//    shared_ptr<int> sp(new int(10));
//    assert(sp.use_count() == 1);
//
//    weak_ptr<int> wp(sp);
//    assert(wp.use_count() == 1);
//    assert(!wp.empty());
//
//    if (!wp.expired())
//    {
//        shared_ptr<int> sp2 = wp.lock();
//        *sp2 = 100;
//        assert(wp.use_count() == 2);
//    }
//
//    assert(wp.use_count() == 1);
//    sp.reset();
//    assert(wp.expired());
//    assert(!wp.lock());
//}


// 对比std::shared_ptr

//int main()
//{
//    typedef shared_ptr<int> int_ptr;
//    // owner_less 比较的是 shared_ptr 的 控制块地址（即所有权），而不是指针指向的地址或值
//    typedef owner_less<int_ptr> int_ptr_less;
//
//    int_ptr p1(new int(10));
//    int n = 20;
//    int_ptr p2(p1, &n);
//    assert(!int_ptr_less()(p1, p2) &&
//        !int_ptr_less()(p2, p1));
//
//    typedef std::set<int_ptr> ins;
//    ins s;
//    s.insert(p1);
//    s.insert(p2);
//    assert(s.size() == 1);
//}

//int main()
//{
//    auto p1 = make_shared<std::pair<int, int>>(0, 1);
//    shared_ptr<int> p2(p1, &p1->second);
//    assert(p1.use_count() == 2 &&
//        p1.use_count() == p2.use_count());
//
//    assert((void*)p1.get() != (void*)p2.get());
//    assert(&p1->second == p2.get());
//    cout << p1->first << " " << p1->second << endl;
//    cout << *p2 << endl;
//}

//void any_func(void* p)
//{
//    cout << "some operator" << endl;
//}
//
//int main()
//{
//    shared_ptr<void> p(nullptr, any_func);
//}

//bool bool_test()
//{
//    auto p = make_shared<int>(776);
//    assert(p);
//    if (p)
//    {
//        cout << "explicit cast" << endl;
//    }
//
//    shared_ptr<std::exception> sp1(new std::bad_exception);
//    auto sp2 = dynamic_pointer_cast<std::bad_exception>(sp1);
//    auto sp3 = static_pointer_cast<std::bad_exception>(sp2);
//    assert(sp3 == sp1);
//
//    return static_cast<bool>(p);
//}
//
//int main()
//{
//    bool_test();
//}


//class Abstract
//{
//public:
//    virtual void f() = 0;
//    virtual void g() = 0;
//protected:
//    virtual ~Abstract() = default;
//};
//
//class impl : public Abstract
//{
//public:
//    impl() = default;
//    virtual ~impl() = default;
//public:
//    virtual void f()
//    {
//        cout << "class impl f" << endl;
//    }
//
//    virtual void g()
//    {
//        cout << "class impl g" << endl;
//    }
//};
//
//shared_ptr<Abstract> create()
//{
//    return make_shared<impl>();
//}
//
//int main()
//{
//    auto p = create();
//    p->f();
//    p->g();
    //Abstract* q = p.get(); // 正确
    //q->f();
    //delete q;              // 错误

    //impl* q = (impl*)(p.get());
    //delete q;                // OK but dangerous
//}

// shared_ptr如何用于pimpl
//class Sample
//{
//private:
//    class impl;
//    shared_ptr<impl> p;
//public:
//    Sample();
//    void print();
//};
//
//class Sample::impl
//{
//public:
//    void print()
//    {
//        cout << "impl print" << endl;
//    }
//};
//Sample::Sample()
//    :p(new impl)
//{}
//
//void Sample::print()
//{
//    p->print();
//}
//int main()
//{
//    Sample s;
//    s.print();
//}


//int main()
//{
//    typedef std::vector<shared_ptr<int>> vs;
//    vs v(10);
//    int i = 0;
//    for (auto pos = v.begin(); pos != v.end(); ++pos)
//    {
//        (*pos) = make_shared<int>(++i);
//        cout << *(*pos) << endl;
//    }
//    cout << endl;
//    shared_ptr<int> p = v[9];
//    *p = 100;
//    cout << *v[9] << endl;
//}

// smart_ptr库提供了一个工厂函数make_shared()
//template<typename T, typename... Args>
//typename boost::detail::sp_if_not_array<T>::type
//make_shared(Args&&... args);


//int main()
//{
//    auto sp = boost::make_shared<std::string>("make_shared");
//    auto spv = make_shared<std::vector<int>>(10, 2);
//    assert(spv->size() == 10);
//}

//class Shared
//{
//private:
//    shared_ptr<int> p;
//public:
//    Shared(shared_ptr<int> p_)
//        :p(p_)
//    {}
//
//    void print()
//    {
//        std::cout << "count: " << p.use_count() << " v = " <<*p << std::endl;
//    }
//};
//
//void print_func(shared_ptr<int> p)
//{
//    std::cout << "count: " << p.use_count() << " v = " << *p << endl;
//}
//
//int main()
//{
//    shared_ptr<int> p(new int(100));
//    Shared s1(p), s2(p);
//    s1.print();
//    s2.print();
//
//    *p = 20;
//    print_func(p);
//
//    s1.print();
//}

//int main()
//{
//    boost::shared_ptr<int> sp(new int(10));
//    assert(sp.unique());
//    boost::shared_ptr<int> sp2 = sp;
//    assert(sp == sp2 && sp.use_count() == 2);
//    *sp2 = 100;
//    assert(*sp == 100);
//
//    sp.reset();
//    assert(!sp);
//
//}

// shared_ptr
//template<typename T>
//class Shared_ptr
//{
//public:
//    typedef T element_type;
//    Shared_ptr();
//
//    template<typename Y>
//    explicit Shared_ptr(Y* p);
//    template<typename Y,typename D>
//    explicit Shared_ptr(Y* p, D d);
//
//    ~Shared_ptr();
//    Shared_ptr(Shared_ptr const& r);
//    Shared_ptr& operator=(Shared_ptr const& r);
//    template<typename Y>
//    Shared_ptr& operator=(Shared_ptr<Y> const& r);
//
//    void reset();
//    template<class Y> void reset(Y* p);
//    template<class Y, class D> reset(Y* p, D d);
//    
//    T& operator*() const;
//    T* operator->() const;
//    T* get() const;
//    bool unique() const;
//    long use_count() const;
//    explicit operator bool() const;
//    void swap(Shared_ptr& b);
//};
//typedef boost::shared_ptr<string> sp_t;
//
//int main()
//{
//    map<sp_t, int> m;
//    sp_t sp(new string("one"));
//    m[sp] = 111;
//    for (auto &[k, v] : m)
//    {
//        cout << "Key: " << *k << " " << "Val: " << v << endl;
//    }
//}

// make_unique
//template<class T, class... Args>
//inline typename boost::detail::up_if_not_array<T>::type
//make_unique(Args&&... Args)
//{
//    return std::unique_ptr<T>(new T(...));
//}

//int main()
//{
//    auto p = boost::make_unique<int>(10);
//    assert(p && *p == 10);
//}

// unique_ptr
//template<typename T, class D = default_delete<T>>
//class Unique_ptr
//{
//public:
//    typedef some_define pointer;        // 内部定义类型
//    typedef T   element_type;
//
//    constexpr Unique_ptr() noexcept;
//    explicit Unique_ptr(pointer p) noexcept;
//
//    ~Unique_ptr();
//    Unique_ptr& Unique_ptr(pointer p) noexcept;
//
//    element_type& operator*() const;
//    pointer operator->() const noexcept;
//    pointer get() const noexcept;
//    explicit operator bool() const noexcept;
//
//    pointer release() noexcept;
//    void reset(pointer p) noexcept;
//    void swap(Unique_ptr& u) noexcept;
//
//    Unique_ptr(const Unique_ptr&) = delete;
//    Unique_ptr operator=(const Unique_ptr&) = delete;
//};
//
//bool operator==(const Unique_ptr& x, const Unique_ptr& y);

//int main()
//{
//    unique_ptr<int> up(new int);
//    assert(up);
//    *up = 10;
//    cout << *up << endl;
//    up.reset();
//    assert(!up);
//}


//class ptr_owned final {
//    scoped_ptr<int> m_ptr;
//public:
//    ptr_owned() : m_ptr(new int(42)) {}
//
//    // 显式删除拷贝操作
//    ptr_owned(const ptr_owned&) = delete;
//    ptr_owned& operator=(const ptr_owned&) = delete;
//};
//
//int main()
//{
	//ptr_owned p;
	//ptr_owned p2(p); // “ptr_owned::ptr_owned(const ptr_owned &)”: 尝试引用已删除的函数
    //scoped_ptr<int> p(new int);
    //if (p)
    //{
    //    *p = 100;
    //    cout << *p << endl;
    //}
    //p.reset();
    //assert(p == 0);
    //if (!p)
    //{
    //    cout << "scoped_ptr == nullptr" << endl;
    //}
//}

//  scoped_ptr. scoped_ptr也有它的优点，它只专注于做好作用域内的指针管理工作，含义明确，而且不允许转让指针的所有权
//template<typename T>
//class Scoped_ptr   // noncopyable
//{
//private:
//	T* px;
//	Scoped_ptr(Scoped_ptr const&);
//	Scoped_ptr& operator=(Scoped_ptr const&);
//
//	void operator==(Scoped_ptr cpmst&) const;
//	void operator !=(Scoped_ptr const&)const;
//public:
//	explicit Scoped_ptr(T* p = nullptr); // 显式构造函数
//	~Scoped_ptr();
//	void reset(T* p = nullptr);
//
//	T& operator*() const;
//	T* operator->() const;
//	T* get()const;
//
//	explicit operator bool() const;
//	void swap(Scoped_ptr& b);
//};
//
//template<class T> inline		// 与空指针比较
//bool operator==(Scoped_ptr<T> const& p, boost::detail::sp_nullptr_t);

//int main()
//{ 
//	scoped_ptr<string> sp(new string("text"));
//	assert(sp); // 显式 bool 转型
//	assert(sp != nullptr); // 空指针比较操作
//
//	cout << *sp << endl;		// operator*
//	cout << sp->size() << endl; // operator->
//
//	scoped_ptr<string> sp2 = sp; //boost::scoped_ptr<std::string>::scoped_ptr:无法访问 private 成员(在“boost::scoped_ptr<std::string>”类中声明)
//
//}