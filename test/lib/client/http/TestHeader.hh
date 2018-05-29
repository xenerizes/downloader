#pragma once

#include "lib/client/http/HttpHeader.hh"

#include "gtest/gtest.h"


TEST(HttpHeader, RequestHeader) {
    const char* url_str = "http://localhost/netinet.html";
    std::string valid_request = ""
        "GET /netinet.html HTTP/1.1\r\n"
        "Host: localhost\r\n"
        "Accept: */*\r\n"
        "Connection: close\r\n"
        "\r\n";

    auto url = UrlParser(url_str).parse();

    HttpHeader header(url);
    auto request = header.build_request();

    ASSERT_STREQ(valid_request.c_str(), request.data());
}
