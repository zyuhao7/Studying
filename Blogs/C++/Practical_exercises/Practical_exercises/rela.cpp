/* ������������(��Ҫ).cpp */
#include <iostream>
using namespace std;

#if 0
class A {
	int a;

public:
	void setA(int x) { a = x; }
	int getA() { return a; }
};
class B : public A {
	int b;

public:
	void setB(int x) { b = x; }
	int getB() { return b; }
};
void f1(A a, int x) { a.setA(x); }
void f2(A* pA, int x) { pA->setA(x); }
void f3(A& rA, int x) { rA.setA(x); }

int main()
{
	A a1, * pA;	
	B b1;

	a1.setA(1);
	b1.setA(2);

	//�����������ֵ���������
	a1 = b1;
	cout << a1.getA() << endl;
	cout << b1.getA() << endl; // 2 2

	a1.setA(10);
	cout << a1.getA() << endl;
	cout << b1.getA() << endl;//10 2

	//�����������ĵ�ַ��ֵ������ָ�롣                     pA->  20 B 20 <- b1
	pA = &b1;
	pA->setA(20);
	cout << pA->getA() << endl;
	cout << b1.getA() << endl; // 20 20

	//������������ʼ�������������á�
	A& ra = b1; // 20
	ra.setA(30);                  // 30
	cout << pA->getA() << endl;   // 30
	cout << b1.getA() << endl;    // 30

	b1.setA(7);
	cout << b1.getA() << endl;   //7
	f1(b1, 100);       
	cout << "1111111111" << endl;

	cout << b1.getA() << endl;
	f2(&b1, 200);

	cout << b1.getA() << endl;
	f3(b1, 300);

	cout << b1.getA() << endl;


	return 0;
}

#endif