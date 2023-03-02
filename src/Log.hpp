#ifndef LOG_HPP
#define LOG_HPP

#include <string>

class Log
{
public:
    static void error(const std::string msg);
    static void warning(const std::string msg);
    static void log(const std::string msg);
};

#endif
