#pragma once

#include <iostream>
#include <string>

#include "types.hpp"

namespace Hash {
class Token {
 public:
  Token(enum Types, std::string, int, int);
  Token(enum Types);
  Token();
  ~Token();
  friend std::ostream& operator<<(std::ostream&, const class Token&);
  static std::string getTypeof(enum Types);
  enum Types getType();
  void setType(enum Types);
  std::string getContent();
  void setContent(std::string);
  int getStart();
  void setStart(int);
  int getEnd();
  void setEnd(int);

 private:
  enum Types type;
  std::string content;
  int start;
  int end;
};
}  // namespace Hash
