#pragma once
#include <iostream>
// ����׷����
class SortTracer
{
private:
	int value;				 // Ҫ�����������ֵ
	int generation;			 // ���������ķ���
	static long n_created;   // ���ÿ������캯���Ĵ���
	static long n_destroyed; // �������������Ĵ���
	static long n_assigned;  // ���ø�ֵ������Ĵ���
	static long n_compared;  // ���ñȽ�������Ĵ���
	static long n_max_live;  // �ִ�����������

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
	//���캯��
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

	//�������캯��
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

	//��������
	~SortTracer()
	{
		n_destroyed++;
		std::cerr << "SortTracer generation " << generation
			<< " destroyed (total: " << n_created - n_destroyed
			<< ")" << std::endl;
	}

	//��ֵ�����
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

	//�Ƚ������
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