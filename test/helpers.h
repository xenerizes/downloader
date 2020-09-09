#pragma once

#include <string>
#include <fstream>

namespace test {
namespace helpers {

bool file_equals(const std::string& str, const std::string& filename);
bool file_equals(const char* lhs_filename, const char* rhs_filename);

}
} // ns test
