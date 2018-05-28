#include "lib/client/url/UrlParser.hh"

#include <stdexcept>
#include <cstring>


constexpr const char* SCHEME_DELIM = "://";
constexpr const char HOSTNAME_DELIM = '/';

namespace util {

    bool starts_with(const std::string& str, const std::string& prefix) {
        if (str.size() < prefix.size()) {
            return false;
        }

        for (size_t i = 0; i < prefix.size(); ++i) {
            if (str[i] != prefix[i]) {
                return false;
            }
        }

        return true;
    }

    std::string extract_hostname(const std::string& str, std::string scheme) {
        if (str.size() < scheme.size()) {
            throw std::invalid_argument("Input URL is too short");
        }

        scheme += SCHEME_DELIM;
        if (!starts_with(str, scheme)) {
            throw std::invalid_argument("Unsupported protocol");
        }

        if (str.size() == scheme.size()) {
            throw std::invalid_argument("Empty hostname");
        }

        size_t hostname_start = scheme.size();
        auto hostname_end = str.find(HOSTNAME_DELIM, hostname_start);

        return str.substr(hostname_start, hostname_end - hostname_start);
    }
}


Url UrlParser::parse(std::string url_str)
{
    auto&& hostname = util::extract_hostname(url_str, "http");
    return Url { std::move(url_str),
                 hostname,
                 80 };
}
