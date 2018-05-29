#include "lib/client/http/header/EmptyProperty.hh"


EmptyProperty::EmptyProperty(const Buffer& b)
    : HeaderProperty(PropertyType::EMPTY, Line(0, 0), b)
{ }

void EmptyProperty::append(Response& resp) { }
