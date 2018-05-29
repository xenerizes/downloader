#include <iostream>
#include "lib/client/http/HttpHeader.hh"

HttpHeader::HttpHeader(const Url& url) : url_(url) { }

Buffer HttpHeader::build_request()
{
    Buffer buf;
    buf.append("GET ");
    buf.append(url_.path);
    buf.append(" HTTP/1.1\r\n");
    buf.append("Host: ");
    buf.append(url_.hostname);
    buf.append("\r\n");
    buf.append("Accept: */*\r\n");
    buf.append("Connection: close\r\n\r\n");

    return buf;
}
