#include "include/scanner.h"

#include <stdexcept>

namespace civitasv {
namespace json {
bool Scanner::IsAtEnd() { return current_ >= source_.size(); }

bool Scanner::IsDigit(char c) { return c >= '0' && c <= '9'; }

char Scanner::Peek() {
  if (IsAtEnd()) return '\0';
  return source_[current_];
}

char Scanner::PeekNext() {
  if (current_ + 1 >= source_.size()) return '\0';
  return source_[current_ + 1];
}

char Scanner::Advance() { return source_[current_++]; }

Scanner::JsonTokenType Scanner::Scan() {
  if (IsAtEnd()) {
    return JsonTokenType::END_OF_SOURCE;
  }

  char c = Advance();

  switch (c) {
    case '[':
      return JsonTokenType::BEGIN_ARRAY;
    case ']':
      return JsonTokenType::END_ARRAY;
    case '{':
      return JsonTokenType::BEGIN_OBJECT;
    case '}':
      return JsonTokenType::END_OBJECT;
    case ':':
      return JsonTokenType::NAME_SEPARATOR;
    case ',':
      return JsonTokenType::VALUE_SEPARATOR;
    case 't':
      ScanTrue();
      return JsonTokenType::LITERAL_TRUE;
    case 'f':
      ScanFalse();
      return JsonTokenType::LITERAL_FALSE;
    case 'n':
      ScanNull();
      return JsonTokenType::LITERAL_NULL;
    case '-':
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      ScanNumber();
      return JsonTokenType::VALUE_NUMBER;
    case '\"':
      ScanString();
      return JsonTokenType::VALUE_STRING;
    case ' ':
    case '\r':
    case '\n':
    case '\t':
      return JsonTokenType::WHITESPACE;
    default:
      // error
      return JsonTokenType::ERROR;
  }
}

void Scanner::ScanTrue() {
  if (source_.compare(current_, 3, "rue") == 0) {
    current_ += 3;
  } else {
    Error("Scan `true` error");
  }
}

void Scanner::ScanFalse() {
  if (source_.compare(current_, 4, "alse") == 0) {
    current_ += 4;
  } else {
    Error("Scan `false` error");
  }
}

void Scanner::ScanNull() {
  if (source_.compare(current_, 3, "ull") == 0) {
    current_ += 3;
  } else {
    Error("Scan `null` error");
  }
}

void Scanner::ScanNumber() {
  size_t pos = current_ - 1;
  if (Peek() == '-') {
    Advance();
  }

  while (IsDigit(Peek())) {
    Advance();
  }

  // fractional part
  if (Peek() == '.' && IsDigit(PeekNext())) {
    Advance();
    while (IsDigit(Peek())) {
      Advance();
    }
  }

  value_number_ = std::atof(source_.substr(pos, current_ - pos).c_str());
}

void Scanner::ScanString() {
  size_t pos = current_ - 1;

  while (Peek() != '\"' && !IsAtEnd()) {
    Advance();
  }
  if (IsAtEnd()) {
    Error("invalid string: missing closing quote");
  }
  Advance();

  value_string_ = source_.substr(pos, current_ - pos);
}

void Scanner::Error(const char* message) { throw std::logic_error(message); }

}  // namespace json
}  // namespace civitasv