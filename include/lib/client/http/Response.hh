#pragma once

#include <string>

struct Response {
    bool success;
    std::string code;
    size_t content_length;
    size_t header_length;

    long first_buffer(size_t buf_size);
    long full_buffers(size_t buf_size);
    long last_buffer_size(size_t buf_size);
};
