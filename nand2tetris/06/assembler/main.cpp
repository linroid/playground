#include <iostream>
#include <vector>
#include "code.h"
#include "parser.h"

void process(const std::string &path_str) {
  auto path = canonical(std::filesystem::path(path_str));
  Code code;
  std::cout << "Parsing " << path << std::endl;
  Parser parser(path.c_str());
  auto instructions = parser.Parse();

  auto filename = path.filename().string();
  auto output_path =
      path.parent_path().string() + "/" + filename.substr(0, filename.find_last_of('.')) +
      ".hack";
  std::cout << "Writing to " << output_path << std::endl;
  std::fstream output_file;
  output_file.open(output_path, std::fstream::in | std::fstream::out | std::fstream::trunc);
  int address = 0;
  for (auto &instruction: instructions) {
    auto machine_code = instruction->Compile(code);
    auto source = instruction->Source();
    std::cout << "#" << std::setw(2) << std::setfill('0') << address << " " << machine_code << "\t(" << source << ")"
              << std::endl;
    output_file << machine_code << std::endl;
    address++;
  }
  output_file.flush();
  output_file.close();
}

int main(int argc, const char **argv) {
  if (argc >= 2) {
    process(std::string(*(argv + 1)));
  } else {
    std::string line;
    while (std::cin >> line) {
      process(line);
    }
  }
  return 0;
}
