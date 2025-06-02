#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <functional>
#include <list>
#include <map>
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
struct billionaire {
	string name;
	double dollars;
	string country;
};

int main()
{
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

	std::map<std::string, size_t> m{ {"b", 1}, {"c", 2}, {"d", 3} };
	auto insert_it(std::end(m));

	for (const auto& s : { "z", "y", "x", "w" }) {
		insert_it = m.insert(insert_it, { s, 1 });
	}

	m.insert(std::end(m), { "a", 1 });

	for(const auto& [key, value] : m) {
		std::cout << "\"" << key << "\": " << value << ", ";
	}
	std::cout << '\n';

}