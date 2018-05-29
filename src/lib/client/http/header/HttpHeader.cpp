#include "lib/client/http/HttpHeader.hh"


Buffer HttpHeader::build_request(const Request& req)
{
    Buffer buf;
    buf.append("GET " + req.path + " HTTP/1.1\r\n");
    buf.append("Host: " + req.hostname + "\r\n");
    buf.append("Accept: */*\r\n");
    buf.append("Connection: close\r\n\r\n");

    return buf;
}

Response HttpHeader::parse_response(const Buffer& buf)
{
    return Response();
}
