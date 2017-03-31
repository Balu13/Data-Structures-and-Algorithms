#include <iostream>
#include <algorithm>
#include <cassert>

int coins[] { 1, 5, 10 };

int get_change_naive(int m)
{
	int numberOfCoins{ 0 };

	while (m >= 10)
	{
		++numberOfCoins;
		m -= 10;
	}
	while (m >= 5)
	{
		++numberOfCoins;
		m -= 5;
	}
	numberOfCoins += m;

	return numberOfCoins;
}

void test1()
{
	assert(get_change_naive(2) == 2);
}

void test2()
{
	assert(get_change_naive(28) == 6);
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
	//testSuite();
	std::cin >> m;
	std::cout << get_change_naive(m) << '\n';
}
