#include "lib/buffer/Buffer.hh"


Buffer::Buffer(size_t size)
    : max_size_(size + 1)
    , size_(0)
    , data_(max_size_, '\0')
{ }

char* Buffer::data() { return data_.data(); }
const char* Buffer::data() const { return data_.data(); }
size_t Buffer::size() const { return data_.size(); }
size_t Buffer::max_size() const { return max_size_; }

void Buffer::append(const std::string& data)
{
    for (const char& c: data) {
        if (size_ >= max_size_) {
            break;
        }
        data_[size_++] = c;
    }
}
