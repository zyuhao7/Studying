#pragma once
#include <deque>
#include <stdexcept>
#include <memory>

// 模板的模板参数
template<typename T,
		template<typename ELEM,
				typename = std::allocator<ELEM>>
				class Container = std::deque> 
class Stack {
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
	template<typename T2,
			template<typename ELEM,
					typename = std::allocator<ELEM>>
					class Container2>
		Stack<T,Container>& operator=(Stack<T2, Container2> const&);
};


template<typename T, template<typename, typename> class Container>
void Stack<T, Container>::push(T const& elem)
{
	elems.push_back(elem);
}

template<typename T, template<typename, typename> class Container>
void Stack<T, Container>::pop()
{
	if (elems.empty())
		throw std::out_of_range("Stack<>::pop(): empty stack");
	elems.pop_back();
}

template<typename T, template<typename, typename> class Container>
T Stack<T, Container>::top() const
{
	if (elems.empty())
		throw std::out_of_range("Stack<>::top(): empty stack");
	return elems.back();
}
template<typename T, template<typename, typename> class Container>
template<typename T2,
	template<typename, typename> class Container2>
Stack<T, Container>& Stack<T, Container>::operator=(Stack<T2, Container2> const& op2)
{
	if ((void*)this == (void*)&op2)
		return *this;
	Stack<T2, Container2> tmp(op2);
	elems.clear();
	while (!tmp.empty())
	{
		elems.push_front(tmp.top());
		tmp.pop();
	}
	return *this;
}
