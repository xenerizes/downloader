#include "lib/data/Data.hh"

Data::Data(const std::string& data)
{
    data_.assign(data.begin(), data.end());
}

std::string Data::filename() const { return "empty"; }

size_t Data::size() const { return data_.size(); }

void Data::append(const Buffer& buf)
{
    data_.insert(data_.end(), buf.begin(), buf.end());
}

const char* Data::access() const { return data_.data(); }
