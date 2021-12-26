#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

struct Item {
  int weight;
  int value;
  double unit; // value per weight
};

double get_optimal_value(int capacity, vector<int> weights, vector<int> values) {
  double value = 0.0;

  // write your code here
  vector<Item> items;
  for (int i = 0; i < weights.size(); ++i) {
    items.push_back(Item {
      .weight = weights[i],
      .value = values[i],
      .unit = ((double) values[i]) / weights[i]
    });
  }
  std::sort(items.begin(), items.end(), [](Item &a, Item &b) {
    return a.unit > b.unit;
  });

  for (int i = 0; i < weights.size() && capacity > 0; ++i) {
    int w = std::min(capacity, items[i].weight);
    capacity -= w;
    value +=  w * items[i].unit;
  }

  return value;
}

int main() {
  int n;
  int capacity;
  std::cin >> n >> capacity;
  vector<int> values(n);
  vector<int> weights(n);
  for (int i = 0; i < n; i++) {
    std::cin >> values[i] >> weights[i];
  }

  double optimal_value = get_optimal_value(capacity, weights, values);

  std::cout.precision(10);
  std::cout << optimal_value << std::endl;
  return 0;
}
