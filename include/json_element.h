#pragma once
#include <iostream>
#include <map>
#include <sstream>
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

    JSON_BOOL,

    JSON_NULL
  };

  union Value {
    JsonObject* value_object;
    JsonArray* value_array;

    std::string* value_string;
    float value_number;

    bool value_bool;
  };

  JsonElement() : JsonElement(Type::JSON_NULL) {}

  JsonElement(Type type) : type_(type) {
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
      case Type::JSON_BOOL:
        value_.value_bool = false;
        break;
      case Type::JSON_NULL:
        break;
      default:
        break;
    }
  };

  JsonElement(JsonObject* object) : type_(Type::JSON_OBJECT) { value(object); }
  JsonElement(JsonArray* array) : type_(Type::JSON_ARRAY) { value(array); }
  JsonElement(std::string* str) : type_(Type::JSON_STRING) { value(str); }
  JsonElement(float number) : type_(Type::JSON_NUMBER) { value(number); }
  JsonElement(bool val) : type_(Type::JSON_BOOL) { value(val); }

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

  Type type() { return type_; }

  void value(JsonObject* value) {
    type_ = Type::JSON_OBJECT;
    value_.value_object = value;
  }
  void value(JsonArray* value) {
    type_ = Type::JSON_ARRAY;
    value_.value_array = value;
  }
  void value(std::string* value) {
    type_ = Type::JSON_STRING;
    value_.value_string = value;
  }
  void value(float value) {
    type_ = Type::JSON_NUMBER;
    value_.value_number = value;
  }
  void value(bool value) {
    type_ = Type::JSON_BOOL;
    value_.value_bool = value;
  }

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
    if (type_ == Type::JSON_BOOL) {
      return value_.value_bool;
    } else {
      Error("Type of JsonElement isn't Boolean!");
    }
  }

  std::string Dumps() {
    std::stringstream ss;
    switch (type_) {
      case Type::JSON_OBJECT:
        ss << *(value_.value_object);
        break;
      case Type::JSON_ARRAY:
        ss << *(value_.value_array);
        break;
      case Type::JSON_STRING:
        ss << '\"' << *(value_.value_string) << '\"';
        break;
      case Type::JSON_NUMBER:
        ss << value_.value_number;
        break;
      case Type::JSON_BOOL:
        ss << (value_.value_bool == true ? "true" : "false");
        break;
      case Type::JSON_NULL:
        ss << "null";
        break;
      default:
        break;
    }
    return ss.str();
  }

  friend std::ostream& operator<<(std::ostream& os, const JsonObject& object) {
    os << "{";
    for (auto iter = object.begin(); iter != object.end(); iter++) {
      os << '\"' << iter->first << '\"' << ": " << iter->second->Dumps();
      if (iter != --object.end()) {
        os << ", ";
      }
    }
    os << "}";
    return os;
  }

  friend std::ostream& operator<<(std::ostream& os, const JsonArray& array) {
    os << "[";
    for (size_t i = 0; i < array.size(); i++) {
      os << array[i]->Dumps();
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