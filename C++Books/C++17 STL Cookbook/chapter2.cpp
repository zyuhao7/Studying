#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <unordered_map> 
#include <functional>
#include <list>
#include <queue>
#include <tuple>
#include <set>
#include <map>
#include <stack>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include <iomanip>


using namespace std;

// 第2章 STL容器
//day-2025-6-2
//template <typename T>
//void quick_remove_at(std::vector<T>& v, std::size_t idx)
//{
//	if (idx < v.size()) {
//		v[idx] = std::move(v.back());
//		v.pop_back();
//	}
//}
//template <typename T>
//void quick_remove_at(std::vector<T>& v,
//	typename std::vector<T>::iterator it)
//{
//	if (it != std::end(v)) {
//		*it = std::move(v.back());
//		v.pop_back();
//	}
//}

//void insert_sorted(vector<string>& v, const string& word)
//{
//	const auto insert_pos(lower_bound(begin(v), end(v), word));
//	v.insert(insert_pos, word);
//}
//
//template <typename C, typename T>
//void insert_sorted(C& v, const T& item)
//{
//	const auto insert_pos(lower_bound(begin(v), end(v), item));
//	v.insert(insert_pos, item);
//}

//int main()
//{
	//vector<int> v{ 1, 2, 3, 2, 5, 2, 6, 2, 4, 8 };
	//const auto new_end(remove(begin(v), end(v), 2));
	//v.erase(new_end, end(v));
	//for (auto i : v) {
	//	cout << i << " ";
	//}
	//cout << endl;

	//const auto odd = [](int i) {return i % 2 == 1;};
	//v.erase(remove_if(begin(v), end(v), odd), end(v));
	//for (auto i : v) {
	//	cout << i << " ";
	//}
	//cout << endl;
	//cout << v.capacity() << endl; // 10
	//v.shrink_to_fit();
	//cout << v.capacity() << endl; // 3

	//std::vector<int> v{ 123, 456, 789, 100, 200 };

	//quick_remove_at(v, 2);
	//for (int i : v) {
	//	std::cout << i << ", ";
	//}
	//std::cout << '\n';

	//quick_remove_at(v, std::find(std::begin(v), std::end(v), 123));
	//for (int i : v) {
	//	std::cout << i << ", ";
	//}
	//std::cout << '\n';

	//const size_t container_size{ 1000 };
	//vector<int> v(container_size, 123);

	//cout << "Out of range element value: "
	//	<< v[container_size + 10] << '\n';

	//cout << "Out of range element value: "
	//	<< v.at(container_size + 10) << '\n';

	/*vector<string> v{ "some", "random", "words",
					 "without", "order", "aaa",
					 "yyy" };
	assert(false == is_sorted(begin(v), end(v)));
	sort(begin(v), end(v));
	assert(true == is_sorted(begin(v), end(v)));
	insert_sorted(v, "foobar");
	insert_sorted(v, "zzz");

	for (const auto& w : v) {
		cout << w << " ";
	}
	cout << '\n';*/



//	return 0;
//}

// 向std::map实例中高效并有条件的插入元素
//struct billionaire {
//	string name;
//	double dollars;
//	string country;
//};

//int main()
//{
	//list<billionaire> billionaires{
	//	{"Bill Gates", 86.0, "USA"},
	//	{"Warren Buffet", 75.6, "USA"},
	//	{"Jeff Bezos", 72.8, "USA"},
	//	{"Amancio Ortega", 71.3, "Spain"},
	//	{"Mark Zuckerberg", 56.0, "USA"},
	//	{"Carlos Slim", 54.5, "Mexico"},
	//	{"Bernard Arnault", 41.5, "France"},
	//	{"Liliane Bettencourt", 39.5, "France"},
	//	{"Wang Jianlin", 31.3, "China"},
	//	{"Li Ka-shing", 31.2, "Hong Kong"}
	//};

	//map<string, pair<const billionaire, size_t>> m;

	//for (const auto& b : billionaires) {
	//	auto [iterator, success] = m.try_emplace(b.country, b, 1);
	//	if (!success) {
	//		iterator->second.second += 1;
	//	}
	//}

	//for (const auto& [key, value] : m) {
	//	const auto& [b, count] = value;
	//	cout << b.country << " : " << count
	//		<< " billionaires. Richest is "
	//		<< b.name << " with " << b.dollars
	//		<< " B$\n";
	//}

	//std::map<std::string, size_t> m{ {"b", 1}, {"c", 2}, {"d", 3} };
	//auto insert_it(std::end(m));

	//for (const auto& s : { "z", "y", "x", "w" }) {
	//	insert_it = m.insert(insert_it, { s, 1 });
	//}

	//m.insert(std::end(m), { "a", 1 });

	//for(const auto& [key, value] : m) {
	//	std::cout << "\"" << key << "\": " << value << ", ";
	//}
	//std::cout << '\n';

//}

// day-2025-6-3
// 高效的修改std::map元素的键值
//template <typename M>
//void print(const M& m)
//{
//	cout << "Race placement:\n";
//	for (const auto& [placement, driver] : m) {
//		cout << placement << ": " << driver << '\n';
//	}
//}
//int main()
//{
//	map<int, string> race_placement{
//	   {1, "Mario"}, {2, "Luigi"}, {3, "Bowser"},
//	   {4, "Peach"}, {5, "Yoshi"}, {6, "Koopa"},
//	   {7, "Toad"}, {8, "Donkey Kong Jr."}
//	};
//	print(race_placement);
//
//	auto a(race_placement.extract(3));
//	auto b(race_placement.extract(8));
//
//	swap(a.key(), b.key());
//
//	race_placement.insert(move(a));
//	race_placement.insert(move(b));
//	
//	print(race_placement);
//}

// std::unordered_map中使用自定义类型
//struct coord {
//	int x;
//	int y;
//};
//
//bool operator==(const coord& l, const coord& r)
//{
//	return l.x == r.x && l.y == r.y;
//}
//
//namespace std
//{
//	template<>
//	struct hash<coord>
//	{
//		using argument_type = coord;
//		using result_type = size_t;
//
//		result_type operator()(const argument_type& c) const
//		{
//			return static_cast<result_type>(c.x) + static_cast<result_type>(c.y);
//		}
//
//	};
//}
//
//
//int main()
//{
//	std::unordered_map<coord, int> m{
//		{{0, 0}, 1},
//		{{0, 1}, 2},
//		{{2, 1}, 3}
//	};
//	for (const auto& [k, v] : m)
//	{
//		std::cout << "{(" << k.x << ", " << k.y
//			<< "): " << v << "} ";
//	}
//	cout << endl;
//
//}

// 通常实例化一个基于哈希的map表(比如: std::unordered_map)时，我们会这样写：
// std::unordered_map<key_type, value_type> my_unordered_map;
// 编译器为我们创建特化的std::unordered_map时，这句话背后隐藏了大量的操作。所以，让我们来看一下其完整的模板类型声明：
//template<
//	class Key,
//	class T,
//	class Hash = std::hash<Key>,
//	class KeyEqual = std::equal_to<Key>,
//	class Allocator = std::allocator< std::pair<const Key, T> >
//> class unordered_map;	


// 过滤用户的重复输入，并以字母序将重复信息打印出——std::set

//int main()
//{
//	set<string> s;
//	istream_iterator<string> it{ cin };
//	istream_iterator<string> end;
//
//	copy(it, end, inserter(s, s.end()));
//
//	for (const auto word : s) {
//		cout << word << " ";
//	}
//}

// 实现简单的逆波兰表示法计算器——std::stack

//map<string, double (*)(double, double)> ops{
//	   {"+", [](double a, double b) { return a + b; }},
//	   {"-", [](double a, double b) { return a - b; }},
//	   {"*", [](double a, double b) { return a * b; }},
//	   {"/", [](double a, double b) { return a / b; }},
//	   {"^", [](double a, double b) { return pow(a, b); }},
//	   {"%", [](double a, double b) { return fmod(a, b); }},
//};
//
//
//template<typename IT>
//double evaluate_rpn(IT it, IT end)
//{
//	stack<double> val_stack;
//	auto pop_stack([&]() {
//		auto r(val_stack.top());
//		val_stack.pop();
//		return r;
//		});
//
//	for (; it != end; ++it)
//	{
//		stringstream ss{ *it };
//		if (double val; ss >> val)
//		{
//			val_stack.push(val);
//		}
//		else
//		{
//			const auto r{ pop_stack() };
//			const auto l{ pop_stack() };
//			try
//			{
//				const auto& op(ops.at(*it));
//				const double result{ op(l, r)};
//				val_stack.push(result);
//			}
//			catch (const out_of_range&)
//			{
//				throw invalid_argument(*it);
//			}
//		}
//	}
//	// 检查栈是否恰好剩下一个结果
//	if (val_stack.size() != 1) {
//		throw invalid_argument("Invalid RPN expression");
//	}
//	return val_stack.top();
//}
//
//int main()
//{
//
//	vector<string> expr2{ "5", "1", "2", "+", "4", "*", "+", "3", "-" }; // 5+((1+2)*4)-3 = 14
//
//	cout << evaluate_rpn(expr2.begin(), expr2.end()) << endl; // 输出 14
//
//	stringstream s{ "3 2 1 + * 2 /" };
//	cout << evaluate_rpn(istream_iterator<string>{s}, {}) << '\n';
//	vector<string> v{ "3", "2", "1", "+", "*", "2", "/" };
//	cout << evaluate_rpn(begin(v), end(v)) << '\n';
//
//	try {
//		cout << evaluate_rpn(istream_iterator<string>{cin}, {})
//			<< '\n';
//	}
//	catch (const invalid_argument& e) {
//		cout << "Invalid operator: " << e.what() << '\n';
//	}
//}

//
// 实现词频计数器——std::map
//string filter_punctuation(const string& s)
//{
//	const char* forbidden{ ".,:; " };
//	const auto idx_start(s.find_first_not_of(forbidden));
//	const auto idx_end(s.find_last_not_of(forbidden));
//	return s.substr(idx_start, idx_end - idx_start + 1);
//}
//
//int main()
//{
//	map<string, size_t> words;
//	int max_word_len{ 0 };
//
//	string s;
//	while (cin >> s) 
//	{
//		auto filtered(filter_punctuation(s));
//		max_word_len = max<int>(max_word_len, filtered.length());
//		++words[filtered];
//	}
//	vector<pair<string, size_t>> word_counts;
//	word_counts.reserve(words.size());
//	move(begin(words), end(words), back_inserter(word_counts));
//
//	sort(begin(word_counts), end(word_counts),
//		[](const auto& a, const auto& b) {
//			return a.second > b.second;
//		});
//
//	cout << "# " << setw(max_word_len) << "<WORD>" << " #<COUNT>\n";
//	for (const auto& [word, count] : word_counts) {
//		cout << setw(max_word_len + 2) << word << " #"
//			<< count << '\n';
//	}
//}

//实现个人待办事项列表——std::priority_queue

//int main()
//{
//	using item_type = std::pair<int, std::string>;
//
//	std::initializer_list<item_type> il{
//		{1, "dishes"},
//		{0, "watch tv"},
//		{2, "do homework"},
//		{0, "read comics"},
//	};
//	auto cmp = [&](const item_type& i1, const item_type& i2) {
//		return i1.first > i2.first;
//		};
//
//	std::priority_queue<item_type, vector<item_type>, decltype(cmp)> q(cmp);
//
//	for (const auto& p : il) {
//		q.push(p);
//	}
//	while (!q.empty()) {
//		std::cout << q.top().first << ": " << q.top().second << '\n';
//		q.pop();
//	}
//	std::cout << '\n';
//}
