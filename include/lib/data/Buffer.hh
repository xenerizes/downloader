#pragma once

#include <vector>
#include <memory>

using BufferWrapper = std::vector<char>;
using BufferSizeType = BufferWrapper::size_type;
using RawBuffer = BufferWrapper::value_type*;

constexpr BufferSizeType BUFFER_SIZE = 1024;

class Buffer {
public:
    Buffer(BufferSizeType size = BUFFER_SIZE);

    RawBuffer access();
    BufferSizeType size();

private:
    BufferWrapper data_;
};
