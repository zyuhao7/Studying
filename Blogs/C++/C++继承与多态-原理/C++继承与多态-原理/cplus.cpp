#include<iostream>
#include<string>
using namespace std;

#if 0
// 
// A�ǻ���
class A
{
public:
	int ma;
protected:
	int mb;
private:
	int mc;
};
// B�������࣬�̳е�����������ĳ�Ա�����޶�ҪС�ڵ��ڼ̳з�ʽ
class B : public A
{
public:
	int md;
protected:
	int me;
private:
	int mf;
};

// �����private˽�г�Ա�����۲���ʲô�̳з�ʽ�������������涼�ǿ��Լ̳������������޷�����
// protected��private�����𡣻����private˽�г�Ա������������ⲿ������ֱ�ӷ��ʣ�
//                           �����protected�ĳ�Ա�������������ǿ��Է��ʵģ����ⲿ���ܷ��ʡ�

class Base
{
public:
	Base(int data) :ma(data) { cout << "Base()" << endl; }
	~Base() { cout << "~Base()" << endl; }
protected:
	int ma;
};
class Derive : public Base
{
public:
	// ����ͨ�����û���Ĺ��캯������ʼ���ӻ���̳����ĳ�Ա
	Derive(int data) :Base(data) { cout << "Derive()" << endl; }
	~Derive() { cout << "~Derive()" << endl; }
private:
	int mb;
};
int main()
{
	Derive d(10);
	return 0;
}

//                                   ���ء����ء�����

class Base
{
public:
	Base(int data) :ma(data) { cout << "Base()" << endl; }
	~Base() { cout << "~Base()" << endl; }

	void show() { cout << "Base::show()" << endl; } // @1
	void show(int) { cout << "Base::show(int)" << endl; } // @2
protected:
	int ma;
};
class Derive : public Base
{
public:
	Derive(int data) :Base(data) { cout << "Derive()" << endl; }
	~Derive() { cout << "~Derive()" << endl; }
	void show() { cout << "Derive::show()" << endl; } // @3

private:
	int mb;
};
int main()
{
	Derive d(10);
	d.show();        // ���õ����������Լ���show����
	d.Base::show();  // ָ���������򣬵��õ���������ӻ���̳�����show����
	//d.show(10);    // ������󣬲��ܵ��ã��������show�����ѻ���̳�����show������������
	return 0; 
}

// ����: һ�麯��������ͳһ��������,��������ͬ, �����б�ͬ,���ܳ�����������, @1 �� @2 �Ǻ�������. @2 @3��Ȼ��������ͬ, �����б�ͬ,
// �����ǲ���ͬһ��������, �������ع�ϵ.

// ����: ָ���ǻ�����������е�ͬ����Ա, ֻҪ��Ա������ͬ, �������������øó�Ա����ʱ,�ͷ���������(�����˻����ͬ����Ա), ������Ĭ��
//���õĶ����Լ��ĳ�Ա, ���Ҫ���û����ͬ������, ��Ҫ��ӻ����������, ��������� @1 �� @3, @2 �� @3 �������ع�ϵ.

// ����: ָ���ǻ�����������е�ͬ����Ա����, ������������ͬ�� ����ֵ��ͬ�� �����б�Ҳ��ͬ, ���һ���ĸú����� virtual �麯��, ��ô������
//��ͬ�������Զ���������麯��, ����֮��Ĺ�ϵ�Ǹ��ǹ�ϵ. ���������û�и��ǹ�ϵ�ĺ���.




//										�麯����vfptr��vftable



class Base
{
public:
	Base(int data) :ma(data) { cout << "Base()" << endl; }
	~Base() { cout << "~Base()" << endl; }
	// �������show()�������麯��
	virtual void show() { cout << "Base::show()" << endl; } // @1
	// �������show(int)�������麯��
	virtual void show(int) { cout << "Base::show(int)" << endl; } // @2
	// �������show(int, int)��������ͨ����
	void show(int, int) { cout << "Base::show(int, int)" << endl; }
protected:
	int ma;
};
class Derive : public Base
{
public:
	Derive(int data) :Base(data) { cout << "Derive()" << endl; }
	~Derive() { cout << "~Derive()" << endl; }
	void show() { cout << "Derive::show()" << endl; } // @3 // ��1 ���ɸ���.
private:
	int mb;
};

// ���� Base�������麯��, ����������ô����?
// �������һ����: ���һ�������麯��, ��ô�������ڱ���׶�, �����ǰ��������һ���麯����,�麯��������ŵ����麯���ĵ�ַ, ���� RTTIָ��
//��Ϣ; �����麯�����ڴ������н׶�, �����ص�.rodata��, Ҳ����˵ֻ����д, �����麯������� vftable.



//											��̬�󶨺Ͷ�̬��

//��̬��: ����ʱ�ں����ĵ��þ���ȷ����.
//��̬��: �����ĵ���Ҫ������ʱ�ڲ���ȷ��.

class Base
{
public:
	Base(int data) :ma(data) { cout << "Base()" << endl; }
	~Base() { cout << "~Base()" << endl; }
	// �������show()�������麯����Ϊ����ʾ��̬��
	virtual void show() { cout << "Base::show()" << endl; }
	// �������show(int, int)��������ͨ������Ϊ����ʾ��̬��
	void show(int, int) { cout << "Base::show(int, int)" << endl; }
protected:
	int ma;
};
class Derive : public Base
{
public:
	Derive(int data) :Base(data) { cout << "Derive()" << endl; }
	~Derive() { cout << "~Derive()" << endl; }
	void show() { cout << "Derive::show()" << endl; }
private:
	int mb;
};
int main()
{
	Derive d(10);
	Base* p = &d;
	/*
	  ����p��������Base��Base�µ�show(int,int)����ͨ�����������Ǿ�̬�󶨣�
	  ���Ǳ���׶ξ�ȷ���ˣ����õ���Base::show(int, int)����������ͨ����
	  ���ָ��鿴��call Base::show...
	*/
	p->show(0, 0);
	/*
	  ����p��������Base��Base�µ�show()���麯���������Ƕ�̬�󶨣���ָ������
	  ����pָ��Ķ����ǰ4���ֽ�vfptr���ٷ��ʶ�Ӧ��vftable��Ȼ���vftable
	  ��ȡ�麯���ĵ�ַ���к������ã�ֻ�������е�ʱ�򣬲���ȡ���麯�����д�ŵ�
	  ������ַ�����������ʱ�İ󶨣�������̬������
	*/
	p->show();

	cout << sizeof(Base) << endl; // 8
	cout << sizeof(Derive) << endl; //  12
	/*
	  ����p��������Base����ΪBase�������麯��������*pʶ��ľ���RTTI���ͣ�ʶ��RTTI
	  ����Ҳ��ͨ��ָ����ʶ����ڴ��vfptr���ٷ���vftable��ͨ��RTTIָ��ȡRTTI������Ϣ����
	  ���p������Base����û���麯������ô*pʶ��ľ��Ǳ���ʱ�ڵ����͡�
	*/
	cout << typeid(*p).name() << endl; // class Derive

	return 0;
}


//													��̬
/* ��ָ̬����, �û���ָ�������ָ������̳е�һ�����������, �����������ͬ�����Ƿ���, ����ָ��ָ���ĸ����������, �ͻ����
* ��Ӧ����������ͬ�����Ƿ���. ��ô��������? ��Ϊͨ������ָ������������ͬ�����Ƿ���ʱ, �����˶�̬��, �����˻���ָ��ָ��
* ������麯���� vftable, ������ vftable ��ȡ�����ľ��������������д���麯���ĵ�ַ, Ȼ����е���, �Ϳ��������˻���ָ��ָ��
* ˭, ���ܵ���˭�ķ���.
*/


//														������
class Animal
{
public:
	Animal(string name)
		:_name(name){}

	virtual void bark() = 0; // ���麯��.
protected:
	string _name;
};

// Animal��һ��������, �����಻�ܶ������, ���ǿ��Զ���ָ���������, һ��ѻ���������Ƴɳ�����, ��Ϊ�������ĳ���,������
// Ϊ���ó���ĳ��ʵ�������. ԭ������:
// 1. ����������������ṩ���������Ժͷ���, ͨ���̳дﵽ���븴�õ�Ŀ��.
// 2. ������Ը������������ṩͳһ�Ĵ��麯���ӿ�, ������ͨ��������д, �ﵽ��̬���õ�Ŀ��.


//													����������

class Base // ���ඨ��
{
public:
	Base(int data=10):_ptrb(new int(data))
	{ cout << "Base()" << endl; }
	// ��Ϊvirtual ��������. 
	virtual ~Base() { delete _ptrb; cout << "~Base()" << endl; }
protected:
	int *_ptrb;
};
class Derive : public Base // �����ඨ��
{
public:
	Derive(int data=20):Base(data), _ptrd(new int(20))
	{ cout << "Derive()" << endl; }
	~Derive() { delete _ptrd; cout << "~Derive()" << endl; }
private:
	int *_ptrd;
};
int main()
{
	Base *p = new Derive();
	delete p; // ֻ������Base������������û�е���Derive���������������
	return 0;
}
#endif
