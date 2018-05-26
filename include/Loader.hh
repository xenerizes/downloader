#pragma once

class Loader {
public:
    Loader(ClientPtr client);

    Data download(const Url& url);

private:
    ClientPtr client_;
};
