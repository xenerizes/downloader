#include "cli/Logger.hh"

#include <iostream>

void Logger::error(const char* data)
{
    std::cerr << data << '\n';
}
