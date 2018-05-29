#pragma once

#include "lib/client/http/Response.hh"
#include "lib/buffer/Buffer.hh"

#include <utility>
#include <memory>

enum class PropertyType {
    EMPTY = 0,
    CODE,
    CONTENT_LENGTH
};

using Line = std::pair<size_t, size_t>;

struct HeaderProperty {
    HeaderProperty(PropertyType type_, Line loc_, const Buffer& buf_);

    virtual void append(Response& resp) = 0;
    std::string extract();

    PropertyType type;
    Line location;
    const Buffer& buf;
};

using HeaderPropertyPtr = std::unique_ptr<HeaderProperty>;
