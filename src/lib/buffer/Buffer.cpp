#include <cstring>
#include "lib/buffer/Buffer.hh"


Buffer::Buffer(size_t size)
    : max_size_(size + 1)
    , size_(0)
    , data_(max_size_, '\0')
{ }

char* Buffer::data() { return data_.data(); }
const char* Buffer::data() const { return data_.data(); }
size_t Buffer::size() const { return size_; }

size_t Buffer::find(char c, size_t pos) const
{
    for (size_t i = pos; i < data_.size(); ++i) {
        if (data_[i] == c) {
            return i;
        }
    }

    return std::string::npos;
}

void Buffer::clear()
{
    size_ = 0;
    std::memset(data_.data(), 0, sizeof(char) * (max_size_ - 1));
}

void Buffer::append(const std::string& data)
{
    for (const char& c: data) {
        if (size_ >= max_size_ - 1) {
            break;
        }
        data_[size_++] = c;
    }
}
