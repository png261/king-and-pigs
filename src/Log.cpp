#include "Log.hpp"
#include <iostream>

const std::string errorPrefix = "Error:   ";
const std::string warningPrefix = "Warning: ";
const std::string logPrefix = "Log:     ";

const std::string bold_red = "\x1B[1;31m";
const std::string red = "\x1B[0;31m";
const std::string bold_cyan = "\x1B[1;36m";
const std::string cyan = "\x1B[0;36m";
const std::string bold_green = "\x1B[1;32m";
const std::string green = "\x1B[0;32m";
const std::string bold_yellow = "\x1B[1;33m";
const std::string yellow = "\x1B[0;33m";
const std::string reset_color = "\x1B[0m";

void Log::error(const std::string& msg)
{
    std::cerr << bold_red << errorPrefix << msg << reset_color << std::endl;
}

void Log::warning(const std::string& msg)
{
    std::cerr << bold_yellow << warningPrefix << msg << reset_color << std::endl;
}

void Log::log(const std::string& msg)
{
    std::cout << bold_green << logPrefix << msg << reset_color << std::endl;
}
