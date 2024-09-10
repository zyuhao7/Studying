#include <iostream>
#include <cstdarg>
#include <memory>
#include <functional>

// C 语言风格不定参.
// void printNum(int n, ...)
// {
//     va_list al;
//     va_start(al, n); // 让al指向n参数之后的第⼀个可变参数
//     for (int i = 0; i < n; i++)
//     {
//         int num = va_arg(al, int); // 从可变参数中取出⼀个整形参数
//         std::cout << num << std::endl;
//     }
//     va_end(al); // 清空可变参数列表--其实是将al置空
// }

// int main()
// {
//     printNum(3, 1, 2, 3);
//     printNum(5, 44, 55, 66, 77, 88);
//     return 0;
// }

// void myprintf(const char *fmt, ...)
// {
//     // int vasprintf(char **strp, const char *fmt, va_list ap);

//     char *res;
//     va_list al;
//     va_start(al, fmt);
//     int len = vasprintf(&res, fmt, al);
//     va_end(al);
//     std::cout << res << std::endl;
//     free(res);
// }

// int main()
// {
//     myprintf("%s 的年龄为: %d 岁", "张三", 8);
//     return 0;
// }

// C++⻛格不定参函数

// void xprintf()
// {
//     std::cout << std::endl;
// }

// template <typename T, typename... Args>
// void xprintf(const T &value, Args &&...args)
// {
//     std::cout << value << " ";
//     if ((sizeof...(args)) > 0)
//     {
//         xprintf(std::forward<Args>(args)...);
//     }
//     else
//     {
//         xprintf();
//     }
// }

// int main()
// {
//     xprintf("沫羽皓");
//     xprintf("沫羽皓", 666);
//     xprintf("沫羽皓", "牛逼", 666);
//     return 0;
// }
