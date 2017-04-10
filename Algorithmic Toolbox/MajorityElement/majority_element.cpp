#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

using std::vector;
using std::map;

int get_majority_element(vector<int> &a, int left, int right) {
  if (left == right) return -1;
  if (left + 1 == right) return a[left];
  
  map<int, int> sortedCount;
  int retVal = -1;
  std::for_each(a.cbegin(), a.cend(), [&](int val)
  {
	  std::pair<map<int, int>::iterator, bool> element = sortedCount.emplace(val, 1);
	  if (!element.second)
	  {
		  ++((*(element.first)).second);
	  }
	  if (((*(element.first)).second) > a.size()/2)
	  {
		  retVal = (*(element.first)).first;
		  return;
	  }
  });
  return retVal;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  std::cout << (get_majority_element(a, 0, a.size()) != -1) << '\n';
}
