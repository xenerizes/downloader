#include "helpers.h"

bool test::helpers::file_equals(const std::string& str, const std::string& filename)
{
    std::ifstream f(filename);
    if (!f.is_open()) {
        throw std::runtime_error("Error opening file " + filename);
    }
    char rhs;
    for (auto& lhs: str) {
        f.get(rhs);
        if (f.fail()) return false;
        if (lhs != rhs) return false;
    }
    f.get(rhs);
    return f.eof();
}

bool test::helpers::file_equals(const char* lhs_filename, const char* rhs_filename)
{
    std::ifstream lhs_stream(lhs_filename);
    std::ifstream rhs_stream(rhs_filename);
    if (!lhs_stream.is_open() || !rhs_stream.is_open()) return false;
    char lhs, rhs;
    while (!lhs_stream.eof() || !rhs_stream.eof()) {
        lhs_stream.get(lhs);
        rhs_stream.get(rhs);
        if (lhs_stream.fail() && rhs_stream.fail()) return true;
        if (lhs_stream.fail() || rhs_stream.fail()) return false;
        if (rhs != lhs) return false;
    }
    return true;
}
