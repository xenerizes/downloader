#include "lib/client/url/Scheme.hh"

#include "lib/client/http/HttpClient.hh"

constexpr const char* VALID_SCHEME_HTTP = "http";

Scheme::Scheme(std::string scheme_str)
    : scheme(std::move(scheme_str))
{
    if (scheme != VALID_SCHEME_HTTP) {
        throw std::invalid_argument("Unsupported protocol");
    }
}

bool Scheme::operator==(const Scheme& oth) const
{
    return scheme == oth.scheme;
}

ClientPtr Scheme::make_client()
{
    return std::make_unique<HttpClient>();
}
