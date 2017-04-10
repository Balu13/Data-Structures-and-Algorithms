#include <iostream>
#include <cassert>
#include <vector>

using std::vector;

int binary_search(const vector<int> &a, int x) {
	int left = 0, right = (int)a.size() - 1;

	while (right >= left)
	{
		int tryPos = left + (right - left + 1) / 2;
		//std::cout << "left: " << left << "  right: " << right << "  trying: " << tryPos << "\n";
		if (a[tryPos] == x)
		{
			return tryPos;
		}
		if (a[tryPos] > x)
		{
			right = tryPos - 1;
		}
		else {
			left = tryPos + 1;
		}
	}
	return -1;
}

int linear_search(const vector<int> &a, int x) {
  for (size_t i = 0; i < a.size(); ++i) {
    if (a[i] == x) return i;
  }
  return -1;
}

void testSolution()
{
	vector<int> a(10);
	vector<int> b(12);
	for (size_t i = 0; i < a.size(); i++)
	{
		a[i] = i + 2;
	}
	for (int i = 0; i < b.size(); ++i)
	{
		b[i] = i + 1;
	}
	for (int i = 0; i < b.size(); ++i)
	{
		std::cout << "search for " << b[i] << '\n';
		std::cout << "result for " << b[i] << ": " << binary_search(a, b[i]) << '\n';
	}
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  int m;
  std::cin >> m;
  vector<int> b(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> b[i];
  }
  //testSolution();
  for (int i = 0; i < m; ++i) {
    //replace with the call to binary_search when implemented
    //std::cout << linear_search(a, b[i]) << ' ';
	  std::cout << binary_search(a, b[i]) << ' ';
  }
}
