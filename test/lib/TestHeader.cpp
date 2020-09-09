#include "gtest/gtest.h"

#include "lib/client/http/HttpHeader.hh"
#include "lib/client/url/Url.hh"


TEST(HttpHeader, RequestHeader) {
    const char* url_str = "http://localhost/netinet.html";
    const char* valid_request = ""
        "GET /netinet.html HTTP/1.1\r\n"
        "Host: localhost\r\n"
        "Accept: */*\r\n"
        "Connection: close\r\n"
        "\r\n";

    auto url = Url(url_str);

    HttpHeader header;
    Request req = { url.hostname, url.path };
    auto request = header.build_request(req);

    EXPECT_STREQ(valid_request, request.data());
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

    EXPECT_EQ(resp.success, true);
    EXPECT_STREQ(resp.code.c_str(), "200 OK");
    EXPECT_EQ(resp.content_length, 21);
    EXPECT_EQ(resp.header_length, 247);
    
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

    EXPECT_EQ(resp.success, false);
    EXPECT_STREQ(resp.code.c_str(), "404 Not Found");
    EXPECT_EQ(resp.content_length, 178);
    EXPECT_EQ(resp.header_length, 47);
}

TEST(HttpHeader, ResponseBuffers) {
    Response empty_resp = {
        .success = true,
        .code = "200 OK",
        .content_length = 0,
        .header_length = 370
    };

    EXPECT_EQ(empty_resp.first_buf_content_size(BUFFER_SIZE), 0);
    EXPECT_EQ(empty_resp.full_buf_count(BUFFER_SIZE), 0);
    EXPECT_EQ(empty_resp.last_buf_content_size(BUFFER_SIZE), 0);

    Response one_buf_resp = {
        .success = true,
        .code = "200 OK",
        .content_length = 150,
        .header_length = 300
    };

    EXPECT_EQ(one_buf_resp.first_buf_content_size(BUFFER_SIZE), 150);
    EXPECT_EQ(one_buf_resp.full_buf_count(BUFFER_SIZE), 0);
    EXPECT_EQ(one_buf_resp.last_buf_content_size(BUFFER_SIZE), 0);

    Response two_buf_resp = {
        .success = true,
        .code = "200 OK",
        .content_length = 700,
        .header_length = 324
    };

    EXPECT_EQ(two_buf_resp.first_buf_content_size(BUFFER_SIZE), 1024 - 324);
    EXPECT_EQ(two_buf_resp.full_buf_count(BUFFER_SIZE), 0);
    EXPECT_EQ(two_buf_resp.last_buf_content_size(BUFFER_SIZE), 0);

    Response full_buf_resp = {
        .success = true,
        .code = "200 OK",
        .content_length = 1024 + 724,
        .header_length = 300
    };

    EXPECT_EQ(full_buf_resp.first_buf_content_size(BUFFER_SIZE), 1024 - 300);
    EXPECT_EQ(full_buf_resp.full_buf_count(BUFFER_SIZE), 1);
    EXPECT_EQ(full_buf_resp.last_buf_content_size(BUFFER_SIZE), 0);

    Response large_resp = {
        .success = true,
        .code = "200 OK",
        .content_length = 65537,
        .header_length = 300
    };

    EXPECT_EQ(large_resp.first_buf_content_size(BUFFER_SIZE), 1024 - 300);
    EXPECT_EQ(large_resp.full_buf_count(BUFFER_SIZE), 63);
    EXPECT_EQ(large_resp.last_buf_content_size(BUFFER_SIZE), 301);
}
