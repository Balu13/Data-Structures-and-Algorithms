#include <iostream>
#include <cassert>

// The following code calls a naive algorithm for computing a Fibonacci number.
//
// What to do:
// 1. Compile the following code and run it on an input "40" to check that it is slow.
//    You may also want to submit it to the grader to ensure that it gets the "time limit exceeded" message.
// 2. Implement the fibonacci_fast procedure.
// 3. Remove the line that prints the result of the naive algorithm, comment the lines reading the input,
//    uncomment the line with a call to test_solution, compile the program, and run it.
//    This will ensure that your efficient algorithm returns the same as the naive one for small values of n.
// 4. If test_solution() reveals a bug in your implementation, debug it, fix it, and repeat step 3.
// 5. Remove the call to test_solution, uncomment the line with a call to fibonacci_fast (and the lines reading the input),
//    and submit it to the grader.

int fibonacci_naive(int n) {
    if (n <= 1)
        return n;

    return fibonacci_naive(n - 1) + fibonacci_naive(n - 2);
}

unsigned long long fibonacci_fast(int n) {
	if (n<=1)
	{
		return n;
	}

	unsigned long long result;
	unsigned long long * results = new unsigned long long[n+1];
	//unsigned long long results[45];
	results[0] = 0;
	results[1] = 1;
	for (int i = 2; i <= n; ++i)
	{
		results[i] = results[i-1] + results[i-2];
	}
	result = results[n];
	delete[] results;
    return result;
}

void test_solution() {
    assert(fibonacci_fast(3) == 2);
    assert(fibonacci_fast(10) == 55);
	for (int n = 0; n < 20; ++n)
	{
		std::cout << n << "...";
		assert(fibonacci_fast(n) == fibonacci_naive(n));
		std::cout << " Ok\n";
	}
}

int main() {
    int n = 0;
    std::cin >> n;

    //std::cout << fibonacci_naive(n) << '\n';
    //test_solution();
    std::cout << fibonacci_fast(n) << '\n';
	//std::cin.clear();
	//std::cin.ignore(32767, '\n');
	//std::cin.get();
	return 0;
}
