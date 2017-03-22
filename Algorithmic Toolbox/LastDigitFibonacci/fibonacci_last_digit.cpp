#include <iostream>
#include <cassert>

int get_fibonacci_last_digit_naive(int n) {
    if (n <= 1)
        return n;

    int previous = 0;
    int current  = 1;

    for (int i = 0; i < n - 1; ++i) {
        int tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % 10;
}

int getFibonacciLastDigitFast(int n)
{
	if (n <= 1)
		return n;

	int previous = 0;
	int current = 1;

	for (int i = 0; i < n - 1; ++i) {
		int tmp_previous = previous;
		previous = current;
		current = (tmp_previous + current) % 10;
	}

	return current;
}

void testSoluton()
{
	//assert(get_fibonacci_last_digit_naive(3) == getFibonacciLastDigitFast(3));
	//assert(get_fibonacci_last_digit_naive(100) == getFibonacciLastDigitFast(100));
	for (int i = 0; i <= 300; ++i)
	{
		std::cout << i << "...";
		int naive = get_fibonacci_last_digit_naive(i);
		int fast = getFibonacciLastDigitFast(i);
		std::cout << naive << "==" << fast << "...";
		assert(naive == fast);
		std::cout << " Ok\n";
	}
}

int main() {
    int n;
    std::cin >> n;
    //int c = get_fibonacci_last_digit_naive(n);
	//testSoluton();
	int c = getFibonacciLastDigitFast(n);
	std::cout << c << '\n';
}
