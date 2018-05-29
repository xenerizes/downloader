#pragma once

#include "lib/buffer/Buffer.hh"
#include "Request.hh"
#include "Response.hh"


class HttpHeader {
public:
    HttpHeader() noexcept = default;

    Buffer build_request(const Request& req);
    Response parse_response(const Buffer& buf);
};
