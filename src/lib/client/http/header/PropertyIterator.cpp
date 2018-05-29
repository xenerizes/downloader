#include "lib/client/http/header/PropertyIterator.hh"

#include "lib/client/http/header/Properties.hh"
#include <cstring>


constexpr const char CARRIAGE_RET = '\r';
constexpr const char NEWLINE = '\n';

constexpr const char* HTTP_1_1_PROPERTY = "HTTP/1.1 ";
constexpr const char* CONTENT_LENGTH_PROPERTY = "Content-Length: ";
constexpr const char* TRANSFER_ENCODING_PROPERTY = "Transfer-Encoding: ";

PropertyIterator::PropertyIterator(const Buffer& buf) : buf_(buf), pos_(0) { }

HeaderPropertyPtr PropertyIterator::next()
{
    HeaderPropertyPtr next_prop;
    Line line;

    do {
        line = getline();
        next_prop = make_property(line);
    } while (next_prop->type == PropertyType::EMPTY && line.first != line.second);

    return next_prop;
}

size_t PropertyIterator::raw_pos() { return pos_; }

Line PropertyIterator::getline()
{
    size_t start = pos_;
    for (size_t i = buf_.find(CARRIAGE_RET, pos_); i < BUFFER_SIZE; ) {
        if (buf_.data()[i + 1] == NEWLINE) {
            pos_ = i + 2;
            if (start == i) break;
            return Line(start, i);
        }
    }

    return Line(pos_, pos_);
}

HeaderPropertyPtr PropertyIterator::make_property(const Line& line)
{
    if (line.first == 0) {
        if (!starts_with(line, HTTP_1_1_PROPERTY)) {
            throw std::runtime_error("Unsupported response protocol");
        }
        auto start = line.first + strlen(HTTP_1_1_PROPERTY);
        return std::make_unique<CodeProperty>(Line(start, line.second), buf_);
    }

    if (line.first != line.second) {
        if (starts_with(line, CONTENT_LENGTH_PROPERTY)) {
            auto start = line.first + strlen(CONTENT_LENGTH_PROPERTY);
            return std::make_unique<ContentLengthProperty>(
                Line(start, line.second), buf_);
        }

        if (starts_with(line, TRANSFER_ENCODING_PROPERTY)) {
            throw std::runtime_error("Transfer encoding is not supported");
        }
    }

    return std::make_unique<EmptyProperty>(buf_);
}

bool PropertyIterator::starts_with(const Line& l, const char* prefix)
{
    auto len = strlen(prefix);
    for (size_t i = l.first; i < l.first + len; i++) {
        if (i >= l.second || buf_.data()[i] != prefix[i - l.first]) {
            return false;
        }
    }
    return true;
}
