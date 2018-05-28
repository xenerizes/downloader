#pragma once

#include "Buffer.hh"

#include <vector>

class Data {
public:
    void append(const Buffer& buf);

    const char* access() const;

private:
    std::vector<char> data_;
};
