#pragma once

#include <array>
#include <memory>

constexpr size_t BUFFER_SIZE = 1024;

using Buffer = std::array<char, BUFFER_SIZE + 1>;
