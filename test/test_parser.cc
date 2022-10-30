#include <iostream>

#include "include/parser.h"

int main() {
  using namespace civitasv::json;
  auto source = R"(
    {
      "name": "��������ľ",
      "university": "whu",
      "age": 22,
      "gender": "��",
      "isProgrammer": true,
      "skills": ["C++", "JS/TS", "Java"]
    }
  )";

  Scanner scanner(source);
  Parser parser(scanner);

  JsonElement* res = parser.Parse();
  JsonObject* obj = res->AsObject();

  obj->insert({"AddTest", new JsonElement(20.0f)});

  std::cout << res->Dumps()  << '\n';

  delete res;
}