#include <iostream>
#include <set>
using namespace std;

// 取样问题
// 从 0 ~ n - 1 中生成 m 个 有序整数.
void genknuth(int m, int n)
{
    // select m of remaining n - i
    if (bingrand() % (n - i) < m)
    {
        cout << i << endl;
        m--;
    }
}

void gensets(int m, int n)
{
    set<int> S;
    while (S.size() < m)
    {
        S.insert(Bigrand() % n);
    }
    set<int>;:iterator it;
    for (it = S.begin(); it != S.end(); ++it)
        cout << *it << endl;
}

void genshuf(int m, int n)
{
    int i, j;
    int *x = new int[n];
    for (int i = 0; i < n; ++i)
        x[i] = i;
    for (int i = 0; i <= m; ++i)
    {
        j = randint(i, n - 1);
        int t = x[i];
        x[i] = x[j];
        x[j] = t;
    }
    sort(x, x + m);
    for (int i = 0; i < m; ++i)
    {
        cout << x[i] << endl;
    }
}

int main()
{

    return 0;
}