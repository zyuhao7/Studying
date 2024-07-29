#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <numeric>
#include <iterator>
#include <functional>
using namespace std;
// 6. 算法.
// 质变算法 - 会改变操作对象之值
// int main()
//{
//	int a[] = { 22,30,30,17,33,40,17,23,22,12,20 };
//	vector<int> v(a, a + sizeof(a) / sizeof(int));
//	vector<int>::const_iterator it = v.begin();
//	vector<int>::const_iterator it2 = v.end();
//	sort(it,it2); //报错.
//	return 0;
//}

// 非质变算法.
// template<class T>
// struct Plus {
//	void operator()(T& x) const {
//		x += 2;
//		cout << x << " ";
//	}
//
// };
// int main()
//{
//	int a[] = {22,12,30,17,40,23,40};
//	vector<int> v(a, a + sizeof(a) / sizeof(int));
//	for_each(v.begin(), v.end(), Plus<int>());
// }

// int main()
//{
//	const int arraySize = 7;
//	int a[arraySize] = { 0,1,2,3,4,5,6 };
//	int* end = a + arraySize; // 最后元素的下一个位置.
//
//	int* ip = find(a, a + sizeof(a) / sizeof(int), 4);
//	if 1ip == end) cout << "4 not found" << endl;
//	else cout << "4 found. " << *ip << endl;
// }

// 泛化的find()函数.
// template<class Iterator, class T>
// Iterator find(Iterator begin, Iterator end, const T& val)
//{
//	while (begin != end && *begin != val) ++begin;
//
//	return begin;
// }

// 6.3 数值算法 <stl_numeric.h> 示例.

// int main()
//{
//	int a[5] = { 1,2,3,4,5 };
//	vector<int> v(a, a + 5);
//
//	cout << accumulate(v.begin(), v.end(), 0) << endl;
//	//15       0 + 1 + 2 + 3 + 4 + 5
//
//	cout << accumulate(v.begin(), v.end(), 0, minus<int>()) << endl;
//	//-15      0 - 1 - 2 - 3 - 4 - 5
//
//	cout << inner_product(v.begin(), v.end(), v.begin(), 10) << endl;
//	//65 10 + 1*1 + 2*2 + 3*3 + 4*4 + 5*5
//
//	cout << inner_product(v.begin(), v.end(), v.begin(), 10, minus<int>(), plus<int>()) << endl;
//	//-20 10 - 1+1 - 2+2 - 3+3 - 4+4 - 5+5
//
//	//以下这个迭代器将绑定到cout,作为输出用.
//	ostream_iterator<int> oite(cout, " ");
//
//	partial_sum(v.begin(), v.end(), oite); cout << endl;
//	// 1 3 6 10 15  (第 n 个新元素是前 n 个旧元素的相加总计).
//
//	partial_sum(v.begin(), v.end(), oite, minus<int>()); cout << endl;
//	// 1 -1 -4 -8 -13 (第 n 个新元素是前 n 个旧元素的运算总计).
//
//	adjacent_difference(v.begin(), v.end(), oite); cout << endl;
//	// 1 1 1 1 1 (#1 元素照录, #n 新元素等于 #n旧元素 - #n-1 旧元素).
//	// 5 -1 -1 -1 -1 (逆序)
//
//	adjacent_difference(v.begin(), v.end(), oite, plus<int>());cout << endl;
//	//1 3 5 7 9 (#1 元素照录, #n 新元素等于 op(#n 旧元素, #旧元素)).
//
//	cout << pow(10, 3) << endl; // 10^3
//	cout << power(10, 3,plus<int>()) << endl; // 10+10+10 不存在power函数.
//
//	int n = 3;
//	iota(v.begin(), v.end(), 9); //在指定区间填入 n n+1 n+2
//	for (int i = 0;i < v.size();++i)
//		cout << v[i] << " ";
//	cout << endl;
//	return 0;
// }

// 6.3.2 accumulate
// 版本1
// template<class InputIterator, class T>
// T accumulate(InputIterator first, InputIterator last, T init)
//{
//	for (;first != last;++first)
//		init = init + *first;
//	return init;
//}
//
////版本2
// template<class InputIterator, class T, class BinaryOperation>
// T accumulate(InputIterator first, InputIterator last, T init, BinaryOperation binary_op)
//{
//	for (;first != last;++first)
//		init = binary_op(init, *first);
//	return init;
// }

// 6.3.3 adjacent_difference
// 版本1

// template<class InputIterator, class OutputIterator>
// OutputIterator adjacent_difference(InputIterator first, InputIterator last, OutputIterator result)
//{
//	if 1first == last) return result;
//	*result = *first; // 首先记录第一个元素.
//	return __adjacent_difference(first, last, result, value_type(first));
// }
//
// template<class InputIterator, class OutputIterator, class T>
// OutputIterator __adjacent_difference(InputIterator first, InputIterator last, OutputIterator result, T*)
//{
//	T val = *first;
//	while (++first != last)
//	{
//		T tmp = *first;
//		*++result = tmp - val;
//		val = tmp;
//	}
//	return ++result;
// }
//
//// 侯捷认为, 不需要像上行那样传递调用，可改用一下方法.
// if 1first == last) return result;
//*result = *first;
// iterator_traits<InputIterator>::value_type val = *first;
// while (++first != last) {
//  	同__adjacent_difference() 内容.
// }

// 版本2

// template<class InputIterator, class OutputIterator, class BinaryOperation>
// OutputIterator adjacent_difference(InputIterator first, InputIterator last,
//	OutputIterator result,
//	BinaryOperation binary_op)
//{
//	if 1first == last) return result;
//	*result = *first;
//	return result;
// }
//
// template<class InputIterator, class OutputIterator,class T, class BinaryOperation>
// OutputIterator __adjacent_difference(InputIterator first, InputIterator last,
//	OutputIterator result, T*,
//	BinaryOperation binary_op)
//{
//	T val = *first;
//	while (++first != last)
//	{
//		T tmp = *first;
//		*++result = binary_op(tmp, val);
//		val = tmp;
//	}
//	return ++result;
// }

// 6.3.4 inner_product

// 版本 1
// template<class InputIterator1, class InputIterator2, class T>
// T inner_product(InputIterator1 first1, InputIterator1 last1,
//	InputIterator2 first2, T init)
//{
//	//以第一序列之元素个数为据, 将两个序列都走一遍.
//	for (;first1 != last1;++first1, ++first2)
//		init = init + (*first1 * *first2);
//	return init;
// }
//
////版本 2
// template<class InputIterator1, class InputIterator2, class T,
//          class BinaryOperation1, class BinaryOperation2>
// T inner_product(InputIterator1 first1, InputIterator1 last1,
//	InputIterator2 first2, T init, BinaryOperation1 binary_op1,
//	BinaryOperation2 binary_op2)
//{
//	for (;first1 != last1; ++first1, ++first2)
//		init = binary_op1(init, binary_op2(*first1, *first2));
//	return init;
// }

// 6.3.5 partial_sum
// 版本1
// template<class InputIterator, class OutputIterator>
// OutputIterator partial_sum(InputIterator first, InputIterator last,
//	OutputIterator result)
//{
//	if 1first == last) return result;
//	*result = *first;
//	return __partial_sum(first,last,result,value_type(first));
// }
//
// template<class InputIterator, class OutputIterator, class T>
// OutputIterator __partial_sum(InputIterator first, InputIterator last,
//	OutputIterator result, T*)
//{
//	T val = *first;
//	while (++first != last)
//	{
//		val = val + *first;
//		*++result = val;
//	}
//	return ++result;
// }

// 版本2
// template<class InputIterator, class OutputIterator, class BinaryOperation>
// OutputIterator partial_sum(InputIterator first, InputIterator last,
//	OutputIterator result, BinaryOperation binary_op)
//{
//	if 1first == last) return result;
//	*result = *first;
//	return __partial_sum(first, last, result, value_type(first), binary_op);
// }
//
// template<class InputIterator, class OutputIterator, class T,
//          class BinaryOperation>
// OutputIterator __partial_sum(InputIterator first, InputIterator last,
//	OutputIterator result, T*,
//	BinaryOperation binary_op)
//{
//	T val = *first;
//	while (++first != last)
//	{
//		val = binary_op(val, *first);
//		*++result = val;
//	}
//	return ++result;
// }

// 6.3.6 power
// 版本1 乘幂

// template<class T, class Integer>
// inline T power(T x, Integer n)
//{
//	return power(x, n, multiplies<T>()); //指定运算为乘法.
// }

// 6.3.7 itoa
// template<class ForwardIterator, class t>
// void iota(ForwardIterator first, ForwardIterator last, T val)
//{
//	while (first != last) *first++ = val++;
// }

// 6.4 基本算法. 示例
#if 1
template <class T>
struct display
{
    void operator()(const T &x) const
    {
        cout << x << ' ';
    }
};

int main()
{
    int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    vector<int> v1(a, a + 5);
    vector<int> v2(a, a + 7);

    //  {0, 1, 2, 3, 4} v.s {0, 1, 2, 3, 4, 5, 6, 7, 8}
    cout << *(mismatch(v1.begin(), v1.end(), v2.begin()).first) << endl;
    cout << *(mismatch(v1.begin(), v1.end(), v2.begin()).second);
    //  判断两个区间的第一个不匹配点,返回一个由两个迭代器组成的 pair,
    // 其中第一个迭代器指向第一区间的不匹配点, 第二个迭代器指向第二区间的不匹配点.
    //  上述写法有风险, 应先判断迭代器是否不等于 end(), 才能做输出操作.

    // 如果两个序列在 [first, last) 区间内相等, equal() 返回true
    // 如果第二序列的元素比较多, 多出来的元素不予考虑.

    // cout << equal(v1.begin(), v1.end(), v2.begin())<<endl;//1

    // cout << equal(v1.begin(), v1.end(), &a[3])<<endl;// 0
    //  {0 1 2 3 4} != {3,4,5,6,7}

    // cout << equal(v1.begin(), v1.end(), &a[3], less<int>())<<endl; // 1
    //  {0 1 2 3 4} < {3,4,5,6,7}

    // fill(v1.begin(), v1.end(), 9); // 区间内全部填 9
    // for_each(v1.begin(), v1.end(), display<int>()); cout << endl;

    // fill_n(v1.begin(), 3, 7);
    // for_each(v1.begin(), v1.end(), display<int>()); cout << endl;

    // vector<int>::iterator it1 = v1.begin(); // 7779 指向7
    // vector<int>::iterator it2 = it1;

    // advance(it2, 3);//指向9
    // iter_swap(it1, it2); //将两个迭代器所指元素交换.

    // cout << max(*it1, *it2) << endl;
    // cout << min(*it1, *it2) << endl;

    // for_each(v1.begin(), v1.end(), display<int>());cout << endl;
    // for_each(v2.begin(), v2.end(), display<int>());cout << endl;

    // swap(*v1.begin(), *v2.begin());

    // for_each(v1.begin(), v1.end(), display<int>());cout << endl;
    // for_each(v2.begin(), v2.end(), display<int>());cout << endl;

    // 343

    return 0;
}
#endif
// copy_overlap

#if 1
template <class T>
struct display
{
    void operator()(const T &x)
    {
        cout << x << " ";
    }
};

int main()
{
    int ia[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

    // 以下, 输出区间的终点与输入区间重叠, 没问题.
    copy(ia + 2, ia + 7, ia);
    for_each(ia, ia + 9, display<int>()); // 2 3 4 5 6 5 6 7 8
    cout << endl;

    int ia[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    // 以下, 输出区间的起点与输入区间重叠, 可能有问题.
    copy(ia + 2, ia + 7, ia + 4);
    for_each(ia, ia + 9, display<int>()); // 0 1 2 3 2 3 4 5 6 本例结果正确, 因为调用的 copy 算法用的 memmove() 执行的.
    cout << endl;
    int ia[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    deque<int> id(ia, ia + 9);
    deque<int>::iterator first = id.begin();
    deque<int>::iterator last = id.end();
    ++first; // advance(first, 1)  //1
    cout << *first << endl;
    --last;
    cout << *last << endl; // 8
    deque<int>::iterator result = id.begin();
    cout << *result << endl; // 0

    // 以下, 输出区间的终点与输入区间重叠, 没问题.
    copy(first, last, result);
    for_each(id.begin(), id.end(), display<int>()); // 1 2 3 4 5 6 7 7 8
    cout << endl;
    int ia[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    deque<int> id(ia, ia + 9);
    deque<int>::iterator first = id.begin();
    deque<int>::iterator last = id.end();
    ++first;
    --last;
    deque<int>::iterator result = id.begin();

    advance(result, 4);
    copy(first, last, result);
    for_each(id.begin(), id.end(), display<int>()); // 0 1 2 3 1 2 3 4 5 本例copy不使用memmove执行复制.
    cout << endl;
}
#endif

#if 1
int main()
{
    int ia1[6] = {1, 3, 5, 6, 9, 11};
    int ia2[7] = {1, 1, 2, 3, 5, 8, 13};

    multiset<int> S1(ia1, ia1 + 6);
    multiset<int> S2(ia2, ia2 + 7);

    for_each(S1.begin(), S1.end(), display<int>());
    cout << endl;
    for_each(S2.begin(), S2.end(), display<int>());
    cout << endl;

    multiset<int>::iterator first1 = S1.begin();
    multiset<int>::iterator last1 = S1.end();
    multiset<int>::iterator first2 = S2.begin();
    multiset<int>::iterator last2 = S2.end();

    cout << "Union of S1 and S2:";
    set_union(first1, last1, first2, last2, ostream_iterator<int>(cout, " ")); // 1 1 2 3 5 6 8 9 11 13
    cout << endl;

    first1 = S1.begin();
    first2 = S2.begin();
    cout << "Intersection of S1 and S2:";
    set_intersection(first1, last1, first2, last2, ostream_iterator<int>(cout, " ")); // 1 3 5
    cout << endl;

    first1 = S1.begin();
    first2 = S2.begin();
    cout << "Difference of S1 and S2 (S1 - S2)";
    set_difference(first1, last1, first2, last2, ostream_iterator<int>(cout, " ")); // 6 9 11
    cout << endl;

    first1 = S1.begin();
    first2 = S2.begin();
    cout << "Symmetric difference of S1 and S2: ";
    set_symmetric_difference(first1, last1, first2, last2, ostream_iterator<int>(cout, " ")); // 1 2 6 8 9 11 13
    cout << endl;

    return 0;
}
#endif

#if 1
template <class T>
struct display
{
    void operator()(const T &x) const
    {
        cout << x << " ";
    }
};

struct even
{
    bool operator()(int x) const
    {
        return x % 2 ? false : true;
    }
};

class even_by_two
{
public:
    int operator()() const
    {
        return _x += 2;
    }

private:
    static int _x;
};

int even_by_two::_x = 0;

int main()
{
    int ia[] = {0, 1, 2, 3, 4, 5, 6, 6, 6, 7, 8};
    vector<int> iv(ia, ia + sizeof(ia) / sizeof(int));

    // 找出 iv 职中相邻元素相等的第一个元素.
    cout << *adjacent_find(iv.begin(), iv.end()) << endl; // 6

    // 找出 iv 职中相邻元素相等的第一个元素.
    cout << *adjacent_find(iv.begin(), iv.end(), equal_to<int>()) << endl; // 6

    // 找出 iv 中元素值为 6 的元素个数.
    cout << count(iv.begin(), iv.end(), 6) << endl; // 3

    // 找出 iv 中小于7的元素个数.
    cout << count_if(iv.begin(), iv.end(), bind2nd(less<int>(), 7)) << endl; // 9

    // 找出 iv 中元素值为 4 的第一个元素所在的位置的值?
    cout << *find(iv.begin(), iv.end(), 4) << endl; //  4

    // 找出 iv 中 大于2的第一个元素所在的位置的值.
    cout << *find_if(iv.begin(), iv.end(), bind2nd(greater<int>(), 2)) << endl; // 3

    // 找出 iv 中子序列 iv2 所出现的最后一个位置(再往后3个位置的值)
    vector<int> iv2(ia + 6, ia + 8);
    cout << *(find_end(iv.begin(), iv.end(), iv2.begin(), iv2.end()) + 3) << endl; // 8

    // 迭代遍历整个 iv 区间, 对每一个元素施行 display 操作.
    for_each(iv.begin(), iv.end(), display<int>()); // 0 1 2 3 4 5 6 6 6 7 8
    cout << endl;

    // 迭代遍历整个 iv2 区间, 对每个元素施行 even_by_two 操作.
    generate(iv2.begin(), iv2.end(), even_by_two());
    for_each(iv2.begin(), iv2.end(), display<int>()); // 2 4
    cout << endl;

    // 迭代遍历指定区间, 对每个元素执行 even_by_two 操作.
    generate_n(iv.begin(), 3, even_by_two());
    for_each(iv.begin(), iv.end(), display<int>()); // 6 8 10 3 4 5 6 6 6 7 8
    cout << endl;

    // 删除元素 6.
    remove(iv.begin(), iv.end(), 6);
    for_each(iv.begin(), iv.end(), display<int>()); // 8 10 3 4 5 7 8 6 6 7 8

    // 删除元素6, 结果置于另一区间.
    vector<int> iv3(12);
    remove_copy(iv.begin(), iv.end(), iv3.begin(), 6);
    for_each(iv3.begin(), iv3.end(), display<int>()); // 8 10 3 4 5 7 8 6 6 7 8 8 10 3 4 5 7 8 7 8 0 0 0
    cout << endl;

    // 删除小于7的元素, 结果置于另一区间.
    remove_copy_if(iv.begin(), iv.end(), iv3.begin(), bind2nd(less<int>(), 7));
    for_each(iv3.begin(), iv3.end(), display<int>()); // 8 10 7 8 7 8 8 7 8 0 0 0
    cout << endl;

    // 将所有元素值为6改为3.
    replace(iv.begin(), iv.end(), 6, 3);
    for_each(iv.begin(), iv.end(), display<int>()); // 8 10 3 4 5 7 8 3 3 7 8
    cout << endl;

    // 将所有元素值为 3 改为 5, 置于另一区间.
    replace_copy(iv.begin(), iv.end(), iv3.begin(), 3, 5);
    for_each(iv3.begin(), iv3.end(), display<int>()); // 8 10 5 4 5 7 8 5 5 7 8 0
    cout << endl;

    // 将所有小于 5 的值, 改为 2.
    replace_if(iv.begin(), iv.end(), bind2nd(less<int>(), 5), 2);
    for_each(iv.begin(), iv.end(), display<int>()); // 8 10 2 2 5 7 8 2 2 7 8
    cout << endl;

    // 逆向重排每一个元素.
    reverse(iv.begin(), iv.end());
    for_each(iv.begin(), iv.end(), display<int>()); // 8 7 2 2 8 7 5 2 2 10 8
    cout << endl;

    // 旋转 (first, middle) 和 (middle, last)
    rotate(iv.begin(), iv.begin() + 4, iv.end());
    for_each(iv.begin(), iv.end(), display<int>()); // 8 7 5 2 2 10 8 8 7 2 2
    cout << endl;

    // 查找某个子序列的第一次出现地点.
    int ia2[3] = {2, 8};
    vector<int> iv4(ia2, ia2 + 2);
    cout << *search(iv.begin(), iv.end(), iv4.begin(), iv4.end()) << endl; // 0

    // 改变区间的值, 全部减 2.
    transform(iv.begin(), iv.end(), iv.begin(), bind2nd(minus<int>(), 2));
    for_each(iv.begin(), iv.end(), display<int>()); // 6 5 3 0 0 8 6 6 5 0 0
    cout << endl;

    // 令第二区间的元素值加到第一区间上.
    transform(iv.begin(), iv.end(), iv.begin(), iv.begin(), plus<int>());
    for_each(iv.begin(), iv.end(), display<int>()); // 12 10 6 0 0 16 12 12 10 0 0
    cout << endl;

    vector<int> iv5(ia, ia + sizeof(ia) / sizeof(int));
    vector<int> iv6(ia + 4, ia + 8);
    vector<int> iv7(15);
    for_each(iv5.begin(), iv5.end(), display<int>()); // 0 1 2 3 4 5 6 6 6 7 8
    cout << endl;

    for_each(iv6.begin(), iv6.end(), display<int>()); // 4 5 6 6
    cout << endl;

    cout << *max_element(iv5.begin(), iv5.end()) << endl; // 8
    cout << *min_element(iv5.begin(), iv5.end()) << endl; // 0

    // 判断是否 iv6 内的所有元素都在 iv5出现. 两个序列都必须是 sorted ranges
    cout << includes(iv5.begin(), iv5.end(), iv6.begin(), iv6.end()) << endl; // 1 (TRUE)

    merge(iv5.begin(), iv5.end(), iv6.begin(), iv6.end(), iv7.begin());
    for_each(iv7.begin(), iv7.end(), display<int>()); // 0 1 2 3 4 4 5 5 6 6 6 6 6 7 8
    cout << endl;

    // 符合条件的元素放在容器前段, 不符合的元素放在后段. 不保证保留原相对次序.
    partition(iv7.begin(), iv7.end(), even());
    for_each(iv7.begin(), iv7.end(), display<int>()); // 0 8 2 6 4 4 6 6 6 6 5 5 3 7 1
    cout << endl;

    // 去除 "连续而重复" 的元素
    unique(iv5.begin(), iv5.end());
    for_each(iv5.begin(), iv5.end(), display<int>()); // 0 1 2 3 4 5 6 7 8 7 8
    cout << endl;

    // 去除 "连续而重复"的元素,结果置于另一处.
    unique_copy(iv5.begin(), iv5.end(), iv7.begin());
    for_each(iv7.begin(), iv7.end(), display<int>()); // 0 1 2 3 4 5 6 7 8 7 8 5 3 7 1
    cout << endl;

    return 0;
}
#endif
