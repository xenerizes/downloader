#pragma once

#include <string>


struct Url {
    std::string scheme;
    std::string hostname;
    std::string port;
    std::string path;
};
