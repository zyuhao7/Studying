#include <iostream>
using namespace std;

// day-2025-2-7
// 求 根号2

// 1. 二分
double sqrt2_binary_search(double epsilon = 1e-8)
{
    double l = 1.0, r = 2.0;
    while (r - l > epsilon)
    {
        double m = (l + r) / 2;
        if (m * m > 2)
            r = m;
        else
            l = m;
    }
    return l;
}

// 2. 牛顿迭代
double sqrt2_newton(double epsilon = 1e-8)
{
    double x = 1.0;
    while (true)
    {
        double nx = 0.5 * (x + 2 / x);
        cout << nx << " ";
        if (abs(x - nx) < epsilon)
            break;
        x = nx;
    }
    return x;
}

int main()
{
    cout << sqrt2_binary_search() << endl;
    cout << sqrt2_newton() << endl;
    return 0;
}