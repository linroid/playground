#include <iostream>

long long lcm_naive(int a, int b) {
  for (long l = 1; l <= (long long) a * b; ++l)
    if (l % a == 0 && l % b == 0)
      return l;

  return (long long) a * b;
}

int gcd_fast(int a, int b) {
  while (b != 0) {
    int temp_a = a;
    a = b;
    b = temp_a % b;
  }
  return a;
}

long long lcm_fast(int a, int b) {
  int gcd = gcd_fast(a, b);
  return ((long long) a) * (b / gcd);
}

int main() {
  int a, b;
  std::cin >> a >> b;
  std::cout << lcm_fast(a, b) << std::endl;
  return 0;
}
