#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>
#include <string>
#include <sstream>
#include <iterator>
#include <tuple>
#include <deque>
#include <fstream>
#include <random>
#include <list>
#include <functional>
#include <iomanip>
using namespace std;

// 第5章 STL基础算法
// day-2025-6-9

//int main()
//{
//    vector<string> v{ istream_iterator<string>{cin}, {} };
//    sort(begin(v), end(v));
//    do {
//        copy(begin(v), end(v),
//            ostream_iterator<string>{cout, " "});
//        cout << '\n';
//    } while (next_permutation(begin(v), end(v)));
//}

//  对大vector进行采样
//int main()
//{
//    const size_t data_points{ 100000 }; // len
//    const size_t sample_points{ 100 };  // step
//
//    const int mean{ 10 };
//    const size_t dev{ 3 };
//
//    random_device rd;
//    mt19937 gen{ rd() };
//    normal_distribution<> d{ mean, dev };
//
//    vector<int> v;
//    v.reserve(data_points);
//
//    generate_n(back_inserter(v), data_points,
//        [&] { return d(gen); });
//
//    vector<int> samples;
//    v.reserve(sample_points);
//
//    sample(begin(v), end(v), back_inserter(samples),
//        sample_points, mt19937{ random_device{}() });
//
//    map<int, size_t> hist;
//
//    for (int i : samples) { ++hist[i]; }
//    for (const auto& [value, count] : hist) {
//        cout << setw(2) << value << " "
//            << string(count, '*') << '\n';
//    }
//}


// 在字符串中定位模式并选择最佳实现——std::search
//template <typename Itr>
//static void print(Itr it, size_t chars)
//{
//    copy_n(it, chars, ostream_iterator<char>{cout});
//    cout << '\n';
//}
//int main()
//{
//    const string long_string{
//        "Lorem ipsum dolor sit amet, consetetur"
//        " sadipscing elitr, sed diam nonumy eirmod" };
//    const string needle{ "elitr" };
//    {
//        auto match(search(begin(long_string), end(long_string), begin(needle), end(needle)));
//        print(match, 5);
//    }
//    // C++ 17
//    {
//        auto match(search(begin(long_string), end(long_string),
//            default_searcher(begin(needle), end(needle))));
//        print(match, 5);
//    }
//    {
//        auto match(search(begin(long_string), end(long_string),
//            boyer_moore_searcher(begin(needle), end(needle))));
//        print(match, 5);
//    }
//    {
//        auto match(search(begin(long_string), end(long_string),
//            boyer_moore_horspool_searcher(begin(needle), end(needle))));
//        print(match, 5);
//    }
//}
//struct city {
//    string name;
//    unsigned population;
//};
//
//bool operator==(const city& a, const city& b)
//{
//    return a.name == b.name && a.population == b.population;
//}
//ostream& operator<<(ostream& os, const city& c)
//{
//    return os << "{" << c.name << ", " << c.population << "}";
//}
//
//template<typename C>
//static auto opt_print(const C& container)
//{
//    return [end_it(end(container))](const auto& item) {
//        if (item != end_it)
//            cout << *item << endl;
//        else
//            cout << "<end>\n";
//        };
//}
//
//int main()
//{
//    const vector<city> c{
//        {"Aachen",246000},
//        {"Berlin",3502000},
//        {"Braunschweig", 251000},
//        {"Cologne",1060000}
//    };
//
//    auto print_city(opt_print(c));
//    {
//        auto found_cologne(find(begin(c), end(c), city{ "Cologne",1060000 }));
//        print_city(found_cologne);
//    }
//    {
//        auto found_cologne(find_if(begin(c), end(c), [](const auto& item) {
//            return item.name == "Cologne";
//            }));
//        print_city(found_cologne);
//    }
//    {
//        auto population_more_than([](unsigned i) {
//            return [=](const city& item) {
//                return item.population > i;
//                };
//            });
//        auto found_large(find_if(begin(c), end(c),
//            population_more_than(2000000)));
//        print_city(found_large);
//    }
//
//    const vector<int> v{ 1,2,3,4,5,6,7,8,9,10 };
//    auto print_int(opt_print(v));
//
//    bool contains_7{ binary_search(begin(v),end(v), 7) };
//    cout << contains_7 << endl;
//
//    auto [lower_it, upper_it](equal_range(begin(v), end(v), 7)); // 7 8
//    print_int(lower_it);
//    print_int(upper_it);
//
//    print_int(lower_bound(begin(v), end(v), 7));
//    print_int(upper_bound(begin(v), end(v), 7));
//
//
//}

//int main()
//{
//    vector<int> v{ 1,2,3,4,5 };
//    transform(begin(v), end(v),
//        ostream_iterator<int>{cout, " "},
//        [](int i) {return i * i;});
//    cout << endl;
//
//    auto int_to_string([](int i) {
//        stringstream ss;
//        ss << i << "^2 = " << i * i;
//        return ss.str();
//        });
//    vector<string> vs;
//    transform(begin(v), end(v),back_inserter(vs),
//        int_to_string);
//    copy(begin(vs), end(vs), ostream_iterator<string>{cout, "\n"});
//}

//void print(const vector<int>& v)
//{
//    copy(begin(v), end(v), ostream_iterator<int>{cout, " "});
//    cout << '\n';
//}
//
//int main()
//{
//    vector<int> v{ 1, 2, 3, 4, 5, 6 };
//    print(v);
//    {
//        const auto new_end(remove(begin(v), end(v), 2));
//        v.erase(new_end, end(v));
//    }
//    print(v);
//
//   {
//        auto odd_number([](int i) { return i % 2 != 0; });
//        const auto new_end(
//            remove_if(begin(v), end(v), odd_number));
//        v.erase(new_end, end(v));
//    }
//    print(v);
//
//    replace(begin(v), end(v), 4, 123);
//    print(v);
//    v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
//
//    vector<int> v2;
//    vector<int> v3;
//    auto odd_number([](int i) { return i % 2 != 0; });
//    auto even_number([](int i) { return i % 2 == 0; });
//    remove_copy_if(begin(v), end(v),
//        back_inserter(v2), odd_number);
//    copy_if(begin(v), end(v),
//        back_inserter(v3), even_number);
//    print(v2);
//    print(v3);
//}


//struct mystruct {
//    int a;
//    int b;
//};
//
//int main()
//{
//    vector<mystruct> mv{ {5, 100}, {1, 50}, {-123, 1000},
//                      {3, 70}, {-10, 20} };
//
//    sort(begin(mv), end(mv),
//        [](const mystruct& lhs, const mystruct& rhs) {
//            return lhs.b < rhs.b;
//        });
//    for (const auto& [a, b] : mv) {
//        cout << "{" << a << ", " << b << "} ";
//    }
//    cout << '\n';
//}

//static void print(const vector<int>& v)
//{
//    copy(begin(v), end(v), ostream_iterator<int>{cout, " "});
//    cout << '\n';
//}
//
//int main()
//{
//    vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
//    random_device rd;
//    mt19937 g{ rd() };
//
//    cout << is_sorted(begin(v), end(v)) << '\n';
//    // std::shuffle将打乱vector中的内容
//    shuffle(begin(v), end(v), g);
//
//    cout << is_sorted(begin(v), end(v)) << '\n';
//    print(v);
//
//    sort(begin(v), end(v));
//
//    cout << is_sorted(begin(v), end(v)) << '\n';
//    print(v);
//
//    shuffle(begin(v), end(v), g);
//
//    partition(begin(v), end(v), [](int i) { return i < 5; });
//    print(v);
//
//    shuffle(begin(v), end(v), g);
//    auto middle(next(begin(v), int(v.size()) / 2));
//
//    print(v);
//    cout << *middle << endl;
//    partial_sort(begin(v), middle, end(v));
//    print(v);
//
//}

//using dict_entry = pair<string, string>;
//namespace std {
//	ostream& operator<<(ostream& os, const dict_entry p)
//	{
//		return os << p.first << " " << p.second;
//	}
//	istream& operator>>(istream& is, dict_entry& p)
//	{
//		return is >> p.first >> p.second;
//	}
//}
//template<typename IS>
//deque<dict_entry> from_instream(IS&& is)
//{
//	deque<dict_entry> d{ istream_iterator<dict_entry>{cin}, {} };
//	sort(begin(d), end(d));
//	return d;
//}
//
//int main()
//{
//	const auto dict1(from_instream(ifstream{ "dict.txt" }));
//	const auto dict2(from_instream(cin));
//
//	merge(begin(dict1), end(dict1),
//		begin(dict2), end(dict2),
//		ostream_iterator<dict_entry>{cout, "\n"});
//}

//namespace std {
//	ostream& operator<<(ostream& os, const pair<int, string>& p)
//	{
//		return os << "(" << p.first << "," << p.second << ")";
//	}
//}

//int main()
//{
	//vector<pair<int, string>> v
	//{
	//	{1,"one"}, {2, "two"}, {3, "three"},
	//	{4, "four"}, {5, "five"}
	//};

	//map<int, string> m;

	//copy_n(begin(v), 3, inserter(m, begin(m)));

	//auto shell_it(ostream_iterator<pair<int, string>>{cout, " "});
	//copy(begin(m), end(m), shell_it);
	//cout << endl;

	//copy(begin(v), end(v), shell_it);
	//cout << endl;

	//m.clear();
	//move(begin(v), end(v), inserter(m, begin(m)));
	//copy(begin(m), end(m), shell_it);
	//cout << endl;

	//copy(begin(v), end(v), shell_it);
	//cout << endl;
	/*
		(1, one) (2, two) (3, three)
		(1, one) (2, two) (3, three) (4, four) (5, five)
		(1, one) (2, two) (3, three) (4, four) (5, five)
		(1, ) (2, ) (3, ) (4, ) (5, )
	*/



	//vector<int> v{ 100, 400, 200 /*, ... */ };

	//int sum{ 0 };
	//for (int i : v) { sum += i; }

	//cout << sum << '\n';

	//cout << accumulate(begin(v), end(v), 0) << '\n';

//	return 0;
//}