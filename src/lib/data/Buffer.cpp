#include "lib/data/Buffer.hh"

Buffer::Buffer(BufferSizeType size) : data_(size) { }

RawBuffer Buffer::access() { return data_.data(); }

BufferSizeType Buffer::size() { return data_.size(); }
