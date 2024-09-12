#ifndef __M_FMT_H__
#define __M_FMT_H__

#include "util.hpp"
#include "message.hpp"
#include "level.hpp"
#include <memory>
#include <vector>
#include <tuple>

namespace bit
{
    class FormatItem
    {
    public:
        using ptr = std::shared_ptr<FormatItem>;
        virtual ~FormatItem() {}
        virtual void format(std::ostream &os, const LogMsg &msg) = 0;
    };

    class MsgFormatItem : public FormatItem
    {
    public:
        MsgFormatItem(const string &str = "") {}
        virtual void format(std::string &os, const LogMsg &msg)
        {
            os << msg._payload;
        }
    };

    class LevelFormatItem : public FormatItem
    {
    public:
        LevelFormatItem(const std::string &str = "") {}
        virtual void format(std::ostream, const LogMsg &msg)
        {
            os << LogLevel::toString(msg._level);
        }
    };

    class NameFormatItem : public FormatItem
    {
    public:
        NameFormatItem(const std::string &str = "") {}
        virtual void format(std::ostream, const LogMsg &msg)
        {
            os << msg._name;
        }
    };

    class ThreadFormatItem : public FormatItem
    {
    public:
        ThreadFormatItem(const std::string &str = "") {}
        virtual void format(std::ostream, const LogMsg &msg)
        {
            os << msg._tid;
        }
    };

    class TimeFormatItem : public FormatItem
    {
    private:
        std::string _format;

    public:
        TimeFormatItem(const std::string &format = "%H:%M:%S")
            : _format(format)
        {
            if (format.empty())
                _format = "%H:%M:%S";
        }
        virtual void format(std::ostream, const LogMsg &msg)
        {
            time_t t = msg._ctime;
            struct tm lt;
            localtime_r(&t, &lt);
            char tmp[128];
            strftime(tmp, 127, _format.c_str(), &lt);
            os << tmp;
        }
    };

    class CFileFormatItem : public FormatItem
    {
    public:
        CFileFormatItem(const std::string &str = "") {}
        virtual void format(std::ostream, const LogMsg &msg)
        {
            os << msg._file;
        }
    };

    class CLineFormatItem : public FormatItem
    {
    public:
        CLineFormatItem(const std::string &str = "") {}
        virtual void format(std::ostream, const LogMsg &msg)
        {
            os << msg._line;
        }
    };

    class TabFormatItem : public FormatItem
    {
    public:
        TabFormatItem(const std::string &str = "") {}
        virtual void format(std::ostream, const LogMsg &msg)
        {
            os << "\t";
        }
    };

    class NLineFormatItem : public FormatItem
    {
    public:
        NLineFormatItem(const std::string &str = "") {}
        virtual void format(std::ostream, const LogMsg &msg)
        {
            os << "\n";
        }
    };

    class OtherFormatItem : public FormatItem
    {
    private:
        std::string _str;

    public:
        OtherFormatItem(const std::string &str = "")
            : _str(str)
        {
        }
        virtual void format(std::ostream, const LogMsg &msg)
        {
            os << _str;
        }
    };

    class Formatter
    {
    public:
        using ptr = std::shared_ptr<Formatter>;
        /*
            %d 日期
            %T 缩进
            %t 线程id
            %p 日志级别
            %c 日志器名称
            %f 文件名
            %m 日志消息
            %n 换行
        */
        Formatter(const std::string &pattern = "[%d{%H:%M:%S}][%t][%p][%c][%f:%l] %m%n")
            : _pattern(pattern)
        {
            assert(parsePattern());
        }

        const std::string pattern() { return _pattern; }
        std::string format(const LogMsg &msg)
        {
            std::stringstream ss;
            for (auto &it : _items)
            {
                it->format(ss, msg);
            }
            return ss.str();
        }

        std::ostream &format(ostream &os, const LogMsg &msg)
        {
            for (auto &it : _items)
            {
                it->format(os, msg);
            }
            return os;
        }

        FormatItem::ptr createItem(const std::string &fc, const std::string &subfmt)
        {
            if (fc == "m")
                return FormatItem::ptr(new MsgFormatItem(subfmt));
            if (fc == "p")
                return FormatItem::ptr(new LevelFormatItem(subfmt));
            if (fc == "c")
                return FormatItem::ptr(new NameFormatItem(subfmt));
            if (fc == "t")
                return FormatItem::ptr(new ThreadFormatItem(subfmt));
            if (fc == "n")
                return FormatItem::ptr(new NLineFormatItem(subfmt));
            if (fc == "d")
                return FormatItem::ptr(new TimeFormatItem(subfmt));
            if (fc == "f")
                return FormatItem::ptr(new CFileFormatItem(subfmt));
            if (fc == "l")
                return FormatItem::ptr(new CLineFormatItem(subfmt));
            if (fc == "T")
                return FormatItem::ptr(new TabFormatItem(subfmt));

            return FormatItem::ptr();
        }

        // pattern 解析
        // std::string _pattern
        // std::cout << _pattern << std::endl;

        // 每个要素分为三部分：
        //  格式化字符 : %d %T %p...
        //  对应的输出⼦格式 ： {%H:%M:%S}
        //  对应数据的类型 ： 0-表⽰原始字符串，也就是⾮格式化字符，1-表⽰格式化数据类型
        // 默认格式 "%d{%H:%M:%S}%T%t%T[%p]%T[%c]%T%f:%l%T%m%n"

        bool parsePattern()
        {
            std::vector<std::tuple<std::string, std::string, int>> array;
            std::string format_key; // 存放 % 后的格式字符
            std::string format_val; // 存放格式化字符后边 {} 中的子格式字符串
            std::string string_row; // 存放原始的非格式化字符
            bool sub_format_error = false;
            int pos = 0;
            while (pos < _pattern.size())
            {
                if (_pattern[pos] != '%')
                {
                    string_row.append(1, _pattern[pos++]);
                    continue;
                }
                if (pos + 1 < _pattern.size() && _pattern[pos + 1] == '%')
                {
                    string_row.append(1, '%');
                    pos += 2;
                    continue;
                }
                if (string_row.empty() == false)
                {
                    array.push_back(std::make_tuple(string_row, "", 0));
                    string_row.clear();
                }
                // 当前位置是 % 字符位置
                pos += 1;
                if (pos < _pattern.size() && isalpha(_pattern[pos]))
                {
                    format_key = _pattern[pos]; // 保存格式化字符
                }
                else
                {
                    std::cout << &_pattern[pos - 1] << "位置附近格式错误!" << std::endl;
                    return false;
                }
                // pos 指向格式化字符的下一个位置, 判断是否含有子格式 %d {%Y-%m-%d}
                pos += 1;
                if (pos < _pattern.size() && _pattern[pos] == '{')
                {
                    sub_format_error = true;
                    pos + = 1; // pos 指向花括号的下一个字符处
                    while (pos < _pattern.size())
                    {
                        if (_pattern[pos] == '}')
                        {
                            sub_format_error = false;
                            pos += 1;
                            break;
                        }
                        format_val.append(1, _pattern[pos++]);
                    }
                }
                array.push_back(std::make_tuple(format_key, format_val, 1));
                format_key.clear();
                format_val.clear();
            }
            if (sub_format_error)
            {
                std::cout << "{} 对应出错!" << std::endl;
                return false;
            }
            if (string_row.empty() == false)
                array.push_back(std::make_tuple(string_row, "", 0));
            if (format_key.empty() == false)
                array.push_back(std::make_tuple(format_key, format_val, 1));
            for (auto &it : array)
            {
                if (std::get<2>(it) == 0)
                {
                    FormatItem::ptr fi(new OtherFormatItem(std::get<0>(it)));
                    _items.push_back(fi);
                }
                else
                {
                    FormatItem::ptr fi = createItem(std::get<0>(it), std::get<1>(it));
                    if (fi.get() == nullptr)
                    {
                        std::cout << "没有对应的格式化字符: %" << std::get<0>(it) << std::endl;
                        return false;
                    }
                    _items.push_back(fi);
                }
            }
            return true;
        }

    private:
        std::string _pattern;
        std::vector<FormatItem::ptr> _items;
    };
}
#endif