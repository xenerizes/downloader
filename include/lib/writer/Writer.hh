#pragma once

#include "lib/Data.hh"

#include <string>


class Writer {
public:
    Writer() noexcept = default;

    void write(const Data& data);
};
