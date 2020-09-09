#pragma once

#include "Scheme.hh"

#include <string>


struct Url {
    Scheme scheme;
    std::string hostname;
    std::string port;
    std::string path;
    std::string filename;
};

inline bool operator==(const Url& lhs, const Url&rhs)
{
    return lhs.path == rhs.path &&
           lhs.hostname == rhs.hostname &&
           lhs.filename == rhs.filename &&
           lhs.port == rhs.port;
}
