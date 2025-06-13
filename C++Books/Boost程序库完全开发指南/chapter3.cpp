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
using namespace boost;
using std::endl;
using std::cin;
using std::cout;


//day-2025-6-13
// ������-�ڴ����
// shared_ptr 
// RAII 
// 

// �Ա�std::shared_ptr
// 

int main()
{
    typedef shared_ptr<int> int_ptr;
    // owner_less �Ƚϵ��� shared_ptr �� ���ƿ��ַ��������Ȩ����������ָ��ָ��ĵ�ַ��ֵ
    typedef owner_less<int_ptr> int_ptr_less;

    int_ptr p1(new int(10));
    int n = 20;
    int_ptr p2(p1, &n);
    assert(!int_ptr_less()(p1, p2) &&
        !int_ptr_less()(p2, p1));

    typedef std::set<int_ptr> ins;
    ins s;
    s.insert(p1);
    s.insert(p2);
    assert(s.size() == 1);
}

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
    //Abstract* q = p.get(); // ��ȷ
    //q->f();
    //delete q;              // ����

    //impl* q = (impl*)(p.get());
    //delete q;                // OK but dangerous
//}

// shared_ptr�������pimpl
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

// smart_ptr���ṩ��һ����������make_shared()
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
//    typedef some_define pointer;        // �ڲ���������
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
//    // ��ʽɾ����������
//    ptr_owned(const ptr_owned&) = delete;
//    ptr_owned& operator=(const ptr_owned&) = delete;
//};
//
//int main()
//{
	//ptr_owned p;
	//ptr_owned p2(p); // ��ptr_owned::ptr_owned(const ptr_owned &)��: ����������ɾ���ĺ���
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

//  scoped_ptr. scoped_ptrҲ�������ŵ㣬��ֻרע�������������ڵ�ָ���������������ȷ�����Ҳ�����ת��ָ�������Ȩ
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
//	explicit Scoped_ptr(T* p = nullptr); // ��ʽ���캯��
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
//template<class T> inline		// ���ָ��Ƚ�
//bool operator==(Scoped_ptr<T> const& p, boost::detail::sp_nullptr_t);

//int main()
//{ 
//	scoped_ptr<string> sp(new string("text"));
//	assert(sp); // ��ʽ bool ת��
//	assert(sp != nullptr); // ��ָ��Ƚϲ���
//
//	cout << *sp << endl;		// operator*
//	cout << sp->size() << endl; // operator->
//
//	scoped_ptr<string> sp2 = sp; //boost::scoped_ptr<std::string>::scoped_ptr:�޷����� private ��Ա(�ڡ�boost::scoped_ptr<std::string>����������)
//
//}