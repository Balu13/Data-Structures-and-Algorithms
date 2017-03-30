#include <iostream>
#include <algorithm>
#include <cassert>

int coins[] { 1, 5, 10 };

int get_change(int m)
{
	int numberOfCoins{ 0 };
	return numberOfCoins;
}

void test1()
{
	assert(get_change(2) == 2);
}

void test2()
{
	assert(get_change(28) == 6);
}

void testEdgeCases()
{
}

void testLargeNumbers()
{
}

void testRandomValues()
{
}

void testSuite()
{
	test1();
	test2();
	testEdgeCases();
	testLargeNumbers();
	testRandomValues();
}

int main()
{
	int m{ 0 };
	testSuite();
//	std::cin >> m;
	std::cout << get_change(m) << '\n';
}
