#pragma once

#include <memory>

class Client {
public:
    virtual Data download(const Url& url) = 0;
};

using ClientPtr = std::unique_ptr<Client>;
