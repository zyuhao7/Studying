#include <vector>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <deque>
#include <list>
using namespace std;


// day-2025-6-5
// 第三章-迭代器
//class num_iterator {
//	int i;
//public:
//	explicit num_iterator(int position = 0) : i{ position } {}
//
//	int operator*() const { return i; }
//
//	num_iterator& operator++() {
//		++i;
//		return *this;
//	}
//
//	bool operator!=(const num_iterator& other) const {
//		return i != other.i;
//	}
//};
//
//class num_range {
//	int a;
//	int b;
//public:
//	num_range(int from, int to)
//		: a{ from }, b{ to }
//	{
//	}
//	num_iterator begin() const { return num_iterator{ a }; }
//	num_iterator end() const { return num_iterator{ b }; }
//};
//
//int main()
//{
//	for (int i : num_range{ 100, 110 }) {
//		std::cout << i << " ";
//	}
//	std::cout << '\n';
//
//}

// for (auto x : range) { code_block; }
// 翻译成以下代码:
//{
//    auto __begin = std::begin(range);
//    auto __end = std::end(range);
//    for (; __begin != __end; ++__begin) {
//        auto x = *__begin;
//        code_block
//    }
//}

// 让自己的迭代器与STL的迭代器兼容
//class num_iterator
//{
//    int i;
//public:
//
//    using iterator_category = std::forward_iterator_tag;
//    using value_type = int;
//    using difference_type = std::ptrdiff_t;
//    using pointer = const int*;
//    using reference = int;
//
//
//    explicit num_iterator(int position = 0) : i{ position } {}
//    int operator*() const { return i; }
//    num_iterator& operator++() {
//        ++i;
//        return *this;
//    }
//    bool operator!=(const num_iterator& other) const {
//        return i != other.i;
//    }
//    bool operator==(const num_iterator& other) const {
//        return !(*this != other);
//    }
//};
//
//class num_range {
//    int a;
//    int b;
//public:
//    num_range(int from, int to)
//        : a{ from }, b{ to }
//    {
//    }
//    num_iterator begin() const { return num_iterator{ a }; }
//    num_iterator end() const { return num_iterator{ b }; }
//};
//
//
//int main()
//{
//    num_range r{ 100, 110 };
//    auto min_max(minmax_element(r.begin(), r.end()));
//    cout << *min_max.first << " - " << *min_max.second << '\n';
//}

// 使用迭代适配器填充通用数据结构

//int main()
//{
//	istream_iterator<int> it_cin{ cin };
//	istream_iterator<int> end_cin;
//
//	deque<int> v;
//	copy(it_cin, end_cin, back_inserter(v));
//
//	istringstream sstr{ "123 456 789" };
//
//	auto deque_middle(next(begin(v), static_cast<int>(v.size()) / 2)); // 向前移动的步数.
//
//	copy(istream_iterator<int>{sstr}, {}, inserter(v, deque_middle));
//
//	initializer_list<int> il2{ -1, -2, -3 };
//	copy(begin(il2), end(il2), front_inserter(v));
//
//	copy(begin(v), end(v), ostream_iterator<int>{cout, "  "});
//	cout << '\n';
//
//	return 0;
//}

// 使用迭代器实现算法
//class fibit
//{
//    size_t i{ 0 };
//    size_t a{ 0 };
//    size_t b{ 1 };
//public:
//    fibit() = default;
//    explicit fibit(size_t i_)
//        : i{ i_ }
//    {
//    }
//    size_t operator*() const { return b; }
//    fibit& operator++() {
//        const size_t old_b{ b };
//        b += a;
//        a = old_b;
//        ++i;
//        return *this;
//    }
//    bool operator!=(const fibit& o) const { return i != o.i; }
//};
//
//class fib_range
//{
//    size_t end_n;
//public:
//    fib_range(size_t end_n_)
//        : end_n{ end_n_ }
//    {
//    }
//    fibit begin() const { return fibit{}; }
//    fibit end() const { return fibit{ end_n }; }
//};
//
//
//int main()
//{
//    for (size_t i : fib_range(10)) {
//        std::cout << i << " ";
//    }
//    std::cout << '\n';
//}

// 使用反向迭代适配器进行迭代

//int main()
//{
//	list<int> l{ 1, 2, 3, 4, 5 };
//	copy(l.rbegin(), l.rend(), ostream_iterator<int>{cout, " "});
//	cout << endl;
//	copy(make_reverse_iterator(end(l)),
//		make_reverse_iterator(begin(l)),
//		ostream_iterator<int>{cout, " "});
//
//	cout << endl;
//}

// 使用哨兵终止迭代

//class cstring_iterator_sentinel {};
//class cstring_iterator {
//	const char* s{ nullptr };
//public:
//    explicit cstring_iterator(const char* str)
//        : s{ str }
//    {
//    }
//    char operator*() const { return *s; }
//    cstring_iterator& operator++() {
//        ++s;
//        return *this;
//    }
//    bool operator!=(const cstring_iterator_sentinel) const {
//        return s != nullptr && *s != '\0';
//    }
//};
//
//class cstring_range {
//    const char* s{ nullptr };
//public:
//    cstring_range(const char* str)
//        : s{ str }
//    {
//    }
//    cstring_iterator begin() const {
//        return cstring_iterator{ s };
//    }
//    cstring_iterator_sentinel end() const {
//        return {};
//    }
//};
//
//int main(int argc, char* argv[])
//{
//    if (argc < 2) {
//        std::cout << "Please provide one parameter.\n";
//        return 1;
//    }
//    for (char c : cstring_range(argv[1])) {
//        std::cout << c;
//    }
//    std::cout << '\n';
//}

int main()
{
    std::vector<int> v{ 1, 2, 3 };
    v.shrink_to_fit();
    const auto it(std::begin(v));
    std::cout << *it << '\n';
    v.push_back(123);
    std::cout << *it << '\n'; // bad bad bad!
}