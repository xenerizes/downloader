#pragma once

#include "lib/buffer/Buffer.hh"

#include <string>
#include <fstream>


class Writer {
public:
    Writer(std::string filename);
    ~Writer();

    void write(const Buffer& data);
    void write(const char* data, size_t len);
    void reset();

private:
    std::string filename_;
    std::ofstream file_;
};
