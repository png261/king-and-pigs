#pragma once

#include <string>

class Log final
{
public:
    static void error(const std::string& messsage);
    static void warning(const std::string& message);
    static void log(const std::string& message);
};
