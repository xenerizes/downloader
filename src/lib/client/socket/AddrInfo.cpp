#include "lib/client/socket/AddrInfo.hh"

#include <netdb.h>
#include <cstring>


AddrInfo::AddrInfo(const std::string& hostname, const std::string& port)
    : info(nullptr)
{
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    getaddrinfo(hostname.c_str(), port.c_str(), &hints, &info);
}

AddrInfo::~AddrInfo()
{
    if (info != nullptr) {
        freeaddrinfo(info);
    }
}
