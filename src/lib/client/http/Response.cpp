#include "lib/client/http/Response.hh"

#include <cmath>

long Response::first_buffer(size_t buf_size)
{
    if (buf_size - header_length > content_length) return content_length;
    return buf_size - header_length;
}

long Response::full_buffers(size_t buf_size)
{
    long tail_len = (content_length - first_buffer(buf_size));
    if (tail_len > 0) return std::trunc(tail_len / buf_size);
    else return 0;
}

long Response::last_buffer_size(size_t buf_size)
{
    auto buffers = full_buffers(buf_size);
    return content_length - first_buffer(buf_size) - buffers * buf_size ;
}
