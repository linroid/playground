//
// Created by Lin Zhang on 12/15/21.
//

#include <sstream>
#include <iostream>
#include "parser.h"

Parser::Parser(const char *path) {
  // TODO: read line by line
  auto input = std::fstream(path, std::fstream::in | std::fstream::binary);
  std::stringstream stream;
  stream << input.rdbuf();
  buffer_ = stream.str();
  input.close();
}

std::vector<std::shared_ptr<Instruction>> Parser::Parse() {
  std::vector<std::shared_ptr<Instruction>> instructions;
  uint16_t address = 0;
  while (HasNext()) {
    ++line_;
    auto token = Peek(2);
    while (token[0] == ' ') {
      Skip(1);
      token = Peek(2);
      if (token.size() < 2) {
        break;
      }
    }
    if (token == "//" || IsLineEnd(token)) {
      // do nothing
    } else if (token[0] == '@') {
      ++address;
      Skip(1);
      token = Peek(1);
      if (isdigit(token[0])) {
        auto numeric = ReadNumeric();
        auto number = (uint16_t) atoi(numeric.c_str());
        instructions.push_back(std::make_shared<AInstruction>(number));
      } else {
        auto symbol_name = ReadSymbolName();
        if (symbol_name.empty()) {
          fputs("Unable to find target symbol for A instruction", stderr);
          abort();
        }
        auto symbol = symbol_table_.Link(symbol_name);
        instructions.push_back(std::make_shared<AInstruction>(symbol));
      }
    } else if (token[0] == '(') {
      Skip(1);
      auto symbol_name = ReadSymbolName();
      // Skip ')'
      Skip(1);
      symbol_table_.Put(symbol_name, address);
    } else {
      ++address;
      std::stringstream buffer;
      std::string dest;
      std::string comp;
      std::string jump;
      while (!token.empty() && token[0] != '\n' && token[0] != '\r' && token[0] != ' ') {
        if (token[0] == '=') {
          dest = buffer.str();
          buffer.str("");
        } else if (token[0] == ';') {
          comp = buffer.str();
          buffer.str("");
        } else {
          buffer << token[0];
        }
        Skip(1);
        token = Peek(1);
      }
      if (comp.empty()) {
        comp = buffer.str();
      } else {
        jump = buffer.str();
      }
      if (comp.empty()) {
        fputs("No comp part found for C instruction", stderr);
        abort();
      }
      instructions.push_back(std::make_shared<CInstruction>(comp, dest, jump));
    }
    NextLine();
  }
  symbol_table_.AssignAddressForVariables();
  return std::move(instructions);
}

bool Parser::HasNext() {
  return cursor_ < buffer_.size() - 1;
}

void Parser::Skip(uint16_t n) {
  cursor_ += n;
}

void Parser::NextLine() {
  bool is_comment = false;
  while (HasNext()) {
    auto ch = Peek(2);
    if (ch[0] == ' ') {
      Skip(1);
      continue;
    } else if (ch[0] == '\n') {
      Skip(1);
      break;
    } else if (ch == "\r\n") {
      Skip(2);
      break;
    } else if (ch == "//") {
      Skip(2);
      is_comment = true;
    } else if (!is_comment) {
      fputs("Unexpected token", stderr);
      abort();
    } else {
      Skip(1);
    }
  }
}

std::string Parser::Peek(uint16_t n) {
  // size_t count = buffer_.str().size();
  // char buffer[1];
  // while (count < n && !input_.eof()) {
  //   input_.read(buffer, 1);
  //
  //   // auto read_count = input_.gcount();
  //   std::cout << buffer[0];
  //   buffer_ << buffer[0];
  //   count += 1;
  // }

  if (buffer_.size() - cursor_ < n) {
    n = buffer_.size() - cursor_;
  }
  return buffer_.substr(cursor_, n);
}

std::string Parser::ReadNumeric() {
  std::stringstream stream;
  auto ch = Peek(1);
  while (isdigit(ch[0])) {
    stream << ch;
    Skip(1);
    ch = Peek(1);
  }
  return stream.str();
}

std::string Parser::ReadSymbolName() {
  std::stringstream stream;
  auto ch = Peek(1);
  while (ch[0] != ' ' && ch[0] != '\r' && ch[0] != '\n' && ch[0] != ')') {
    stream << ch;
    Skip(1);
    ch = Peek(1);
  }
  return stream.str();
}

bool Parser::IsLineEnd(std::string &buffer) {
  return buffer == "\r\n" || buffer[0] == '\n';
}
