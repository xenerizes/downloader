#pragma once

//#include "lib/client/url/Url.hh"
#include "lib/buffer/Buffer.hh"
#include "AddrInfo.hh"


class Socket {
public:
    Socket(std::string hostname, std::string port);
    virtual ~Socket();

    virtual void send_data(const Buffer& data);
    virtual Buffer read_data();

private:
    int descr_;
    const std::string host_;
    std::string port_;
    AddrInfo info_;

    virtual void make_connection();
};

using SocketPtr = std::shared_ptr<Socket>;
