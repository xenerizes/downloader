#include <fstream>
#include "gtest/gtest.h"
#include "lib/client/url/UrlParser.hh"
#include "lib/client/http/HttpClient.hh"
#include "helpers.h"

namespace test {

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
