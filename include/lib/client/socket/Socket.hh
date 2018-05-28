#pragma once

#include "lib/client/url/Url.hh"

#include "Request.hh"
#include "Response.hh"


class Socket {
public:
    void connect();
    void close();

    Response send(const Request& req);

private:
    int descr_;
};
