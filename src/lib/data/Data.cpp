#include "lib/data/Data.hh"

Data::Data(std::string filename) : filename_(std::move(filename)) { }

std::string Data::filename() const { return filename_; }

size_t Data::size() const { return data_.size(); }

void Data::append(const Buffer& buf)
{
    const char* p = buf.data();
    for (size_t i = 0; i < buf.size(); ++i) {
        data_.emplace_back(*(p + i));
    }
}

const char* Data::access() const { return data_.data(); }
