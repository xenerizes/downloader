#pragma once

#include <string>

struct Response {
    bool success;
    std::string code;
    size_t content_length;
    std::string filename;
    size_t header_length;
};
