#include <iostream>
#include <vector>

using std::vector;

vector<int> optimal_summands(int n) {
  vector<int> summands;
  int sum = 0;
  int x = 0;
  while (n > sum) {
    ++x;
    if (n - sum == x || (n - sum > x * 2)) {
      summands.push_back(x);
      sum += x;
    } else {
      summands.push_back(n - sum);
      break;
    }
  }
  //write your code here
  return summands;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> summands = optimal_summands(n);
  std::cout << summands.size() << std::endl;
  for (size_t i = 0; i < summands.size(); ++i) {
    std::cout << summands[i] << ' ';
  }
  std::cout << std::endl;
}
