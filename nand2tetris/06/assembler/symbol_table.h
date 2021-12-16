//
// Created by Lin Zhang on 12/15/21.
//

#ifndef ASSEMBLER_SYMBOL_TABLE_H
#define ASSEMBLER_SYMBOL_TABLE_H


#include <string>
#include <map>
#include <vector>

struct Symbol {
  std::string name;
  uint16_t address;
};
const uint16_t kNoAddress = 1 << 15;

class SymbolTable {
public:
  SymbolTable();

  void Put(std::string name, uint16_t address = kNoAddress);

  std::shared_ptr<Symbol> Link(std::string name);

  void AssignAddressForVariables();

private:
  std::vector<std::shared_ptr<Symbol>> symbols_;

  std::shared_ptr<Symbol> Find(std::string &name);
};


#endif //ASSEMBLER_SYMBOL_TABLE_H
