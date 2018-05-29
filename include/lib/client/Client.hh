#pragma once


#include <memory>

struct Url;

class Client {
public:
    virtual void download(const Url& url) = 0;
};

using ClientPtr = std::unique_ptr<Client>;
