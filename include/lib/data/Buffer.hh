#pragma once

#include <memory>
#include <vector>

constexpr size_t BUFFER_SIZE = 1024;

class Buffer {
public:
    Buffer(size_t size = BUFFER_SIZE + 1);

    char* data();
    const char* data() const;
    size_t size() const;
    size_t max_size() const;

    void append(const std::string& data);

private:
    size_t max_size_ {BUFFER_SIZE + 1};
    std::vector<char> data_;
};
