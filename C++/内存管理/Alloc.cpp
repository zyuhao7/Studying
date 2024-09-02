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