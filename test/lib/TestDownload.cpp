#include <fstream>
#include "gtest/gtest.h"
#include "lib/client/url/Url.hh"
#include "lib/client/http/HttpClient.hh"
#include "helpers.h"

namespace test {

TEST(Download, Index) {
    Url url("http://0.0.0.0:9999/index.html");
    HttpClient client;
    client.download(url);

    EXPECT_TRUE(helpers::file_equals("../../web/index.html", "index.html"));

    std::remove("index.html");
}

TEST(Download, Orchid) {
    Url url("http://0.0.0.0:9999/files/orchid.jpg");
    HttpClient client;
    client.download(url);

    EXPECT_TRUE(helpers::file_equals("../../web/files/orchid.jpg", "orchid.jpg"));

    std::remove("orchid.jpg");
}

TEST(Download, Errors) {
    HttpClient client;

    std::vector<std::string> bad_urls = { "file.txt",
                                          ".",
                                          "..",
                                          "http.",
                                          "http.txt" };

    for (auto& url_str: bad_urls) {
        Url url(url_str);
        EXPECT_ANY_THROW(client.download(url)) << "\t\tUrl: " << url_str << std::endl;
    }
}

} // ns test
