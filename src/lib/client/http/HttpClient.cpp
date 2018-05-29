#include "lib/client/http/HttpClient.hh"

#include "lib/client/http/HttpHeader.hh"
#include "lib/writer/Writer.hh"

#include <iostream>
#include <cstring>


void HttpClient::download(const Url& url)
{
    socket_ = std::make_unique<Socket>(url.hostname, url.port);
    HttpHeader http_header(url);
    socket_->send_data(http_header.build_request());
    std::string filename = "file.html";
    Writer writer(filename);
    Buffer buf;
    do {
        buf = socket_->read_data();
        writer.write(buf);
    } while (buf.size() == buf.max_size());
}
