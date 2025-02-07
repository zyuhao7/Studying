#include <iostream>
#include <cstddef>

using namespace std;

// day-2025-2-7
//  memcpy函数模拟实现

// 不考虑内存重叠
// void *my_memcpy(void *dest, const void *src, size_t n)
// {
//     if (!dest || !src)
//         return nullptr;
//     char *d = (char *)dest;
//     char *s = (char *)src;
//     while (n--)
//     {
//         *dest++ = *src++;
//     }
//     return d;
// }

// 考虑内存重叠
void *my_memcpy(void *dest, const void *src, size_t n)
{
    if (!dest || !src)
        return nullptr;
    char *d = (char *)dest;
    char *s = (char *)src;
    //   [dest] [src] 或者 [src][dest] 前面或者后面
    if (d < s || d >= s + n)
    {
        while (n--)
        {
            *d++ = *s++;
        }
    }
    // [src  dest[   ]   // 在 src 内, 从后往前复制.
    else
    {
        d = d + n - 1;
        s = s + n - 1;
        while (n--)
        {
            *d-- = *s--;
        }
    }
    return dest;
}

int main()
{
    char src[] = "hello world";
    char dest[20];
    my_memcpy(dest, src, 5);
    cout << dest << endl;
    return 0;
}
