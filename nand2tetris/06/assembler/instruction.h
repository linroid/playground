//
// Created by Lin Zhang on 12/15/21.
//
#include <cstdint>
#include <string>
#include <utility>
#include "code.h"
#include "symbol_table.h"

#ifndef ASSEMBLER_INSTRUCTION_H
#define ASSEMBLER_INSTRUCTION_H

class Instruction {
public:
  virtual std::string Compile(Code &code) = 0;

  virtual std::string Source() = 0;
};

class AInstruction : public Instruction {
public:
  explicit AInstruction(std::shared_ptr<Symbol> symbol)
      : Instruction(), symbol_(std::move(symbol)), address_(kNoAddress) {}

  explicit AInstruction(uint16_t address) : Instruction(), address_(address) {}

  std::string Source() override;

private:
  std::shared_ptr<Symbol> symbol_;
  uint16_t address_;

  std::string Compile(Code &code) override;
};

class CInstruction : public Instruction {
public:
  CInstruction(std::string comp,
               std::string dest,
               std::string jump)
      : comp_(std::move(comp)),
        dest_(std::move(dest)),
        jump_(std::move(jump)) {
  }

  std::string Compile(Code &code) override;

  std::string Source() override;


private:
  std::string comp_;
  std::string dest_;
  std::string jump_;
};


#endif //ASSEMBLER_INSTRUCTION_H
