#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;
// Line 247

// vector

// int main()
// {
//     vector<int> v;
//     v.push_back(9);
//     v.push_back(9);
//     v.push_back(2);
//     vector<int>::iterator it = find(v.begin(), v.end(), 2);
//     if (it != v.end())
//         v.insert(it, 3, 4); // 9 9 4 4 4 2
//     for (auto it : v)
//     {
//         cout << it << ' ';
//     }

//     return 0;
// }

//  list
// 每一个设计过 list 的人都知道, list 本身 和 list 的节点是不同的结构, 需要分开设计.

// STL list 的节点 (node) 结构:

// template<class T>
// struct __list_node {
//	typedef void* void_pointer;
//	void_pointer prev;  //型别为void*, 其实可以设计为 __list_node<T>*
//	void_pointer next;
//	T data;
// };

// 双向链表节点.
//  __list_node<T> node
//          [prev] ->
//          [next] ->
//          [data]

// list 的迭代器.  Bidirectionaliterators
// list 有一个重要性质: 插入操作(insert) 和 接合操作(splice) 都不会造成原来的 list 迭代器失效.
//  SGI STL 有单向链表 slist.

// list 迭代器的设计:
// template<class T, class Ref, class Ptr>
// struct __list_iterator
//{
//	typedef __list_iterator<T, T&, T*> iterator;
//	typedef __list_iterator<T, Ref, Ptr> self;
//
//	typedef bidirectional_iterator_tag iterator_category;
//	typedef T value_type;
//	typedef Ptr pointer;
//	typedef Ref reference;
//	typedef __list_node<T>* link_type;
//	typedef size_t size_type;
//	typedef ptrdiff_t difference_type;
//
//	link_type node; // 迭代器内部当然有一个普通指针, 指向list的节点.
//
//	//constructor
//	__list_iterator(link_type x)
//		:node(x){}
//	__list_iterator(){}
//	__list_iterator(const iterator& x)
//		:node(x.node){}
//
//	bool operator==(const self& x) const
//	{
//		return node == x.node;
//	}
//
//	bool operator!=(const self& x) const
//	{
//		return node != x.node;
//	}
//	//以下对迭代器取值, (dereference) 取的是节点的数据值.
//	reference operator* () const
//	{
//		return(*node).data;
//	}
//
//	pointer operator->() const
//	{
//		return &(operator*());
//	}
//
//	//对迭代器累加1, 就是前进一个节点.
//	self& operator++()
//	{
//		node = (link_type)(node->next);// (*node).next;
//		return *this;
//	}
//
//	self operator++(int)
//	{
//		self tmp = *this;
//		++(*this);
//		return tmp;
//	}
//
//	self& operator--()
//	{
//		node = (link_type)(node->prev);
//		return *this;
//	}
//
//	self operator--(int)
//	{
//		self tmp = *this;
//		--(*this);
//		return tmp;
//	}

////////////////////////
// iterator begin()
//{
//	return (link_type)((*node).next);
// }

// iterator end()
//{
//	return node;
// }

// bool empty() const
//{
//	return node->next == node;
// }

// size_type size() const
//{
//	size_type result = 0;
//	distance(begin(), end(), result);
//	return result;
// }

// reference front()
//{
//	return *begin(); // (*node).data;
// }

// reference back()
//{
//	return *(--end());
// }

// iterator insert(iterator pos, const T& x) //在pos所指位置插入一个节点.
//{
//	link_type tmp = create_node(x);
//	tmp->next = pos.node;
//	tmp->prev = pos.node->prev;
//	 (link_type(pos.node->prev))->next = tmp;
//	 pos.node->prev = tmp;
//	 return tmp;
// }

////list 的元素操作.
////插入一个节点, 作为头结点.
// void push_front(const T& x)
//{
//	insert(begin(), x);
// }

//// 插入一个节点,作为尾节点.
// void push_back(const T& x)
//{
//	insert(end(), x);
// }

////移除迭代器 pos 所指节点.
// iterator erase(iterator pos)
//{
//	link_type next_node = (link_type)(pos.node->next);
//	link_type prev_node = (link_type)(pos.node->prev);
//	prev_node->next = next_node;
//	next_node->prev = prev_node;
//	destroy_node(pos.node);
//	return iterator(next_node);
// }

////移除头结点.
// void pop_front()
//{
//	erase(begin());
// }

////移除尾结点.
// void pop_back()
//{
//	iterator tmp = end();
//	erase(--tmp);
// }

// 清除所有节点. (整个链表)
// template<class T, class Alloc>
// void list<T, Alloc>::clear()
//{
//	link_type cur = (link_type)node->next; // begin();
//	while (cur != node)
//	{
//		link_type tmp = cur;
//		cur = (link_type)cur->next;
//		destroy_node(tmp); // 销毁一个节点.
//	}
//	//恢复node 原始状态.
//	node->next = node;
//	node->prev = node;
// }

// 将数值为 value 的所有元素移除.
// template<class T, class Alloc>
// void list<T, Alloc>::remove(const T& val)
//{
//	iterator first = begin();
//	iterator last = end();
//	while (first != last)
//	{
//		iterator next = first;
//		++next;
//		if (*first == val) erase(first);
//		first = next;
//	}
// }

//// 移除数值相同的连续元素 只有 " 连续并且相同的元素 " 才会被移除剩一个.
// template<class T,class Alloc>
// void list<T, Alloc>::unique()
//{
//	iterator first = begin();
//	iterator last = end();
//	if (first == last) return; //空链表, 什么不用做.
//	iterator next = first;
//	while (++next != last)
//	{
//		if (*first == *next) erase(next);
//		else first = next;    //调整指针.
//		next = first;         // 修正区段范围.
//	}
// }

// 迁移操作(transfer) 将某连续范围的元素迁移到某个特定位置之前.
//	protected:
//		//将 [first,last) 内的所有元素移动到 Pos 之前.
//		void transfer(iterator pos, iterator first, iterator last)
//		{
//			if (pos != last)
//			{
//				(*(link_type((*last.node).prev))).next = pos.node;
//				(*(link_type((*first.node).prev))).next = last.node;
//				(*(link_type((*pos.node).prev))).next = first.node;
//				link_type tmp = (link_type)((*pos.node).prev);
//				(*pos.node).prev = (*last.node).prev;
//				(*last.node).prev = (*first.node).prev;
//				(*first.node).prev = tmp;
//			}
//		}
//
//		public:
//			//将 x 接合于 pos 所指位置之前, x 必须不同于 *this.
//			void splice(iterator pos, list& x)
//			{
//				if (!x.empty())
//					transfer(pos, x.begin(), x.end());
//			}
//
//			//将 i 所指元素接合于 pos所指位置之前, pos 与 i 可指同一个list.
//			void splice(iterator pos, list&, iterator i)
//			{
//				iterator j = i;
//				++j;
//				if (pos == i || pos == j) return;
//				transfer(pos, i, j);
//			}
//
//			//将[first,last)内所有元素接合于pos所指位置之前.
//			// pos 和 [first,last) 可指向同一个list.
//			//但pos不能位于[first,last) 之内.
//			void splice(iterator pos, list&, iterator first, iterator last)
//			{
//				if (first != last)
//					transfer(pos, first, last);
//			}
//
//			//merge() 将 x 合并到 *this 身上, 两个 lists 的内容必须先经过递增排序.
//			template<class T,class Alloc>
//			void list<T, Alloc>::merge(list<T, Alloc>& x)
//			{
//				iterator first1 = begin();
//				iterator last1 = end();
//				iterator first2 = x.begin();
//				iterator last2 = x.end();
//
//				//注意: 前提是, 两个lists 都已经递增排序.
//				while (first1 != last1 && first2 != last2)
//				{
//					if (*first1 > *first2)
//					{
//						iterator next = first2;
//						transfer(first1, first2, ++next);
//						first2 = next;
//					}
//					else
//						++first1;
//				}
//				if (first2 != last2) transfer(last1, first2, last2);
//			}
//
//			// reverse() 将*this 的内容逆向重置.
//			template<class T,class Alloc>
//			void list<T, Alloc>::reverse()
//			{
//				//以下判断,如果是空链表或者一个元素,就不进行任何操作.
//				//使用 size() ==0 || size() == 1 也可，但慢.
//				if (node->next == node || link_type(node->next)->next == node) return;
//
//				iterator first = begin();
//				++first;
//				while (first != end())
//				{
//					iterator old = first;
//					++first;
//					transfer(begin(), old, first);
//				}
//			}
//
//			// kanbudong wuw
//			//list 本身不能用 STL 算法sort() ,必须用自己的 sort()成员函数.
//			// STL 算法的 sort() 只接受 randomAccessIterator
//			//本函数采用quick_sort
//			template<class T,class Alloc>
//			void list<T, Alloc>::sort()
//			{
//				if (node->next == node || link_type(node->next)->next == node) return;
//
//				//开一些新的 lists, 作为中介数据存放区.
//				list<T, Alloc> carry;
//				list<T, Alloc> counter[64];
//				int fill = 0;
//				while (!empty())
//				{
//					carry.splice(carry.begin(), *this, begin());
//					int i = 0;
//					while (i < fill && !counter[i].empty())
//					{
//						counter[i].merge(carry);
//						carry.swap(counter[i++]);
//					}
//					carry.swap(count[i]);
//					if (i == fill) ++fill;
//				}
//				for (int i = 1;i < fill;++i)
//				{
//					count[i].merge(counter[i - 1]);
//				}
//				swap(counter[fill - 1]);
//			}
//
//
//};

// list 的 数据结构.
//  SGI list 不仅是一个双向链表，而且还是一个环状双向链表.
// class alloc {};
// template<class T, class Alloc=alloc>
// class List
//{
// protected:
//	typedef __list_node<T> list_node;
// public:
//	typedef list_node* link_type;
// protected:
//	link_type node; //只要一个指针,便可以表示整个环状双向链表.
//	//...
// };
//
//// list 的构造与内存管理.
//// 所谓 插入 是指 " 插入在...之前",
// int main()
//{
//	//测试程序1.
//	int i;
//	list<int> ilist;
//	cout << "size=" << ilist.size() << endl; //size=0
//	ilist.push_back(0);
//	ilist.push_back(1);
//	ilist.push_back(2);
//	ilist.push_back(3);
//	ilist.push_back(4);
//	cout << "size=" << ilist.size() << endl; //size=5
//
//	list<int>::iterator it;
//	for (it = ilist.begin();it != ilist.end();++it)
//		cout << *it << " "; // 0 1 2 3 4
//	cout << endl;
//
//	it = find(ilist.begin(), ilist.end(), 3);
//	if (it != ilist.end())
//		ilist.insert(it, 99);
//
//	cout << "size=" << ilist.size() << endl; //size=6
//
//	for (it = ilist.begin();it != ilist.end();++it)
//		cout << *it << " "; // 0 1 2 99 3 4
//	cout << endl;
//
//	it = find(ilist.begin(), ilist.end(), 1);
//	if (it != ilist.end())
//		cout << *(ilist.erase(it))<<endl; // 2
//
//	for (it = ilist.begin();it != ilist.end();++it)
//		cout << *it << " "; // 0 2 99 3 4
//	cout << endl;
//
//	int iv[5] = { 5,6,7,8,9 };
//	list<int> ilist2(iv, iv + 5);
//
//	it = find(ilist.begin(), ilist.end(), 99);
//	ilist.splice(it, ilist2);
//
//	for (it = ilist.begin();it != ilist.end();++it)
//		cout << *it << " "; // 0 2 5 6 7 8 9 99 3 4
//	cout << endl;
//
//	ilist.reverse();
//
//	for (it = ilist.begin();it != ilist.end();++it)
//		cout << *it << " ";  //4 3 99 9 8 7 6 5 2 0
//	cout << endl;
//
//	ilist.sort();
//
//	for (it = ilist.begin();it != ilist.end();++it)
//		cout << *it << " ";  // 0 2 3 4 5 6 7 8 9 99
//	cout << endl;
// }