#include "cli/Application.hh"
#include "cli/Settings.hh"
#include "cli/Logger.hh"
#include "lib/client/socket/Socket.hh"
#include <exception>


int main(int argc, char** argv) {
    ArgumentParser parser;
    Application app;
    Logger log;
    //SocketPtr socket = std::make_shared<Socket>("google.com", "80");
    try {
        auto&& settings = parser.parse_args(argc, argv, nullptr);
        app.run(settings);
    } catch (const std::exception& err) {
        log.error(err.what());
        return 1;
    }

    return 0;
}
