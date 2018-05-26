#include "Application.hh"
#include "Settings.hh"
#include "Loader.hh"
#include "Writer.hh"


void Application::run(const Settings& settings)
{
    Loader loader(settings.client);
    Writer writer(settings.filename);
    auto&& data = loader.download(settings.url);
    writer.write(data);
}

