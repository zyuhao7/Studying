#ifndef __CURRENCY__
#define __CURRENCY__
#include <iostream>
#include <string>
using namespace std;

class illegalParameterValue
{
public:
    illegalParameterValue()
        : message("Illegal parameter value")
        {}
    illegalParameterValue(char* msg)
    {
        message = msg;
    }
    void outputMessage()
    {
        cout << message << endl;
    }

private:
    string message;
};

enum signType
{
    positive,
    negative
};
// 货币.
class currency
{
public:
    currency(signType theSign = positive,
             unsigned long theDollars = 0,
             unsigned int theCents = 0);

    ~currency() {}
    void setValue(signType, unsigned long, unsigned int);
    void setValue(double);
    signType getSign() const { return sign; }
    unsigned long getDollars() const { return dollars; }
    unsigned int getCents() const { return cents; }
    currency add(const currency &) const;
    currency &increment(const currency &);
    void output() const;

private:
    signType sign;         // 对象的符号
    unsigned long dollars; // 美元的数量
    unsigned int cents;    // 美分的数量
};

currency::currency(signType theSign, unsigned long theDollars, unsigned int theCents)
{
    // 创建一个 currency 对象
    setValue(theSign, theDollars, theCents);
}
void currency::setValue(signType theSign, unsigned long theDollars, unsigned int theCents)
{
    if (theCents >= 99)
    {
        cout << "Cents should be < 100" << endl;
    }
    sign = theSign;
    dollars = theDollars;
    cents = theCents;
}

void currency::setValue(double theAmount)
{
    if (theAmount < 0)
    {
        sign = negative;
        theAmount = -theAmount;
    }
    else
        sign = positive;

    dollars = (unsigned long)theAmount;
    cents = ((theAmount + 0.001 - dollars) * 100);
}

currency currency::add(const currency &x) const
{
    // 把 x 和 *this 相加.
    long a1, a2, a3;
    currency result;

    // 把调用对象转化为符号整数
    a1 = dollars * 100 + cents;
    if (sign == negative)
        a1 = -a1;

    // 把 x 转化为符号整数
    a2 = x.dollars * 100 + x.cents;
    if (x.sign == negative)
        a2 = -a2;

    a3 = a1 + a2;

    // 转换为 currency 对象的表达式
    if (a3 < 0)
    {
        result.sign = negative;
        a3 = -a3;
    }
    else
        result.sign = positive;
    result.dollars = a3 / 100;
    result.cents = a3 - result.dollars * 100;

    return result;
}

currency &currency::increment(const currency &x)
{
    // 增加 x
    (*this) = add(x);
    return *this;
}

void currency::output() const
{
    // 输出负号
    if (sign == negative)
        cout << '-';
    // 美元负号.
    cout << '$' << dollars << '.';
    // 前导 0
    if (cents < 10)
        cout << '0';

    cout << cents;
}
#endif