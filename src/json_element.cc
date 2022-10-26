#include "include/json_element.h"

namespace civitasv {
namespace json {
JsonElement::JsonElement(Type type) : type_(type) {
  switch (type) {
    case Type::JSON_OBJECT:
      value_.value_object = new std::map<std::string, JsonElement*>();
      break;
    case Type::JSON_ARRAY:
      value_.value_array = new std::vector<JsonElement*>();
      break;
    case Type::JSON_STRING:
      value_.value_string = new std::string("");
      break;
    case Type::JSON_NUMBER:
      value_.value_number = 0;
      break;
    case Type::JSON_TRUE:
      value_.value_bool = true;
      break;
    case Type::JSON_FALSE:
      value_.value_bool = false;
      break;
    case Type::JSON_NULL:
      break;
    default:
      break;
  }
}

}  // namespace json
}  // namespace civitasv
