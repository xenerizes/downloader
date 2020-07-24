#include "cli/Application.hh"
#include "cli/Settings.hh"
#include "cli/Logger.hh"
#include "lib/client/socket/Socket.hh"
#include <exception>

int main(int argc, char **argv)
{
    ArgumentParser parser;
    Application app;
    Logger log;
    
    try
    {
        auto &&url = parser.parse_args(argc, argv, nullptr);
        SocketPtr socket = std::make_shared<Socket>(url.hostname, url.port);
        auto &&client_ptr = url.scheme.make_client(socket);
        Settings settings(url, client_ptr);
        app.run(settings);
    }
    catch (const std::exception &err)
    {
        log.error(err.what());
        return 1;
    }

    return 0;
}
