#include<iostream>
#include<cstring>
#include<vector>
#include<unordered_set>
#include<time.h>
#include<list>
#include<algorithm>
#include<iterator>
using namespace std;

//iterator迭代器实现
// 简单的vector容器实现，主要查看其嵌套类iterator迭代器的实现
#if 0
template<typename T,
	typename Alloc = std::allocator<T>>
	class MyVector
{
public:
	MyVector(const Alloc& alloc = Alloc())
		:_allocator(alloc)
	{
		_first._ptr = _last._ptr = _end._ptr = nullptr;
	}

	template<typename T>
	void push_back(T&& val)
	{
		if (full())
			resize();
		_allocator.construct(_last._ptr, std::forward<T>(val));
		_last._ptr++;
	}

	void pop_back()
	{
		if (empty())
			return;
		_last._ptr--;
		_allocator.destroy(_last._ptr);
	}

	bool full()const { return _last._ptr == _end._ptr; }
	bool empty()const { return _first._ptr == _last._ptr; }

	// 容器迭代器的实现
	class iterator
	{
	public:
		friend class MyVector;
		iterator(T* ptr = nullptr)
			:_ptr(ptr) {}
		void operator++() { ++_ptr; }
		bool operator!=(const iterator& it) { return _ptr != it._ptr; }
		T& operator*() { return *_ptr; }
		T* operator->() { return _ptr; }
	private:
		T* _ptr;
	};
	// 容器的begin方法返回首元素迭代器
	iterator begin() { return iterator(_first._ptr); }
	// 容器的end方法返回末尾元素后继位置的迭代器
	iterator end() { return iterator(_last._ptr); }
private:
	iterator _first; // 指向数组起始地址
	iterator _last;  // 指向最后一个有效元素的后继位置
	iterator _end;   // 指向数据空间末尾元素的后继位置
	Alloc _allocator;// 容器底层的空间配置器

	// 容器的扩容函数
	void resize()
	{
		if (_first._ptr == nullptr)
		{
			_first._ptr = _allocator.allocate(1);
			_last._ptr = _first._ptr;
			_end._ptr = _first._ptr + 1;
		}
		else
		{
			int size = _last._ptr - _first._ptr;
			T* ptmp = _allocator.allocate(2 * size);
			for (int i = 0; i < size; ++i)
			{
				_allocator.construct(ptmp + i, _first._ptr[i]);
				_allocator.destroy(_first._ptr + i);
			}
			_allocator.deallocate(_first._ptr, size);
			_first._ptr = ptmp;
			_last._ptr = _first._ptr + size;
			_end._ptr = _first._ptr + 2 * size;
		}
	}
};
#endif

// const_iterator 迭代器实现.
// 简单的vector容器实现，主要查看其嵌套类iterator迭代器的实现
//template<typename T,
//	typename Alloc = std::allocator<T>>
//	class MyVector
//{
//public:
//	MyVector(const Alloc& alloc = Alloc())
//		:_allocator(alloc)
//	{
//		_first._ptr = _last._ptr = _end._ptr = nullptr;
//	}
//
//	template<typename T>
//	void push_back(T&& val)
//	{
//		if (full())
//			resize();
//		_allocator.construct(_last._ptr, std::forward<T>(val));
//		_last._ptr++;
//	}
//
//	void pop_back()
//	{
//		if (empty())
//			return;
//		_last._ptr--;
//		_allocator.destroy(_last._ptr);
//	}
//
//	bool full()const { return _last._ptr == _end._ptr; }
//	bool empty()const { return _first._ptr == _last._ptr; }
//
//	// 容器常量迭代器的实现
//	class const_iterator
//	{
//	public:
//		friend class MyVector;
//		const_iterator(T* ptr = nullptr)
//			:_ptr(ptr) {}
//		void operator++() { ++_ptr; }
//		bool operator!=(const const_iterator& it) { return _ptr != it._ptr; }
//		// 返回值被const修饰，只能读，不能修改
//		const T& operator*()const { return *_ptr; }
//		const T* operator->()const { return _ptr; }
//	protected:
//		T* _ptr;
//	};
//
//	// 普通iterator继承自const_iterator
//	class iterator : public const_iterator
//	{
//	public:
//		iterator(T* ptr = nullptr)
//			:const_iterator(ptr) {}
//		// 返回类型是T&的普通引用，可读可写
//		T& operator*() { return *const_iterator::_ptr; }
//		T* operator->() { return const_iterator::_ptr; }
//	};
//	// 容器的begin方法返回首元素迭代器
//	iterator begin() { return iterator(_first._ptr); }
//	// 容器的end方法返回末尾元素后继位置的迭代器
//	iterator end() { return iterator(_last._ptr); }
//
//	// 常对象调用常begin和end方法返回的是常量迭代器，只能读容器数据，不能修改
//	const_iterator begin()const { return const_iterator(_first._ptr); }
//	const_iterator end()const { return const_iterator(_last._ptr); }
//
//private:
//	iterator _first; // 指向数组其实地址
//	iterator _last;  // 指向最后一个有效元素的后继位置
//	iterator _end;   // 指向数据空间末尾元素的后继位置
//	Alloc _allocator;// 容器底层的空间配置器
//
//	// 容器的扩容函数
//	void resize()
//	{
//		if (_first._ptr == nullptr)
//		{
//			_first._ptr = _allocator.allocate(1);
//			_last._ptr = _first._ptr;
//			_end._ptr = _first._ptr + 1;
//		}
//		else
//		{
//			int size = _last._ptr - _first._ptr;
//			T* ptmp = _allocator.allocate(2 * size);
//			for (int i = 0; i < size; ++i)
//			{
//				_allocator.construct(ptmp + i, _first._ptr[i]);
//				_allocator.destroy(_first._ptr + i);
//			}
//			_allocator.deallocate(_first._ptr, size);
//			_first._ptr = ptmp;
//			_last._ptr = _first._ptr + size;
//			_end._ptr = _first._ptr + 2 * size;
//		}
//	}
//};

//reverse_iterator和const_reverse_iterator的设计
//     反向迭代器实现
template<typename Iterator>
class _reverse_iterator
{
public:
	using value_type = typename Iterator::value_type;
	// 通过一个正向迭代器构建一个反向迭代器
	_reverse_iterator(Iterator it) :_it(it) {}

	template<typename Other>
	_reverse_iterator(const _reverse_iterator<Other>& src)
		: _it(src._it) {}

	bool operator!=(const _reverse_iterator<Iterator>& it)
	{
		return _it != it._it; // 实际调用的还是正向迭代器的operator!=函数
	}
	void operator++() { --_it; } // 反向迭代器的++操作，就是正向迭代器的--操作
	value_type& operator*() { return *_it; }
	value_type* operator->() { return &(*this); } // 获取迭代的元素的地址
private:
	Iterator _it; // 反向迭代器依赖容器的正向迭代器实现

	template<typename Other>
	friend class _reverse_iterator;
};

// 简单的vector容器实现，主要查看其嵌套类iterator迭代器的实现
template<typename T,
	typename Alloc = std::allocator<T>>
	class MyVector
{
public:
	// 类型前置声明
	class const_iterator;
	class iterator;
	// 定义反向迭代器和反向常量迭代器的类型名称
	using reverse_iterator = _reverse_iterator<iterator>;
	using const_reverse_iterator = _reverse_iterator<const_iterator>;

	MyVector(const Alloc& alloc = Alloc())
		:_allocator(alloc)
	{
		_first._ptr = _last._ptr = _end._ptr = nullptr;
	}

	template<typename T>
	void push_back(T&& val)
	{
		if (full())
			resize();
		_allocator.construct(_last._ptr, std::forward<T>(val));
		_last._ptr++;
	}

	void pop_back()
	{
		if (empty())
			return;
		_last._ptr--;
		_allocator.destroy(_last._ptr);
	}

	bool full()const { return _last._ptr == _end._ptr; }
	bool empty()const { return _first._ptr == _last._ptr; }

	// 容器常量迭代器的实现
	class const_iterator
	{
	public:
		using value_type = const T;

		friend class MyVector;
		const_iterator(T* ptr = nullptr)
			:_ptr(ptr) {}
		void operator++() { ++_ptr; }
		void operator--() { --_ptr; }
		bool operator!=(const const_iterator& it) { return _ptr != it._ptr; }
		// 返回值被const修饰，只能读，不能修改
		const T& operator*()const { return *_ptr; }
		const T* operator->()const { return _ptr; }
	protected:
		T* _ptr;
	};

	// 普通iterator继承自const_iterator
	class iterator : public const_iterator
	{
	public:
		using value_type = T;

		iterator(T* ptr = nullptr)
			:const_iterator(ptr) {}
		// 返回类型是T&的普通引用，可读可写
		T& operator*() { return *const_iterator::_ptr; }
		T* operator->() { return const_iterator::_ptr; }
	};
	// 容器的begin方法返回首元素迭代器
	iterator begin() { return iterator(_first._ptr); }
	// 容器的end方法返回末尾元素后继位置的迭代器
	iterator end() { return iterator(_last._ptr); }

	// 常对象调用常begin和end方法返回的是常量迭代器，只能读容器数据，不能修改
	const_iterator begin()const { return const_iterator(_first._ptr); }
	const_iterator end()const { return const_iterator(_last._ptr); }

	// rbegin返回的是最后一个有效元素的迭代器表示
	reverse_iterator rbegin() { return reverse_iterator(iterator(_last._ptr - 1)); }
	// rend返回的是首元素的前导位置
	reverse_iterator rend() { return reverse_iterator(iterator(_first._ptr - 1)); }
	// rbegin返回的是最后一个有效元素的迭代器表示
	const_reverse_iterator rbegin()const { return const_reverse_iterator(iterator(_last._ptr - 1)); }
	// rend返回的是首元素的前导位置
	const_reverse_iterator rend()const { return const_reverse_iterator(iterator(_first._ptr - 1)); }
private:
	iterator _first; // 指向数组其实地址
	iterator _last;  // 指向最后一个有效元素的后继位置
	iterator _end;   // 指向数据空间末尾元素的后继位置
	Alloc _allocator;// 容器底层的空间配置器

	// 容器的扩容函数
	void resize()
	{
		if (_first._ptr == nullptr)
		{
			_first._ptr = _allocator.allocate(1);
			_last._ptr = _first._ptr;
			_end._ptr = _first._ptr + 1;
		}
		else
		{
			int size = _last._ptr - _first._ptr;
			T* ptmp = _allocator.allocate(2 * size);
			for (int i = 0; i < size; ++i)
			{
				_allocator.construct(ptmp + i, _first._ptr[i]);
				_allocator.destroy(_first._ptr + i);
			}
			_allocator.deallocate(_first._ptr, size);
			_first._ptr = ptmp;
			_last._ptr = _first._ptr + size;
			_end._ptr = _first._ptr + 2 * size;
		}
	}
};


//int main()
//{
	/* 迭代器iterator是C++ STL的组件之一，作用是用来遍历容器，而且是通用的遍历容器元素的方式，无论容器是基于什么数据结构实现
	* 的, 尽管不同的数据结构, 遍历元素的方式不一样, 但是使用迭代器遍历不同容器的代码是完全一样的.
	*  经典迭代器遍历容器的代码如下:
	*/
	//vector<int> vec(10, 0);

	//vector<int>::iterator it = vec.begin();
	//for (; it != vec.end(); ++it)
	//{
	//	cout << *it << " ";
	//}
	//cout << endl;

	//unordered_set<int> us;
	//us.insert(1);
	//us.insert(55);
	//us.insert(25);

	//unordered_set<int>::iterator it = us.begin();
	//for (; it != us.end(); ++it)
	//{
	//	cout << *it << " ";
	//}
	//cout << endl;

	//for (int val : vec) // 实际上是用迭代器遍历容器vec
	//{
	//	cout << val << " ";
	//}
	//cout << endl;

	//容器迭代器失效问题
	//std::vector<int> vec1;
	//srand(time(nullptr));
	//for (int i = 0; i < 20; ++i)
	//{
	//	vec1.push_back(rand() % 100);
	//}

	//// 删除所有偶数
	//auto it = vec1.begin();
	//while (it != vec1.end())
	//{
	//	if (*it % 2 == 0) it = vec1.erase(it); // 需要对迭代器进行实时更新, 否则会失效.
	//	else it++;
	//}

	//for (int v : vec1)
	//{
	//	cout << v << " ";
	//}
	//cout << endl;

	//srand(time(nullptr));
	//MyVector<int> vec;
	//for (int i = 0; i < 20; ++i)
	//{
	//	vec.push_back(rand() % 100);
	//}

	//MyVector<int>::const_iterator cit = vec.begin();
	//for (; cit != vec.end(); ++cit)
	//{
	//	std::cout << *cit <<endl;  // 这里*cit不能被赋值作为左值
	//}
	//std::cout << std::endl;

	//MyVector<int> vec;
	//for (int i = 0; i < 20; ++i)
	//{
	//	vec.push_back(rand() % 100);
	//}

	//// 正向遍历容器元素
	//auto it = vec.begin();
	//for (; it != vec.end(); ++it)
	//{
	//	std::cout << *it << " ";
	//}
	//std::cout << std::endl;

	//// 反向遍历容器元素
	//MyVector<int>::const_reverse_iterator rit = vec.rbegin();
	//for (; rit != vec.rend(); ++rit)
	//{
	//	std::cout << *rit << " ";
	//	// *rit = 20; 反向常量迭代器不能修改容器元素的值
	//}
	//std::cout << std::endl;

//
//	return 0;
//
//}

int main()
{
	// insert 插入型迭代器
	
	//srand(time(nullptr));
	//vector<int> vec;
	//for (int i = 0;i < 20;++i) vec.push_back(rand() % 100);
	//vector<int> vec2;
	//copy(vec.begin(), vec.end(), back_inserter(vec2));
	//for (int v : vec2) cout << v << " ";
	//cout << endl;

	//list<int> ml;
	//for (int v : vec) cout << v << " ";
	//cout << endl;
	//reverse_copy(vec.begin(), vec.end(), back_inserter(ml));
	//for (int l : ml) cout << l << " ";
	//cout << endl;

	// 流迭代器

	//vector<int> vec;
	//copy(istream_iterator<int>(cin), istream_iterator<int>(),
	//	inserter(vec, vec.begin()));

	//vector<int> vec2;
	//copy(vec.begin(), vec.end(), back_inserter(vec2));
	//copy(vec2.begin(), vec2.end(), ostream_iterator<int>(cout, " "));
	//cout << endl;
}