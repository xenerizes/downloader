#include "cli/Settings.hh"
#include "lib/client/url/UrlParser.hh"


Settings::Settings(Url& url_, ClientPtr& cp) noexcept
    : url(std::move(url_))
    , client(std::move(cp))
{ }


Settings ArgumentParser::parse_args(int argc, char** argv, SocketPtr socket)
{
    if (argc > 1) {
        UrlParser parser(argv[1]);
        auto&& url = parser.parse();
        auto&& client_ptr = url.scheme.make_client(socket);

        return Settings(url, client_ptr);
    } else {
        throw std::invalid_argument("Wrong number of arguments");
    }
}
