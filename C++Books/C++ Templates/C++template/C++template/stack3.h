#pragma once
#include <vector>
#include <stdexcept>

// 缺省模板参数

template<typename T, typename Container = std::vector<T>>
class Stack
{
private:
	Container elems;

public:
	void push(T const& elem);
	void pop();
	T  top() const;
	bool empty() const
	{
		return elems.empty();
	}
};

template<typename T, typename Container>
void Stack<T, Container>::push(T const& elem)
{
	elems.push_back(elem);
}

template<typename T, typename Container>
void Stack<T, Container>::pop()
{
	if(elems.empty())
		throw std::out_of_range("Stack<>::pop(): empty stack");
	elems.pop_back();
}

template<typename T, typename Container>
T  Stack<T, Container>::top() const
{
	if (elems.empty())
		throw std::out_of_range("Stack<>::top(): empty stack");
	return elems.back();
}

