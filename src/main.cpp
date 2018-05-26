#include "Application.hh"
#include "Settings.hh"
#include "Error.hh"
#include "Logger.hh"

int main(int argc, char** argv) {
    ArgumentParser parser;
    Application app;
    Logger log;
    try {
        auto&& settings = parser.parse_args(argc, argv);
        app.run(settings);
    } catch (const Error& err) {
        log.write(err.what());
        return 1;
    }

    return 0;
}
