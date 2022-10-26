#pragma once
#include <iostream>
#include <map>
#include <vector>

namespace civitasv {
namespace json {
class JsonElement {
 public:
  enum class Type {
    JSON_OBJECT,
    JSON_ARRAY,

    JSON_STRING,
    JSON_NUMBER,

    JSON_TRUE,
    JSON_FALSE,

    JSON_NULL
  };

  using JsonObject = std::map<std::string, JsonElement*>;
  using JsonArray = std::vector<JsonElement*>;

  JsonElement() : type_(Type::JSON_NULL) {}
  JsonElement(Type type);

 private:
  union Value {
    JsonObject* value_object;
    JsonArray* value_array;

    std::string* value_string;
    float value_number;

    bool value_bool;
  };

  Type type_;
  Value value_;
};
}  // namespace json
}  // namespace civitasv