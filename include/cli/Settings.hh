#pragma once

#include "lib/client/url/Url.hh"
#include "lib/client/Client.hh"


struct Settings {
    Settings(Url& url_, ClientPtr& cp) noexcept;

    Url url;
    ClientPtr client;
};


class ArgumentParser {
public:
    Settings parse_args(int argc, char** argv);
};
