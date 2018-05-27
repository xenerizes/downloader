#include "application/Application.hh"
#include "application/Settings.hh"
#include "client/Loader.hh"
#include "writer/Writer.hh"


void Application::run(const Settings& settings)
{
    Loader loader(settings.client);
    Writer writer(settings.filename);
    auto&& data = loader.download(settings.url);
    writer.write(data);
}

