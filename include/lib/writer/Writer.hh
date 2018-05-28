#pragma once

#include "lib/data/Data.hh"

#include <string>


class Writer {
public:
    Writer() noexcept = default;

    void write(const Data& data);
};
