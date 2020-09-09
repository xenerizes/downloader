#pragma once

#include "lib/client/Client.hh"

#include <string>


class Scheme {
public:
    Scheme();
    explicit Scheme(std::string scheme_str);

    bool operator==(const Scheme& oth) const;

    ClientPtr make_client();

private:
    std::string scheme;
};
