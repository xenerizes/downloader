#pragma once

#include "Scheme.hh"

#include <string>


struct Url {
    Scheme scheme;
    std::string hostname;
    std::string port;
    std::string path;
};
