//
// Created by Lin Zhang on 12/15/21.
//

#include "code.h"

Code::Code() {
  // dest
  dest_["M"] = "001";
  dest_["D"] = "010";
  dest_["MD"] = "011";
  dest_["A"] = "100";
  dest_["AM"] = "101";
  dest_["AD"] = "110";
  dest_["AMD"] = "111";

  // comp
  comp_["0"]   = "0101010";
  comp_["1"]   = "0111111";
  comp_["-1"]  = "0111010";
  comp_["D"]   = "0001100";
  comp_["A"]   = "0110000";
  comp_["M"]   = "1110000";
  comp_["!D"]  = "0001101";
  comp_["!A"]  = "0110001";
  comp_["!M"]  = "1110001";
  comp_["-D"]  = "0001111";
  comp_["-A"]  = "0110011";
  comp_["-M"]  = "1110011";
  comp_["D+1"] = "0011111";
  comp_["A+1"] = "0110111";
  comp_["M+1"] = "1110111";
  comp_["D-1"] = "0001110";
  comp_["A-1"] = "0110010";
  comp_["M-1"] = "1110010";
  comp_["D+A"] = "0000010";
  comp_["D+M"] = "1000010";
  comp_["D-A"] = "0010011";
  comp_["D-M"] = "1010011";
  comp_["A-D"] = "0000111";
  comp_["M-D"] = "1000111";
  comp_["D&A"] = "0000000";
  comp_["D&M"] = "1000000";
  comp_["D|A"] = "0010101";
  comp_["D|M"] = "1010101";

  // jump
  jump_["JGT"] = "001";
  jump_["JEQ"] = "010";
  jump_["JGE"] = "011";
  jump_["JLT"] = "100";
  jump_["JNE"] = "101";
  jump_["JLE"] = "110";
  jump_["JMP"] = "111";
}

std::string Code::Jump(std::string &source) {
  if (source.empty()) {
    return "";
  }
  if (jump_.find(source) != jump_.end()) {
    return jump_[source];
  }
  fputs(("Couldn't recognize jump " + source).c_str(), stderr);
  abort();
}

std::string Code::Comp(std::string &source) {
  if (source.empty()) {
    return "";
  }
  if (comp_.find(source) != comp_.end()) {
    return comp_[source];
  }
  fputs(("Couldn't recognize comp: " + source).c_str(), stderr);
  abort();
}

std::string Code::Dest(std::string &source) {
  if (source.empty()) {
    return "";
  }
  if (dest_.find(source) != dest_.end()) {
    return dest_[source];
  }
  fputs(("Couldn't recognize dest " + source).c_str(), stderr);
  abort();
}
