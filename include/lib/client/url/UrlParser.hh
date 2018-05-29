#pragma once

#include "Url.hh"
#include "Scheme.hh"


class UrlParser {
public:
    UrlParser(std::string url_str);

    Url parse();

private:
    std::string url_str_;
    size_t idx_;

    Scheme extract_scheme();
    std::string extract_hostname();
    std::string extract_port();
    std::string extract_path();

    bool starts_with(const std::string& prefix);
};
