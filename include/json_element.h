#pragma once
#include <iostream>
#include <map>
#include <vector>

namespace civitasv {
namespace json {
class JsonElement;
using JsonObject = std::map<std::string, JsonElement*>;
using JsonArray = std::vector<JsonElement*>;

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

  union Value {
    JsonObject* value_object;
    JsonArray* value_array;

    std::string* value_string;
    float value_number;

    bool value_bool;
  };

  JsonElement() : type_(Type::JSON_NULL) {}
  JsonElement(Type type);

  void type(Type type) { type_ = type; }

  void value(JsonObject* value) { value_.value_object = value; }
  void value(JsonArray* value) { value_.value_array = value; }
  void value(std::string* value) { value_.value_string = value; }
  void value(float value) { value_.value_number = value; }
  void value(bool value) { value_.value_bool = value; }

  friend std::ostream& operator<<(std::ostream& os,
                                  const JsonElement& element) {
    switch (element.type_) {
      case Type::JSON_OBJECT:
        os << *(element.value_.value_object);
        break;
      case Type::JSON_ARRAY:
        os << *(element.value_.value_array);
        break;
      case Type::JSON_STRING:
        os << '\"' << *(element.value_.value_string) << '\"';
        break;
      case Type::JSON_NUMBER:
        os << element.value_.value_number;
        break;
      case Type::JSON_TRUE:
      case Type::JSON_FALSE:
        os << (element.value_.value_bool == true ? "true" : "false");
        break;
      case Type::JSON_NULL:
        os << "NULL";
        break;
      default:
        break;
    }
    return os;
  }

  friend std::ostream& operator<<(std::ostream& os, const JsonObject& object) {
    os << "{" << '\n';
    for (auto iter = object.begin(); iter != object.end(); iter++) {
      os << '\"' << iter->first << '\"' << ": " << *iter->second;
      if (iter != --object.end()) {
        os << ", ";
      }
      os << '\n';
    }
    os << "}" << '\n';
    return os;
  }

  friend std::ostream& operator<<(std::ostream& os, const JsonArray& array) {
    os << "[";
    for (size_t i = 0; i < array.size(); i++) {
      os << *array[i];
      if (i != array.size() - 1) {
        os << ", ";
      }
    }
    os << "]";
    return os;
  }

 private:
  Type type_;
  Value value_;
};
}  // namespace json
}  // namespace civitasv