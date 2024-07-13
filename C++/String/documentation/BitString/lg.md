# string 类
## 标准库中的 string 类
    1. 字符串是表示字符序列的类

    2. 标准的字符串类提供了对此类对象的支持, 其接口类似于标准字符容器的接口, 但添加了专门用于操作单字节字符串的设计特性

    3. string 类是使用 char(即作为它的字符类型, 使用它的默认 char_traits 和分配器类型)

    4. string 类 是 basic_string 模板类的一个实例, 它使用 char 来实例化 basic_string 模板类, 并用 char_traits 和 allocator 作为 basic_string 的默认参数

    5. 这个类独立于所使用的编码来处理字节: 如果用来处理多字节或变长字符的序列, 这个类的所有成员以及它的迭代器, 任然按照字节来操作

    总结:
    1. string 是表示字符串的字符串类
    2. 该类的接口与常规容器的接口基本相同, 再添加一些专门用来操作 string 的常规操作.
    3. string在底层实际是: basic_string 模板类的别名, typedef basic_string<char, char_traits, allocator> string;
    4. 不能操作多字节或者变长字符的序列.

```c++

/*
下述结构是在32位平台下进行验证，32位平台下指针占4个字节.

                             vs下string的结构

string总共占28个字节，内部结构稍微复杂一点，先是有一个联合体，联合体用来定义string中字符串的存储空间：

 · 当字符串长度小于16时，使用内部固定的字符数组来存放
 · 当字符串长度大于等于16时，从堆上开辟空间

union _Bxty
{
    value_type _Buf[_BUF_SIZE];
    pointer _Ptr;
    char _Alias[_BUF_SIZE];
};
_Bxty _Bx; 

    size_type _Mysize = 0; // current length of string (size)
    size_type _Myres  = 0; // current storage reserved for string (capacity)

其次：还有一个size_t字段保存字符串长度，一个size_t字段保存从堆上开辟空间总的容量.
最后：还有一个指针做一些其他事情;



                g++ 下 string 的结构.

G++下，string是通过写时拷贝实现的，string对象总共占16个字节，内部只包含了一个指针，该指针将来指向一块堆空间，内部包含了如下字段:

            1 空间总大小
            2 字符串有效长度
            3 引用计数
            4 指向堆空间的指针，用来存储字符串
*/ 
struct _Rep_base
{
    size_type _M_length;
    size_type _M_capacity;
    _Atomic_word _M_refcount;
};
```

```c++
// string类的模拟实现
/*
    浅拷贝:
     浅拷贝是对象复制的一种方法，它复制对象的所有成员变量的值，包括指针的值（即内存地址），而不复制指针所指向的内容。换句话说，浅拷贝仅仅复制对象的成员变量，并不考虑成员变量指向的动态内存或其他资源.
    
    浅拷贝的特点
      1. 只复制指针的值，不复制指针所指向的实际内存数据.
      2. 两个对象共享同一块内存资源。修改一个对象的数据会影响到另一个对象。
      3. 如果在一个对象被删除时释放了共享的内存资源，另一个对象再访问该内存时会导致悬挂指针（dangling pointer）.


     深拷贝:
      深拷贝是对象复制的另一种方法，它不仅复制对象的所有成员变量的值，还会为指针所指向的动态内存分配新的内存空间，并复制原始对象中的数据到新分配的内存中。这样，两个对象各自拥有独立的内存资源，修改一个对象的数据不会影响到另一个对象.

    深拷贝的特点
      1. 复制指针所指向的实际数据，并分配新的内存空间。
      2. 每个对象拥有独立的内存资源。
      3. 修改一个对象的数据不会影响到另一个对象。
      4. 删除一个对象时，不会影响到另一个对象，避免了悬挂指针的问题。
*/

```

```c++
    //                      写时拷贝(COW)
    /*   
    写时拷贝的基本概念

        1 共享数据：多个对象共享同一块数据，避免了重复的内存占用。
        2 懒拷贝：只有在对象需要修改时，才会执行实际的深拷贝，从而获得自己的数据副本.

    写时拷贝的优点
        1. 节省内存：多个对象共享数据，直到有对象需要修改，才会分配新的内存。
        2. 提高性能：减少了不必要的复制操作，尤其是在只读场景下，可以大幅提高性能。
        3. 延迟开销：将深拷贝的开销推迟到真正需要修改数据时，分散了资源分配的压力。

    写时拷贝的实现机制   

        写时拷贝的核心思想是使用 共享数据 和 引用计数 （reference counting）来管理资源。以下是写时拷贝的一些关键实现步骤：

        1.  引用计数：每个数据块都有一个引用计数，记录有多少对象共享这块数据。

        2.  共享数据：对象间共享数据块，引用计数递增。

        3.  检查修改：在修改数据之前，检查引用计数。如果引用计数大于 1，表示数据被共享，需要进行深拷贝；否则直接修改数据。 

code:
#include <iostream>
#include <cstring>

class CowString
{
private:
    struct StringData
    {
        char *data;
        int ref_count;

        // 构造函数
        StringData(const char *str)
        {
            data = new char[strlen(str) + 1];
            strcpy(data, str);
            ref_count = 1;
        }

        // 析构函数
        ~StringData()
        {
            delete[] data;
        }
    };

    StringData *str_data;

    // 实现深拷贝
    void detach()
    {
        if (str_data->ref_count > 1)
        {
            str_data->ref_count--;
            str_data = new StringData(str_data->data);
        }
    }

public:
    // 构造函数
    CowString(const char *str = "")
    {
        str_data = new StringData(str);
    }

    // 拷贝构造函数
    CowString(const CowString &other)
    {
        str_data = other.str_data;
        str_data->ref_count++;
    }

    // 赋值运算符
    CowString &operator=(const CowString &other)
    {
        if (this != &other)
        {
            if (--str_data->ref_count == 0)
            {
                delete str_data;
            }
            str_data = other.str_data;
            str_data->ref_count++;
        }
        return *this;
    }

    // 下标运算符（返回可修改的字符引用）
    char &operator[](size_t index)
    {
        detach(); // 确保修改之前不共享数据
        return str_data->data[index];
    }

    // 下标运算符（返回只读字符引用）
    const char &operator[](size_t index) const
    {
        return str_data->data[index];
    }

    // 获取字符串
    const char *c_str() const
    {
        return str_data->data;
    }

    // 析构函数
    ~CowString()
    {
        if (--str_data->ref_count == 0)
        {
            delete str_data;
        }
    }
};

int main() {
    CowString s1("Hello, World!");
    CowString s2 = s1;  // s2 与 s1 共享数据

    std::cout << "s1: " << s1.c_str() << std::endl;
    std::cout << "s2: " << s2.c_str() << std::endl;

    s2[7] = 'W';  // 修改 s2，触发深拷贝

    std::cout << "After modification:" << std::endl;
    std::cout << "s1: " << s1.c_str() << std::endl;
    std::cout << "s2: " << s2.c_str() << std::endl;

    return 0;
}
    */
   // 总结:
   /*
    写时拷贝是一种高效的优化技术，可以通过延迟深拷贝来减少内存使用和提升性能。在实现写时拷贝时，需要仔细管理 引用计数 和深拷贝 的逻辑，以确保资源的正确分配和释放。
   */
```