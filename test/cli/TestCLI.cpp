#include "gtest/gtest.h"
#include "cli/Settings.hh"

TEST(Cli, ParseArgs) {
    const char* args_ok[2] = {"./downloader",
                              "http://tools.ietf.org/rfc/rfc793.txt"};
    Url url = {
        .scheme = Scheme("http"),
        .hostname = "tools.ietf.org",
        .port = "80",
        .path = "/rfc/rfc793.txt",
        .filename = "rfc793.txt"};

    ArgumentParser argparser;
    Settings st = argparser.parse_args(2, (char**)args_ok);
    EXPECT_TRUE(st.client);
    EXPECT_EQ(st.url, url);
}
