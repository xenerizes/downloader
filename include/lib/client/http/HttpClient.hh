#pragma once

#include "lib/client/socket/Socket.hh"
#include "lib/client/url/Url.hh"
#include "lib/client/Client.hh"
#include "lib/client/http/header/HttpHeader.hh"


class HttpClient: public Client {
public:
    HttpClient() noexcept = default;

    void download(const Url& url) override;

private:
    SocketPtr socket_;
    HttpHeader header_;
};
