#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

using std::vector;

struct Segment {
  int start, end;
};

vector<int> optimal_points(vector<Segment> &segments) {
  vector<int> points;
  vector<Segment> covered;

  size_t curSegment{ 0 };
  for (size_t i = 1; i < segments.size(); ++i) {
	  if (segments[i].end < segments[curSegment].end) {
		  if (segments[i].end >= segments[curSegment].start) {
			  covered.push_back(segments[curSegment]);
		  }
	  }
  }
  covered.push_back(segments[0]);

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
  std::cout << points.size() << "\n";
  for (size_t i = 0; i < points.size(); ++i) {
    std::cout << points[i] << " ";
  }
}
