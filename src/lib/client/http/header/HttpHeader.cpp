#include "lib/client/http/HttpHeader.hh"

#include "lib/client/http/header/PropertyIterator.hh"

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
    PropertyIterator iterator(buf);
    Response resp;

    for (auto prop = iterator.next();
         !(prop->type == PropertyType::EMPTY);
         prop = iterator.next()) {

        prop->append(resp);
    }

    resp.header_length = iterator.raw_pos();
    return resp;
}
