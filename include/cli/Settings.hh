#pragma once
#include "lib/client/socket/Socket.hh"
#include "lib/client/url/Url.hh"
#include "lib/client/Client.hh"


struct Settings {
    Settings(Url& url_, ClientPtr& cp) noexcept;

    Url url;
    ClientPtr client;
};


class ArgumentParser {
public:
    Url parse_args(int argc, char** argv, SocketPtr socket);
};
