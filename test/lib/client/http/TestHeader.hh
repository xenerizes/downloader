#pragma once

#include "lib/client/http/header/HttpHeader.hh"

#include "gtest/gtest.h"


TEST(HttpHeader, RequestHeader) {
    const char* url_str = "http://localhost/netinet.html";
    const char* valid_request = ""
        "GET /netinet.html HTTP/1.1\r\n"
        "Host: localhost\r\n"
        "Accept: */*\r\n"
        "Connection: close\r\n"
        "\r\n";

    auto url = UrlParser(url_str).parse();

    HttpHeader header;
    Request req = { url.hostname, url.path };
    auto request = header.build_request(req);

    ASSERT_STREQ(valid_request, request.data());
}

TEST(HttpHeader, ResponseHeaderOK) {
    const char* raw_response = ""
        "HTTP/1.1 200 OK\r\n"
        "Server: nginx/1.10.3 (Ubuntu)\r\n"
        "Date: Tue, 29 May 2018 14:42:12 GMT\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: 21\r\n"
        "Last-Modified: Mon, 28 May 2018 20:52:08 GMT\r\n"
        "Connection: keep-alive\r\n"
        "ETag: \"5b0c6bf8-1451\"\r\n"
        "Accept-Ranges: bytes\r\n"
        "\r\n"
        "<DOCTYPE html PUBLIC>";

    Buffer buf;
    buf.append(raw_response);

    HttpHeader header;
    auto resp = header.parse_response(buf);

    ASSERT_EQ(resp.success, true);
    ASSERT_STREQ(resp.code.c_str(), "200 OK");
    ASSERT_STREQ(resp.filename.c_str(), "");
    ASSERT_EQ(resp.content_length, 21);
    ASSERT_EQ(resp.header_length, 247);
}

TEST(HttpHeader, ResponseHeaderFail) {
    const char* raw_response = ""
        "HTTP/1.1 404 Not Found\r\n"
        "Content-Length: 178\r\n"
        "\r\n"
        "<html>\n"
        "<head><title>404 Not Found</title></head>\n"
        "<body bgcolor=\"white\">\n"
        "<center><h1>404 Not Found</h1></center>\n"
        "<hr><center>nginx/1.10.3 (Ubuntu)</center>\n"
        "</body>\n"
        "</html>";

    Buffer buf;
    buf.append(raw_response);

    HttpHeader header;
    auto resp = header.parse_response(buf);

    ASSERT_EQ(resp.success, false);
    ASSERT_STREQ(resp.code.c_str(), "400 Not Found");
    ASSERT_STREQ(resp.filename.c_str(), "");
    ASSERT_EQ(resp.content_length, 178);
    ASSERT_EQ(resp.header_length, 47);
}
