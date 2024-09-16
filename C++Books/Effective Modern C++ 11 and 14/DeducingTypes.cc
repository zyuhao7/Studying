#include <iostream>
using namespace std;

// day-2024-9-16
// Item 1:理解模板类型推导

// 在模板类型推导时，有引用的实参会被视为无引用，他们的引用会被忽略
// 对于通用引用的推导，左值实参会被特殊对待
// 对于传值类型推导，const和/或volatile实参会被认为是non-const的和non-volatile的
// 在模板类型推导时，数组名或者函数名实参会退化为指针，除非它们被用于初始化引用

// Item 2:理解auto类型推导

// auto类型推导通常和模板类型推导相同，但是auto类型推导假定花括号初始化代表std::initializer_list，而模板类型推导不这样做
// 在C++14中auto允许出现在函数返回值或者lambda函数形参中，但是它的工作机制是模板类型推导那一套方案，而不是auto类型推导

int main()
{

    return 0;
}