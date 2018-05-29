#pragma once

#include "lib/buffer/Buffer.hh"
#include "lib/client/http/Request.hh"
#include "lib/client/http/Response.hh"


class HttpHeader {
public:
    HttpHeader() noexcept = default;

    Buffer build_request(const Request& req);
    Response parse_response(const Buffer& buf);
};
