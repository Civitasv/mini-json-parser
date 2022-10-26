#pragma once
#include <iostream>
#include <map>
#include <vector>

#include "error.h"

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

  ~JsonElement() {
    if (type_ == Type::JSON_OBJECT) {
      JsonObject* object = value_.value_object;
      for (auto& [key, value] : *object) {
        delete value;
      }
      delete object;
    } else if (type_ == Type::JSON_ARRAY) {
      JsonArray* array = value_.value_array;
      for (auto& item : *array) {
        delete item;
      }
      delete array;
    } else if (type_ == Type::JSON_STRING) {
      std::string* val = value_.value_string;
      delete val;
    }
  }

  void type(Type type) { type_ = type; }

  void value(JsonObject* value) { value_.value_object = value; }
  void value(JsonArray* value) { value_.value_array = value; }
  void value(std::string* value) { value_.value_string = value; }
  void value(float value) { value_.value_number = value; }
  void value(bool value) { value_.value_bool = value; }

  JsonObject* AsObject() {
    if (type_ == Type::JSON_OBJECT) {
      return value_.value_object;
    } else {
      Error("Type of JsonElement isn't JsonObject!");
    }
  }

  JsonArray* AsArray() {
    if (type_ == Type::JSON_ARRAY) {
      return value_.value_array;
    } else {
      Error("Type of JsonElement isn't JsonArray!");
    }
  }

  std::string* AsString() {
    if (type_ == Type::JSON_STRING) {
      return value_.value_string;
    } else {
      Error("Type of JsonElement isn't String!");
    }
  }

  float AsNumber() {
    if (type_ == Type::JSON_NUMBER) {
      return value_.value_number;
    } else {
      Error("Type of JsonElement isn't Number!");
    }
  }

  float AsBoolean() {
    if (type_ == Type::JSON_FALSE || type_ == Type::JSON_TRUE) {
      return value_.value_bool;
    } else {
      Error("Type of JsonElement isn't Boolean!");
    }
  }

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