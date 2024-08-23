#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*
int main()
{
#if 0
    printf("for test1\n"); // test1
    printf("for test2\n"); // test2
#endif

    if (0) // 不推荐, 严重影响视觉和代码运行期间处理.
    {
        printf("for test1\n"); // test1
        printf("for test2\n"); // test2
    }

    printf("%d \n", sizeof(1));   // 4
    printf("%d \n", sizeof("1")); // 2

    printf("%d \n", sizeof('1')); // 4  整型字符常量, 被看作是 int型
    char c = '1';
    printf("%d \n", sizeof(c)); // 1

    printf("%d\n", sizeof("")); // 1

    return 0;
}
*/

/*
int main()
{
    int i = 0;
    int j = 0;
    if ((++i < 0) && (++j > 0))
    {

        printf("enter if!\n");
    }
    printf("%d, %d\n", i, j); // 1, 0

    char c = 0;
    printf("sizeof(c): %d\n", sizeof(c));      // 1
    printf("sizeof(c): %d\n", sizeof(~c));     // 4
    printf("sizeof(c): %d\n", sizeof(c << 1)); // 4
    printf("sizeof(c): %d\n", sizeof(c >> 1)); // 4

    return 0;
}
*/

/*
int main()
{

    // 左移

    unsigned int a = 1;
    printf("%u\n", a << 1); // 2
    printf("%u\n", a << 2); // 4
    printf("%u\n", a << 3); // 8

    // 逻辑右移
    unsigned int b = 100;
    printf("%u\n", b >> 1); // 50
    printf("%u\n", b >> 2); // 25
    printf("%u\n", b >> 3); // 12

    // 算术右移，最高位补符号位1， 虽然移出了最低位1，但是补得还是1
    int c = -1;
    printf("%d\n", c >> 1); // -1
    printf("%d\n", c >> 2); // -1
    printf("%d\n", c >> 3); // -1

    // 是算术右移，还是逻辑右移?
    unsigned int d = -1;
    printf("%d\n", d >> 1); // 21亿
    printf("%d\n", d >> 2); // 10亿
    printf("%d\n", d >> 3);
    return 0;
}
*/

/*
int main()
{
    printf("%d \n", 0x01 << 2 + 3);   // 32
    printf("%d \n", 0x01 << (2 + 3)); // 32
    printf("%d \n", (0x01 << 2) + 3); // 7

    char a[] = {"abcde"};
    printf("%d\n", sizeof(a)); // 6

    char b[10] = {"abcde"};
    printf("%d\n", sizeof(b)); // 10

    int i = 1;
    int j = (++i) + (++i) + (++i);
    printf("%d\n", j); // 10
    return 0;
}
*/

/*
int main()
{
    printf("%d \n", 2 / -2); // -1

    const char *format = "%.1f \t%.1f \t%.1f \t%.1f \t%.1f\n";
    printf("value\tround\tfloor\tceil\ttrunc\n");
    printf("-----\t-----\t-----\t----\t-----\n");
    printf(format, 2.3, round(2.3), floor(2.3), ceil(2.3), trunc(2.3));
    printf(format, 3.8, round(3.8), floor(3.8), ceil(3.8), trunc(3.8));
    printf(format, 5.5, round(5.5), floor(5.5), ceil(5.5), trunc(5.5));
    printf(format, -2.3, round(-2.3), floor(-2.3), ceil(-2.3), trunc(-2.3));
    printf(format, -3.8, round(-3.8), floor(-3.8), ceil(-3.8), trunc(-3.8));
    printf(format, -5.5, round(-5.5), floor(-5.5), ceil(-5.5), trunc(-5.5));

    int a = -10;
    int b = 3;

    printf("%d \n", a / b);    // -3
    printf("%d \n", a % b);    // -1
    printf("%d \n", -10 / -3); // 3
    printf("%d \n", -10 % -3); // -1

    return 0;
}
*/