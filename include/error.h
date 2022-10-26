#pragma once
#include <stdexcept>

namespace civitasv {
namespace json {
inline void Error(const char* message) { throw std::logic_error(message); }
}  // namespace json
}  // namespace civitasv