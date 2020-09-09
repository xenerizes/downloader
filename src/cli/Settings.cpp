#include "cli/Settings.hh"

#include "lib/client/url/Url.hh"


Settings::Settings(Url& url_, ClientPtr& cp) noexcept
    : url(std::move(url_))
    , client(std::move(cp))
{ }


Settings ArgumentParser::parse_args(int argc, char** argv)
{
    if (argc > 1) {
        Url url(argv[1]);
        auto&& client_ptr = url.scheme.make_client();

        return Settings(url, client_ptr);
    } else {
        throw std::invalid_argument("Wrong number of arguments");
    }
}
