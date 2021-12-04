#include <iostream>
#include <vector>
#include <algorithm>

int64_t MaxPairwiseProduct(const std::vector<int>& numbers) {
    int max_product = 0;
    int n = numbers.size();
    
    if (n < 2) return -1;

    int no1 = 0;
    int no2 = 0;

    for (int i = 0; i < n; ++i) {
        if (numbers[i] > no2) {
            if (numbers[i] > no1) {
                no2 = no1;
                no1 = numbers[i];
            } else {
                no2 = numbers[i];
            }
	}
    }

    return (int64_t) no1 * no2;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> numbers[i];
    }

    std::cout << MaxPairwiseProduct(numbers) << "\n";
    return 0;
}
