#pragma once

#include "lib/client/url/Url.hh"
#include "lib/data/Data.hh"


class Socket {
public:
    void connect();
    void close();

    Data send(const Data& req);

private:
    int descr_;
};
