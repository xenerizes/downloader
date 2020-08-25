#pragma once

#include <fstream>
#include <cstdio>
#include "gtest/gtest.h"
#include "lib/writer/Writer.hh"

namespace test {

namespace helpers {

bool file_equals(const std::string& str, const std::string& filename)
{
    std::ifstream f(filename);
    if (!f.is_open()) {
        throw std::runtime_error("Error opening file " + filename);
    }
    char rhs;
    for (auto& lhs: str) {
        f.get(rhs);
        if (f.fail()) return false;
        if (lhs != rhs) return false;
    }
    f.get(rhs);
    return f.eof();
}

} // namespace helpers

TEST(Writer, WriteStr) {
    auto filename = "temp-file.txt";
    std::string data = "rnd string\nto be written";

    Writer wr(filename);
    wr.write(data.c_str(), data.length());

    EXPECT_TRUE(helpers::file_equals(data, filename));

    std::remove(filename);
}

TEST(Writer, WriteBuf) {
    auto filename = "temp-file.txt";
    std::string data = "rnd string\nto be written";

    Buffer buf;
    buf.append(data);

    Writer wr(filename);
    wr.write(buf);

    EXPECT_TRUE(helpers::file_equals(data, filename));

    std::remove(filename);
}

} // namespace test