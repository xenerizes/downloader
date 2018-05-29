#include "lib/client/http/HttpClient.hh"

#include "lib/writer/Writer.hh"

#include <cmath>


void HttpClient::download(const Url& url) {
    socket_ = std::make_unique<Socket>(url.hostname, url.port);
    auto req = Request { url.hostname, url.path };

    socket_->send_data(header_.build_request(req));
    Buffer buf = socket_->read_data();
    auto resp = header_.parse_response(buf);

    if (!resp.success) {
        throw std::runtime_error("HTTP error: " + resp.code);
    }

    auto buffers = resp.full_buffers(BUFFER_SIZE);
    auto first_buffer = resp.first_buffer(BUFFER_SIZE);
    auto last_buffer = resp.last_buffer_size(BUFFER_SIZE);

    Writer writer(url.filename);
    writer.write(buf.data() + resp.header_length, first_buffer);

    for (int i = 0; i < buffers; ++i) {
        buf = socket_->read_data();
        writer.write(buf);
    }

    if (last_buffer > 0) {
        buf = socket_->read_data();
        writer.write(buf.data(), last_buffer);
    }
}
