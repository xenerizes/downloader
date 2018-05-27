#include "cli/Settings.hh"

#include "lib/client/url/UrlParser.hh"
#include "lib/client/http/HttpClient.hh"

#include <exception>
#include <memory>


Settings ArgumentParser::parse_args(int argc, char** argv)
{
    Settings settings;

    switch (argc) {
        case 2:
            UrlParser parser;
            settings.url = parser.parse(argv[1]);
            settings.filename = settings.url.filename;
            break;
        default:
            throw std::invalid_argument("Wrong number of arguments");
    }

    settings.filename = settings.url.filename;
    settings.client = std::make_unique<HttpClient>();

    return settings;
}
