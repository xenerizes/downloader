#pragma once

#include "lib/buffer/Buffer.hh"
#include "HeaderProperty.hh"

class PropertyIterator {
public:
    PropertyIterator(const Buffer& buf);

    HeaderProperty next();
    size_t raw_pos();

private:
    const Buffer& buf_;
    size_t pos_;

    Line getline();
    HeaderProperty make_property(const Line& line);
};
