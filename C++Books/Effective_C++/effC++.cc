#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <memory>
#include <mutex>

using namespace std;
// 《Effective C++》 second learning.
// day-2024-8-17

// 第一章 -  让自己习惯 C++

// 条款 1 视 C++ 为一个语言联邦

// 条款 2 尽量用 const、 enum、inline 替换 #define.

// 条款 3 尽可能使用 const

/*
class TextBlock
{
public:
	TextBlock(const string s)
		: text(s)
	{
	}
	const char &operator[](std ::size_t pos) const
	{
		cout << " const char &operator[](std ::size_t pos) const" << endl;
		return text[pos];
	}

	char &operator[](std::size_t pos)
	{
		cout << "  char &operator[](std::size_t pos)" << endl;
		return text[pos];
	}

private:
	std::string text;
};

int main()
{
	TextBlock tb("hello");
	std::cout << tb[0]; //  non-const []
	tb[0] = 'x'; // ok!

	const TextBlock ctb("world");
	std::cout << ctb[0]; // const []
	ctb[0] = 'x'; // err!
}
*/

// 条款 4  确定对象被使用前已被初始化

/*
 * 为内置型对象进行手工初始化, 因为C++不保证初始化它们.
 * 构造函数最好使用初始化列表, 而不要在构造函数本体内使用赋值操作.初始列列出的成员变量,其排列次序应该和它们在class中的声明次序相同.
 * 为免除 "跨编译单元之初始化次序"问题, 以 local static 对象替换 non-local static 对象.
 */

// day-2024-8-18

// 第二章 -   构造/析构/赋值运算

// 条款 5 了解C++ 默默编写并调用哪些函数
class Empty
{
};

// 编译器默认声明空类的操作.
// class Empty
// {
// public:
// 	Empty() {}
// 	Empty(const Empty &rhs) {}
// 	~Empty() {}
// 	Empty &operator=(const Empty &rhs) {}
// }
// 编译器可以暗自为 class 创建 default 构造函数、 copy构造函数、 copy assignment操作符, 以及析构函数.

// 条款 6 若不想使用编译器自动生成的函数, 就该明确拒绝
class Uncopyable
{
protected:
	Uncopyable() {} // 允许 derived 对象构造和析构.
	~Uncopyable() {}

private:
	Uncopyable(const Uncopyable &); // 但阻止 copying.
	Uncopyable &operator=(const Uncopyable &);
};

// 为驳回编译器自动提供的机能, 可将相应的成员函数声明为 private 并且不实现.

// 条款 7 为多态基类声明 virtual 析构函数.
/*
 * polymorphic base classes 应该声明一个 virtual 析构函数. 如果class 带有任何 virtual 函数, 它就应该拥有一个virtual 析构函数.
 * classes 的设计目的如果不是作为 base classes使用, 或不是为了具备多态性, 就不该声明 virtual 析构函数.
 */

// 条款 8 别让异常逃离析构函数

/*
 * 析构函数绝对不要吐出异常. 如果一个被析构函数调用的函数可能抛出异常, 析构函数应该捕捉任何异常, 然后吞下它们或结束程序.
 * 如果客户需要对某个操作函数运行期间抛出的异常做出反应, 那么class 应该提供一个普通函数执行该操作.
 */

// 条款 9 绝不在构造和析构过程调用 virtual 函数.

// 在构造和析构期间不要调用 virtual 函数, 因为这类调用从不下降至 derived class.

// day-2024-8-20

// 条款 10 令 operator= 返回一个 reference to *this

// 令 赋值(assignment) 操作符返回一个 reference to *this.

// 条款 11 在 operator= 中处理 "自我赋值"

#if 0
class Bitmap{};
class Widget {
private:
	Bitmap* pb;
	void Swap( Widget& rhs);
	Widget& operator=(const Widget& rhs);
};

Widget& Widget::operator=(const Widget& rhs) // 一份不安全的 operator= 实现版本.
{
	delete pb;
	pb = new Bitmap(*rhs.pb);               // 无法避免自我复制造得成内存泄漏.
	return *this;
}

Widget& Widget::operator=(const Widget& rhs)
{
	if (this == *rhs) return *this;      // 如果是自我赋值, 就不做任何事情. 异常方面有问题.
	delete pb;
	pb = new Bitmap(*rhs.pb);
	return *this;
}
Widget& Widget::operator=(const Widget& rhs)
{
	Bitmap* pOrig = pb;
	pb = new Bitmap(*rhs.pb);  	       	  // 效率低
	delete pOrig;
	return *this;
}
Widget& Widget::operator=(const Widget& rhs)
{
	Widget tmp(rhs);
	Swap(tmp);
	return *this;
}

Widget& Widget::operator=( Widget rhs)
{
	Swap(rhs);
	return *this;                // 牺牲清晰性
}
#endif

/*
 * 确保当对象自我赋值时 operator= 有良好行为. 其中技术包括比较 "来源对象" 和 "目标对象" 的地址、 精心周到的语句顺序、 以及 copy-and-swap.
 * 确定任何函数如果操作一个及以上的对象, 而其中多个对象是同一个对象时, 其行为任然正确.
 */

// 条款 12 复制对象时勿忘其每一个成分

/*
 *  Copying函数应该确保复制"对象内的所有成员变量" 及 "所有 base class 成分"
 * 不要尝试以某个 copying函数实现另一个copying函数. 应该将共同机能放进第三个函数中, 并有两个coping函数共同调用.
 */

//										资源管理

// 条款 13 以对象管理资源

/*
 * 为防止资源泄露, 使用 RAII 对象, 它们在构造函数中获得资源并在析构函数中释放资源.
 * 两个常被使用的  RAII classes 分别是 tr1;:shared_ptr 和 auto_ptr. 前者通常是较佳选择,因为其 copy行为比较直观.
 * 若选择 auto_ptr, 复制动作会使它指向 null.
 */

// day-2024-8-22

// 条款 14 在资源管理类中小心 coping 行为
/*
class Lock
{
	explicit Lock(mutex *pm)
		: mtx(pm)
	{
		lock(mtx);
	}

	explicit Lock(mutex* pm)
		: shared_ptx(pm, unlock)
	{
		lock(shared_ptx.get());
	}
	~Lock()
	{
		unlock(mtx);
	}

private:
	mutex *mtx;
	shared_ptr<mutex> shared_ptx;
};
*/

/*
 * 复制 RAII 对象必须一并复制它所管理的资源,所以资源的 coping行为决定 RAII 对象的coping行为.
 * 普遍而常见的 RAII class coping 行为是: 抑制 coping、施行引用计数方法. 不过其他行为也都可能被实现.
 */

// 条款 15 在资源管理类中提供对初始资源的访问
/* APIs往往要求访问原始资源, 所以每一个 RAII class 应该提供一个 "取得其资源之管理" 的方法(get).
 * 对原始资源的访问可能经由显式转换或隐式转换. 一般而言, 显示转换比较安全, 但是隐式转换对用户比较方便.
 */

// 条款 16 成对使用 new 和 delete 时要采取相同形式.
// 如果你在 new 表达式中使用[], 必须在相应的 delete 表达式中也使用 []. 如果你在 new 表达式中不使用 [], 一定不使用 delete[].

// 条款 17 以独立语句将 newed 对象置入智能指针.
// 以独立语句将 newed 对象存储于智能指针内. 如果不那样做, 一旦异常抛出, 有可能导致难以察觉的资源泄露.

// day-2024-8-23
//  			第四章 设计与声明

// 条款 18 让接口容易被正确使用, 不易被误用
/*
 *  好的接口很容易被正确使用, 不容易被误用. 你应该在你的所有接口中努力达成这些性质.
 * "促进正确使用" 的方法包括接口的一致性, 以及与内置类型的行为兼容.
 * "组织误用" 的方法包括建立新类型, 限制类型上的操作, 束缚对象值, 以及消除客户的资源管理责任.
 *  tr1::shared_ptr 支持定制型删除器, 这可防范 DLL 问题, 可被用来自动解除 互斥锁(mutexes) 等.
 */

// 条款 19 设计 class 犹如设计 type
// Class 的设计就是 type 的设计. 在定义一个新 type之前, 请确定你已经考虑过本条款覆盖的所有讨论主题.

// 条款 20 宁以 pass-by-reference-to-const 替换 pass-by-value
#if 0
class Person
{
public:
	Person()
	{
		cout << "Person()" << endl;
	}
	virtual ~Person()
	{
		cout << "~Person()" << endl;
	}

private:
	string name;
	string address;
};

class Student : public Person
{
public:
	Student() { cout << "Student()" << endl; }
	~Student() { cout << "~Student()" << endl; }
	Student(const Student &s)
	{
		cout << "Student(const Student& s)" << endl;
	}

private:
	string schoolName;
	string schoolAddress;
};

bool validateStudent(Student s)
{
	cout << "call validateStudent(Student s) succeed!" << endl;
	return true;
}

int main()
{
	Student plato;
	bool pio = validateStudent(plato);
	return 0;
}
#endif

/* 尽量以 pass-by-reference-to-const 替换 pass-by-value. 前者通常比较高效, 并可避免切割问题.
 * 以上规则并不适用于内置类型，以及 STL的迭代器和函数对象, 对它们而言 pass-by-value 往往比较适当.
 */

// 条款 21 必须返回对象时, 别妄想返回其 reference
/*
 * 绝不要返回 pointer或reference指向一个 local stack 对象, 或返回 reference指向一个 heap-allocated对象,或返回pointer 或
 * reference 指向一个 local static 对象而有可能同时需要多个这样的对象。 条款 4 已经为 "在单线程环境中合理返回 reference 指向
 * 一个 local static" 提供了一份设计实例.
 */

// day-2024-8-24

// 条款 22 将成员变量声明为 private

/*
 * 切记将成员变量声明为 private. 这可赋予客户访问数据的一致性、可细微划分访问控制、允诺约束条件获得保证, 并提供 class
 * 作者以充分的实现弹性. protected 并不比 public 更具有封装性.
 */

// 条款 23 宁以 non-member、 non-friend 替换 member 函数.
// 宁可拿 non-member non-friend 函数替换member函数. 这样做可以增加封装性、包裹弹性和技能扩充性.

// 条款 24 若所有参数皆需类型转换, 请为此采用 non-member 函数.
// 如果你需要为某个函数的所有参数(包括被this指针所指的那个隐喻参数)进行类型转换, 那么这个函数必须是个 non-member.

// 条款 25 考虑一个不抛异常的 swap 函数

#if 0
template<typename T>
void swap(T& a, T& b)
{
	T tmp(a);
	a = b;
	b = t;
}

class WidgetImpl {
public:
private:
	int a, b, c;
	vector<double> v;
};

class Widget
{
public:
	Widget(const Widget& rhs);
	Widget& operator=(const Widget& rhs)
	{
		//...
		//  *pimpl = *(rhs.pimpl);
		//...
		return *this;
	}

	void swap(Widget& other)
	{
		swap(pimpl, other.pimpl);
	}
private:
	WidgetImpl* pimpl;
};

template<>
void swap<Widget>(Widget& a, Widget& b)
{
	swap(a.pimpl, b.pimpl);
}

template<>
void swap<Widget>(Widget& a, Widget& b)
{
	a.swap(b);
}
#endif
/* 当 std::swap 对你的类型效率不高时, 提供一个 swap成员函数, 并确定这个函数不抛出异常.
 * 如果你提供一个 member swap 也该提供一个 non-member swap 用来调用前者. 对于 classes(而非 templates), 也特化 std::swap.
 * 调用 swap 时应针对 std::swap使用using声明式, 然后调用 swap 并且不带任何 "命名空间资格修饰".
 * 为 "用户定义类型" 进行 std templates 全特化是好的, 但千万不要尝试在std内加入某些对std而言全新的东西.
 */

// day-2024-8-25

// 											第五章 实现
// 条款 26 尽可能延后变量定义式的出现时间

// 尽可能延后变量定义式的出现. 这样做可以增加程序的清晰度并改善程序效率.

// 条款 27 尽量少做转型动作

//  (T) expression  将 expression 转型为 T
//   T (expression) 将 expression 转型为 T  "旧式转型"

// const_cast<T> (expression)
// 通常被用来将对象的常量性转除.

// dynamic_cast<T> (expression)
// 执行 "安全向下转型", 也就是用来决定某个对象是否归属继承体系中的某个类型.

// reinterpret_cast<T> (expression)
// 意图执行低级转型, 实际动作可能取决于编译器, 也就表示不可移植。 例如将一个 int* 转型为 int.

// static_cast<T> (expression)          "新式转型"
// 用来强迫隐式转换, 例如将 non-const 对象转为 const 对象, 或将int转为 double. 它也可以用来执行上诉多种转换的反向转换,
// 例如将 void* 转换成 typed指针, 将 基类指针 转换成 派生类指针, 但无法将 const 转为 non-const.

/* 避免转型, 特别是在注重效率的代码中避免 dynamic_casts.
 * 如果转型是必要的, 试图将它隐藏于某个函数背后. 客户随后可以调用该函数, 而不需要将转型放进它的代码内.
 * 宁可使用 C++ 新式转型, 不使用旧式类型.
 */

// 条款 28 避免返回 handlers 指向对象内部成分

/* 避免返回 handlers(包括 references、指针、迭代器)指向对象内部. 遵守这个条款可以增加封装性, 帮助 const 成员函数的行为
 * 像个const, 并将发生 "虚吊号码牌" 的可能性降到最低.
 */

// 条款 29 为 "异常安全" 而努力是值得的

/* 异常安全函数, 即使发生异常也不会泄露资源或允许任何数据结构败坏. 三种可能的保证: 基本型、强烈型、Nothrow 型.
 * " 强烈保证" 往往能够以 Copy-And-Swap 实现出来, 但 "强烈保证" 并非对所有函数都可实现或具备实现意义.
 * 函数提供的 "异常安全保证" 通常最高只等于其所调用之各个函数的 "异常安全保证" 中的最弱者.
 */

// day-2024-8-26
// 条款 30 彻底了解 "inlining" 的里里外外

/*
 * 将大多数 inlining 限制在小型、被频繁调用的函数身上. 这可使日后的调试过程和二进制升级更容易, 也可使潜在的代码膨胀问题
 * 最小化, 使程序的速度提升机会最大化.
 * 不要只因为 function templates 出现在头文件, 就将他们声明为 inline.
 */

// 条款 31 将文件件的编译依存关系降至最低

/*
 * 支持 "编译依存性最小化" 的一般构想是: 相依于声明式, 不要相依于定义式. 基于此构想的两个手段是 handle classes 和 Interface ..
 *  程序库头文件应该以 "完全且仅有声明式" 的形式存在. 这种做法不论是否涉及 templates 都适用.
 */

// 							第六章 继承与面向对象设计

// 条款 32 确定你的 public 继承塑模出 is-a 关系
/* "public 继承" 意味 is-a. 适用于 base classes 身上的每一件事情一定也适用于 derived classes 身上, 因为没一个derived class
 * 对象也是一个 base class 对象.
 */

// 条款 33 避免遮掩继承而来的名称
/* derived classes 内的名称会遮掩 base classes 内的名称. 在 public 继承下从来没有人希望如此.
 * 为了让被遮掩的名称再见天日, 可以使用 using 声明式或转交函数.
 */

// day-2024-8-27

// 条款 34 区分接口继承和实现继承
/* 接口继承和实现继承不同. 在public 继承之下, derived classes 总是继承 base class 的接口.
 * pure virtual 函数只具体指定接口继承.
 * 简朴的 impure virtual 函数具体指定接口继承以及缺省实现继承.
 * non-virtual 函数具体指定接口继承以及强制性实现继承.
 */

// 条款 35 考虑 virtual 函数以外的其他选择

/* virtual 函数的替代方案包括 NVI 手法及 Strategy 设计模式的多种形式. NVI 手法本身是一个特殊形式的 Template Method设计模式
 * 将机能从成员函数移到 class 外部函数, 带来的一个缺点是, 非成员函数无法访问无法访问 class 的 non-public成员.
 * tr1::function 对象的行为就是一般函数指针. 这样的对象可接纳 "与给定之目标签名式兼容" 的所有可调用物.
 */

// 条款 36 绝不重新定义继承而来的 non-virtual 函数.
#if 0

class B
{
public:
	virtual void mf() { cout << "B::mf()" << endl; }
};

class D : public B
{
public:
	void mf() { cout << "D::mf()" << endl; }
};

int main()
{
	// D x;
	// B *pB = &x;
	// pB->mf(); // B::mf()

	// D *pD = &x;
	// pD->mf(); // B::mf();  D 没实现 void mf()

	// D x;
	// B *pB = &x;
	// pB->mf(); // B::mf()

	// D *pD = &x;
	// pD->mf(); // D::mf(); D 实现 void mf()

	// D x;
	// B *pB = &x;
	// pB->mf(); // D::mf()

	// D *pD = &x;
	// pD->mf(); // D::mf(); B 内 为 virtual void mf()
	return 0;
}
#endif

// 绝对不要重新定义继承而来的 non-virtual 函数.

// 条款 37 绝对不重新定义继承而来的缺省参数值.
// 绝对不要重新定义一个继承而来的缺省参数值, 因为缺省参数值都是静态绑定, 而 virtual 函数 - 你唯一应该覆写的东西 - 确实动态绑定的.

// 条款 38 通过复合塑模出 has-a 或 "根据某物质实现出"
/* 复合的意义和 public 继承完全不同.
 * 在应用域, 复合意味 has-a. 在实现域, 复合意味 is-implemented-in-terms-of(根据某物实现出).
 */

// 条款 39 明智而审慎地使用 private 继承
// Private 继承意味 is-implemented-in-terms of. 它通常比复合的级别低. 但是当 derived class 需要访问 protected base class 的成员,
// 或需要重新定义继承而来的 virtual 函数时, 这么设计是合理的.
// 和复合不同, private 继承可以造成 empty base 最优化. 这对致力于 "对象尺寸最小化" 的程序库开发者而言可能很重要.

// 条款 40 明智而审慎地使用多重继承
/* 多重继承比单一继承复杂. 它可能导致新的歧义性, 以及对 virtual 继承的需要.
 * virtual 继承会增加 大小、速度、初始化复杂度等等成本. 如果 virtual base classes 不带任何数据, 将是最具有实用价值的.
 * 多重继承正当用途: 其中一个情节涉及 "public 继承某个 Interface class" 和 "private 继承某个协助实现的class" 的两项组合.
 */

//										第七章 模板与泛型编程
// 条款 41 了解隐式接口和编译期多态.
/* classes 和 templates 都支持 接口 和 多态.
 * 对 classes 而言接口是显式的, 以函数签名为中心. 多态则是通过 virtual 函数发生于运行期.
 * 对 template 参数而言, 接口是隐式的, 奠基于有效表达式. 多态则是通过 template 具现化 和 函数重载解析发生于编译期.
 */

// 条款 42 了解typename的双重意义
/* 声明 template 参数时, 前缀关键字 class 和 typename 可互换.
 * 请使用关键字 typename 标识嵌套从属类型名称; 但不得在 base class lists(基类列) 或 member init list(成员初值列)内以它作为 base class 修饰符.
 */

// 条款 43 学习处理模板化基类内的名称
// 可在 derived class templates 内通过 "this->" 指涉 base class templates内的成员名称, 或藉由一个明白写出的"base class 资格修饰符"完成.

// 条款 44 将于参数无关的代码抽离 templates
/* Templates 生成多个 classes 和 多个函数, 所以任何 template 代码都不该与某个造成膨胀的 template 参数产生相依关系.
 * 因非类型模板参数而造成的代码膨胀, 往往可消除, 做法是以函数参数或class成员变量代替template参数.
 * 因类型参数而造成的代码膨胀, 往往可降低, 做法是让带有完全相同二进制表述的具现类型共享实现码.
 */

// 条款 45 运用成员函数模板接受所有兼容类型
/* 请使用 member function templates 生成 "可接受所有兼容类型" 的函数.
 * 如果你生命 member templates 用于 "泛化 copy构造" 或 "泛化 assignment操作" 你还是需要声明正常的 copy构造函数和 copy assignment操作符.
 */

// 使用类型转换时请为模板定义非成员函数.
/* 当我们编写一个 class template, 而它所提供之 "于此template 相关的" 函数支持 "所有参数之隐式类型转换"时, 请将那些函数定义为 "class template
 * 内部的 friend函数".
 */

// 条款 47 请使用 traits classes 表现类型信息
// 为了支持指针迭代器, iterator_traits 针对指针提供了一个偏特化版本.
// template<typename IterT>
// struct iterator_traits<IterT*>
//{
//	typedef random_access_iterator_tag iterator_category;
//};
/* Traits classes使得 "类型相关信息" 在编译期可用. 它们以 templates 和 "templates特化" 完成实现.
 * 整合重载技术后, traits classes 有可能在编译期对类型执行 if...else 测试.
 */

// 条款 48 认识template 元编程

// template<unsigned n>
// class fac
//{
// public:
//	enum { val = n * fac<n - 1>::val };
// };
//
// template<>
// struct fac<0>
//{
//	enum { val = 1 };
// };
//
// int main()
//{
//	fac<5> f;
//	cout << f.val;
//	return 0;
// }

/* Template metaprogramming(TMP 模板元编程) 可将工作由运行期往编译期, 因而得以实现早期错误侦测和更高的执行效率.
 * TMP 可被用来生成 "基于政策选择组合" 的客户定制代码, 也可用来避免生成对某些特殊类型不合适的代码.
 */

//														第八章 定制 New 和 delete
//
// 条款 49 了解 new-handler 的行为
/* set_new_handler 允许客户指定一个函数, 在内存分配无法获得满足时被调用.
 * Nothrow new 是一个 颇为局限的工具, 因为它只适用于内存分配; 后继的构造函数调用还是可能抛出异常.
 */

// 条款 50 了解 new 和 delete 的合理替换时机
// 有很多理由需要写个自定的 new 和 delete, 包括改善效能、对 heap 运用错误进行调试、收集 heap 使用信息.

// 条款 51 编写 new 和 delete时需固守常规

/* operator new 应该内含一个无穷循环, 并在其中尝试分配内存,如果它无法满足内存需求, 就该调用 new-handler。 它也应该有能力处理 0 bytes申请.
 * Class 专属版本则还应该处理 "比正确大小更大的申请"
 * operator delete 应在收到null 指针时不做任何事. Class 专属版本则还应该处理 "比正确大小更大的错误申请"。
 */

// 条款 52 学了 placement new 也要写 placement delete

/* 但你写了一个 placement operator new, 请确定你也写出相应的 placement operator delete. 如果没, 你的程序可能会发生隐微而时断时续的内存泄漏.
 * 当你生命 定位 new 和 定位 delete, 请确定不要无意识地掩盖了它正常版本.
 */

//												第九章 杂项讨论.

// 条款 53 不要轻忽编译器的警告

/* 严肃对待编译器发出的警告信息. 努力在你的编译器的最高警告级别下争取"无任何警告"的荣誉.
 * 不要过度依赖编译器的警告能力, 因为不同的编译器对待事情的态度不相同. 一旦移植到另一个编译器上, 你原本依赖的警告信息可能消失.
 */

// 条款 54 让自己熟悉包括 TR1 在内的标准程序库

/* C++ 标准程序库的主要机能是由 STL、 iostreams、 locales组成. 并包含 C99 标准程序库.
 * TR1 添加了智能指针(例如 tr1::shared_ptr)、 一般化函数指针(tr1::function)、 hash-based 容器、正则表达式以及另外十个组件的支持.
 * TR1 自身只是一份规范. 为获得 TR1 提供的好处, 需要 Boost.
 */

// 条款 55 让自己熟悉 Boost.
// Boost 是一个社群 也是一个网站. Boost 提供许多 TR1 组件实现品, 以及许多程序库.

// 2024/2/29
