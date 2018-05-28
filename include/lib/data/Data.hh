#pragma once

#include "Buffer.hh"

#include <vector>

class Data {
public:
    Data() noexcept = default;
    Data(const std::string& data);

    void append(const Buffer& buf);

    const char* access() const;

private:
    std::vector<char> data_;
};
