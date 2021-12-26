#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::max;

int compute_min_refills(int dist, int tank, vector<int>& stops) {
    stops.push_back(dist);
    int last_stop = 0;
    int fill_count = 0;
    for (int i = 0; i < stops.size(); ++i) {
      if (i == stops.size() - 1) {
        if (stops[i] - last_stop > tank) {
          return -1;
        }
      } else if (i == stops.size() - 1 || stops[i + 1] - last_stop > tank) {
        if (stops[i] - last_stop > tank) {
          return -1;
        }
        dist -= stops[i] - last_stop;
        last_stop = stops[i];
        ++fill_count;
      }
    }
    return fill_count;
}

int main() {
    int d = 0;
    cin >> d;
    int m = 0;
    cin >> m;
    int n = 0;
    cin >> n;

    vector<int> stops(n);
    for (size_t i = 0; i < n; ++i) {
        cin >> stops.at(i);
    }

    cout << compute_min_refills(d, m, stops) << "\n";

    return 0;
}
