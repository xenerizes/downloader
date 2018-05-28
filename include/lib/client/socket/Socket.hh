#pragma once

#include "lib/client/url/Url.hh"
#include "lib/data/Data.hh"


class Socket {
public:
    Data request(const Data& req);

private:
    int descr_;
};
