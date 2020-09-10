#include <cstring>
#include <stdexcept>
#include <netdb.h>

#include "lib/client/socket/AddrInfo.hh"


AddrInfo::AddrInfo(const std::string& hostname, const std::string& port)
    : info(nullptr)
{
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    auto res = getaddrinfo(hostname.c_str(), port.c_str(), &hints, &info);
    if (res) {
        throw std::invalid_argument("Address error: " + std::string(gai_strerror(res)));
    }
}

AddrInfo::~AddrInfo()
{
    if (info != nullptr) {
        freeaddrinfo(info);
    }
}
