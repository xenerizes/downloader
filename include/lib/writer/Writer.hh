#pragma once

#include "lib/buffer/Buffer.hh"

#include <string>
#include <fstream>


class Writer {
public:
    Writer(std::string filename);
    ~Writer();

    void write(const Buffer& data);

private:
    std::string filename_;
    std::ofstream file_;
};
