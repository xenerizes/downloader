#pragma once

#include <string>


struct Url {
    std::string path;
    std::string hostname;
    std::string filename;
    int port {0};
};
