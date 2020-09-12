#include <vector>

#include "gtest/gtest.h"
#include "lib/client/url/Url.hh"


namespace test {

TEST(UrlParser, ParseUrl) {
    const char* url_str = "http://tools.ietf.org/rfc/rfc793.txt";

    auto url = Url(url_str);

    EXPECT_EQ(url.scheme, Scheme("http"));
    EXPECT_STREQ(url.path.c_str(), "/rfc/rfc793.txt");
    EXPECT_STREQ("tools.ietf.org", url.hostname.c_str());
    EXPECT_STREQ("rfc793.txt", url.filename.c_str());
    EXPECT_EQ("80", url.port);
}

TEST(UrlParser, Defaults) {
    const char* url_str = "tools.ietf.org";

    auto url = Url(url_str);

    EXPECT_EQ(url.scheme, Scheme("http"));
    EXPECT_STREQ(url.path.c_str(), "");
    EXPECT_STREQ("tools.ietf.org", url.hostname.c_str());
    EXPECT_STREQ("index.html", url.filename.c_str());
    EXPECT_EQ("80", url.port);
}

TEST(UrlParser, ParseInvalidUrl) {
    std::vector<std::string> urls = {"https://tools.ietf.org/rfc/rfc793.txt",
                                     "http://",
                                     "http:/",
                                     "",
                                     " ",
                                     "/",
                                     "http:///",
                                     "http://:/" };

    for (const auto& url_str: urls) {
        EXPECT_ANY_THROW({
            Url url(url_str);
        }) << "     Url: " << url_str << std::endl;
    }
}

TEST(UrlParser, ParseValidUrl) {
    std::vector<std::string> urls = {"http://tools.ietf.org/rfc/rfc793.txt",
                                     "tools.ietf.org/rfc/rfc793.txt",
                                     "tools.ietf.org",
                                     "  tools.ietf.org",
                                     "  tools.ietf.org   ",
                                     "tools.ietf.org ",
                                     "http",
                                     "localhost",
                                     "0.0.0.0",
                                     "yandex.ru",
                                     "server:43" };

    for (const auto& url_str: urls) {
        EXPECT_NO_THROW({
            Url url(url_str);
        }) << "     Url: " << url_str << std::endl;
    }
}

TEST(UrlParser, ParseSite) {
    const char* url_str = "http://tools.ietf.org";

    auto url = Url(url_str);

    EXPECT_STREQ(url.path.c_str(), "");
    EXPECT_STREQ("tools.ietf.org", url.hostname.c_str());
    EXPECT_STREQ("index.html", url.filename.c_str());
    EXPECT_EQ("80", url.port);
}

TEST(UrlParser, ParseSpecificPort) {
    const char* url_str = "http://tools.ietf.org:8000/";

    auto url = Url(url_str);

    EXPECT_STREQ(url.path.c_str(), "/");
    EXPECT_STREQ("tools.ietf.org", url.hostname.c_str());
    EXPECT_STREQ("index.html", url.filename.c_str());
    EXPECT_EQ("8000", url.port);
}

}