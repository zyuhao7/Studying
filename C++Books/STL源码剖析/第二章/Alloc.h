#pragma once

#ifndef __YUHALLOC_
#define __YUHALLOC_
#include<new>
#include<cstddef>
#include<cstdlib>
#include<climits>
#include<cerrno>
#include<iostream>

using namespace std;
namespace yuh
{
	template<class T>
	inline T* _allocate(ptrdiff_t size, T*)
	{
		set_new_handler(0);
		T* tmp = (T*)(::operator new((size_t)(size * sizeof(T))));
		if (tmp == 0)
		{
			cerr << "out of memory" << endl;
			exit(1);
		}
	}

	template<class T>
	inline void _deallocate(T* buf)
	{
		::operator delete(buf);
	}

	template<class T1, class T2>
	inline void _construct(T1* p, const T2& val)
	{
		new(p) T1(val);                          //定位 new 调用 T1的构造.
	}

	template<class T>
	inline void _destroy(T* ptr)
	{
		ptr->~T();
	}

	template<class T>
	class allocator {
	public:
		typedef T           val_type;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef T& reference;
		typedef const T& const_reference;
		typedef size_t      size_type;
		typedef ptrdiff_t   difference_type;

		// rebind allocator of  type U
		template<class U>
		struct rebind {
			typedef allocator<U> other;
		};

		pointer allocate(size_type n, const void* hint = 0)
		{
			return _allocate((difference_type)n, (pointer)0);
		}

		void deallocate(pointer p, size_type n)
		{
			_deallocate(p);
		}

		void construct(pointer p, const T& val)
		{
			_construct(p, val);
		}

		void destroy(pointer p)
		{
			_destroy(p);
		}

		pointer address(reference x)
		{
			return (pointer)&x;
		}

		const_pointer const_address(const_reference x)
		{
			return (const_reference)&x;
		}

		size_type max_size() const
		{
			return size_type(UINT_MAX / sizeof(T));
		}
	};

} //end of namespace yuh

#endif //__yuhAlloc_