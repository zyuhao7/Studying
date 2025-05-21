#pragma once
#include <stdexcept>
// 模板的模板参数
#include<deque>
template<typename T,
		template <typename ELEM> class Container = std::deque>
class Stack 
{
private:
	Container<T> elems;

public:
	void push(T const&);
	void pop();
	T top() const;
	bool empty() const
	{
		return elems.empty();
	}
};

template<typename T, template<typename> class Container>
void Stack<T, Container>::push(T const& elem)
{
	elems.push_back(elem);
}

template<typename T, template<typename> class Container>
void Stack<T, Container>::pop()
{
	if (elems.empty())
		throw std::out_of_range("Stack<>::pop(): empty stack");
	elems.pop_back();
}
template<typename T, template<typename> class Container>
T Stack<T, Container>::top() const
{
	if (elems.empty())
		throw std::out_of_range("Stack<>::top(): empty stack");
	return elems.back();
}

