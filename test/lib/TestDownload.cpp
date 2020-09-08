#include <fstream>
#include "gtest/gtest.h"
#include "lib/client/url/UrlParser.hh"
#include "lib/client/http/HttpClient.hh"

namespace test {

namespace helpers {

bool file_equals(const char* lhs_filename, const char* rhs_filename)
{
    std::ifstream lhs_stream(lhs_filename);
    std::ifstream rhs_stream(rhs_filename);
    if (!lhs_stream.is_open() || !rhs_stream.is_open()) return false;
    char lhs, rhs;
    while (!lhs_stream.eof() || !rhs_stream.eof()) {
        lhs_stream.get(lhs);
        rhs_stream.get(rhs);
        if (lhs_stream.fail() && rhs_stream.fail()) return true;
        if (lhs_stream.fail() || rhs_stream.fail()) return false;
        if (rhs != lhs) return false;
    }
    return true;
}

}

TEST(Download, Index) {
    UrlParser parser("http://0.0.0.0:9999/index.html");
    HttpClient client;
    client.download(parser.parse());

    EXPECT_TRUE(helpers::file_equals("../../web/index.html", "index.html"));

    std::remove("index.html");
}

TEST(Download, Orchid) {
    UrlParser parser("http://0.0.0.0:9999/files/orchid.jpg");
    HttpClient client;
    client.download(parser.parse());

    EXPECT_TRUE(helpers::file_equals("../../web/files/orchid.jpg", "orchid.jpg"));

    std::remove("orchid.jpg");
}

} // ns test
