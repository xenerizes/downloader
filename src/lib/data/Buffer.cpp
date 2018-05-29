#include "lib/data/Buffer.hh"

#include <cstring>


Buffer::Buffer(size_t size)
    : max_size_(size)
    , data_()
{
    data_.reserve(max_size_);
}

char* Buffer::data() { return data_.data(); }
const char* Buffer::data() const { return data_.data(); }
size_t Buffer::size() const { return strlen(data_.data()); }
size_t Buffer::max_size() const { return max_size_; }

void Buffer::append(const std::string& data)
{
    auto at = data_.size();
    for (const char& c: data) {
        if (at++ >= max_size_) {
            break;
        }
        data_.push_back(c);
    }
}
