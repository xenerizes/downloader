#pragma once

#include <string>


struct Url {
    std::string path;
    std::string hostname;
    int port {0};
};
