#include "lib/client/http/header/HttpHeader.hh"


Buffer HttpHeader::build_request(const Request& req)
{
    Buffer buf;
    buf.append("GET ");
    buf.append(req.path);
    buf.append(" HTTP/1.1\r\n");
    buf.append("Host: ");
    buf.append(req.hostname);
    buf.append("\r\n");
    buf.append("Accept: */*\r\n");
    buf.append("Connection: close\r\n\r\n");

    return buf;
}

Response HttpHeader::parse_response(const Buffer& buf)
{
    return Response();
}
