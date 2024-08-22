#include <stdio.h>
#include <string.h>
// auto 关键字 伟大! 无需多言!

// register 关键字
// 请求编译器尽可能将变量存在 CPU 内部寄存器中, 而不是通过内存寻址访问以提高效率.
// 长度小于等于整型的长度, 而且 register 变量可能不放在内存中, 因此不能用取址运算符 "&" 来获取 register 变量的地址.

// static 关键字
// 1. 修饰变量, 变量分为局部变量和全局变量, 但它们都在内存的静态区.
// 静态全局变量, 作用域仅限于变量被定义的文件中, 其他文件即使使用 extern 声明也没法使用它.
// 静态局部变量, 在函数体里定义的, 只能在这个函数里用, 同一个文档中的其他函数用不了,  由于被 static 修饰的变量总是存在内存的静态区, 所以即使这个函数运行结束,
// 这个静态变量的值也不会摧毁, 函数下次使用时仍然能用到这个值...

#if 0
static int j;
void func1()
{
    static int i = 0;
    i++;
    printf("i = %d \n", i); // 1 2 3 4 ... 10
}

void func2()
{
    j = 0;
    j++;
}

int main()
{
    int k = 0;
    for (k = 0; k < 10; ++k)
    {
        func1();
        func2();
        if (k == 9)
        {
            printf("j = %d \n", j); //  j = 1
        }
    }
    return 0;
}
#endif

// 2. 修饰函数
//  函数前面加 static 使得函数成为静态函数. 此处 "static"的含义不是指存储方式, 而是指对函数的作用域仅限于本文件(又称内部函数).
//  使用内部函数的好处是, 不同的人编写不同的函数时, 不用担心自己定义的函数是否与其他文件中的函数同名.

// 基本数据类型  -- short、 int、 long、 char、 float、 double

// sizeof 关键字

#if 0
void func(int b[100])
{
    printf("sizeof(b) = %d\n", sizeof(b));
}

int main()
{
    int *p = NULL;

    printf("sizeof(p) = %d\n", sizeof(p));   // 8
    printf("sizeof(*p) = %d\n", sizeof(*p)); // 4

    int a[100];
    printf("sizeof(a) = %d \n", sizeof(a)); // 400

    printf("sizeof(a[100]) = %d \n", sizeof(a[100])); // 4

    printf("sizeof(&a) = %d \n", sizeof(&a)); // 8

    printf("sizeof(&a[0]) = %d \n", sizeof(&a[0])); // 4 首元素地址就是数组地址啊, 地址是指针, 指针就是 8 啊. 怎么糊涂了..

    func(a); // 8

    return 0;
}
#endif

// signed、 unsigned 关键字

#if 0
int main()
{
    signed char a[1000];
    int i;
    for (i = 0; i < 1000; ++i)
    {
        a[i] = -1 - i;
    }
    printf("%d \n", strlen(a));

    int i = -20;
    unsigned j = 10;
    printf("%u \n", i + j);

    unsigned k;
    for (k = 9; k >= 0; k--)
    {
        printf("%u \n", k);
    }
}
#endif

// do、 while、 for 关键字
// goto 关键字
// void 关键字
// 修饰函数返回值和参数
// return 关键字
// const关键字
// 编译器通常不为普通 const 只读变量分配存储空间, 而是将它们保存在符号表中, 这使得它成为一个编译期间的值.

// 2024-8-22
// struct

// struct student
// {
// } stu;

// int main()
// {
//     printf("%d \n", sizeof(stu)); // 1
//     return 0;
// }
#include <memory>

// 柔性数组
// typedef struct st_type
// {
//     int i;
//     int a[];
// } type_a;

// int main()
// {
//     printf("%d \n", sizeof(type_a)); // 4

//     type_a *p = (type_a *)malloc(sizeof(type_a) + sizeof(int) * 100);

//     free(p);
// }

// struct 和 class 的区别
// struct 默认属性是 public, class 是 private

// union

// union
// {
//     int i;
//     char a[2];
// } *p, u;

// void checkSystem()
// {
//     union check
//     {
//         int i;
//         char ch;
//     } c;
//     c.i = 1;
//     if (c.ch == 1)
//     {
//         printf("1");
//         printf("小端 \n");
//     }
//     else
//     {
//         printf("2");
//         printf("大端 \n");
//     }
// };

// int main()
// {
//     p = &u;
//     p->a[0] = 0x39;
//     p->a[1] = 0x38;
//     printf("%0x \n", p->i); // 3839
//     checkSystem();          // 小端.
//     printf("%d \n", sizeof(int *));
// }

// int main()
// {
//     printf("%d \n", sizeof(int *));
//     int a[5] = {1, 2, 3, 4, 5};
//     int *ptr1 = (int *)(&a + 1);
//     int *ptr2 = (int *)((int)a + 1);
//     printf("%x %x \n", ptr1[-1], *ptr2); // 5 2000000
// }

// typedef 