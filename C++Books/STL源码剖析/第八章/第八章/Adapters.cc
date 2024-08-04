#include <iostream>
#include <functional>
#include <queue>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;
//  配接器 adapter
#if 0
int main()
{
    ostream_iterator<int> outite(cout, " ");

    int ia[] = {0, 1, 2, 3, 4, 5};
    deque<int> id(ia, ia + 6);

    copy(id.begin(), id.end(), outite); // 0 1 2 3 4 5
    cout << endl;

    copy(ia + 1, ia + 2, front_inserter(id));
    copy(id.begin(), id.end(), outite); // 1 0 1 2 3 4 5
    cout << endl;

    copy(ia + 3, ia + 4, back_inserter(id));
    copy(id.begin(), id.end(), outite); // 1 0 1 2 3 4 5 3
    cout << endl;

    deque<int>::iterator ite = find(id.begin(), id.end(), 5);
    copy(ia, ia + 3, inserter(id, ite));
    copy(id.begin(), id.end(), outite); // 1 0 1 2 3 4 0 1 2 5 3
    cout << endl;

    copy(id.rbegin(), id.rend(), outite); // 3 5 2 1 0 4 3 2 1 0 1
    cout << endl;

    return 0;
}
#endif

#if 0
int main()
{
    ostream_iterator<int> outite(cout, " ");

    int ia[6] = {2, 21, 12, 7, 19, 23};
    vector<int> iv(ia, ia + 6);

    // 想对每个元素 v 执行 (v + 2) * 3
    // for_each() 是 Immutable algorithm, 元素内容不能更改.
    // 所以执行之后 iv 内容不变.

    // for_each(iv.begin(), iv.end(), compose1(bind2nd(multiplies<int>(), 3), bind2nd(plus<int>(), 2)));

    copy(iv.begin(), iv.end(), outite); // 2 21 12 7 19 23
    cout << endl;

    // transform(iv.begin(), iv.end(), outite, compose1(bind2nd(multiplies<int>(), 3), bind2nd(plus<int>(), 2)));

    return 0;
}
#endif

void print(int i)
{
    cout << i << " ";
}

class Int
{
public:
    explicit Int(int i)
        : m_i(i)
    {
    }

    void print1() const
    {
        cout << "[" << m_i << "]";
    }

private:
    int m_i;
};

#if 0
int main()
{
    ostream_iterator<int> outite(cout, " ");
    int ia[6] = {2, 21, 12, 7, 19, 23};
    vector<int> iv(ia, ia + 6);

    // 找出不小于 12 的元素个数.
    cout << count_if(iv.begin(), iv.end(), not1(bind2nd(less<int>(), 12))); // 12
    cout << endl;

    // 将下列所有元素拷贝到 outite, 有很多方法.
    copy(iv.begin(), iv.end(), outite); // 2 21 12 7 19 23
    cout << endl;

    for_each(iv.begin(), iv.end(), print); // 2 21 12 7 19 23
    cout << endl;

    for_each(iv.begin(), iv.end(), ptr_fun(print)); // 2 21 12 7 19 23
    cout << endl;

    Int t1(3), t2(7), t3(20), t4(14), t5(68);

    vector<Int> Iv;
    Iv.push_back(t1);
    Iv.push_back(t2);
    Iv.push_back(t3);
    Iv.push_back(t4);
    Iv.push_back(t5);

    for_each(Iv.begin(), Iv.end(), mem_fun_ref(&Int::print1)); // [3][7][20][14][68]
}
#endif

#if 0
#include <deque>
//  container adapters

int main()
{
    int ia[] = {1, 0, 1, 2, 3, 4, 0, 1, 2, 5, 3};
    deque<int> id(ia, ia + 11);

    deque<int>::reverse_iterator rite(id.end());
    cout << *(rite) << endl; // 3

    cout << *(++ ++ ++rite) << endl; // 1

    cout << *(--rite) << endl; // 2

    cout << *(rite.base()) << endl; // 5

    cout << rite[3] << endl; // 4
    return 0;
    
}
#endif

class Shape
{
public:
    virtual void display() = 0;
};

class Rect : public Shape
{
public:
    virtual void display()
    {
        cout << "Rect ";
    }
};

class Circle : public Shape
{
public:
    virtual void display()
    {
        cout << "Circle ";
    }
};

class Square : public Shape
{
public:
    virtual void display()
    {
        cout << "Square ";
    }
};

int main()
{
    vector<Shape *> V;
    V.push_back(new Rect);
    V.push_back(new Circle);
    V.push_back(new Square);
    V.push_back(new Circle);
    V.push_back(new Rect);

    // 多态.
    for (int i = 0; i < V.size(); ++i)
    {
        V[i]->display(); // Rect Circle Square Circle Rect
    }
    cout << endl;

    for_each(V.begin(), V.end(), mem_fun(&Shape::display)); // // Rect Circle Square Circle Rect
    cout << endl;

    // for_each(V.begin(), V.end(), &Shape::display); // err
    // for_each(V.begin(), V.end(), Shape::display);  // err
}