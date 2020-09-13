#pragma once

#include "lib/client/url/Url.hh"
#include "lib/buffer/Buffer.hh"
#include "AddrInfo.hh"


class Socket {
public:
    Socket(std::string hostname, std::string port);
    Socket(const Socket& oth) = delete;
    ~Socket();

    void send_data(const Buffer& data);
    Buffer read_data();

private:
    int descr_;
    const std::string host_;
    std::string port_;
    AddrInfo info_;

    void make_connection();
    void close_connection();
};

std::string socket_error_str(ssize_t sock_err);

using SocketPtr = std::unique_ptr<Socket>;
