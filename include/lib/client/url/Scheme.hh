#pragma once

#include "lib/client/Client.hh"

#include <string>


class Scheme {
public:
    Scheme(const std::string scheme_str);

    ClientPtr make_client();
};
