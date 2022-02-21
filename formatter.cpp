#include <time.h>

#include "common_func.h"
#include "formatter.h"

namespace fatdog {

// actual text to log
class v_format_item : public format_item {
public:
    std::string format(const log_event& msg) override
    {
        return msg._msg;
    }
};

// logger's name
class n_format_item : public format_item {
public:
    std::string format(const log_event& msg) override
    {
        return "fatdog";
    }
};

// log level
class l_format_item : public format_item {
public:
    std::string format(const log_event& msg) override
    {
        return msg._level.format();
    }
};

// year
class Y_format_item : public format_item {
public:
    std::string format(const log_event& msg) override
    {
        auto ts = time(NULL);
        auto *tm = localtime(&ts);
        return std::to_string(tm->tm_year + 1900);
    }
};

// month
class m_format_item : public format_item {
public:
    std::string format(const log_event& msg) override
    {
        auto ts = time(NULL);
        auto *tm = localtime(&ts);
        return std::to_string(tm->tm_mon + 1);
    }
};

// day
class d_format_item : public format_item {
public:
    std::string format(const log_event& msg) override
    {
        auto ts = time(NULL);
        auto *tm = localtime(&ts);
        return std::to_string(tm->tm_mday);
    }
};

// hour
class H_format_item : public format_item {
public:
    std::string format(const log_event& msg) override
    {
        auto ts = time(NULL);
        auto *tm = localtime(&ts);
        return std::to_string(tm->tm_hour);
    }
};

// minutes
class M_format_item : public format_item {
public:
    std::string format(const log_event& msg) override
    {
        auto ts = time(NULL);
        auto *tm = localtime(&ts);
        return std::to_string(tm->tm_min);
    }
};

// second
class S_format_item : public format_item {
public:
    std::string format(const log_event& msg) override
    {
        auto ts = time(NULL);
        auto *tm = localtime(&ts);
        return std::to_string(tm->tm_sec);
    }
};

// millisecond 000-999
class e_format_item : public format_item {
public:
    std::string format(const log_event& msg) override
    {
        return "123";
    }
};

// char
class ch_format_item : public format_item {
public:
    ch_format_item() = default;

    ch_format_item(char c)
    {
        add_ch(c);
    }

    std::string format(const log_event& msg) override
    {
        return _chs;
    }

    void add_ch(const char c)
    {
        _chs += c;
    }

private:
    std::string _chs;
};

// default format [2014-10-31 23:46:59.678] [mylogger] [info] Some message
class default_format_item : public format_item {
public:
    std::string format(const log_event& msg) override
    {
        return "2022:02:07";
    }
};

// name of file
class s_format_item : public format_item {
public:
    std::string format(const log_event& msg) override
    {
        return msg._loc._filename;
    }
};

// name of file with path
class g_format_item : public format_item {
public:
    std::string format(const log_event& msg) override
    {
        return "/haha/" + msg._loc._filename;
    }
};

// line num
class line_format_item : public format_item {
public:
    std::string format(const log_event& msg) override
    {
        return std::to_string(msg._loc._line);
    }
};

// function name
class fn_format_item : public format_item {
public:
    std::string format(const log_event& msg) override
    {
        return msg._loc._funcname;
    }
};



formatter::formatter(const std::string& pattern)
    :_pattern(pattern)
{
    parse();
}

void formatter::set_pattern(const std::string& pattern)
{
    _pattern = pattern;
    parse();
}

std::string formatter::format(const log_event& msg)
{
    std::string formatted_msg;
    for (auto &it : _formatters) {
        formatted_msg += it->format(msg);
    }

    return formatted_msg;
}

/*
 * %v	        The actual text to log	                                    "some user text"
 * %n	        Logger's name	                                            "some logger name"
 * %l	        The log level of the message	                            "debug", "info", etc
 * %Y	        Year in 4 digits	                                        "2014"
 * %m	        Month 01-12	                                                "11"
 * %d	        Day of month 01-31	                                        "29"
 * %H	        Hours in 24 format 00-23	                                "23"
 * %M	        Minutes 00-59	                                            "59"
 * %S	        Seconds 00-59	                                            "58"
 * %e	        Millisecond part of the current second 000-999	            "678"
 * %%	        The % sign	                                                "%"
 * %+	        spdlog's default format	                                    "[2014-10-31 23:46:59.678] [mylogger] [info] Some message"
 * %@	        Source file and line (use SPDLOG_TRACE(..), SPDLOG_INFO(...) etc. instead of spdlog::trace(...)	my_file.cpp:123
 * %s	        Basename of the source file (use SPDLOG_TRACE(..), SPDLOG_INFO(...) etc.)	my_file.cpp
 * %g	        Full or relative path of the source file as appears in the __FILE__ macro (use SPDLOG_TRACE(..), SPDLOG_INFO(...) etc.)	/some/dir/my_file.cpp
 * %#	        Source line (use SPDLOG_TRACE(..), SPDLOG_INFO(...) etc.)	123
 * %!	        Source function (use SPDLOG_TRACE(..), SPDLOG_INFO(...) etc. see tweakme for pretty-print)	my_func
*/
void formatter::parse()
{
    std::unique_ptr<ch_format_item> p;
    for (auto it = _pattern.begin(); it != _pattern.end(); ++it) {
        if (*it == '%') {
            if (p) {
                _formatters.emplace_back(std::move(p));
            }
            char c = *(++it);
            switch (c)
            {
            case 'v':
                _formatters.emplace_back(detail::make_unique<v_format_item>());
                break;
            case 'n':
                _formatters.emplace_back(detail::make_unique<n_format_item>());
                break;
            case 'l':
                _formatters.emplace_back(detail::make_unique<l_format_item>());
                break;
            case 'Y':
                _formatters.emplace_back(detail::make_unique<Y_format_item>());
                break;
            case 'm':
                _formatters.emplace_back(detail::make_unique<m_format_item>());
                break;
            case 'd':
                _formatters.emplace_back(detail::make_unique<d_format_item>());
                break;
            case 'H':
                _formatters.emplace_back(detail::make_unique<H_format_item>());
                break;
            case 'M':
                _formatters.emplace_back(detail::make_unique<M_format_item>());
                break;
            case 'S':
                _formatters.emplace_back(detail::make_unique<S_format_item>());
                break;
            case 'e':
                _formatters.emplace_back(detail::make_unique<e_format_item>());
                break;
            case '%':
                _formatters.emplace_back(detail::make_unique<ch_format_item>('%'));
                break;
            case '+':
                break;
            case '@':
                _formatters.emplace_back(detail::make_unique<line_format_item>());
                break;
            case 's':
                _formatters.emplace_back(detail::make_unique<s_format_item>());
                break;
            case 'g':
                _formatters.emplace_back(detail::make_unique<g_format_item>());
                break;
            case '#':
                _formatters.emplace_back(detail::make_unique<line_format_item>());
                break;
            case '!':
                _formatters.emplace_back(detail::make_unique<fn_format_item>());
                break;
            
            default:
                break;
            }

            if (it == _pattern.end())
                break;
        }
        else {
            if (!p) {
                p = detail::make_unique<ch_format_item>();
            }
            p->add_ch(*it);
        }
    }
    
    if (p) {
        _formatters.emplace_back(std::move(p));
    }
}

}