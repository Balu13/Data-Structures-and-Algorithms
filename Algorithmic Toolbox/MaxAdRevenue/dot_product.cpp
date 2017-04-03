#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

using std::vector;
using std::set;

long long max_dot_product(set<int> a, set<int> b) {
  // write your code here
  long long result = 0;
  //for (size_t i = 0; i < a.size(); i++) {
  //  result += ((long long) a[i]) * b[i];
  //}
  set<int>::const_iterator ita, itb;
  for (ita = a.cbegin(), itb = b.cbegin(); ita != a.cend(); ita++, itb++)
  {
	  result += ((long long)*ita) * (*itb);
  }
  return result;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<int> a(n), b(n);
  std::set<int> sa, sb;
  for (size_t i = 0; i < n; i++) {
    std::cin >> a[i];
	sa.insert(a[i]);
  }
  for (size_t i = 0; i < n; i++) {
    std::cin >> b[i];
	sb.insert(b[i]);
  }
  std::cout << max_dot_product(sa, sb) << std::endl;
}