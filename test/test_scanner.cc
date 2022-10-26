#include <iostream>

#include "include/scanner.h"

int main() {
  using namespace civitasv::json;
  auto source = R"(
      {
      "glossary" : {
        "test": true,
        "hello": null,
        "hello2": "miao\"miao"
      }
      }
  )";

  auto source2 = "[1, 2, 3, 4, 5, \"Hello\"]";

  Scanner scanner(source2);
  Scanner::JsonTokenType type;
  while ((type = scanner.Scan()) != Scanner::JsonTokenType::END_OF_SOURCE) {
    std::cout << "Type: " << type;
    if (type == Scanner::JsonTokenType::VALUE_NUMBER) {
      std::cout << " Value: " << scanner.GetNumberValue();
    } else if (type == Scanner::JsonTokenType::VALUE_STRING) {
      std::cout << " Value: " << scanner.GetStringValue();
    }
    std::cout << '\n';
  }
}