#pragma once
#include <iostream>
// 排序追踪器
class SortTracer
{
private:
	int value;				 // 要被排序的整数值
	int generation;			 // 产生拷贝的份数
	static long n_created;   // 调用拷贝构造函数的次数
	static long n_destroyed; // 调用析构函数的次数
	static long n_assigned;  // 调用赋值运算符的次数
	static long n_compared;  // 调用比较运算符的次数
	static long n_max_live;  // 现存对象的最大个数

	static void update_max_live()
	{
		if (n_created - n_destroyed > n_max_live)
			n_max_live = n_created - n_destroyed;
	}

public:

	static long creations()
	{
		return n_created;
	}

	static long destructions()
	{
		return n_destroyed;
	}

	static long assignments()
	{
		return n_assigned;
	}

	static long comparisons()
	{
		return n_compared;
	}

	static long max_live()
	{
		return n_max_live;
	}
public:
	//构造函数
	SortTracer(int v = 0)
		: value(v), generation(1)
	{
		n_created++;
		update_max_live();
		std::cerr << "SortTracer # " << n_created
			<< ", created generation " << generation
			<< ", (total: " << n_created - n_destroyed
			<< ")" << std::endl;
	}

	//拷贝构造函数
	SortTracer(SortTracer const& st)
		: value(st.value), generation(st.generation + 1)
	{
		n_created++;
		update_max_live();
		std::cerr << "SortTracer # " << n_created
			<< ", copied generation " << generation
			<< ", (total: " << n_created - n_destroyed
			<< ")" << std::endl;
	}

	//析构函数
	~SortTracer()
	{
		n_destroyed++;
		std::cerr << "SortTracer generation " << generation
			<< " destroyed (total: " << n_created - n_destroyed
			<< ")" << std::endl;
	}

	//赋值运算符
	SortTracer& operator=(SortTracer const& st)
	{
		++n_assigned;
		std::cerr << "SortTracer assignment # " << n_assigned
			<< ", (generation " << generation
			<< " = " << st.generation
			<< ")" << std::endl;
		value = st.value;
		return *this;
	}

	//比较运算符
	friend bool operator<(SortTracer const& st1, SortTracer const& st2)
	{
		++n_compared;
		std::cerr << "SortTracer comparison # " << n_compared
			<< ", (generation " << st1.generation
			<< " < " << st2.generation
			<< ")" << std::endl;
		return st1.value < st2.value;
	}

	int val() const
	{
		return value;
	}
};