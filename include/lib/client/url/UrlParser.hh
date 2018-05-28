#pragma once

#include "Url.hh"


class UrlParser {
public:
    UrlParser() noexcept = default;

    Url parse(std::string url);
};
