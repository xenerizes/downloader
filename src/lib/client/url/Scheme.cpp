#include "lib/client/url/Scheme.hh"
#include "lib/client/http/HttpClient.hh"

constexpr const char *VALID_SCHEME_HTTP = "http";

Scheme::Scheme(const std::string scheme_str)
{
    if (scheme_str != VALID_SCHEME_HTTP)
    {
        throw std::invalid_argument("Unsupported protocol");
    }
}

ClientPtr Scheme::make_client(SocketPtr socket)
{
    if (!socket)
        return std::make_unique<HttpClient>();
    else
        return std::make_unique<HttpClient>(socket);
}
