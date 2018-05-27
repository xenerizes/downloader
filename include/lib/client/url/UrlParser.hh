#pragma once

#include "Url.hh"


class UrlParser {
public:
    UrlParser() noexcept = default;

    Url parse(const char* url);
};
