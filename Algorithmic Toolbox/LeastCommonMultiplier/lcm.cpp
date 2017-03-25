#include <iostream>
#include <algorithm>
#include <cassert>

long long lcm_naive(int a, int b) {
  for (long l = 1; l <= (long long) a * b; ++l)
    if (l % a == 0 && l % b == 0)
      return l;

  return (long long) a * b;
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

unsigned long long lcm_fast(int a, int b)
{
	int gcd = gcd_fast(a, b);
	return  ((long long)a * b) / gcd;
}

void test_solution(int range)
{
	for (int a = 1; a < range; ++a)
	{
		for (int b = 1; b < range; ++b)
		{
			assert(lcm_fast(a, b) == lcm_fast(a, b));
		}
	}
}

int main() {
  int a, b;
  //std::cin >>a;
  //test_solution(a);
  std::cin >> a >> b;
  //std::cout << lcm_naive(a, b) << std::endl;
  std::cout << lcm_fast(a, b) << std::endl;
  return 0;
}
