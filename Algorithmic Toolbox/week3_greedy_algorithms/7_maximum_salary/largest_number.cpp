#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>

using std::vector;
using std::string;

string largest_number(vector<string> &numbers) {
  std::stringstream stream;
  std::sort(numbers.begin(), numbers.end(), [](string &a, string &b) {
    return a + b > b + a;
  });
  for (auto &number: numbers) {
    stream << number;
  }
  return stream.str();
}

int main() {
  int n;
  std::cin >> n;
  vector<string> numbers(n);
  for (auto &number: numbers) {
    std::cin >> number;
  }
  std::cout << largest_number(numbers) << std::endl;
}