#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

string largest_number(vector<string> &numbers) {
  std::stringstream stream;
  std::sort(numbers.begin(), numbers.end(), [](string &a, string &b) {
    std::cout << "a=" << a<<", b=" << b<< std::endl;
    for (int i = 0; i < a.size() && i < b.size(); ++i) {
      if (a[i] != b[i]) {
        return a[i] > b[i];
      }
    }
    if (a.size() > b.size()) {
      return a[b.size()] > b[0];
    } else {
      return a[0] > b[a.size()];
    }
  });
  for (size_t i = 0; i < numbers.size(); i++) {
    stream << numbers[i];
  }
  return stream.str();
}

int main() {
  int n;
  std::cin >> n;
  vector<string> numbers(n);
  for (size_t i = 0; i < numbers.size(); i++) {
    std::cin >> numbers[i];
  }
  std::cout << largest_number(numbers) << std::endl;
}
