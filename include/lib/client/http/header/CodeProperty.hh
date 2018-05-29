#pragma once

#include <lib/buffer/Buffer.hh>
#include "HeaderProperty.hh"


struct CodeProperty: public HeaderProperty {
    CodeProperty(const Line& line, const Buffer& buf);

    void append(Response& resp) override;
};
