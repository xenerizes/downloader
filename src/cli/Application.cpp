#include "cli/Application.hh"

#include "cli/Settings.hh"
#include "lib/writer/Writer.hh"


void Application::run(const Settings& settings)
{
    Writer writer;
    auto&& data = settings.client->download(settings.url);
    writer.write(data);
}
