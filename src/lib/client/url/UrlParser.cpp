#include "lib/client/url/UrlParser.hh"


Url UrlParser::parse(std::string url_str)
{
    Url url;
    url.path = std::move(url_str);
    return url;
}
