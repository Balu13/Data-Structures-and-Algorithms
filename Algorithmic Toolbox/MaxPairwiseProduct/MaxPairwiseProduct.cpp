#include "stdafx.h"
#include <iostream>
#include <vector>

using std::vector;
using std::cin;
using std::cout;

long long MaxPairwiseProduct(const vector<int>& numbers) {
	long long result = 0;
	int n = numbers.size();
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			if (((long long)numbers[i]) * numbers[j] > result) {
				result = ((long long)numbers[i]) * numbers[j];
			}
		}
	}
	return result;
}

long long MaxPaiwiseProductFast(const vector<int>& numbers)
{
	int n = numbers.size();

	int max_index1 = -1;
	for (int i = 0; i<n; ++i)
	{
		if (max_index1 == -1 || numbers[i]>numbers[max_index1])
		{
			max_index1 = i;
		}
	}

	int max_index2 = -1;
	for (int j = 0; j<n; ++j)
	{
		if (j != max_index1 && (max_index2 == -1 || numbers[j]>numbers[max_index2]))
		{
			max_index2 = j;
		}
	}

	return ((long long)numbers[max_index1]) * numbers[max_index2];
}

int main() {
	int n;
	cin >> n;
	vector<int> numbers(n);
	for (int i = 0; i < n; ++i) {
		cin >> numbers[i];
	}

	//long long result1 = MaxPairwiseProduct(numbers);
	long long result2 = MaxPaiwiseProductFast(numbers);
	//long long result3 = MaxPairwiseProduct(vector<int>(200000, 0));
	//long long result4 = MaxPaiwiseProductFast(vector<int>(200000, 0));
	cout /*<< result1 << "\n"*/ << result2 << "\n" /*<< result4*/;

	std::cin.clear();
	std::cin.ignore(32767, '\n');
	std::cin.get();
	return 0;
}