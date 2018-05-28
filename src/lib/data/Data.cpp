#include "lib/data/Data.hh"

void Data::append(const Buffer& buf)
{
    data_.insert(data_.end(), buf.begin(), buf.end());
}

const char* Data::access() const { return data_.data(); }
