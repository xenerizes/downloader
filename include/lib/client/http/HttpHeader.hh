#pragma once

#include "lib/client/url/Url.hh"
#include "lib/data/Buffer.hh"

class HttpHeader {
public:
    HttpHeader(const Url& url);

    Buffer build_request();

private:
    const Url& url_;
};
