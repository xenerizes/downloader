#pragma once

#include "lib/client/Client.hh"
#include "lib/client/socket/Socket.hh"

#include <string>


class Scheme {
public:
    Scheme(const std::string scheme_str);

    ClientPtr make_client(SocketPtr socket);
};
