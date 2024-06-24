#include <iostream>
#include <string>
#include <cassert>
#include <string.h>
#include <algorithm>
#include <utility>
using namespace std;
// 传统版本的 String 写法.
#if 0
class String
{
public:
    String(const char *str = "")
    {
        if (str == nullptr) // nullptr == str
        {
            assert(false);
            return;
        }
        _str = new char[strlen(str) + 1];
        strcpy(_str, str);
    }

    String(const String &str)
        : _str(new char[strlen(str._str) + 1])
    {
        strcpy(_str, str._str);
    }

    String &operator=(const String &str)
    {
        if (this != &str)
        {
            char *Pstr = new char[strlen(str._str) + 1];
            strcpy(Pstr, str._str);
            delete _str;
            _str = Pstr;
        }
        return *this;
    }

    ~String()
    {
        if (_str)
        {
            delete _str;
            _str = nullptr;
        }
    }

private:
    char *_str;
};

#endif

#if 1
// 现代版本 String 写法.
class String
{
public:
    String(const char *str = "")
    {
        if (str == nullptr)
        {
            assert(false);
            return;
        }
        _str = new char[strlen(str) + 1];
        strcpy(_str, str);
    }

    String(const String &str)
        : _str(nullptr)
    {
        String strTemp(str);
        swap(_str, strTemp._str);
    }

    String &operator=(String str)
    {
        swap(_str, str._str);
        return *this;
    }

    ~String()
    {
        if (_str)
        {
            delete _str;
            _str = nullptr;
        }
    }

private:
    char *_str;
};

#endif

int main()
{
    // String s1;
    // String s2("hello world!");
    // String s3(s2);
}


