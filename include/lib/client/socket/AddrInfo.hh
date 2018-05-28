#pragma once

#include <string>

struct AddrInfo {
    AddrInfo(const std::string& hostname, const std::string& port);
    ~AddrInfo();

    struct addrinfo* info;
};
