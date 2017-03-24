#include <iostream>
#include <cassert>
#include <algorithm>

int gcd_naive(int a, int b) {
  int current_gcd = 1;
  for (int d = 2; d <= a && d <= b; d++) {
    if (a % d == 0 && b % d == 0) {
      if (d > current_gcd) {
        current_gcd = d;
      }
    }
  }
  return current_gcd;
}

int gcd_fast(int a, int b)
{
	int currentMultiplier = std::max(a, b);
	int currentDivisor = std::min(a, b);
	int current_gcd;
	while ((current_gcd = currentMultiplier % currentDivisor) != 0)
	{
		currentMultiplier = currentDivisor;
		currentDivisor = current_gcd;
	}

	return currentDivisor;
}

void testSolution()
{
	//assert(gcd_naive(18, 35)==gcd_fast(18, 35));
	//assert(gcd_naive(18, 35)==gcd_fast(18, 35));
	for (int a = 1; a < 35; ++a)
	{
		for (int b = 1; b < 35; ++b)
		{
			assert(gcd_naive(a, b) == gcd_fast(a, b));
		}
	}
}

int main() {
  int a, b;
  std::cin >> a >> b;
  //testSolution();
  //std::cout << gcd_naive(a, b) << std::endl;
  std::cout << gcd_fast(a, b) << std::endl;
  return 0;
}
