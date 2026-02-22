#include <iostream>
#include <print>
struct A
{
	int a, b;
};
// 制定初始化器

int main()
{
	A a{ .a = 1,.b{2} };
	std::println("{} : {}",a.a,  a.b);
}