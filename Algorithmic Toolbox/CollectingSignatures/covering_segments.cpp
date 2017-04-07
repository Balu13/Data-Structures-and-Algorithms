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

	if (segments.empty())
	{
		return points;
	}

	std::sort(segments.begin(), segments.end(), [](Segment s1, Segment s2) { return s1.end < s2.end; });

	int curSegment{ 0 };
	points.push_back(segments[0].end);
	for (size_t i = 1; i < segments.size(); ++i)
	{
		if (segments[i].start > segments[curSegment].end && segments[i].end > segments[curSegment].end)
		{
			points.push_back(segments[i].end);
			curSegment = i;
		}
	}

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
