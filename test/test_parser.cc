#include <iostream>

#include "include/parser.h"
#include "include/scanner.h"

int main() {
  using namespace civitasv::json;
  auto source = R"(
    {
      "glossary" : {
        "test": true,
        "hello": null,
        "hello2": "miao\nmiao"
      }
    }
  )";

  auto source2 = "[1, 2, 3, 4, 5, \"Hello\"]";

  Scanner scanner(source);
  Parser parser(scanner);

  JsonElement* res = parser.Parse();
  JsonObject* obj = res->AsObject();

  obj->insert({"tes", new JsonElement(20.0f)});

  std::cout << res->dumps()  << '\n';

  delete res;
}