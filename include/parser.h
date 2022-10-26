#pragma once

#include "scanner.h"

namespace civitasv {
namespace json {
class Parser {
  typedef Scanner::JsonTokenType JsonTokenType;

 public:
  void Parse();

 private:
 private:
  /// @brief Used to scan input file or string.
  Scanner scanner_;
  /// @brief Type of the last read token.
  JsonTokenType token_type_;
};
}  // namespace json
}  // namespace civitasv