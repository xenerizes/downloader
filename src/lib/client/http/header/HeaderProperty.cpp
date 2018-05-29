#include "lib/client/http/header/HeaderProperty.hh"

HeaderProperty::HeaderProperty(PropertyType ty_, Line loc_, const Buffer& buf_)
    : type(ty_)
    , location(std::move(loc_))
    , buf(buf_)
{ }

std::string HeaderProperty::extract()
{
    std::string extracted;

    for (size_t i = location.first; i < location.second; ++i) {
        extracted.push_back(buf.data()[i]);
    }

    return extracted;
}
