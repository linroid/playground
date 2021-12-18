#include <iostream>
#include <vector>

const int kPeriodLength = 60;

long long get_fibonacci_partial_sum(long long from, long long to) {

  long long previous = 0;
  long long current = 1;

  std::vector<int> last_digits(kPeriodLength);
  last_digits[0] = 0;
  last_digits[1] = 1;

  long long period_sum = 1;
  for (int i = 2; i < kPeriodLength; ++i) {
    long long tmp_previous = previous;
    previous = current;
    current = (tmp_previous + current) % 10;
    last_digits[i] = current;
    period_sum = (period_sum + current) % 10;
  }
  long long sum = period_sum * ((to - from) % kPeriodLength);
  int start = from % kPeriodLength;
  int end = to % kPeriodLength;
  if (end < start) {
    end += kPeriodLength;
  }
  for (int i = start; i <= end; ++i) {
    sum = (sum + last_digits[i % kPeriodLength]) % 10;
  }
  return sum;
}

int main() {
  long long from, to;
  std::cin >> from >> to;
  std::cout << get_fibonacci_partial_sum(from, to) << std::endl;
}
