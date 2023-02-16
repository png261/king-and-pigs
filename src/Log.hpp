#ifndef LOG_HPP
#define LOG_HPP

#include <string>

class Log
{
public:
    static void error(std::string msg);
    static void warning(std::string msg);
    static void log(std::string msg);
};

#endif
