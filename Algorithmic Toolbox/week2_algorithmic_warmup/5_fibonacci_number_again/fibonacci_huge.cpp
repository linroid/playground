#include <iostream>
#include <vector>

long long get_fibonacci_huge(long long n, long long m) {
  if (n <= 1)
    return n;

  long long previous = 0;
  long long current = 1;

  std::vector<int> periods_table;
  periods_table.push_back(0);
  periods_table.push_back(1);
  int period_length = -1;
  for (long long i = 2; i <= n; ++i) {
    long long tmp_previous = previous;
    previous = current;
    current = (tmp_previous + current) % m;
    if (period_length > 0) {
      if (periods_table[i - period_length] != current) {
        period_length = -1;
      } else if (i == period_length * 2 - 1) {
        break;
      }
    } else if (current == periods_table[0]) {
      period_length = i;
    }
    if (i == n) {
      period_length = -1;
    }
    periods_table.push_back(current);
  }
  if (period_length < 0) {
    return periods_table[n];
  }
  return periods_table[n % period_length];
}

int main() {
  long long n, m;
  std::cin >> n >> m;
  std::cout << get_fibonacci_huge(n, m) << std::endl;
}
