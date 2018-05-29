#include "lib/client/http/header/ContentLengthProperty.hh"


ContentLengthProperty::ContentLengthProperty(const Line& l, const Buffer& buf_)
    : HeaderProperty(PropertyType::CONTENT_LENGTH, l, buf_)
{ }

void ContentLengthProperty::append(Response& resp)
{
    auto length = extract();
    try {
        resp.content_length = std::stoull(length);
    } catch (const std::invalid_argument&) {
        throw std::runtime_error("Error in HTTP response: "
                                     "unsupported content-length");
    } catch (const std::out_of_range&) {
        throw std::runtime_error("Error in HTTP response: "
                                     "content-length is out of range");
    }
}
