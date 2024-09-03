// compiler : g++ (GCC) 7.3.1 20180303 (Red Hat 7.3.1-5)

#include <iostream>
#include <string>
#include <complex>
#include <ctime>
#include <cstring> //strlen()
#include <type_traits>
#include <memory>
#include <ext/pool_allocator.h>

using namespace std;
// day-2024-9-2
/*
namespace myh
{
    void test_primitives()
    {
        cout << "\ntest_primitives().......... \n";

        void *p1 = malloc(512); // 512 bytes
        free(p1);

        complex<int> *p2 = new complex<int>; // one object
        delete p2;

        void *p3 = ::operator new(512); // 512 bytes
        ::operator delete(p3);

// 以下使用 C++标准库提供的 allocators
#ifdef _MSC_VER
        int *p4 = allocator<int>().allocate(3, (int *)0);
        allocator<int>().deallocate(p4, 3);
#endif

#ifdef __BORLANDC__
        int *p4 = allocator<int>().allocate(5);
        allocator<int>().deallocate(p4, 5);
#endif

#ifdef __GNUC__
        // 以下兩函數都是 static，可通過全名調用之。以下分配 512 bytes.
        // void* p4 = alloc::allocate(512);
        // alloc::deallocate(p4,512);

        // 以下兩函數都是 non-static，定要通過 object 調用。以下分配 7 個 ints.
        void *p4 = allocator<int>().allocate(7);
        allocator<int>().deallocate((int *)p4, 7);

        // 以下兩函數都是 non-static，定要通過 object 調用。以下分配 9 個 ints.
        void *p5 = __gnu_cxx::__pool_alloc<int>().allocate(9);
        __gnu_cxx::__pool_alloc<int>().deallocate((int *)p5, 9);
#endif
    }
}

int main()
{
    // myh::test_primitives();

    return 0;
}
*/

/*
namespace myh
{

    class A
    {
    public:
        int id;

        A() : id(0) { cout << "default ctor. this=" << this << " id=" << id << endl; }
        A(int i) : id(i) { cout << "ctor. this=" << this << " id=" << id << endl; }
        ~A() { cout << "dtor. this=" << this << " id=" << id << endl; }
    };

    void test_call_ctor_directly()
    {
        cout << "\n test_call_ctor_directly().......... \n";

        string *pstr = new string;
        cout << "str= " << *pstr << endl; // str=

        *pstr = "xiaomotongxue";
        cout << "str= " << *pstr << endl; // str= xiaomotongxue

        // pstr->string::string("myh");
        //[Error] 'class std::basic_string<char>' has no member named 'string'
        pstr->~string();                  // 语法语义符合规范
        cout << "str= " << *pstr << endl; // str=

        cout << "-- -- -- -- -- -- -- -- -- -- -- -" << endl;

        A *pA = new A(1);       // ctor. this=0xbeec70 id=1
        cout << pA->id << endl; // 1
                                // pA->A::A(3);            // in GCC cannot call constructor ‘myh::A::A’ directly

        // A::A(5); // in GCC cannot call constructor ‘myh::A::A’ directly
        //       note: for a function-style cast, remove the redundant ‘::A’

        delete pA; // dtor. this=0x17f5c70 id=1

        // // simulate new
        void *p = ::operator new(sizeof(A));
        cout << "p=" << p << endl; // p=0x237ec70
        pA = static_cast<A *>(p);
        // pA->A::A(2); // in GCC : [Error] cannot call constructor ‘myh::A::A’ directly

        cout << pA->id << endl; // in GCC : 0

        // // simulate delete
        pA->~A(); // dtor. this=0x237ec70 id=0

        // ::operator delete(pA); // free()
    }
}

int main()
{
    myh::test_call_ctor_directly();
    return 0;
}
*/

/*
#include <new> //placement new
namespace myh
{

    class A
    {
    public:
        int id;

        A() : id(0) { cout << "default ctor. this=" << this << " id=" << id << endl; }
        A(int i) : id(i) { cout << "ctor. this=" << this << " id=" << id << endl; }
        ~A() { cout << "dtor. this=" << this << " id=" << id << endl; }
    };

    void test_array_new_and_placement_new()
    {
        cout << "\n test_placement_new().......... \n";

        size_t size = 3;
        {
            // case 1
            // 模拟 memory pool 的作法, array new + placement new. 崩溃.

            A *buf = (A *)(new char[sizeof(A) * size]);
            A *tmp = buf;

            cout << "buf=" << buf << "  tmp=" << tmp << endl;

            for (int i = 0; i < size; ++i)
                new (tmp++) A(i); // 3次 ctor

            cout << "buf=" << buf << "  tmp=" << tmp << endl;

            // delete[] buf; // crash. why?
            // 这其实是个 char array, 看到 delete [] buf; 编译器会企图唤起多次 A::~A.
            // 但 array memory layout 中找不到 array 元素个数 (本例 3) 相关的信息.
            // 整个格局都错乱! 于是崩溃.

            delete buf; // dtor just one time, ~[0]
            cout << endl;
        }

        {
            // case 2
            // 回头测试单纯的  array new

            A *buf = new A[size]; // default ctor 3 次. [0]先於[1]先於[2]
                                  // A必須有 default ctor, 否則 [Error] no matching function for call to 'myh::A::A()'
            A *tmp = buf;

            cout << "buf=" << buf << "  tmp=" << tmp << endl;

            for (int i = 0; i < size; ++i)
                new (tmp++) A(i); // 3次 ctor

            cout << "buf=" << buf << "  tmp=" << tmp << endl;

            delete[] buf; // dtor three times (次序逆反, [2]先於[1]先於[0])
            cout << endl;
        }

        {
            // case 3
            // 掌握崩潰原因, 再次模拟 memory pool 作法, array new + placement new.
            // 不, 不做了, 因为 memory pool 只是供应 memory, 它并不管 construction,
            // 也不管 destruction. 它只负责回收 memory.
            // 所以它是以 void* 或 char* 取得 memory, 释放 (刪除)的也是 void* or char*.
            // 不像本例 case 1 释放 (刪除) 的是 A*.
        }
    }
}

int main()
{
    myh::test_array_new_and_placement_new();

    return 0;
}
*/

// 2024-9-3

/*
#include <cstddef>
#include <iostream>
namespace myh
{
    // ref. C++Primer 3/e, p.765
    // per-class allocator

    class Screen
    {
    public:
        Screen(int x) : i(x) {};
        int get() { return i; }

        void *operator new(size_t);
        void operator delete(void *, size_t); //(2)
        // void operator delete(void *);         //(1) 二选一. 若(1)(2)並存,會有很奇怪的報錯 (摸不著頭緒)

    private:
        Screen *next;
        static Screen *freeStore;
        static const int screenChunk;

    private:
        int i;
    };

    Screen *Screen::freeStore = 0;
    const int Screen::screenChunk = 24;

    void *Screen::operator new(size_t size)
    {
        Screen *p;
        if (!freeStore)
        {
            // linked list 是空的，所以获取一大块 memory
            // 以下呼叫的是 global operator new
            size_t chunk = screenChunk * size;
            freeStore = p =
                reinterpret_cast<Screen *>(new char[chunk]);
            // 將分配得來的一大塊 memory 當做 linked list 般小塊小塊串接起來
            for (; p != &freeStore[screenChunk - 1]; ++p)
                p->next = p + 1;
            p->next = 0;
        }
        p = freeStore;
        freeStore = freeStore->next;
        return p;
    }

    //! void Screen::operator delete(void *p)		//(1)
    void Screen::operator delete(void *p, size_t) //(2)二擇一
    {
        // 將 deleted object 收回插入 free list 前端
        (static_cast<Screen *>(p))->next = freeStore;
        freeStore = static_cast<Screen *>(p);
    }

    //-------------
    void test_per_class_allocator_1()
    {
        cout << "\ntest_per_class_allocator_1().......... \n";

        cout << sizeof(Screen) << endl; // 16

        size_t const N = 100;
        Screen *p[N];

        for (int i = 0; i < N; ++i)
            p[i] = new Screen(i);

        // 輸出前 10 個 pointers, 用以比較其間隔
        for (int i = 0; i < 10; ++i)
            cout << p[i] << endl;

        for (int i = 0; i < N; ++i)
            delete p[i];
    }
}

int main()
{
    myh::test_per_class_allocator_1();
    return 0;
}
*/

/*
#include <cstddef>
#include <iostream>
namespace myh
{
    // ref. Effective C++ 2e, item10
    // per-class allocator

    class Airplane
    { // 支援 customized memory management
    private:
        struct AirplaneRep
        {
            unsigned long miles;
            char type;
        };

    private:
        union
        {
            AirplaneRep rep; // 此針對 used object
            Airplane *next;  // 此針對 free list
        };

    public:
        unsigned long getMiles() { return rep.miles; }
        char getType() { return rep.type; }
        void set(unsigned long m, char t)
        {
            rep.miles = m;
            rep.type = t;
        }

    public:
        static void *operator new(size_t size);
        static void operator delete(void *deadObject, size_t size);

    private:
        static const int BLOCK_SIZE;
        static Airplane *headOfFreeList;
    };

    Airplane *Airplane::headOfFreeList;
    const int Airplane::BLOCK_SIZE = 512;

    void *Airplane::operator new(size_t size)
    {
        // 如果大小错误，转交給 ::operator new()
        if (size != sizeof(Airplane))
            return ::operator new(size);

        Airplane *p = headOfFreeList;

        // 如果 p 有效，就把list頭部移往下一個元素
        if (p)
            headOfFreeList = p->next;
        else
        {
            // free list 已空. 配置一块够大内存
            // 令足够容纳 BLOCK_SIZE 个 Airplanes

            Airplane *newBlock = static_cast<Airplane *>(::operator new(BLOCK_SIZE * sizeof(Airplane)));

            // 组成一个新的 free list : 将小块串在一起, 但跳过 #0 元素, 因为要将他传回给呼叫者.
            for (int i = 1; i < BLOCK_SIZE - 1; ++i)
                newBlock[i].next = &newBlock[i + 1];

            newBlock[BLOCK_SIZE - 1].next = 0; // 以null結束

            // 将 p 设为头部, 将 headOfFreeList 设至为下一个可被使用的小块.
            p = newBlock;
            headOfFreeList = &newBlock[1];
        }
        return p;
    }

    // operator delete 接收一块内存
    // 如果它的大小正確，就把它加到 free list 的前端
    void Airplane::operator delete(void *deadObject,
                                   size_t size)
    {
        if (deadObject == 0)
            return;
        if (size != sizeof(Airplane))
        {
            ::operator delete(deadObject);
            return;
        }

        Airplane *carcass =
            static_cast<Airplane *>(deadObject);

        carcass->next = headOfFreeList;
        headOfFreeList = carcass;
    }

    //-------------
    void test_per_class_allocator_2()
    {
        cout << "\ntest_per_class_allocator_2().......... \n";

        cout << sizeof(Airplane) << endl; // 16

        size_t const N = 100;
        Airplane *p[N];

        for (int i = 0; i < N; ++i)
            p[i] = new Airplane;

        // 随机测试 object 正常否
        p[1]->set(1000, 'A');
        p[5]->set(2000, 'B');
        p[9]->set(500000, 'C');
        cout << p[1] << ' ' << p[1]->getType() << ' ' << p[1]->getMiles() << endl;
        cout << p[5] << ' ' << p[5]->getType() << ' ' << p[5]->getMiles() << endl;
        cout << p[9] << ' ' << p[9]->getType() << ' ' << p[9]->getMiles() << endl;

        // 輸出前 10 個 pointers, 用以比較其間隔
        for (int i = 0; i < 10; ++i)
            cout << p[i] << endl;

        for (int i = 0; i < N; ++i)
            delete p[i];
    }
}

int main()
{
    myh::test_per_class_allocator_2();
    return 0;
}
*/

/*
#include <cstddef>
#include <iostream>
#include <string>
namespace myh
{

    class Foo
    {
    public:
        int _id;
        long _data;
        string _str;

    public:
        static void *operator new(size_t size);
        static void operator delete(void *deadObject, size_t size);
        static void *operator new[](size_t size);
        static void operator delete[](void *deadObject, size_t size);

        Foo() : _id(0) { cout << "default ctor. this=" << this << " id=" << _id << endl; }
        Foo(int i) : _id(i) { cout << "ctor. this=" << this << " id=" << _id << endl; }

        // virtual
        virtual ~Foo() { cout << "dtor. this=" << this << " id=" << _id << endl; }

        // 不加 virtual dtor, sizeof = 24, new Foo[5] => operator new[]() 的 size 參數是 128
        // 加了 virtual dtor, sizeof = 32, new Foo[5] => operator new[]() 的 size 參數是 168

        // 上述二例，多出來的 8 可能就是個 size_t 欄位用來放置 array size.
    };

    void *Foo::operator new(size_t size)
    {
        Foo *p = (Foo *)malloc(size);
        cout << "Foo::operator new(), size=" << size << "\t  return: " << p << endl;

        return p;
    }

    void Foo::operator delete(void *pdead, size_t size)
    {
        cout << "Foo::operator delete(), pdead= " << pdead << "  size= " << size << endl;
        free(pdead);
    }

    void *Foo::operator new[](size_t size)
    {
        Foo *p = (Foo *)malloc(size); // crash, 問題可能出在这里.
        cout << "Foo::operator new[](), size=" << size << "\t  return: " << p << endl;

        return p;
    }

    void Foo::operator delete[](void *pdead, size_t size)
    {
        cout << "Foo::operator delete[](), pdead= " << pdead << "  size= " << size << endl;

        free(pdead);
    }

    //-------------
    void test_overload_operator_new_and_array_new()
    {
        cout << "\ntest_overload_operator_new_and_array_new().......... \n";

        cout << "sizeof(Foo)= " << sizeof(Foo) << endl;

        {
            Foo *p = new Foo(7);
            delete p;

            Foo *pArray = new Foo[5]; // 無法給 array elements 以 initializer
            delete[] pArray;
        }

        {
            cout << "testing global expression ::new and ::new[] \n";
            // 這會繞過 overloaded new(), delete(), new[](), delete[]()
            // 但當然 ctor, dtor 都會被正常呼叫.

            Foo *p = ::new Foo(7);
            ::delete p;

            Foo *pArray = ::new Foo[5];
            ::delete[] pArray;
        }
    }
}

int main()
{
    myh::test_overload_operator_new_and_array_new();
    return 0;
}
*/