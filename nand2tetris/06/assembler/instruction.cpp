//
// Created by Lin Zhang on 12/15/21.
//

#include <sstream>
#include <iomanip>
#include "instruction.h"

std::string AInstruction::Compile(Code &code) {
  std::stringstream stream;
  auto address = std::bitset<16>(symbol_ ? symbol_->address : address_).to_string();
  stream << address;
  return stream.str();
}

std::string AInstruction::Source() {
  std::stringstream stream;
  stream << '@';
  if (symbol_) {
    stream << symbol_->name << "=" << symbol_->address;
  } else {
    stream << address_;
  }
  return stream.str();
}

std::string CInstruction::Compile(Code &code) {
  std::stringstream stream;
  stream << "111"
         << std::setw(7) << std::setfill('0') << code.Comp(comp_)
         << std::setw(3) << std::setfill('0') << code.Dest(dest_)
         << std::setw(3) << std::setfill('0') << code.Jump(jump_);
  return stream.str();
}

std::string CInstruction::Source() {
  std::stringstream stream;
  if (!dest_.empty()) {
    stream << dest_ << "=";
  }
  stream << comp_;
  if (!jump_.empty()) {
    stream << ";" << jump_;
  }
  stream << " | dest=" << dest_ << ", comp=" << comp_ << ", jump=" << jump_;
  return stream.str();
}
