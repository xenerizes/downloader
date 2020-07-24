#pragma once

#include "lib/client/socket/Socket.hh"
#include "lib/client/url/Url.hh"
#include "lib/client/Client.hh"
#include "HttpHeader.hh"


class HttpClient: public Client {
public:
    HttpClient() noexcept = default;
    HttpClient(SocketPtr socket) {
        socket_ = socket;
    }
    void download(const Url& url) override;

private:
    SocketPtr socket_;
    HttpHeader header_;
};
