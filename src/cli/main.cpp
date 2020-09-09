#include <exception>
#include <iostream>

#include "cli/Application.hh"
#include "cli/Settings.hh"

int main(int argc, char** argv) {
    ArgumentParser parser;
    Application app;
    try {
        auto&& settings = parser.parse_args(argc, argv);
        app.run(settings);
    } catch (const std::exception& err) {
        std::cerr << err.what();
        return 1;
    }

    return 0;
}
