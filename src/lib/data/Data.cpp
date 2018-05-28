#include "lib/data/Data.hh"

Data::Data(std::string filename) : filename_(std::move(filename)) { }

std::string Data::filename() const { return filename_; }

size_t Data::size() const { return data_.size(); }

void Data::append(const Buffer& buf)
{
    data_.insert(data_.end(), buf.begin(), buf.end());
}

const char* Data::access() const { return data_.data(); }
