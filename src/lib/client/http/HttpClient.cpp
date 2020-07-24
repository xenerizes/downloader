#include "lib/client/http/HttpClient.hh"

#include "lib/writer/Writer.hh"
#include "lib/buffer/Profiler.h"
#include <cmath>
#include <iostream>

void HttpClient::download(const Url &url)
{
    if (!socket_)
        socket_ = std::make_shared<Socket>(url.hostname, url.port);
    auto req = Request{url.hostname, url.path};

    socket_->send_data(header_.build_request(req));
    Buffer buf = socket_->read_data();
    auto resp = header_.parse_response(buf);

    if (!resp.success)
    {
        throw std::runtime_error("HTTP error: " + resp.code);
    }

    auto buffers = resp.full_buffers(BUFFER_SIZE);
    auto first_buffer = resp.first_buffer(BUFFER_SIZE);
    auto last_buffer = resp.last_buffer_size(BUFFER_SIZE);

    Writer writer(url.filename);
    writer.write(buf.data() + resp.header_length, first_buffer);
    size_t last_kbps = 0;
    for (int i = 0; i < buffers; ++i)
    {
        buf = socket_->read_data();
        writer.write(buf);
        bps->profile([&buf](size_t &counter) { counter+=buf.size(); }, [](size_t &counter) { counter = 0; });
        size_t now_kbps = bps->getSample();
        if (now_kbps!=last_kbps) 
            std::cout << last_kbps/1000 << " kbps" << std::endl;
        last_kbps = now_kbps;
    }

    if (last_buffer > 0)
    {
        buf = socket_->read_data();
        writer.write(buf.data(), last_buffer);
    }
}
