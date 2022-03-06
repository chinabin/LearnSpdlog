#include "common_func.h"
#include "formatter.h"
#include "type.h"

#include <iostream>

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
        return msg._logger_name;
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
        auto tm = detail::localtime();
        return std::to_string(tm.tm_year + 1900);
    }
};

// month
class m_format_item : public format_item {
public:
    std::string format(const log_event& msg) override
    {
        auto tm = detail::localtime();
        return std::to_string(tm.tm_mon + 1);
    }
};

// day
class d_format_item : public format_item {
public:
    std::string format(const log_event& msg) override
    {
        auto tm = detail::localtime();
        return std::to_string(tm.tm_mday);
    }
};

// hour
class H_format_item : public format_item {
public:
    std::string format(const log_event& msg) override
    {
        auto tm = detail::localtime();
        return std::to_string(tm.tm_hour);
    }
};

// minutes
class M_format_item : public format_item {
public:
    std::string format(const log_event& msg) override
    {
        auto tm = detail::localtime();
        return std::to_string(tm.tm_min);
    }
};

// second
class S_format_item : public format_item {
public:
    std::string format(const log_event& msg) override
    {
        auto tm = detail::localtime();
        return std::to_string(tm.tm_sec);
    }
};

// millisecond 000-999
class e_format_item : public format_item {
public:
    std::string format(const log_event& msg) override
    {
        auto t = detail::time_fraction<std::chrono::milliseconds>(msg._time);
        return std::to_string(t.count());
    }
};

// char
class ch_format_item : public format_item {
public:
    ch_format_item() = default;

    ch_format_item(char c)
        :_ch(c)
    {
    }

    std::string format(const log_event& msg) override
    {
        return std::string(1, _ch);
    }

private:
    char _ch;
};

class aggregate_formatter final : public format_item
{
public:
    aggregate_formatter() = default;

    void add_ch(char ch)
    {
        _str += ch;
    }
    std::string format(const log_event& msg) override
    {
        return _str;
    }

private:
    std::string _str;
};

// default format [2014-10-31 23:46:59.678] [mylogger] [info] Some message
class default_format_item : public format_item {
public:
    std::string format(const log_event& msg) override
    {
        std::string full_msg;

        full_msg += "[";
        auto tm = detail::localtime();
        full_msg += std::to_string(tm.tm_year + 1900);
        full_msg += "-";
        full_msg += std::to_string(tm.tm_mon + 1);
        full_msg += "-";
        full_msg += std::to_string(tm.tm_mday);
        full_msg += " ";
        full_msg += std::to_string(tm.tm_hour);
        full_msg += ":";
        full_msg += std::to_string(tm.tm_min);
        full_msg += ":";
        full_msg += std::to_string(tm.tm_sec);
        full_msg += ".";
        auto t = detail::time_fraction<std::chrono::milliseconds>(msg._time);
        full_msg += std::to_string(t.count());
        full_msg += "]";

        full_msg += " ";
        full_msg += "[";
        full_msg += msg._logger_name;
        full_msg += "]";

        full_msg += " ";
        full_msg += "[";
        full_msg += msg._level.format();
        full_msg += "]";

        full_msg += " ";
        full_msg += msg._msg;

        return full_msg;
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

class color_start_format_item : public format_item {
public:
    std::string format(const log_event& msg) override
    {
        switch (msg._level._level)
        {
        case LOG_LEVEL_TRACE:
            return white;
        case LOG_LEVEL_DEBUG:
            return cyan;
        case LOG_LEVEL_INFO:
            return green;
        case LOG_LEVEL_WARN:
            return yellow;
        case LOG_LEVEL_ERROR:
            return red;
        case LOG_LEVEL_CRITICAL:
            return magenta;
        }
        return white;
    }
private:
    const std::string black = "\033[30m";
    const std::string red = "\033[31m";
    const std::string green = "\033[32m";
    const std::string yellow = "\033[33m";
    const std::string blue = "\033[34m";
    const std::string magenta = "\033[35m";
    const std::string cyan = "\033[36m";
    const std::string white = "\033[37m";
};

class color_end_format_item : public format_item {
public:
    std::string format(const log_event& msg) override
    {
        return reset;
    }
private:
    const std::string reset = "\033[m";
};



formatter::formatter(const std::string& pattern)
    :_pattern(pattern)
{
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

std::unique_ptr<formatter> formatter::clone()
{
    return detail::make_unique<formatter>(_pattern);
}

/*
 * %^           color start
 * %$           color end
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
 * %s	        Basename of the source file (use SPDLOG_TRACE(..), SPDLOG_INFO(...) etc.)	my_file.cpp
 * %#	        Source line (use SPDLOG_TRACE(..), SPDLOG_INFO(...) etc.)	123
 * %!	        Source function (use SPDLOG_TRACE(..), SPDLOG_INFO(...) etc. see tweakme for pretty-print)	my_func
*/
void formatter::parse()
{
    std::unique_ptr<aggregate_formatter> p;
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
                _formatters.emplace_back(detail::make_unique<default_format_item>());
                break;
            case 's':
                _formatters.emplace_back(detail::make_unique<s_format_item>());
                break;
            case '#':
                _formatters.emplace_back(detail::make_unique<line_format_item>());
                break;
            case '!':
                _formatters.emplace_back(detail::make_unique<fn_format_item>());
                break;
            case '^':
                _formatters.emplace_back(detail::make_unique<color_start_format_item>());
                break;
            case '$':
                _formatters.emplace_back(detail::make_unique<color_end_format_item>());
                break;
            
            default:
                break;
            }

            if (it == _pattern.end())
                break;
        }
        else {
            if (!p) {
                p = detail::make_unique<aggregate_formatter>();
            }
            p->add_ch(*it);
        }
    }
    
    if (p) {
        _formatters.emplace_back(std::move(p));
    }
}

}