#include "lib/client/http/Response.hh"

#include <cmath>

long Response::first_buffer(size_t buf_size)
{
    return buf_size - header_length;
}

long Response::full_buffers(size_t buf_size)
{
    return std::trunc((content_length - first_buffer(buf_size)) / buf_size);
}

long Response::last_buffer_size(size_t buf_size)
{
    auto buffers = full_buffers(buf_size);
    return buffers * buf_size - content_length - first_buffer(buf_size);
}
