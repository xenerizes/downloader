#include "gtest/gtest.h"
#include "cli/Settings.hh"
#include "cli/Application.hh"
#include "helpers.h"

namespace test {

TEST(Cli, ParseArgs) {
    const char* args_ok[2] = {"./downloader",
                              "http://tools.ietf.org/rfc/rfc793.txt"};
    Url url = {
        .scheme = Scheme("http"),
        .hostname = "tools.ietf.org",
        .port = "80",
        .path = "/rfc/rfc793.txt",
        .filename = "rfc793.txt"
    };

    ArgumentParser argparser;
    Settings st = argparser.parse_args(2, (char**)args_ok);
    EXPECT_TRUE(st.client);
    EXPECT_EQ(st.url, url);
}

TEST(Cli, DownloadThroughApp) {
    Url url = {
        .scheme = Scheme("http"),
        .hostname = "0.0.0.0",
        .port = "9999",
        .path = "/files/orchid.jpg",
        .filename = "orchid.jpg"
    };

    auto client = url.scheme.make_client();
    Settings st(url, client);
    Application app;

    app.run(st);
    EXPECT_TRUE(helpers::file_equals("../../web/files/orchid.jpg", "orchid.jpg"));

    std::remove("orchid.jpg");
}

} // ns test
