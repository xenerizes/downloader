#include "lib/data/Data.hh"

Data::Data(const std::string& data)
{
    data_.assign(data.begin(), data.end());
}

void Data::append(const Buffer& buf)
{
    data_.insert(data_.end(), buf.begin(), buf.end());
}

const char* Data::access() const { return data_.data(); }
