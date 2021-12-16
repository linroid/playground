//
// Created by Lin Zhang on 12/15/21.
//

#ifndef ASSEMBLER_CODE_H
#define ASSEMBLER_CODE_H

#include <cstdint>
#include <string>
#include <map>

class Code {
public:
  Code();

  std::string Comp(std::string &source);
  std::string Dest(std::string &source);
  std::string Jump(std::string &source);

private:
  std::map<std::string, std::string> comp_;
  std::map<std::string, std::string> jump_;
  std::map<std::string, std::string> dest_;
};


#endif //ASSEMBLER_CODE_H
