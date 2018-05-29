#include "lib/client/http/header/CodeProperty.hh"

constexpr const char* SUCCESS_CODE = "200 OK";


CodeProperty::CodeProperty(const Line& line, const Buffer& buf_)
    : HeaderProperty(PropertyType::CODE, line, buf_)
{ }

void CodeProperty::append(Response& resp)
{
    resp.code = extract();
    resp.success = resp.code == SUCCESS_CODE;
}
