#include "Log.hpp"

#include <iostream>

const std::string error_prefix = "Error:   ";
const std::string warning_prefix = "Warning: ";
const std::string log_prefix = "Log:     ";

const std::string bold_red = "\x1B[1;31m";
const std::string red = "\x1B[0;31m";
const std::string bold_cyan = "\x1B[1;36m";
const std::string cyan = "\x1B[0;36m";
const std::string bold_green = "\x1B[1;32m";
const std::string green = "\x1B[0;32m";
const std::string bold_yellow = "\x1B[1;33m";
const std::string yellow = "\x1B[0;33m";
const std::string reset_color = "\x1B[0m";

void Log::error(const std::string& message)
{
    std::cerr << bold_red << error_prefix << message << reset_color << std::endl;
}

void Log::warning(const std::string& message)
{
    std::cerr << bold_yellow << warning_prefix << message << reset_color << std::endl;
}

void Log::log(const std::string& message)
{
    std::cout << bold_green << log_prefix << message << reset_color << std::endl;
}
