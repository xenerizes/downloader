#include "lib/client/http/header/PropertyIterator.hh"

#include "lib/client/http/header/Properties.hh"
#include <cstring>


constexpr const char CARRIAGE_RETURN = '\r';
constexpr const char NEWLINE = '\n';

constexpr const char* HTTP_1_1_PROPERTY = "HTTP/1.1 ";
constexpr const char* CONTENT_LENGTH_PROPERTY = "Content-Length: ";
constexpr const char* TRANSFER_ENCODING_PROPERTY = "Transfer-Encoding: ";


PropertyIterator::PropertyIterator(const Buffer& buf) : buf_(buf), pos_(0) { }

HeaderPropertyPtr PropertyIterator::next()
{
    auto line = getline();
    HeaderPropertyPtr next_prop;

    do {
        next_prop = make_property(line);
    } while (next_prop->type == PropertyType::EMPTY && line != Line(0, 0));

    return next_prop;
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

HeaderPropertyPtr PropertyIterator::make_property(const Line& line)
{
    size_t start;
    if (line.first == 0) {
        start = end_of_prefix(line, HTTP_1_1_PROPERTY);
        if (start == line.first) {
            throw std::runtime_error("Unsupported response protocol");
        }
        return std::make_unique<CodeProperty>(Line(start, line.second), buf_);
    }

    start = end_of_prefix(line, CONTENT_LENGTH_PROPERTY);
    if (start != line.first) {
        return std::make_unique<ContentLengthProperty>(Line(start, line.second),
                                                       buf_);
    }

    start = end_of_prefix(line, TRANSFER_ENCODING_PROPERTY);
    if (start != line.first) {
        throw std::runtime_error("Transfer encoding is not supported");
    }

    return std::make_unique<EmptyProperty>(buf_);
}

size_t PropertyIterator::end_of_prefix(const Line& l, const char* prefix)
{
    return l.first;
}
