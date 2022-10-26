#include <iostream>

#include "include/parser.h"
#include "include/scanner.h"

int main() {
  using namespace civitasv::json;
  auto source =
      "{"
      "\"glossary\" : {"
      "  \"test\": true,"
      "  \"hello\": 10.2,"
      "  \"hello2\": \"miaomiao\""
      "}"
      "}";

  auto source2 = "[1, 2, 3, 4, 5, \"Hello\"]";

  Scanner scanner(source2);
  Parser parser(scanner);

  JsonElement* res = parser.Parse();
  std::cout << *res;
}