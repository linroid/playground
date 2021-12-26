#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

using std::vector;

struct Segment {
  int start, end;
};

vector<int> optimal_points(vector<Segment> &segments) {
  if (segments.empty()) {
    return vector<int>();
  }
  std::sort(segments.begin(), segments.end(), [](Segment &a, Segment &b) {
    return a.start < b.start;
  });
  vector<int> points;
  int start = segments[0].start;
  int end = segments[0].end;
  for (size_t i = 1; i < segments.size(); ++i) {
    if (segments[i].start <= end) {
      start = std::max(segments[i].start, start);
      end = std::min(segments[i].end, end);
    } else {
      points.push_back(start);
      start = segments[i].start;
      end = segments[i].end;
    }
  }
  points.push_back(start);
  return points;
}

int main() {
  int n;
  std::cin >> n;
  vector<Segment> segments(n);
  for (size_t i = 0; i < segments.size(); ++i) {
    std::cin >> segments[i].start >> segments[i].end;
  }
  vector<int> points = optimal_points(segments);
  std::cout << points.size() << std::endl;
  for (size_t i = 0; i < points.size(); ++i) {
    std::cout << points[i] << " ";
  }
  std::cout << std::endl;
}
