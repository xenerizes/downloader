#pragma once

#include "HeaderProperty.hh"

class PropertyIterator {
public:
    PropertyIterator(const Buffer& buf);

    HeaderPropertyPtr next();
    size_t raw_pos();

private:
    const Buffer& buf_;
    size_t pos_;

    Line getline();
    HeaderPropertyPtr make_property(const Line& line);

    size_t end_of_prefix(const Line& l, const char* prefix);
};
