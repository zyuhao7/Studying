#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <set>
#include <deque>
#include <map>
#include <list>
#include <numeric>
using namespace std;
// 2024 - 8 - 6 review first
//								Effective STL

// 条款 1 仔细选择你的容器

// 标准STL序列容器 ：vector、string、deque和list
// 标准STL关联容器 ：set、multiset、map和multimap
// 非标准序列容器 slist和rope slist是一个单向链表，rope本质上是一 "重型" string
// 非标准关联容器 hash_set、hash_multiset、hash_map和hash_multimap
// vector<char>作为string的替代
// vector作为标准关联容器的替代
// 几种标准的非STL容器 , 包括 数组、bitset、valarray、stack、queue 和 priority_queue

// 条款 2  不要试图编写独立于容器类型的代码

//  条款 3 确保容器中的对象副本正确而高效

// 条款 4 调用empty而不是检查size()是否为 0

// 条款 5 区间成员函数优先于与之对应的单元素成员函数

#if 0
int main()
{
    vector<int> v1, v2;
    for (int i = 0; i < 10; ++i)
        v2.push_back(i);
    v1.assign(v2.begin() + v2.size() / 2, v2.end());
    for (auto v : v1)
        cout << v << " ";
    cout << endl;

    v1.clear();
    v1.insert(v1.end(), v2.begin() + v2.size() / 2, v2.end());
    for (auto v : v1)
        cout << v << " ";
    cout << endl;

    v1.clear();
    copy(v2.begin() + v2.size() / 2, v2.end(), back_inserter(v1));
    for (auto v : v1)
        cout << v << " ";
    cout << endl;
    return 0;
}
#endif

// day-2024-8-7
//  条款 6 当心C++编译器最烦人的分析机制

// 使用命名的迭代器对象与通常的STL程序风格相违背，但你或许觉得为了使代码对所有编译器都没有二义性，
// 并且使维护代码的人理解起来更容易，这一 代价是值得的.

// 条款 7 如果容器中包含了通过new操作创建的指针，切记在容器对象析构前将指针delete掉

// 条款 8 切勿创建包含auto_ptr的容器对象

// 条款 9 在删除选项中仔细选择

//  条款 10 了解分配子（allocator）的约定和限制

template <typename T,
		  typename Allocator = allocator<T>>
class list
{
private:
	Allocator alloc;

	struct ListNode
	{
		T data;
		ListNode *prev;
		ListNode *next;
	};
};

template <typename T>
class allocator
{
public:
	template <typename U>
	struct rebind
	{
		typedef allocator<U> other;
	};
};

// 条款 11 理解自定义分配子的合理用法

// 条款 12 切勿对STL容器的线程安全性有不切实际的依赖

// day-2024-8-8

//							vector 和 string
// 条款 13 尽量使用 vector 和 string 来替代动态分配的数组

// 条款 14 使用 reserve 来避免不必要的重新分配

// 2024-3-5
//   条款 15 小心string实现的多样性
#if 0
int main()
{
	cout << sizeof(string) << endl; //32
	return 0;
}
#endif

// 条款 16 如何将 vector 和 string 的数据传给遗留的 API

// 条款 17 使用 "交换技巧" 来修正过剩容量
// vector<Contestant>(contestants).swap(contestants);

// 条款 18 避免使用 vector<bool>

#if 0
template <typename Allocator>
vector<bool, Allocator>
{
public:
	class reference
	{
	};
	reference operator[](size_type n);
}
#endif
// 2024-8-9

//													关联容器

//  条款 19 了解 相等 和 等价之间的区别

// 条款 20 为指针的关联容器指定比较类型

#if 0
#include <iterator>
struct StringPtrLess
{

	bool operator()(const string *ps1, const string *ps2) const
	{
		return *ps1 < *ps2;
	}
};

// 当本类型的仿函数被传入一个 T* 时, 它们返回一个 const T&
struct Dereference
{
	template <typename T>
	const T &operator()(const T *ptr) const
	{
		return *ptr;
	}
};

void print(const string *ps)
{
	cout << *ps << endl;
}

int main()
{
	string s;
	cout << sizeof(s) << endl; //  x64 40  x86 28  gcc 32
	cout << sizeof(char *) << endl;

	set<string *, StringPtrLess> ssp;
	ssp.insert(new string("Anteater"));
	ssp.insert(new string("Wombat"));
	ssp.insert(new string("Lemur"));
	ssp.insert(new string("Penguin"));

	for_each(ssp.begin(), ssp.end(), print);

	for (set<string *>::const_iterator i = ssp.begin();
		 i != ssp.end();
		 ++i)
	{
		cout << **i << endl;
	}

	transform(ssp.begin(), ssp.end(), ostream_iterator<string>(cout, "\n"),
			  Dereference());

	return 0;
}
#endif

// 3.6
//  条款 21 永远让比较函数对相等的值返回 false
#if 0
int main()
{
	set<int, less_equal<int>> s;
	s.insert(10);
	s.insert(10);
	for (auto val : s)
		cout << val << endl; // 10 10 ??? Amazing!
	return 0;
}
#endif

// 条款 22 避免原地修改 set 和 multiset 的键

// 条款 23 考虑有序 vector 代替 关联容器

// 条款 24 在 map::operator[] 和 map-insert	之间仔细选择

#if 0

template <typename MapType,
		  typename KeyArgType,
		  typename ValueArgType>
typename MapType::iterator
efficientAddOrUpdate(MapType &m,
					 const KeyArgType &k,
					 const ValueArgType &v)
{
	typename MapType::iterator Ib = m.lower_bound(k); // 找到k.
	if (Ib != m.end() && !(m.key_comp()(k, Ib->first)))
	{
		Ib->second = v;
		return Ib;
	}
	else
	{
		typedef typename MapType::value_type MVT;
		return m.insert(Ib, MVT(k, v)); // 把 pair(k,v) 添加到 m, 返回指向新 map元素的迭代器.
	}
}

class Widget
{
public:
	Widget();
	Widget(double w);
	Widget &operator=(double w);
};

int main()
{
	map<int, Widget> m;
	m[0] = 1.50;
	m[1] = 3.67;
}

// day2024-8-11 

// 条款 25 熟悉非标准散列容器
// 散列容器的声明
template <typename T,
		  typename HashFunction,
		  typename CompareFunction,
		  typename Allocator = allocator<T>>
class hash_container;
#endif
// day2024-3-7
// 条款 26 尽量用 iterator 代替 const_iterator, reverse_iterator 和 const_reverse_iterator

// 条款 27 用 distance 和 advance 把 const_iterator 转化成 iterator

// 条款 28 了解如何通过 reverse_iterator 的base 得到 iterator
#if 0
int main()
{
	vector<int> v;
	v.reserve(5);
	for (int i = 0; i < 5; ++i)
		v.push_back(i);
	vector<int>::reverse_iterator Ri = find(v.rbegin(), v.rend(), 3);
	v.erase(--Ri.base()); // 删除3.
	for (int i = 0; i < v.size(); ++i)
		cout << v[i] << " ";
	cout << endl;

	Ri = find(v.rbegin(), v.rend(), 3);
	cout << *Ri << endl;
	vector<int>::iterator I(Ri.base());
	cout << *I << " "; // 0
}
#endif
// 条款 29 需要一个一个字符输入时考虑使用 istreambuf_iterator

// ifstream inputFile("data.txt");
//
// inputFile.unset(ios::skipws);
//
// string fileData((istream_iterator<char>(inputFile)),
//	istream_iterator<>());
#if 0
ifstream inputFile("data.txt");

string fileData((istreambuf_iterator<char>(inputFile)),
				istreambuf_iterator<>());

// day-2024-8-12

//													算法
// 条款 30 确保目标区间足够大

// 条款 31 了解你的排序选项

partial_sort(Widget.begin(),
			 Widget.begin() + 20, // 把最好的 20 个元素按顺序放在 Widgets的前端.
			 Widget.end(),
			 QualityComp);

nth_element(Widget.begin(), // 把最好的20个元素放在 Widgets的前端, 不担心顺序.
			Widget.begin() + 19,
			Widget.end(),
			QualityComp);
#endif
// day-2024-3-8

// 条款 32 如果真的想删除东西就在类似 remove 的后面接erase
#if 0
int main()
{
	vector<int> v;
	v.reserve(10);
	for (int i = 1; i <= 10; ++i)
		v.push_back(i);
	cout << v.size() << endl;
	v[3] = v[5] = v[9] = 100;
	// remove(v.begin(), v.end(), 100);
	// cout << v.size() << endl; // 10

	v.erase(remove(v.begin(), v.end(), 100), v.end());
	cout << v.size() << endl; // 7
}

#endif
// 条款 33 提防在指针的容器上使用类似 remove 的算法

// day-2024-8-13

// 条款 34 注意哪个算法需要有序区间

// 条款 35 通过 mismatch 或 lexicographical 比较实现简单的忽略大小学字符串比较

#if 0
int ciCharCompare(char c1, char c2)
{
	int Ic1 = tolower(static_cast<char>(c1));
	int Ic2 = tolower(static_cast<char>(c2));

	if (Ic1 < Ic2)
		return -1;
	if (Ic1 > Ic2)
		return 1;
	return 0;
}

int ciStringCompareImpl(const string &s1, const string &s2);

int ciStringCompare(const string &s1, const string &s2)
{
	if (s1.size() <= s2.size())
		return ciStringCompareImpl(s1, s2);
	else
		return -ciStringCompareImpl(s2, s1);
}

int ciStringCompareImpl(const string &s1, const string &s2)
{
	typedef pair<string::const_iterator,
				 string::const_iterator>	PSCI; // pair of string::const::iterator

	PSCI p = mismatch(
		s1.begin(), s1.end(),
		s2.begin(),
		not2(ptr_fun(ciCharCompare)));

	if (p.first != s1.end()) 
	{
		if (p.second == s2.end())
			return 0;
		else
			return -1;
	}
	return ciCharCompare(*p.first, *p.second);
}

bool ciCharLess(char c1, char c2)
{
	tolower(static_cast<unsigned char>(c1)) <
		tolower(static_cast<unsigned char>(c2));
}

bool ciStringCompare(const string& s1, const string& s2)
{
	return lexicographical_compare(s1.begin(), s1.end(),
		s2.begin(), s2.end(),
		ciCharLess);
}

bool ciStringCompare2(const string& s1, const string& s2)
{
	return stricmp(s1.c_str(), s2.c_str());
}


// 3.9
//  条款 36 了解copy_if的正确实现

template <typename InputIterator,
		  typename OutputIterator,
		  typename Predicate>
OutputIterator copy_if(InputIterator begin,
					   InputIterator end,
					   OutputIterator destBegin,
					   Predicate p)
{
	while (begin != end)
	{
		if (p(*begin))
			*destBegin++ = *begin;
		begin++;
	}
	return destBegin;
}

// 条款 37 用 accumulate 或 for_each 来统计区间

// accumulate的返回值是 double. 初始化 0.0 sum = accumulate(v.begin(),v.end(),0.0)

string::size_type stringLengthSum(string::size_type sumSoFar, const string &s)
{
	return sumSoFar + s.size();
}

set<string> ss;

string::size_type lengthSum = accumulate(ss.begin(), ss.end(), 0, stringLengthSum);

vector<float> vf;

float product = accumulate(vf.begin(), vf.end(), 1.0f, multiplies<float>());

struct Point
{		
	Point(double initX, double initY)
		: x(initX),
		  y(initY)
	{
	}
	double x, y;
};

list<Point> lp;

Point avg = accumulate(lp.begin(), lp.end(), Point(0, 0), PointAverage());

class PointAverage : public binary_function<Point, Point, Point>
{
public
	PointAverage()
		: numPoints(0),
		  xSum(0),
		  ySum(0)
	{
	}

	const Point operator()(const Point &avgSoFar, const Point &p)
	{
		++numPoints;
		xSum += p.x;
		ySum += p.y;
		return Point(xSum / numPoints, ySum / numPoints);
	}

private:
	size_t numPoints;
	double xSum;
	double ySum;
};

///////////////////////////////////////////////////////////////////

struct Point
{
	;
	Point(double initX, double initY)
		: x(initX),
		  y(initY)
	{
	}
	double x, y;
};

class PointAverage : public unary_function<Point, void>
{
public
	PointAverage()
		: numPoints(0),
		  xSum(0),
		  ySum(0)
	{
	}

	void operator()(const Point &p)
	{
		++numPoints;
		xSum += p.x;
		ySum += p.y;
	}

	Point result() const
	{
		return Point(xSum / numPoints, ySum / numPoints);
	}

private:
	size_t numPoints;
	double xSum;
	double ySum;
};

list<Point> lp;

Point avg = for_each(lp.begin(), lp.end(), PointAverage()).result;

int main()
{

	// cout << "The sum of the ints on the standard input is " << accumulate(istream_iterator<int>(cin), istream_iterator<int>(), 0);
}
// ----------

//											仿函数、仿函数类、函数等
// 条款 38 把仿函数类设计为用于值传递

// 使得 for_each 通过引用传递和返回它的仿函数
class Dosomething : public unary_function<int, void>
{
public:
	void operator()(int x)
	{
	}
};

typedef deque<int>::iterator DequeIterator;
deque<int> di;

Dosomething d;
for_each<DequeIterator,
		 DoSomething &>(di.begin(), // 调用 for_each 参数类型是 DequeIterator和DoSomething& 迫使d按引用传递和返回.
						di.end(),
						d);

// 条款 39 用纯函数做判断式

class Widget;

// bad judge class
class BadPredicate : public unary_function<Widget, bool>
{
public:
	BadPredicate()
		: timesCalled(0)
	{
	}

	// bool operator()(const Widget& w) const
	//{
	//	return ++timesCalled == 3; // 错误, 在 const 成员函数不能改变局部数据.
	// }

	// bool anotherBadPredicate(const Widget&, const Widget&)
	//{
	//	static int timesCalled = 0；     // no no no no no no
	//		return ++timesCalled == 3;	 // 判断式应该是纯函数, 纯函数没有状态/
	// }

private:
	size_t timesCalled;
};

// 假设我们用这个类从一个 vector<Widget> 除去 第三个 Widget
vector<Widget> vw;

vw.erase(remove_if(vw.begin(), vw.end(), BadPredicate()), vw.end()); // 看似合理, 它不仅会从 vw中除去第三个元素, 也会除去第六个.

template <typename FwdIterator, typename Predicate>
FwdIterator remove_if(FwdIterator begin, FwdIterator end, Predicate p)
{
	begin = find_if(begin, end, p);
	if (begin == end)
		return begin;
	else
	{
		FwdIterator next = begin;
		return remove_copy_if(++next, end, begin, p);
	}
}

// 条款 40 使仿函数类可适配

list<Widget *> widgetPtrs;

bool isInteresting(const Widget *pw);

// 指向第一个有趣的 widget 指针.
list<Widget *>::iterator it = find_if(widgetPtrs.begin(), widgetPtrs.end(), isInteresting);
if (it != widgetPtrs.end())
{
	...
}

// 指向第一个不有趣的 widget 指针.
list<Widget *>::iterator it2 = find_if(widgetPtrs.begin(), widgetPtrs.end(),
									   not1(ptr_fun(isInteresting)));
if (it2 != widgetPtrs.end())
{
	...
}

class Widget;
template <typename T>
class MeetsThreshold : public unary_function<Widget, bool>
{
private:
	const T threshold;

public:
	Meetsthreshold(const T &ts);
	bool operator()(const Widget &) const;
};

struct WidgetNameCompare : public binary_function<Widget, Widget, bool>
{
	bool operator()(const Widget &lhs, const Widget &rhs) const;
};

struct PtrWidgetNameCompare : public binary_function<const Widget *, const Widget *, bool>
{
	bool operator()(const Widget *lhs, const Widget *rhs) const;
};

// 3.10
// 条款 41 了解 ptr_fun、 mem_fun 和 mem_fun_ref的原因

// 条款 42 确定 less<T> 表示 operator <

class Widget
{
public:
	size_t weight() const;
	size_t maxSpeed() const;

	bool operator<(const Widget &lhs, const Widget &rhs)
	{
		return lhs.weight() < rhs.weight();
	}

private:
};

// err idea
template <>
struct Less<Widget> : public binary_function<Widget,
											 Widget,
											 bool>
{
	bool operator<(const Widget &lhs, const Widget &rhs) const
	{
		return lhs.maxSpeed() < rhs.maxSpeed();
	}
};

//
struct MaxSpeedCompare : public binary_function<Widget, Widget, bool>
{
	bool operator()(const Widget &lhs, const Widget &rhs) const
	{
		return lhs.maxSpeed() < rhs.maxSpeed();
	}
};
multiset<Widget, MaxSpeedCompare> widgets;
#endif

//										 使用 STL 编程

// 条款 43 尽量用算法调用代替手写循环

// 把所有元素从 data拷贝到 d的前端, 每个增加 41
// transform(data, data + numDobules,
//	inserter(d, d.begin()),
//	bind2nd(plus<doube>(), 41));

// 条款 44 尽量使用成员函数代替同名的算法

// 条款 45 注意 count、 find 、 binary_search 、 lower_bound、 upper_bound 和 equal_range的区别

// 3.11
// 条款 46 考虑使用函数对象代替函数作算法的参数

// 条款 47 避免产生只写代码

// 条款 48 总是#include适当的头文件

// 条款 49 学习破解有关 STL 的编译器诊断信息

//...
//... end