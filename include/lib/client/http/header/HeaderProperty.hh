#pragma once

#include <utility>
#include <memory>

enum class PropertyType {
    EMPTY = 0,
    CODE,
    CONTENT_LENGTH,
    TRANSFER_ENCODING
};

using Line = std::pair<size_t, size_t>;
using HeaderProperty = std::pair<PropertyType, Line>;
