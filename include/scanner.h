#pragma once
#include <iostream>
#include <string>

namespace civitasv {
namespace json {
class Scanner {
 public:
  Scanner(std::string source) : source_(source), current_(0) {}

  enum class JsonTokenType {
    /// @brief [
    BEGIN_ARRAY,
    /// @brief ]
    END_ARRAY,
    /// @brief {
    BEGIN_OBJECT,
    /// @brief }
    END_OBJECT,

    /// @brief `:`
    NAME_SEPARATOR,
    /// @brief `,`
    VALUE_SEPARATOR,

    /// @brief number, include unsigned integer, signed integer, floating point
    /// number
    VALUE_NUMBER,
    /// @brief string
    VALUE_STRING,

    /// @brief `true`
    LITERAL_TRUE,
    /// @brief `false`
    LITERAL_FALSE,
    /// @brief `null`
    LITERAL_NULL,

    /// @brief End of source
    END_OF_SOURCE
  };

  friend std::ostream& operator<<(std::ostream& os, const JsonTokenType& type) {
    switch (type) {
      case JsonTokenType::BEGIN_ARRAY:
        os << "[";
        break;
      case JsonTokenType::END_ARRAY:
        os << "]";
        break;
      case JsonTokenType::BEGIN_OBJECT:
        os << "{";
        break;
      case JsonTokenType::END_OBJECT:
        os << "}";
        break;
      case JsonTokenType::NAME_SEPARATOR:
        os << ":";
        break;
      case JsonTokenType::VALUE_SEPARATOR:
        os << ",";
        break;
      case JsonTokenType::VALUE_NUMBER:
        os << "number";
        break;
      case JsonTokenType::VALUE_STRING:
        os << "string";
        break;
      case JsonTokenType::LITERAL_TRUE:
        os << "true";
        break;
      case JsonTokenType::LITERAL_FALSE:
        os << "false";
        break;
      case JsonTokenType::LITERAL_NULL:
        os << "null";
        break;
      case JsonTokenType::END_OF_SOURCE:
        os << "EOF";
        break;
      default:
        break;
    }
    return os;
  }

  JsonTokenType Scan();
  void Rollback();

  float GetNumberValue() { return value_number_; };
  std::string GetStringValue() { return value_string_; };

 private:
  char Advance();
  char Peek();
  char PeekNext();
  bool IsAtEnd();
  bool IsDigit(char c);

  void ScanTrue();
  void ScanFalse();
  void ScanNull();
  void ScanString();
  void ScanNumber();

 private:
  std::string source_;  ///< json source string
  size_t prev_pos_;     ///< previous pos of processing character
  size_t current_;      ///< current pos of processing character
  size_t line_;         ///< current line

  float value_number_;        ///< number value
  std::string value_string_;  ///< string value
};
}  // namespace json
}  // namespace civitasv