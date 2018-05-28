#pragma once

#include "lib/client/url/Url.hh"
#include "lib/data/Data.hh"


class Socket {
public:
    Socket(const std::string& hostname, int port);
    ~Socket();

    void send_data(const Buffer& data);
    Buffer read_data();

private:
    int descr_;
    const std::string host_;
    int port_;

    void make_connection();
};

using SocketPtr = std::unique_ptr<Socket>;
