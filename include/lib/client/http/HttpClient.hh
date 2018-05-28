#pragma once

#include "lib/client/socket/Socket.hh"
#include "lib/client/url/Url.hh"
#include "lib/client/Client.hh"


class HttpClient: public Client {
public:
    HttpClient() noexcept = default;

    Data download(const Url& url) override;

private:
    SocketPtr socket_;
};
