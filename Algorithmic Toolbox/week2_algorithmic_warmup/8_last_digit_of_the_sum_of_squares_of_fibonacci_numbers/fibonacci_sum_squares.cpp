#include <iostream>
#include <vector>

const int kPeriodLength = 60;

int fibonacci_sum_squares(long long n) {
  if (n <= 1) {
    return n;
  }
  long long sum = 0;

  long long previous = 0;
  long long current = 1;

  std::vector<int> last_digits(kPeriodLength);
  last_digits[0] = 0;
  last_digits[1] = 1;
  for (int i = 2; i < kPeriodLength; ++i) {
    long long tmp_previous = previous;
    previous = current;
    current = (tmp_previous + current) % 10;
    last_digits[i] = current;
  }
  // (F(n) * F(n + 1)) % 10
  return (last_digits[n % kPeriodLength] * last_digits[(n + 1) % kPeriodLength]) % 10;
}

int main() {
  long long n = 0;
  std::cin >> n;
  std::cout << fibonacci_sum_squares(n) << std::endl;
}
