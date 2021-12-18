#include <iostream>
#include <vector>

const int kPeriodLength = 60;

int fibonacci_sum(long long n) {
  if (n <= 1)
    return n;

  long long previous = 0;
  long long current = 1;

  std::vector<int> last_digits(kPeriodLength);
  last_digits[0] = 0;
  last_digits[1] = 1;
  long long sum = 1;
  for (int i = 2; i < kPeriodLength; ++i) {
    long long tmp_previous = previous;
    previous = current;
    current = (tmp_previous + current) % 10;
    last_digits[i] = current;
    sum = (sum + current) % 10;
  }
  sum = (sum * (n / kPeriodLength)) % 10;
  for (int i = 0; i <= n % kPeriodLength; ++i) {
    sum = (sum + last_digits[i]) % 10;
  }
  return sum;
}

int main() {
  long long n = 0;
  std::cin >> n;
  std::cout << fibonacci_sum(n) << std::endl;
}
