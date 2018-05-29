#include "cli/Settings.hh"

#include "lib/client/url/UrlParser.hh"


Settings ArgumentParser::parse_args(int argc, char** argv)
{
    Settings settings;

    if (argc > 1) {
        UrlParser parser(argv[1]);
        settings.url = parser.parse();
    } else {
        throw std::invalid_argument("Wrong number of arguments");
    }

    settings.client = settings.url.scheme.make_client();

    return settings;
}
