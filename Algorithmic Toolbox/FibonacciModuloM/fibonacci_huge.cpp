#include <iostream>
#include <cassert>
#include <vector>

long long get_fibonacci_modulo_naive(long long n, long long m) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % m;
}

unsigned long long get_fibonacci_modulo_fast(unsigned long long n, unsigned long long m)
{
	if (n<2)
	{
		return n;
	}

	unsigned long long m1{ 0 };
	unsigned long long m2{ 1 };
	for (unsigned long long i = 2; i <= n; ++i)
	{
		unsigned long long tmp = (m1 + m2) % m;
		m1 = m2;
		m2 = tmp;
	}

	return m2;
}

void testSolution(unsigned long long n, unsigned long long m)
{
	//assert(get_fibonacci_modulo_naive(1, 239) == get_fibonacci_modulo_fast(1, 239));
	std::cout << std::endl;
	for (unsigned long long b = 2; b < m; ++b)
	//for (unsigned long long b = 100; b < 101; ++b)
		{
		std::cout << "Mod(" << b << "): ";
		for (unsigned long long a = 0; a < n; ++a)
		{
			std::cout << a << ":" << get_fibonacci_modulo_fast(a, b) << " ";
		}
		std::cout << std::endl;
	}
}

int main() {
	unsigned long long n, m;
    std::cin >> n >> m;
	//testSolution(n, m);
	//   std::cout << get_fibonacci_huge_naive(n, m) << '\n';
	std::cout << get_fibonacci_modulo_fast(n, m) << '\n';
}
