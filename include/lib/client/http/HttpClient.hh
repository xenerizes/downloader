#pragma once
#include "lib/buffer/Profiler.h"
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
    std::shared_ptr<ProfilerVariable<size_t>> bps = std::make_shared<ProfilerVariable<size_t>>(1000);

};
