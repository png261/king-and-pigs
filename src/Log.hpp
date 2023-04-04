#pragma once

#include <string>

class Log final
{
public:
    static void error(const std::string msg);
    static void warning(const std::string msg);
    static void log(const std::string msg);
};
