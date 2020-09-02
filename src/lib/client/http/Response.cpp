#include "lib/client/http/Response.hh"

#include <cmath>

long Response::first_buf_content_size(size_t buf_size)
{
    auto remaining_buf = buf_size - header_length;
    return remaining_buf > content_length ? content_length : remaining_buf;
}

long Response::full_buf_count(size_t buf_size)
{
    long tail_len = (content_length - first_buf_content_size(buf_size));
    if (tail_len > 0) return std::trunc(tail_len / buf_size);
    else return 0;
}

long Response::last_buf_content_size(size_t buf_size)
{
    auto buffers = full_buf_count(buf_size);
    return content_length - first_buf_content_size(buf_size) - buffers * buf_size ;
}
