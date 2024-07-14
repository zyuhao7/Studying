#include <iostream>
#include <memory>
using namespace std;
#define MEASURE(T, text)                      \
    {                                         \
        cout << text << "\t";                 \
        cout << sizeof(T) << "\t";            \
        int lastp = 0;                        \
        for (int i = 0; i < 11; ++i)          \
        {                                     \
            T *p = new T;                     \
            int thisp = (int)p;               \
            if (lastp != 0)                   \
                cout << " " << thisp - lastp; \
            lastp = thisp;                    \
        }                                     \
        cout << "\n";                         \
    }
struct structc
{
    char c;
};
int main()
{
    MEASURE(structc, "structc");
    MEASURE(int, "int");

    return 0;
}