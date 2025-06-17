#include <iostream>
#include <string>
#include <string_view>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <typeinfo>
#include <fstream>
#include <iterator>
#include <iomanip>
#include <locale>
#include <map>
#include <numeric>
#include <vector>
#include <unordered_map>
using namespace std;
using namespace std::string_literals;

// 第7章 字符串, 流和正则表达
// 
// day-2025-6-17
//  通过集成std::char_traits创建自定义字符串类
//class lc_traits : public char_traits<char> {
//public:
//    static constexpr void assign(char_type& r, const char_type& a)
//    {
//        r = tolower(a);
//    }
//
//    static char_type* copy(char_type* dest,
//        const char_type* src,
//        size_t count)
//    {
//        transform(src, src + count, dest, tolower);
//        return dest;
//    }
//};
//
//class ci_traits : public char_traits<char> {
//public:
//    static constexpr bool eq(char_type a, char_type b)
//    {
//        return tolower(a) == tolower(b);
//    }
//
//    static constexpr bool lt(char_type a, char_type b)
//    {
//        return tolower(a) < tolower(b);
//    }
//
//    static constexpr int compare(const char_type* s1, const char_type* s2, size_t count)
//    {
//        for (; count; ++s1, ++s2, --count)
//        {
//            const char_type diff(tolower(*s1) - tolower(*s2));
//            if (diff < 0) return -1;
//            else if (diff > 0) return 1;
//        }
//        return 0;
//    }
//
//    static constexpr const char_type* find(const char_type* p, size_t count, const char_type& ch)
//    {
//        const char_type find_c{ tolower(ch) };
//        for (; count != 0; --count, ++p)
//        {
//            if (find_c == tolower(*p)) return p;
//        }
//        return nullptr;
//    }
//};
//
//using lc_string = basic_string<char, lc_traits>;
//using ci_string = basic_string<char, ci_traits>;
//
//ostream& operator<<(ostream& os, const lc_string& str) {
//    return os.write(str.data(), str.size());
//}
//
//ostream& operator<<(ostream& os, const ci_string& str) {
//    return os.write(str.data(), str.size());
//}
//
//int main()
//{
//    cout << " string: "
//        << string{ "Foo Bar Baz" } << '\n'
//        << "lc_string: "
//        << lc_string{ "Foo Bar Baz" } << '\n'
//        << "ci_string: "
//        << ci_string{ "Foo Bar Baz" } << '\n';
//
//        ci_string user_input{ "MaGiC PaSsWoRd!" };
//        ci_string password{ "magic password!" };
//
//        if (user_input == password) {
//         cout << "Passwords match: \"" << user_input
//              << "\" == \"" << password << "\"\n";
//        }
//}


// 使用特定代码段将输出重定向到文件
//class redirect_cout_region
//{
//    using buftype = decltype(cout.rdbuf());
//    ofstream ofs;
//    buftype buf_backup;
//
//public:
//    explicit redirect_cout_region(const string& filename)
//        :ofs{ filename },
//        buf_backup{ cout.rdbuf(ofs.rdbuf()) }
//    {
//
//    }
//    redirect_cout_region()
//        : ofs{}
//        , buf_backup{ cout.rdbuf(ofs.rdbuf()) }
//    {
//    }
//
//    ~redirect_cout_region()
//    {
//        cout.rdbuf(buf_backup);
//    }
//};
//
//void my_output_heavy_function()
//{
//    cout << "some output\n";
//    cout << "this function does really heavy work\n";
//    cout << "... and lots of it...\n";
//    // ...
//}
//
//int main()
//{
//    cout << "Readable from normal stdout\n";
//    {
//        redirect_cout_region _{ "output.txt" };
//        cout << "only visible in output.txt\n";
//        my_output_heavy_function();
//    }
//
//    {
//        redirect_cout_region _;
//        cout << "This output will "
//            "completely vanish\n";
//    }
//
//    cout << "Readable from normal stdout again\n";
//}

// 
// 迭代器进行打印——std::ostream
//string word_num(int n)
//{
//    unordered_map<int, string> m{
//        {1, "one"}, {2, "two"}, {3, "three"},
//        {4, "four"}, {5, "five"}
//    };
//
//    const auto match(m.find(n));
//    if (match == end(m)) return "Unknown";
//    return match->second;
//}
//
//struct bork
//{
//    int borks;
//    bork(int i)
//        :borks(i)
//    {}
//
//    void print(ostream& os) const
//    {
//        fill_n(ostream_iterator<string>{os, " "},
//            borks, "bork!"s);
//    }
//};
//
//ostream& operator<<(ostream& os, const bork& b) {
//    b.print(os);
//    return os;
//}
//
//int main()
//{
//    const vector<int> v{ 1,2,3,4,5 };
//    ostream_iterator<int> oit{ cout };
//    for (int i : v)
//    {
//        *oit = i;
//    }
//    cout << endl;
//
//    ostream_iterator<int> oit_comma{ cout, " " };
//    for (int i : v) { *oit_comma = i; }
//    cout << endl;
//
//    copy(begin(v), end(v), oit);
//    cout << '\n';
//
//    copy(begin(v), end(v), oit_comma);
//    cout << '\n';
//
//    transform(begin(v), end(v),
//        ostream_iterator<string>{cout, " "}, word_num);
//    cout << '\n';
//
//    copy(begin(v), end(v),
//        ostream_iterator<bork>{cout, "\n"});
//}

// 迭代器填充容器——std::istream
//struct meme {
//    string description;
//    size_t year;
//};
//
//istream& operator>>(istream& is, meme& m)
//{
//    return is >> quoted(m.description) >> m.year;
//}
//
//istream& operator>>(istream& is, pair<string, meme>& p)
//{
//    return is >> quoted(p.first)>>p.second;
//}
//
//int main()
//{
//    map<string, meme> m;
//    copy(istream_iterator<pair<string, meme>>{cin},
//        {},
//        inserter(m, end(m)));
//    auto max_func([](size_t old_max, const auto& b) {
//        return max(old_max, b.first.length());
//        });
//
//    size_t width{ accumulate(begin(m), end(m), 0u, max_func) };
//
//    for (const auto& [meme_name, meme_desc] : m) {
//        const auto& [desc, year] = meme_desc;
//
//        cout << left << setw(width) << meme_name << " : " << desc << ", " << year << endl;
//    }
//}

// 
// day-2025-6-11
using namespace std::literals;

// 格式化输出
//void print_aligned_demo(int val, size_t width, char fill_char = ' ')
//{
//    cout << "================\n";
//    cout << setfill(fill_char);
//    cout << left << setw(width) << val << '\n';
//    cout << right << setw(width) << val << '\n';
//    cout << internal << setw(width) << val << '\n';
//}
//
//int main()
//{
//    print_aligned_demo(123456, 15);
//    print_aligned_demo(123456, 15,'-');
//
//    cout << hex << showbase;
//    print_aligned_demo(0x123abc, 15);
//
//    cout << oct;
//    print_aligned_demo(0123456, 15);
//
//    cout << "A hex number with upper case lettters: " << hex << uppercase << 0x123abc << endl;
//    cout << "A number: " << 100 << endl;
//
//    cout << dec;
//    cout << "Oops. now in decimal again: " << 100 << endl;
//
//    cout << "true/false values:" << true << "," << false << endl;
//
//    cout << boolalpha << "true/false values: " << true << ", " << false << endl;
//
//    cout << "doubles: " << 12.3 << ", " << 12.0 << "," << showpoint << 12.0 << endl;
//
//    cout << "scientific double: " << scientific
//        << 123000000000.123 << '\n';
//    cout << "fixed double: " << fixed
//        << 123000000000.123 << '\n';
//
//    cout << "Very precise double: "
//        << setprecision(10) << 0.0000000001 << '\n';
//    cout << "Less precise double: "
//        << setprecision(1) << 0.0000000001 << '\n';
//}

// 计算文件中的单词数量
//template<typename T>
//size_t wordcount(T& is)
//{
//    return distance(istream_iterator<string>{is}, {});
//}
//int main(int argc, char** argv)
//{
//    size_t wc;
//    if (argc == 2)
//    {
//        ifstream ifs{ argv[1] };
//        wc = wordcount(ifs);
//    }
//    else
//        wc = wordcount(cin);
//    cout << "There are " << wc << " words" << endl;
//}


//int main()
//{
//    cout << "Please Enter Two numbers:\n> ";
//    int x;
//    double y;
//    if (cin >> x >> y)
//    {
//        cout << "You entered: " << x << " and " << y << endl;
//    }
//    else
//    {
//        cout << "input not well!" << endl;
//        cin.clear();
//        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//    }
//
//    cout << "now please enter some "
//        "comma-separated names:\n> ";
//    for (string s; getline(cin >> ws, s, ',');) {
//        if (s.empty())
//        {
//            break;
// }
//        cout << "name: \"" << s << "\"\n";
//    }
//}

//void print(string_view v)
//{
//    const auto words_begin(v.find_first_not_of(" \t\n"));
//    v.remove_prefix(min(words_begin, v.size()));
//
//    const auto words_end(v.find_last_not_of(" \t\n"));
//    if (words_end != string_view::npos)
//        v.remove_suffix(v.size() - words_end - 1);
//
//    cout << "length: " << v.length()
//        << " [" << v << "]\n";
//}
//
//int main(int argc, char* argv[])
//{
//    print(argv[0]);
//    print({});
//    print("a const char * array");
//    print("an std::string_view literal"sv);
//    print("an std::string instance"s);
//    print(" \t\n foobar \n \t ");
//    char cstr[]{ 'a', 'b', 'c' };
//    print(string_view(cstr, sizeof(cstr)));
//}


//  消除字符串开始和结束处的空格
//string trim_whitespace_surrounding(const string& s)
//{
//    const char whitespace[]{ " \t\n" };
//    const size_t first(s.find_first_not_of(whitespace));
//    if (string::npos == first) return {};
//    const size_t last(s.find_last_not_of(whitespace));
//
//    return s.substr(first, last - first + 1);
//
//}
//
//int main()
//{
//    string s{ " \t\n string surrounded by ugly"
//             " whitespace \t\n " };
//
//    cout << "{" << s << "}\n";
//    cout << trim_whitespace_surrounding(s) << endl;
// 
//}

//int main()
//{
//    string a{ "a" };
//    auto b{ "b"s };
//
//    string_view c{ "c" };
//    auto d("d"sv);
//
//    cout << a << " " << typeid(b).name()  << endl;
//    cout << c << " " << typeid(d).name() << endl;
//
//    cout << a + b << '\n';
//    cout << a + string{ c } << '\n';
//
//    ostringstream os;
//    os << a << " " << b << " " << c << " " << d << endl;
//    auto concatenated(os.str());
//    cout << concatenated << endl;
//
//    transform(begin(concatenated), end(concatenated), begin(concatenated), ::toupper);
//    cout << concatenated << endl;
//}