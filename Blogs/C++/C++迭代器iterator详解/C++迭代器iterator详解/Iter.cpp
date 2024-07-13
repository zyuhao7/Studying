#include<iostream>
#include<cstring>
#include<vector>
#include<unordered_set>
#include<time.h>
#include<list>
#include<algorithm>
#include<iterator>
using namespace std;

//iterator������ʵ��
// �򵥵�vector����ʵ�֣���Ҫ�鿴��Ƕ����iterator��������ʵ��
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

	// ������������ʵ��
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
	// ������begin����������Ԫ�ص�����
	iterator begin() { return iterator(_first._ptr); }
	// ������end��������ĩβԪ�غ��λ�õĵ�����
	iterator end() { return iterator(_last._ptr); }
private:
	iterator _first; // ָ��������ʼ��ַ
	iterator _last;  // ָ�����һ����ЧԪ�صĺ��λ��
	iterator _end;   // ָ�����ݿռ�ĩβԪ�صĺ��λ��
	Alloc _allocator;// �����ײ�Ŀռ�������

	// ���������ݺ���
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

// const_iterator ������ʵ��.
// �򵥵�vector����ʵ�֣���Ҫ�鿴��Ƕ����iterator��������ʵ��
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
//	// ����������������ʵ��
//	class const_iterator
//	{
//	public:
//		friend class MyVector;
//		const_iterator(T* ptr = nullptr)
//			:_ptr(ptr) {}
//		void operator++() { ++_ptr; }
//		bool operator!=(const const_iterator& it) { return _ptr != it._ptr; }
//		// ����ֵ��const���Σ�ֻ�ܶ��������޸�
//		const T& operator*()const { return *_ptr; }
//		const T* operator->()const { return _ptr; }
//	protected:
//		T* _ptr;
//	};
//
//	// ��ͨiterator�̳���const_iterator
//	class iterator : public const_iterator
//	{
//	public:
//		iterator(T* ptr = nullptr)
//			:const_iterator(ptr) {}
//		// ����������T&����ͨ���ã��ɶ���д
//		T& operator*() { return *const_iterator::_ptr; }
//		T* operator->() { return const_iterator::_ptr; }
//	};
//	// ������begin����������Ԫ�ص�����
//	iterator begin() { return iterator(_first._ptr); }
//	// ������end��������ĩβԪ�غ��λ�õĵ�����
//	iterator end() { return iterator(_last._ptr); }
//
//	// ��������ó�begin��end�������ص��ǳ�����������ֻ�ܶ��������ݣ������޸�
//	const_iterator begin()const { return const_iterator(_first._ptr); }
//	const_iterator end()const { return const_iterator(_last._ptr); }
//
//private:
//	iterator _first; // ָ��������ʵ��ַ
//	iterator _last;  // ָ�����һ����ЧԪ�صĺ��λ��
//	iterator _end;   // ָ�����ݿռ�ĩβԪ�صĺ��λ��
//	Alloc _allocator;// �����ײ�Ŀռ�������
//
//	// ���������ݺ���
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

//reverse_iterator��const_reverse_iterator�����
//     ���������ʵ��
template<typename Iterator>
class _reverse_iterator
{
public:
	using value_type = typename Iterator::value_type;
	// ͨ��һ���������������һ�����������
	_reverse_iterator(Iterator it) :_it(it) {}

	template<typename Other>
	_reverse_iterator(const _reverse_iterator<Other>& src)
		: _it(src._it) {}

	bool operator!=(const _reverse_iterator<Iterator>& it)
	{
		return _it != it._it; // ʵ�ʵ��õĻ��������������operator!=����
	}
	void operator++() { --_it; } // �����������++���������������������--����
	value_type& operator*() { return *_it; }
	value_type* operator->() { return &(*this); } // ��ȡ������Ԫ�صĵ�ַ
private:
	Iterator _it; // ����������������������������ʵ��

	template<typename Other>
	friend class _reverse_iterator;
};

// �򵥵�vector����ʵ�֣���Ҫ�鿴��Ƕ����iterator��������ʵ��
template<typename T,
	typename Alloc = std::allocator<T>>
	class MyVector
{
public:
	// ����ǰ������
	class const_iterator;
	class iterator;
	// ���巴��������ͷ���������������������
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

	// ����������������ʵ��
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
		// ����ֵ��const���Σ�ֻ�ܶ��������޸�
		const T& operator*()const { return *_ptr; }
		const T* operator->()const { return _ptr; }
	protected:
		T* _ptr;
	};

	// ��ͨiterator�̳���const_iterator
	class iterator : public const_iterator
	{
	public:
		using value_type = T;

		iterator(T* ptr = nullptr)
			:const_iterator(ptr) {}
		// ����������T&����ͨ���ã��ɶ���д
		T& operator*() { return *const_iterator::_ptr; }
		T* operator->() { return const_iterator::_ptr; }
	};
	// ������begin����������Ԫ�ص�����
	iterator begin() { return iterator(_first._ptr); }
	// ������end��������ĩβԪ�غ��λ�õĵ�����
	iterator end() { return iterator(_last._ptr); }

	// ��������ó�begin��end�������ص��ǳ�����������ֻ�ܶ��������ݣ������޸�
	const_iterator begin()const { return const_iterator(_first._ptr); }
	const_iterator end()const { return const_iterator(_last._ptr); }

	// rbegin���ص������һ����ЧԪ�صĵ�������ʾ
	reverse_iterator rbegin() { return reverse_iterator(iterator(_last._ptr - 1)); }
	// rend���ص�����Ԫ�ص�ǰ��λ��
	reverse_iterator rend() { return reverse_iterator(iterator(_first._ptr - 1)); }
	// rbegin���ص������һ����ЧԪ�صĵ�������ʾ
	const_reverse_iterator rbegin()const { return const_reverse_iterator(iterator(_last._ptr - 1)); }
	// rend���ص�����Ԫ�ص�ǰ��λ��
	const_reverse_iterator rend()const { return const_reverse_iterator(iterator(_first._ptr - 1)); }
private:
	iterator _first; // ָ��������ʵ��ַ
	iterator _last;  // ָ�����һ����ЧԪ�صĺ��λ��
	iterator _end;   // ָ�����ݿռ�ĩβԪ�صĺ��λ��
	Alloc _allocator;// �����ײ�Ŀռ�������

	// ���������ݺ���
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
	/* ������iterator��C++ STL�����֮һ����������������������������ͨ�õı�������Ԫ�صķ�ʽ�����������ǻ���ʲô���ݽṹʵ��
	* ��, ���ܲ�ͬ�����ݽṹ, ����Ԫ�صķ�ʽ��һ��, ����ʹ�õ�����������ͬ�����Ĵ�������ȫһ����.
	*  ������������������Ĵ�������:
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

	//for (int val : vec) // ʵ�������õ�������������vec
	//{
	//	cout << val << " ";
	//}
	//cout << endl;

	//����������ʧЧ����
	//std::vector<int> vec1;
	//srand(time(nullptr));
	//for (int i = 0; i < 20; ++i)
	//{
	//	vec1.push_back(rand() % 100);
	//}

	//// ɾ������ż��
	//auto it = vec1.begin();
	//while (it != vec1.end())
	//{
	//	if (*it % 2 == 0) it = vec1.erase(it); // ��Ҫ�Ե���������ʵʱ����, �����ʧЧ.
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
	//	std::cout << *cit <<endl;  // ����*cit���ܱ���ֵ��Ϊ��ֵ
	//}
	//std::cout << std::endl;

	//MyVector<int> vec;
	//for (int i = 0; i < 20; ++i)
	//{
	//	vec.push_back(rand() % 100);
	//}

	//// �����������Ԫ��
	//auto it = vec.begin();
	//for (; it != vec.end(); ++it)
	//{
	//	std::cout << *it << " ";
	//}
	//std::cout << std::endl;

	//// �����������Ԫ��
	//MyVector<int>::const_reverse_iterator rit = vec.rbegin();
	//for (; rit != vec.rend(); ++rit)
	//{
	//	std::cout << *rit << " ";
	//	// *rit = 20; �����������������޸�����Ԫ�ص�ֵ
	//}
	//std::cout << std::endl;

//
//	return 0;
//
//}

int main()
{
	// insert �����͵�����
	
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

	// ��������

	//vector<int> vec;
	//copy(istream_iterator<int>(cin), istream_iterator<int>(),
	//	inserter(vec, vec.begin()));

	//vector<int> vec2;
	//copy(vec.begin(), vec.end(), back_inserter(vec2));
	//copy(vec2.begin(), vec2.end(), ostream_iterator<int>(cout, " "));
	//cout << endl;
}