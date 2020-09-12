#pragma once


#include <memory>

class Url;

class Client {
public:
    virtual void download(const Url& url) = 0;
};

using ClientPtr = std::unique_ptr<Client>;
