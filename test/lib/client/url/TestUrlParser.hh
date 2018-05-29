#pragma once

#include "lib/client/url/UrlParser.hh"

#include "gtest/gtest.h"
#include <vector>


namespace test {

TEST(UrlParser, ParseValidUrl) {
    const char* url_str = "http://tools.ietf.org/rfc/rfc793.txt";

    auto url = UrlParser(url_str).parse();

    ASSERT_STREQ(url.path.c_str(), "/rfc/rfc793.txt");
    ASSERT_STREQ("tools.ietf.org", url.hostname.c_str());
    ASSERT_EQ("80", url.port);
}

TEST(UrlParser, ParseInvalidUrl) {
    std::vector<std::string> urls = {"https://tools.ietf.org/rfc/rfc793.txt",
                                     "http://",
                                     "tools.ietf.org/rfc/rfc793.txt",
                                     "h",
                                     "http:/",
                                     "http",
                                     "",
                                     " ",
                                     "/"
                                     "http:///",
                                     "http://:/" };

    for (const auto& url_str: urls) {
        ASSERT_THROW({
            auto url = UrlParser(url_str).parse();
        }, std::invalid_argument);
    }
}

TEST(UrlParser, ParseSite) {
    const char* url_str = "http://tools.ietf.org";

    auto url = UrlParser(url_str).parse();

    ASSERT_STREQ(url.path.c_str(), "/");
    ASSERT_STREQ("tools.ietf.org", url.hostname.c_str());
    ASSERT_EQ("80", url.port);
}

TEST(UrlParser, ParseSpecificPort) {
    const char* url_str = "http://tools.ietf.org:8000/";

    auto url = UrlParser(url_str).parse();

    ASSERT_STREQ(url.path.c_str(), "/");
    ASSERT_STREQ("tools.ietf.org", url.hostname.c_str());
    ASSERT_EQ("8000", url.port);
}

}