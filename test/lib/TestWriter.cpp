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
    Writer wr(filename);

    std::string data = "rnd string\nto be written";
    wr.write(data.c_str(), data.length());
    EXPECT_TRUE(helpers::file_equals(data, filename));

    wr.reset();

    std::string data_empty = "";
    wr.write(data_empty.c_str(), data_empty.length());
    EXPECT_TRUE(helpers::file_equals(data_empty, filename));

    wr.reset();

    std::string data_binary = "\1\2\3\4\5\6\7\a\b\f\r\v\n\t";
    wr.write(data_binary.c_str(), data_binary.length());
    EXPECT_TRUE(helpers::file_equals(data_binary, filename));

    std::remove(filename);
}

TEST(Writer, WriteBuf) {
    auto filename = "temp-file.txt";
    Writer wr(filename);
    Buffer buf;

    std::string data = "rnd string\nto be written";
    buf.append(data);
    wr.write(buf);
    EXPECT_TRUE(helpers::file_equals(data, filename));

    buf.clear();
    wr.reset();

    std::string data_empty = "";
    buf.append(data_empty);
    wr.write(buf);
    EXPECT_TRUE(helpers::file_equals(data_empty, filename));

    buf.clear();
    wr.reset();

    std::string data_binary = "\1\2\3\4\5\6\7\a\b\f\r\v\n\t";
    buf.append(data_binary);
    wr.write(buf);
    EXPECT_TRUE(helpers::file_equals(data_binary, filename));

    std::remove(filename);
}

} // namespace test