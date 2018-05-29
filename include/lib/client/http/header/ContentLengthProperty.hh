#pragma once

#include "HeaderProperty.hh"


struct ContentLengthProperty: public HeaderProperty {
    ContentLengthProperty(const Line& line, const Buffer& buf);

    void append(Response& resp) override;
};
