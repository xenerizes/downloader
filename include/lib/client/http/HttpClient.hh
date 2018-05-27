#pragma once

#include "lib/client/url/Url.hh"
#include "lib/client/Client.hh"
#include "lib/Data.hh"


class HttpClient: public Client {
public:
    virtual Data download(const Url& url) override;

};
