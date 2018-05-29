#include "lib/client/http/HttpClient.hh"

#include "lib/writer/Writer.hh"

#include <cmath>


namespace util {

long buffers(size_t content_length, size_t buf_size)
{
    return std::ceil(content_length / buf_size);
}

}

void HttpClient::download(const Url& url) {
    socket_ = std::make_unique<Socket>(url.hostname, url.port);
    auto req = Request { url.hostname, url.path };

    socket_->send_data(header_.build_request(req));
    Buffer buf = socket_->read_data();
    auto resp = header_.parse_response(buf);

    if (!resp.success) {
        throw std::runtime_error("HTTP error: " + resp.code);
    }

    Writer writer(url.filename);
    auto buffers = util::buffers(resp.content_length, BUFFER_SIZE);

    for (int i = 0; i < buffers; ++i) {
        buf = socket_->read_data();
        writer.write(buf);
    }
}
