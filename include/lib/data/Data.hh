#pragma once

#include "Buffer.hh"

#include <vector>

class Data {
public:
    Data() noexcept = default;
    Data(std::string filename);

    std::string filename() const;
    const char* access() const;
    size_t size() const;

    void append(const Buffer& buf);

private:
    std::vector<char> data_;
    std::string filename_;
};
