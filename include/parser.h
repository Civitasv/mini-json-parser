#pragma once

#include "include/json_element.h"
#include "scanner.h"

namespace civitasv {
namespace json {
class Parser {
  using JsonTokenType = Scanner::JsonTokenType;

 public:
  JsonElement* Parse();

  Parser(Scanner scanner) : scanner_(scanner) {}
 private:
  JsonObject* ParseObject();
  JsonArray* ParseArray();

 private:
  /// @brief Used to scan input file or string.
  Scanner scanner_;
};
}  // namespace json
}  // namespace civitasv