#include <iostream>
using namespace std;

// day-2024-9-16
// Item 1:理解模板类型推导

// 在模板类型推导时,有引用的实参会被视为无引用,他们的引用会被忽略
// 对于通用引用的推导,左值实参会被特殊对待
// 对于传值类型推导,const和/或volatile实参会被认为是non-const的和non-volatile的
// 在模板类型推导时,数组名或者函数名实参会退化为指针,除非它们被用于初始化引用

// Item 2:理解auto类型推导

// auto类型推导通常和模板类型推导相同,但是auto类型推导假定花括号初始化代表std::initializer_list,而模板类型推导不这样做
// 在C++14中auto允许出现在函数返回值或者lambda函数形参中,但是它的工作机制是模板类型推导那一套方案,而不是auto类型推导

// 2024-9-19
// Item 3:理解decltype

// decltype总是不加修改的产生变量或者表达式的类型。
// 对于 T 类型的不是单纯的变量名的左值表达式,decltype总是产出 T 的引用即 T&。
// C++14支持decltype(auto),就像auto一样,推导出类型,但是它使用decltype的规则进行推导。

// Item 4:学会查看类型推导结果

// class Widget
// {
// };

// template <typename T>
// void f(const T &param)
// {
//     cout << "T =     " << typeid(T).name() << '\n'; // 显示 T PK6Widget

//     cout << "param = " << typeid(param).name() << '\n'; // 显示 param PK6Widget
// }

// int main()
// {
//     const Widget *w;
//     f(w);

//     return 0;
// }

// 类型推断可以从IDE看出,从编译器报错看出,从Boost TypeIndex库的使用看出
// 这些工具可能既不准确也无帮助,所以理解C++ 类型推导规则才是最重要的

// 第二章 auto
// Item 5:优先考虑auto而非显式类型声明

// auto变量必须初始化,通常它可以避免一些移植性和效率性的问题,也使得重构更方便,还能让你少打几个字
// 正如Item 2 和 6 讨论的,auto类型的变量可能会踩到一些陷阱

// Item 6:auto推导若非己愿,使用显式类型初始化惯用法

// 不可见的代理类可能会使auto从表达式中推导出“错误的”类型
// 显式类型初始器惯用法强制auto推导出你想要的结果

// 第三章 移步现代C++

// Item 7:区别使用()和{}创建对象

// 花括号初始化是最广泛使用的初始化语法,它防止变窄转换,并且对于C++最令人头疼的解析有天生的免疫性
// 在构造函数重载决议中,编译器会尽最大努力将括号初始化与std::initializer_list参数匹配,即便其他构造函数看起来是更好的选择
// 对于数值类型的std::vector来说使用花括号初始化和圆括号初始化会造成巨大的不同
// 在模板类选择使用圆括号初始化或使用花括号初始化创建对象是一个挑战

// Item 8:优先考虑nullptr而非0和NULL

// 优先考虑nullptr而非0和NULL
// 避免重载指针和整型

// day-2024-9-20
// Item 9:优先考虑别名声明而非typedefs

// std::remove_const<T>::type          //C++11: const T → T
// std::remove_const_t<T>              //C++14 等价形式

// std::remove_reference<T>::type      //C++11: T&/T&& → T
// std::remove_reference_t<T>          //C++14 等价形式

// std::add_lvalue_reference<T>::type  //C++11: T → T&
// std::add_lvalue_reference_t<T>      //C++14 等价形式

// template <class T>
// using remove_const_t = typename remove_const<T>::type;

// template <class T>
// using remove_reference_t = typename remove_reference<T>::type;

// template <class T>
// using add_lvalue_reference_t =
//     typename add_lvalue_reference<T>::type;

// typedef不支持模板化,但是别名声明支持。
// 别名模板避免了使用“::type”后缀,而且在模板中使用typedef还需要在前面加上typename
// C++14提供了C++11所有type traits 转换的别名声明版本

// Item 10:优先考虑限域枚举而非未限域枚举

// C++98的enum即 非限域enum。
// 限域enum 的枚举名 仅在enum内可见。要转换为其它类型只能使用cast。
// 非限域/限域enum 都支持底层类型说明语法,限域enum 底层类型默认是int。非限域enum 没有默认底层类型。
// 限域enum总是可以前置声明。非限域enum 仅当指定它们的底层类型时才能前置。

// Item 11:优先考虑使用deleted函数而非使用未定义的私有声明

// 比起声明函数为private但不定义,使用deleted函数更好
// 任何函数都能被删除（be deleted）,包括非成员函数和模板实例（译注：实例化的函数）

// Item 12:使用override声明重载函数

// 要想重写一个函数,必须满足下列要求：
//  基类函数必须是virtual
//  基类和派生类函数名必须完全一样（除非是析构函数)
//  基类和派生类函数形参类型必须完全一样
//  基类和派生类函数常量性 constness 必须完全一样
//  基类和派生类函数的返回值和异常说明（exception specifications）必须兼容
// C++ 11 新加入的限制: 函数的引用限定符（reference qualifiers）必须完全一样。

// class Widget {
// public:
//      ...
//     void doWork() &;    //只有*this为左值的时候才能被调用
//     void doWork() &&;   //只有*this为右值的时候才能被调用
// };

// 为重写函数加上override
// 成员函数引用限定让我们可以区别对待左值对象和右值对象（即*this)

// 2024-9-23
// Item 13:优先考虑const_iterator而非iterator

// 优先考虑const_iterator而非iterator
// 在最大程度通用的代码中,优先考虑非成员函数版本的begin,end,rbegin等,而非同名成员函数

// Item 14:如果函数不抛出异常请使用noexcept

// int f(int x) throw();   //C++98风格,没有来自f的异常
// int f(int x) noexcept;  //C++11风格,没有来自f的异常

// noexcept是函数接口的一部分,这意味着调用者可能会依赖它
// noexcept函数较之于non -noexcept函数更容易优化
// noexcept对于移动语义,swap,内存释放函数和析构函数非常有用
// 大多数函数是异常中立的（译注：可能抛也可能不抛异常）而不是noexcept

// Item 15:尽可能的使用constexpr

//  constexpr对象是const,它被在编译期可知的值初始化
// 当传递编译期可知的值时,constexpr函数可以产出编译期可知的结果
// constexpr对象和函数可以使用的范围比non-constexpr对象和函数要大
// constexpr是对象和函数接口的一部分

// Item 16:让const成员函数线程安全

// 确保const成员函数线程安全,除非你确定它们永远不会在并发上下文（concurrent context）中使用。
// 使用std::atomic变量可能比互斥量提供更好的性能,但是它只适合操作单个变量或内存位置。

// Item 17:理解特殊成员函数的生成
// class Widget
// {
// public:
//     Widget(Widget &&rhs);              // 移动构造函数
//     Widget &operator=(Widget &&rhs);   // 移动赋值运算符
// };

// class Base {
// public:
//     virtual ~Base() = default;              //使析构函数virtual

//     Base(Base&&) = default;                 //支持移动
//     Base& operator=(Base&&) = default;

//     Base(const Base&) = default;            //支持拷贝
//     Base& operator=(const Base&) = default;
// };

// 特殊成员函数是编译器可能自动生成的函数：默认构造函数,析构函数,拷贝操作,移动操作。
// 移动操作仅当类没有显式声明移动操作,拷贝操作,析构函数时才自动生成。
// 拷贝构造函数仅当类没有显式声明拷贝构造函数时才自动生成,并且如果用户声明了移动操作,拷贝构造就是delete。
// 拷贝赋值运算符仅当类没有显式声明拷贝赋值运算符时才自动生成,并且如果用户声明了移动操作,拷贝赋值运算符就是delete。
// 当用户声明了析构函数,拷贝操作的自动生成已被废弃。
// 成员函数模板不抑制特殊成员函数的生成。

// day-2024-9-24
// 第四章 智能指针
// Item 18:对于独占资源使用std::unique_ptr

// std::unique_ptr是轻量级、快速的、只可移动（move-only）的管理专有所有权语义资源的智能指针
// 默认情况,资源销毁通过delete实现,但是支持自定义删除器。有状态的删除器和函数指针会增加std::unique_ptr对象的大小
// 将std::unique_ptr转化为std::shared_ptr非常简单

// Item 19:对于共享资源使用std::shared_ptr

// std::shared_ptr 为有共享所有权的任意资源提供一种自动垃圾回收的便捷方式。
// 较之于std::unique_ptr,std::shared_ptr 对象通常大两倍,控制块会产生开销,需要原子性的引用计数修改操作。
// 默认资源销毁是通过delete,但是也支持自定义删除器。删除器的类型是什么对于std::shared_ptr的类型没有影响。
// 避免从原始指针变量上创建std::shared_ptr。

// Item 20:当std::shared_ptr可能悬空时使用std::weak_ptr

// 用std::weak_ptr替代可能会悬空的std::shared_ptr。
// std::weak_ptr的潜在使用场景包括：缓存、观察者列表、打破std::shared_ptr环状结构。

// Item 21:优先考虑使用std::make_unique和std::make_shared而非new

// 和直接使用new相比,make函数消除了代码重复,提高了异常安全性。对于std::make_shared和std::allocate_shared,生成的代码更小更快。
// 不适合使用make函数的情况包括需要指定自定义删除器和希望用花括号初始化。
// 对于std::shared_ptrs,其他不建议使用make函数的情况包括
// (1)有自定义内存管理的类；
// (2)特别关注内存的系统,非常大的对象,以及std::weak_ptrs比对应的std::shared_ptrs活得更久。

// day-2024-9-25
// Item 22:当使用Pimpl惯用法,请在实现文件中定义特殊成员函数

// Pimpl惯用法通过减少在类实现和类使用者之间的编译依赖来减少编译时间。
// 对于std::unique_ptr类型的pImpl指针,需要在头文件的类里声明特殊的成员函数,
// 但是在实现文件里面来实现他们。即使是编译器自动生成的代码可以工作,也要这么做。
// 以上的建议只适用于std::unique_ptr,不适用于std::shared_ptr。

// 第五章 右值引用,移动语义,完美转发

// Item 23:理解std::move和std::forward

// std::move执行到右值的无条件的转换,但就自身而言,它不移动任何东西。
// std::forward只有当它的参数被绑定到一个右值时,才将参数转换为右值。
// std::move和std::forward在运行期什么也不做。

// Item 24:区别通用引用和右值引用

// 如果一个函数模板形参的类型为T&&,并且T需要被推导得知,或者如果一个对象被声明为auto&&,这个形参或者对象就是一个通用引用。
// 如果类型声明的形式不是标准的type&&,或者如果类型推导没有发生,那么type&&代表一个右值引用。
// 通用引用,如果它被右值初始化,就会对应地成为右值引用；如果它被左值初始化,就会成为左值引用。

// 2024-9-26
// Item 25:对于右值引用使用std::move,对于通用引用使用std::forward

// 最后一次使用时,在右值引用上使用std::move,在通用引用上使用std::forward。
// 对按值返回的函数要返回的右值引用和通用引用,执行相同的操作。
// 如果局部对象可以被返回值优化消除,就绝不使用std::move或者std::forward。

// Item 26:避免重载通用引用

// 对通用引用形参的函数进行重载,通用引用函数的调用机会几乎总会比你期望的多得多。
// 完美转发构造函数是糟糕的实现,因为对于non-const左值,它们比拷贝构造函数而更匹配,
// 而且会劫持派生类对于基类的拷贝和移动构造函数的调用。

// Item 27:熟悉重载通用引用的替代品

// 通用引用和重载的组合替代方案包括使用不同的函数名，通过lvalue-reference-to-const传递形参，按值传递形参，使用tag dispatch。
// 通过std::enable_if约束模板，允许组合通用引用和重载使用，但它也控制了编译器在哪种条件下才使用通用引用重载。
// 通用引用参数通常具有高效率的优势，但是可用性就值得斟酌。

// day-2024-10-3
// Item 28:理解引用折叠

// 通用引用不是一种新的引用，它实际上是满足以下两个条件下的右值引用：
// 1. 类型推导区分左值和右值。T类型的左值被推导为T&类型，T类型的右值被推导为T。
// 2. 发生引用折叠。

// 引用折叠发生在四种情况下：模板实例化，auto类型推导，typedef与别名声明的创建和使用，decltype。
// 当编译器在引用折叠环境中生成了引用的引用时，结果就是单个引用。有左值引用折叠结果就是左值引用，否则就是右值引用。
// 通用引用就是在特定上下文的右值引用，上下文是通过类型推导区分左值还是右值，并且发生引用折叠的那些地方。

// Item 29:认识移动操作的缺点
// 假定移动操作不存在，成本高，未被使用。
// 在已知的类型或者支持移动语义的代码中，就不需要上面的假设。

// Item 30:熟悉完美转发失败的情况
// 当模板类型推导失败或者推导出错误类型，完美转发会失败。
// 导致完美转发失败的实参种类有花括号初始化，作为空指针的0或者NULL，仅有声明的整型static const数据成员，模板和重载函数的名字，位域。

int main()
{
}