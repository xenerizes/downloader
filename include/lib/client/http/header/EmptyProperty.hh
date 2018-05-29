#pragma once

#include "HeaderProperty.hh"


struct EmptyProperty: public HeaderProperty {
    EmptyProperty(const Buffer& b);

    void append(Response& resp) override;
};
