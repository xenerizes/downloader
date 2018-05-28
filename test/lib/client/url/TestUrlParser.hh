#pragma once

#include "lib/client/url/UrlParser.hh"

#include "gtest/gtest.h"


namespace test {

TEST(UrlParser, ParseValidUrl) {
    const char* url_str = "http://tools.ietf.org/rfc/rfc793.txt";
    UrlParser parser;

    auto url = parser.parse(url_str);

    ASSERT_STREQ(url_str, url.path.c_str());
    ASSERT_STREQ("tools.ietf.org", url.hostname.c_str());
    ASSERT_EQ(80, url.port);
}

TEST(UrlParser, ParseInvalidUrl) {
    const char* url_str_1 = "https://tools.ietf.org/rfc/rfc793.txt";
    const char* url_str_2 = "http://";
    const char* url_str_3 = "tools.ietf.org/rfc/rfc793.txt";

    UrlParser parser;

    ASSERT_THROW({
        auto url = parser.parse(url_str_1);
    }, std::invalid_argument);

    ASSERT_THROW({
        auto url = parser.parse(url_str_2);
    }, std::invalid_argument);

    ASSERT_THROW({
        auto url = parser.parse(url_str_3);
    }, std::invalid_argument);
}

TEST(UrlParser, ParseSite) {
    const char* url_str = "http://tools.ietf.org";
    UrlParser parser;

    auto url = parser.parse(url_str);

    ASSERT_STREQ(url_str, url.path.c_str());
    ASSERT_STREQ("tools.ietf.org", url.hostname.c_str());
    ASSERT_EQ(80, url.port);
}

}