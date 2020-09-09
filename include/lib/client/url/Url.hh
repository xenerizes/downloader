#pragma once

#include "Url.hh"
#include "Scheme.hh"


class Url {
private:
    std::string url_str_; // to be initialized first
    size_t idx_;

public:
    explicit Url(std::string url_str);
    Url(const Url&);
    ~Url() = default;

    bool operator==(const Url&rhs) const;

    Scheme scheme;
    std::string hostname;
    std::string port;
    std::string path;
    std::string filename;

private:
    Scheme extract_scheme();
    std::string extract_hostname();
    std::string extract_port();
    std::string extract_path();
    std::string extract_filename();

    bool starts_with(const std::string& prefix);
};
