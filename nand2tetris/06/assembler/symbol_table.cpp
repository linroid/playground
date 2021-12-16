//
// Created by Lin Zhang on 12/15/21.
//

#include <iostream>
#include "symbol_table.h"

void SymbolTable::Put(std::string name, uint16_t address) {
  std::cout << "Found symbol: " << name << " -> " << address << std::endl;
  Link(std::move(name))->address = address;
}

std::shared_ptr<Symbol> SymbolTable::Find(std::string &name) {
  for (const auto &symbol: symbols_) {
    if (symbol->name == name) {
      return symbol;
    }
  }
  return nullptr;
}

std::shared_ptr<Symbol> SymbolTable::Link(std::string name) {
  auto symbol = Find(name);
  if (!symbol) {
    symbol = std::make_shared<Symbol>();
    symbol->name = name;
    symbol->address = kNoAddress;
    symbols_.push_back(symbol);
  }
  return symbol;
}

void SymbolTable::AssignAddressForVariables() {
  uint16_t address = 16;
  for (const auto &symbol: symbols_) {
    if (symbol->address == kNoAddress) {
      std::cout << "Assign: " << symbol->name << "=" << address << std::endl;
      symbol->address = address++;
    }
  }
}

SymbolTable::SymbolTable() {
  Put("SCREEN", 16384);
  Put("KBD", 24576);
  Put("SP", 0);
  Put("LCL", 1);
  Put("ARG", 2);
  Put("THIS", 3);
  Put("THAT", 4);
  for (int i = 0; i < 16; ++i) {
    Put("R" + std::to_string(i), i);
  }
}

