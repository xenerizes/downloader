#include "lib/client/url/UrlParser.hh"

#include <stdexcept>
#include <cstring>


constexpr const char* DEFAULT_PORT = "80";
constexpr const char* SCHEME_DELIM = "://";
constexpr const char* SLASH_DELIM = "/";
constexpr const char* COLON_DELIM = ":";

bool UrlParser::starts_with(const std::string& prefix) {
    if (url_str_.size() - idx_ < prefix.size()) {
        return false;
    }

    for (size_t i = 0; i < prefix.size(); ++i) {
        if (url_str_[i + idx_] != prefix[i]) {
            return false;
        }
    }

    return true;

}

Scheme UrlParser::extract_scheme()
{
    idx_ = url_str_.find(COLON_DELIM);
    if (idx_ == std::string::npos) {
        throw std::invalid_argument("Input URL is too short");
    }

    auto scheme_str = url_str_.substr(0, idx_);
    return Scheme(scheme_str);
}

std::string UrlParser::extract_hostname() {
    if (!starts_with(SCHEME_DELIM)) {
        throw std::invalid_argument("Bad URL format: unexpected scheme delim");
    }

    size_t hostname_start = idx_ + strlen(SCHEME_DELIM);
    auto hostname_end = url_str_.find(COLON_DELIM, hostname_start);
    if (hostname_end == std::string::npos) {
        hostname_end = url_str_.find(SLASH_DELIM, hostname_start);
    }

    auto result = url_str_.substr(hostname_start, hostname_end - hostname_start);
    if (result == "") {
        throw std::invalid_argument("Bad URL format: empty hostname");
    }

    idx_ = hostname_end == std::string::npos ? url_str_.size() : hostname_end;

    return result;
}

std::string UrlParser::extract_port()
{
    if (idx_ == url_str_.size() or
        starts_with(SLASH_DELIM) or
        !starts_with(COLON_DELIM)) {

        return DEFAULT_PORT;
    }

    auto port_start = idx_ + 1;
    auto port_end = url_str_.find(SLASH_DELIM, port_start);

    idx_ = port_end == std::string::npos ? url_str_.size() : port_end;

    auto result = url_str_.substr(port_start, port_end - port_start);
    if (result == "") {
        throw std::invalid_argument("Bad URL format: unexpected port");
    }

    return result;
}

std::string UrlParser::extract_path()
{
    if (!starts_with(SLASH_DELIM)) {
        return SLASH_DELIM;
    }

    return url_str_.substr(idx_);
}

UrlParser::UrlParser(std::string url_str)
    : url_str_(std::move(url_str))
    , idx_(0)
{ }

Url UrlParser::parse()
{
    return Url { extract_scheme(),
                 extract_hostname(),
                 extract_port(),
                 extract_path() };
}
