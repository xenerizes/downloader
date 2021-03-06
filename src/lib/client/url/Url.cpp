#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include <locale>

#include "lib/client/url/Url.hh"

constexpr const char* DEFAULT_PORT = "80";
constexpr const char* SCHEME_DELIM = "://";
constexpr const char* SLASH_DELIM = "/";
constexpr const char* COLON_DELIM = ":";
constexpr const char* DOT_DELIM = ".";
constexpr const char* HTML_DEFAULT_NAME = "index.html";


bool Url::starts_with(const std::string& prefix) {
    if (url_str_.size() - idx_ < prefix.size()) return false;

    for (size_t i = 0; i < prefix.size(); ++i) {
        if (url_str_[i + idx_] != prefix[i]) return false;
    }

    return true;
}

std::string Url::strip_spaces(std::string str)
{
    size_t idx{0};
    for (; idx < str.size() && std::isspace(str[idx]); ++idx) ;
    if (idx) str.erase(0, idx);
    for (idx = str.size(); idx > 0 && std::isspace(str[idx - 1]); --idx) ;
    if (idx < str.size()) str.erase(idx, str.size());
    return str;
}

Scheme Url::extract_scheme()
{
    idx_ = url_str_.find(SCHEME_DELIM);
    if (idx_ == std::string::npos) {
        idx_ = 0;
        return {};
    }

    auto scheme_str = url_str_.substr(0, idx_);
    idx_ += strlen(SCHEME_DELIM);

    return Scheme(scheme_str);
}

std::string Url::extract_hostname() {
    size_t hostname_start = idx_;
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

std::string Url::extract_port()
{
    if (idx_ == url_str_.size() or starts_with(SLASH_DELIM) or !starts_with(COLON_DELIM)) {
        return DEFAULT_PORT;
    }

    auto port_start = idx_ + 1;
    auto port_end = url_str_.find(SLASH_DELIM, port_start);

    idx_ = port_end == std::string::npos ? url_str_.size() : port_end;

    auto result = url_str_.substr(port_start, port_end - port_start);
    if (result.empty()) {
        throw std::invalid_argument("Bad URL format: unexpected port");
    }

    return result;
}

std::string Url::extract_path()
{
    if (!starts_with(SLASH_DELIM)) return {};

    return url_str_.substr(idx_);
}

std::string Url::extract_filename()
{
    auto delim_pos = url_str_.rfind(SLASH_DELIM);
    auto res = url_str_.substr(++delim_pos);
    if (res.empty() || delim_pos < idx_) return HTML_DEFAULT_NAME;
    return res;
}

Url::Url(std::string url_str)
    : url_str_(strip_spaces(std::move(url_str)))
    , idx_(0)
    , scheme(extract_scheme())
    , hostname(extract_hostname())
    , port(extract_port())
    , path(extract_path())
    , filename(extract_filename())
{ }

bool Url::operator==(const Url& rhs) const
{
    return scheme == rhs.scheme &&
           path == rhs.path &&
           hostname == rhs.hostname &&
           filename == rhs.filename &&
           port == rhs.port;
}
