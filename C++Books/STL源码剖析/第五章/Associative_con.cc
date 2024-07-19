#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

// 关联式容器.
// AVL 树.
// 单旋转  左左 右右 采用单旋,     左右 右左 采用双旋

typedef bool __rb_tree_color_type;
const __rb_tree_color_type __rb_tree_red = false;  // 红色为 0
const __rb_tree_color_type __rb_tree_black = true; // 黑色为 1

struct __rb_tree_node_base
{
    typedef __rb_tree_color_type color_type;
    typedef __rb_tree_node_base *base_ptr;

    color_type color; // 节点颜色，非红即黑
    base_ptr parent;  // RB 树的许多操作，必须知道父节点
    base_ptr left;    //  指向左节点
    base_ptr right;   //  指向右节点

    static base_ptr mininum(base_ptr x)
    {
        while (x->left != nullptr)
            x = x->left; // 一直向左走,就会找到最小值.
        return x;
    }

    static base_ptr maxinum(base_ptr x)
    {
        while (x->right != nullptr)
            x = x->right;
        return x;
    }
};

template <class Value>
struct __rb_tree_node : public __rb_tree_node_base
{
    typedef __rb_tree_node<Value> *link_type;
    Value value_field; // 节点值.
};

// 基层迭代器
struct __rb_tree_base_iterator
{
    typedef __rb_tree_node_base::base_ptr base_ptr;
    typedef bidirectional_iterator_tag iterator_category;
    typedef ptrdiff_t difference_type;

    base_ptr node; // 用来与容器之间产生一个连结关系 (make a reference)

    // 以下其实可以实现于 operator++内，因为再无他处调用此函数了.
    void increment()
    {
        if (node->right != nullptr)
        {
            node = node->right;
            while (node->left != nullptr)
            {
                node = node->left;
            }
        }
        else // 没有右节点, 状况2
        {
            base_ptr y = node->parent; // 找出父节点.
            while (node == y->right)   // 如果现行节点本身就是个右子节点.
            {
                node = y; // 就一直上溯, 直到 "不为右节点"为止.
                y = y->parent;
            }
            if (node->right != y) // 若此时的右子节点不等于此时的父节点.
            {
                node = y; // 状况 3 此时的父亲节点为解.
            } // 否则此时的node为解, 状况4.
        }
        // 以上判断 "若此时的右节点不等于此时的父节点" 是为了应付一种
        // 特殊情况: 我们欲寻找根节点的下一节点,而恰巧根节点无右子节点
        // 当然, 以上特殊做法必须配合 红黑树 根节点与特殊 header 之间的特殊关系.
    }

    // 同 ++
    void decrement()
    {
        if (node->color == __rb_tree_red && // 如果是红节点,且父节点等于自己.
            node->parent->parent == node)   // 状况 1 右节点即为解答.
            node = node->right;
        // 以上情况 发生于 node 为 header时, (亦即 node 为 end()时).
        // header 之右节点即 mostright 指向整棵树的max 节点.
        else if (node->left != nullptr)
        {
            base_ptr y = node->left;
            while (y->right != nullptr)
            {
                y = y->right;
                node = y;
            }
        }
        else
        {
            base_ptr y = node->parent;
            while (node == y->left)
            {
                node = y;
                y = y->parent;
            }
            node = y;
        }
    }
};

// 红黑树的正规迭代器.
template <class Value, class Ref, class Ptr>
struct __rb_tree_iterator : public __rb_tree_base_iterator
{
    typedef Value value_type;
    typedef Ref reference;
    typedef Ptr pointer;
    typedef __rb_tree_iterator<Value, Value &, Value *> iterator;
    typedef __rb_tree_iterator<Value, const Value &, const Value *> const_iterator;
    typedef __rb_tree_iterator<Value, Ref, Ptr> self;
    typedef __rb_tree_node<Value> *link_type;

    __rb_tree_iterator() {}
    __rb_tree_iterator(link_type x) { node = x; }
    __rb_tree_iterator(const iterator &it) { node = it.node; }

    reference operator*() const { return link_type(node)->value_field; }

#ifndef __SGI_STL_NO_ARROW_OPERATOR
    pointer operator->() const { return &(operator*()); }
#endif

    self &operator++()
    {
        increment();
        return *this;
    }
    self operator++(int)
    {
        self tmp = *this;
        increment();
        return tmp;
    }

    self &operator--()
    {
        decrement();
        return *this;
    }
    self operator--(int)
    {
        self tmp = *this;
        decrement();
        return tmp;
    }
};

// 元素插入操作 insert_equal()
// 插入新值，节点键允许重复. 返回值是一个 RB-tree 迭代器，指向新增节点

// template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
// typename rb_tree<Key, Value, KeyOfValue, Alloc>::insert_equal(const Value& v)
//{
//	link_type y = header;
//	link_type x = root(); // 从根节点开始.
//	while (x)
//	{
//		y = x;
//		x = key_compare(KeyOfValue()(v), key(x)) ? left(x) : right(x); //遇 "大" 往左, "小" 则右.
//	}
//	return __insert(x, y, v);
//	// x 为新值插入点, y为其父节点， v为新值.
// }

// insert_unique()
// 插入新值, 节点键不允许重复, 若重复则插入无效.
// 返回值是 pair, 第一个元素是个 RB-tree 迭代器, 指向新增节点,
// 第二元素表示插入成功与否.

// template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
// pair<typename rb_tree<key,Value,KeyOfValue,Compare,Alloc>::iterator, bool>  rb_tree<Key,Value,KeyOfValue,Compare,Alloc>::
// insert_unique(const Value& v)
//{
//	link_type y = header;
//	link_type x = root();
//	bool comp = true;
//	while (x)
//	{
//		y = x;
//		x = comp ? left(x) : right(x);
//	}
//	// 离开 while循环后, y 所指即插入节点的父节点,此时 y 为叶子节点.
//
//	iterator j = iterator(y);  //令迭代器 j 指向插入点父节点 y.
//	if (comp) // 如果离开 while 循环时, comp 为真, (表示遇 "大" , 将插入于左侧)
//	{
//		if (j == begin()) // 如果插入点的父节点是最左节点.
//			return pair<iterator, bool>(__insert(x, y, v), true);
//		else //否则, 插入点的父节点不为最左节点.
//			--j;
//	}
//	if (key_compare(key(j.node), KeyOfValue(v)))
//	{
//		// 小于新值, 表示遇到 " 小 " 则插入右侧.
//		return pair<iterator, bool>(__insert(x, y, v), true);
//	}
//	// 如果到此, 表示新值一定与树中键重复,则不该插入新值.
//	return  pair<iterator, bool>(j, false);
// }

inline void __rb_tree_rotate_left(__rb_tree_node_base *x, __rb_tree_node_base *&root)
{
    // x 为旋转点.
    __rb_tree_node_base *y = x->right; // 令 y 为旋转点的右子节点.
    x->right = y->left;

    if (y->left != nullptr)
    {
        y->left->parent = x;
    }
    y->parent = x->parent;

    if (x == root)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

inline void __rb_tree_rotate_right(__rb_tree_node_base *x, __rb_tree_node_base *&root)
{
    // x 为旋转点
    __rb_tree_node_base *y = x->left; // y为旋转点的左子结点.
    x->left = y->right;
    if (y->right != nullptr)
    {
        y->right->parent = x;
    }
    y->parent = x->parent;

    // 令 y 完全顶替 x 的地位, (必须将 x 对其 父节点的关系完全接受过来)
    if (x == root)
        root = y;
    else if (x == x->parent->right) // x 为其父节点的右节点
        x->parent->right = y;
    else
        x->parent->left = y; // x 为其父节点的左节点
    y->right = x;
    x->parent = y;
}

// 寻找 红黑树中是否有键值为 k 的节点.
// template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
// typename rb_tree<Key,Value,KeyOfValue, Compare, Alloc>::iterator
// rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::find() (const Key& k)
//{
//	link_type y = header;
//	link_type x = root();
//
//	while (x != nullptr)
//	{
//		// 以下，key_compare 是节点键值大小比较准则, 应该是个 function object.
//		 y = x;
//		if (!key_compare(key(x), k))
//		{
//			// 表示 x 键大于k, 向左走.
//			x = left(x);
//		}
//		else
//		{
//			x = right(x);
//		}
//		inteator j = iterator(y);
//		return (j == end() || key_compare(k, key(j.node))) ? end() : j;
//	}
//}

// hash table
template <class Value>
struct __Hashtable_node
{
    __Hashtable_node *next; //[·]->
    Value val;              //[  ]   这是个 __Hashtable_node 对象.
};

// int main()
// {

// multimap<int, string> mp;
// mp.insert(make_pair(1, "apple"));
// mp.insert(make_pair(2, "banana"));
// mp.insert(make_pair(3, "cherry"));
// mp.insert(make_pair(1, "avocade"));

// for (const auto& pair : mp)
//{
//	cout << pair.first << ": " << pair.second << endl;
// }

// set 示例
// int i;
// int ia[5] = { 0,1,3,2,4 };
// set<int,greater<int>> s(ia, ia + 5);
// cout << s.size() << endl;
// s.insert(3);
// for (auto e : s)
//{
//	cout << e << ' ';
// }
// cout << endl;

// set<int, greater<int>>::iterator it = find(s.begin(), s.end(), 3);
// if (it != s.end())
//	cout << "3 found!\n"<<endl;

// map示例
// map<string, int> map;

// map[string("jjhou")] = 1;
// map[string("jerry")] = 2;
// map[string("zason")] = 3;
// map[string("jimmy")] = 4;

// pair<string, int> val(string("david"), 5);
// map.insert(val);

// map<string, int>::iterator it = map.begin();
// for(;it != map.end();++it)
//	cout << it->first << " "
//	<< it->second << endl;

// auto it1 = map.find(string("jerry"));
// it1->second = 9;
// int n = map[string("jerry")];
// cout << n << endl;

//     return 0;
// }
