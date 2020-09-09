#include <fstream>
#include <cstdio>
#include "gtest/gtest.h"
#include "lib/writer/Writer.hh"
#include "helpers.h"

namespace test {

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

TEST(Writer, WriteFullJPG) {
    std::fstream jpg_file("../../web/files/orchid.jpg");
    std::stringstream ss;
    ss << jpg_file.rdbuf();
    std::string jpg(ss.str());

    auto filename = "tmp.jpg";
    Writer wr(filename);
    wr.write(jpg.c_str(), jpg.length());
    EXPECT_TRUE(helpers::file_equals(jpg, filename));

    std::remove(filename);
}

TEST(Writer, WriteJPGBuffers) {
    std::fstream jpg_file("../../web/files/orchid.jpg");
    std::stringstream ss;
    ss << jpg_file.rdbuf();
    std::string jpg(ss.str());
    Buffer buf[76];
    for (unsigned i = 0; i < 76; ++i) {
        buf[i].append(jpg.substr(i * BUFFER_SIZE, (i + 1) * BUFFER_SIZE));
    }

    auto filename = "tmp.jpg";
    Writer wr(filename);
    for (unsigned i = 0; i < 76; ++i) {
        wr.write(buf[i]);
    }
    EXPECT_TRUE(helpers::file_equals(jpg, filename));

    std::remove(filename);
}

} // namespace test