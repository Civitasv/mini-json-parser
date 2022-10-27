#include "include/parser.h"

#include "include/error.h"

namespace civitasv {
namespace json {
using Type = JsonElement::Type;

JsonElement* Parser::Parse() {
  JsonElement* element = new JsonElement();
  JsonTokenType token_type_ = scanner_.Scan();

  if (token_type_ != JsonTokenType::END_OF_SOURCE) {
    switch (token_type_) {
      case JsonTokenType::BEGIN_OBJECT: {
        JsonObject* object = ParseObject();
        element->value(object);
        break;
      }
      case JsonTokenType::BEGIN_ARRAY: {
        JsonArray* array = ParseArray();
        element->value(array);
        break;
      }
      case JsonTokenType::VALUE_STRING: {
        std::string* val = new std::string(scanner_.GetStringValue());
        element->value(val);
        break;
      }
      case JsonTokenType::VALUE_NUMBER: {
        element->value(scanner_.GetNumberValue());
        break;
      }
      case JsonTokenType::LITERAL_TRUE: {
        element->value(true);
        break;
      }
      case JsonTokenType::LITERAL_FALSE: {
        element->value(false);
        break;
      }
      case JsonTokenType::LITERAL_NULL: {
        break;
      }
    }
  }
  return element;
}

JsonObject* Parser::ParseObject() {
  JsonObject* res = new JsonObject();

  JsonTokenType next = scanner_.Scan();
  if (next == JsonTokenType::END_OBJECT) {
    return res;
  }
  scanner_.Rollback();

  while (true) {
    next = scanner_.Scan();
    if (next != JsonTokenType::VALUE_STRING) {
      Error("Key must be string!");
    }
    std::string key = scanner_.GetStringValue();
    next = scanner_.Scan();
    if (next != JsonTokenType::NAME_SEPARATOR) {
      Error("Expected ':' in object!");
    }
    (*res)[key] = Parse();
    next = scanner_.Scan();
    if (next == JsonTokenType::END_OBJECT) {
      break;
    }
    if (next != JsonTokenType::VALUE_SEPARATOR) {
      Error("Expected ',' in object!");
    }
  }

  return res;
}

JsonArray* Parser::ParseArray() {
  JsonArray* res = new JsonArray();
  JsonTokenType next = scanner_.Scan();
  if (next == JsonTokenType::END_ARRAY) {
    return res;
  }
  scanner_.Rollback();

  while (true) {
    res->push_back(Parse());
    next = scanner_.Scan();
    if (next == JsonTokenType::END_ARRAY) {
      break;
    }
    if (next != JsonTokenType::VALUE_SEPARATOR) {
      Error("Expected ',' in array!");
    }
  }

  return res;
}

}  // namespace json
}  // namespace civitasv