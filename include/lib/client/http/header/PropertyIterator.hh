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

    bool starts_with(const Line& l, const char* prefix);
};
