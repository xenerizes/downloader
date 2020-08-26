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

} // test