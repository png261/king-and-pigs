#include "Log.hpp"
#include <iostream>

const std::string errorPrefix = "Error:   ";
const std::string warningPrefix = "Warning: ";
const std::string logPrefix = "Log:     ";

const std::string bold_red = "\e[1;31m";
const std::string red = "\e[0;31m";
const std::string bold_cyan = "\e[1;36m";
const std::string cyan = "\e[0;36m";
const std::string bold_green = "\e[1;32m";
const std::string green = "\e[0;32m";
const std::string bold_yellow = "\e[1;33m";
const std::string yellow = "\e[0;33m";
const std::string reset_color = "\e[0m";

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
