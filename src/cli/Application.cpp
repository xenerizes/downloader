#include "cli/Application.hh"

#include "cli/Settings.hh"
#include "lib/writer/Writer.hh"


void Application::run(const Settings& settings)
{
    settings.client->download(settings.url);
}
