#pragma once


struct Settings {
    std::string path_;
};


class ArgumentParser {
public:
    Settings parse_args(int argc, char** argv);
};
