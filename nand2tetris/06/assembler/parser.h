//
// Created by Lin Zhang on 12/15/21.
//

#ifndef ASSEMBLER_PARSER_H
#define ASSEMBLER_PARSER_H

#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include "instruction.h"

class Parser {
public:
  explicit Parser(const char *path);

  std::vector<std::shared_ptr<Instruction>> Parse();

private:
  std::string buffer_;
  SymbolTable symbol_table_;
  uint16_t line_ = 0;
  size_t cursor_ = 0;

  bool HasNext();

  void Skip(uint16_t n);

  void NextLine();

  bool IsLineEnd(std::string &buffer);

  std::string Peek(uint16_t n);

  std::string ReadNumeric();

  std::string ReadSymbolName();
};


#endif //ASSEMBLER_PARSER_H
