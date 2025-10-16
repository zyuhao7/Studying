#include <iostream>
using namespace std;

// day-2025-10-16
// 第五章 泛化仿函数
template <typename R, class TList>
class Functor
{
public:
    template <class Fun>
    Functor(const Fun &fun);
};

class Parrot
{
public:
    void Eat()
    {
        cout << "Tsk, knick, tsk ..." << endl;
    }
    void Speak()
    {
        cout << "Oh Captain, my Captain! " << endl;
    }
};

int main()
{
    typedef void (Parrot::*tpMemFun)();
    tpMemFun memFun = &Parrot::Eat;

    Parrot geronimo;
    Parrot *pGeronimo = &geronimo;

    (geronimo.*memFun)();
    (pGeronimo->*memFun)();

    memFun = &Parrot::Speak;
    (geronimo.*memFun)();
}