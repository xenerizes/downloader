#include "lib/client/http/header/PropertyIterator.hh"

#include <cstring>

constexpr const char* HTTP_1_1_ = "HTTP/1.1";
constexpr const char CARRIAGE_RETURN = '\r';
constexpr const char NEWLINE = '\n';

PropertyIterator::PropertyIterator(const Buffer& buf) : buf_(buf), pos_(0) { }

HeaderProperty PropertyIterator::next()
{
    auto line = getline();
    return make_property(line);
}

size_t PropertyIterator::raw_pos() { return pos_; }

Line PropertyIterator::getline()
{
    size_t start = pos_;
    // FIXME: search for full delim
    size_t end = buf_.find(CARRIAGE_RETURN, start);
    if (end != std::string::npos) {
        pos_ = end + 2;
        return Line(start, end);
    }

    return Line(0, 0);
}

HeaderProperty PropertyIterator::make_property(const Line& line)
{
    return HeaderProperty(PropertyType::EMPTY, line);
}
