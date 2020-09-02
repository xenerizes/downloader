#pragma once

#include <string>

struct Response {
    bool success;
    std::string code;
    size_t content_length;
    size_t header_length;

    long first_buf_content_size(size_t buf_size);
    long full_buf_count(size_t buf_size);
    long last_buf_content_size(size_t buf_size);
};
