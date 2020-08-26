#include "gtest/gtest.h"
#include "lib/buffer/Buffer.hh"

namespace test {

TEST(Buffer, Append) {
    Buffer buf;
    std::string str = "rnd test\nstring\t\t!";

    buf.append("");
    EXPECT_STREQ(buf.data(), "");
    EXPECT_EQ(buf.size(), 0);

    buf.append(str);
    EXPECT_STREQ(buf.data(), str.c_str());
    EXPECT_EQ(buf.size(), str.length());

    buf.append("");
    EXPECT_STREQ(buf.data(), str.c_str());
    EXPECT_EQ(buf.size(), str.length());

    std::string str_2 = "new data";
    buf.clear();
    buf.append(str_2);
    EXPECT_STREQ(buf.data(), str_2.c_str());
    EXPECT_EQ(buf.size(), str_2.length());
}

TEST(Buffer, AppendLarge) {
    Buffer buf(5);

    buf.append("short string");
    EXPECT_STREQ(buf.data(), "short");
    EXPECT_EQ(buf.size(), 5);
}

TEST(Buffer, Find) {
    Buffer buf;

    EXPECT_EQ(std::string::npos, buf.find('7', 0));
    EXPECT_EQ(std::string::npos, buf.find('7', 5));
    EXPECT_EQ(std::string::npos, buf.find('7', 2048));

    buf.append("rnd.test\nstring\t\t!");
    EXPECT_EQ(std::string::npos, buf.find('7', 0));
    EXPECT_EQ(std::string::npos, buf.find('7', 5));
    EXPECT_EQ(std::string::npos, buf.find('7', 2048));
    EXPECT_EQ(std::string::npos, buf.find('r', 2048));
    EXPECT_EQ(0, buf.find('r', 0));
    EXPECT_EQ(4, buf.find('t', 0));
    EXPECT_EQ(4, buf.find('t', 4));
    EXPECT_EQ(7, buf.find('t', 5));
    EXPECT_EQ(8, buf.find('\n', 2));
}

} // test