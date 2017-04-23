#include <iostream>

int fibonacci_sum_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current;
    }

    return sum % 10;
}

int fibonacci_sum_optimal(long long n)
{
	n %= 60;
	if (n == 0) return 0;

	int previous1 = 0;
	int previous2 = 1;
	int lastDigitOfSum = 1;
	for (long long i = 0; i < n - 1; ++i)
	{
		int tmpPrevious = previous1;
		previous1 = previous2;
		previous2 = (tmpPrevious + previous1) % 10;
		lastDigitOfSum = (lastDigitOfSum + previous2) % 10;
		//std::cout << lastDigitOfSum << " ";
	}
	return lastDigitOfSum;
}

int main() {
    long long n = 0;
    std::cin >> n;
    //std::cout << fibonacci_sum_naive(n) << '\n';
	std::cout << fibonacci_sum_optimal(n) << '\n';
}
