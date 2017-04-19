#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using std::vector;

//Failed case #3 / 16: (Wrong answer)
//got: 15 expected : 14
//	Input :
//	96234
//
//	Your output :
//	 15
//		 1 2 4 5 10 11 22 66 198 594 1782 5346 16038 16039 32078 96234
//		 Correct output :
//	 14
//		 1 3 9 10 11 22 66 198 594 1782 5346 16038 16039 32078 96234

vector<int> greedy_sequence(int n) {
	std::vector<int> sequence;
	while (n >= 1) {
		sequence.push_back(n);
		if (n % 3 == 0) {
			n /= 3;
		}
		else if (n % 2 == 0) {
			n /= 2;
		}
		else {
			n = n - 1;
		}
	}
	reverse(sequence.begin(), sequence.end());
	return sequence;
}

std::map<int, int> memo;
std::map<int, int[3]> paths;

vector<int> total_recursive(int n) {
	std::vector<int> sequence;
	int c1{ n };
	int c2{ n };
	int c3{ n };
	int n1{ n - 1 };
	int n2{ n };
	int n3{ n };

	while (n >= 1)
	{
		auto it = memo.find(n);
		if (it != memo.end())
		{
			while (n >= 1)
			{
				sequence.push_back(n);
				std::cout << n << " ";
				if (n == 1)
				{
					break;
				}
				if (n % 3 == 0 && memo.find(n / 3)!=memo.end() && memo[n/3] == memo[n] - 1)
				{
					n /= 3;
				}
				else if (n % 2 == 0 && memo.find(n / 2) != memo.end() && memo[n / 2] == memo[n] - 1)
				{
					n /= 2;
				}
				else if (memo.find(n - 1) != memo.end() && memo[n - 1] == memo[n] - 1)
				{
					--n;
				}
			}
			reverse(sequence.begin(), sequence.end());
			return sequence;
		}

		sequence.push_back(n);
		std::cout << n << " ";
		if (n == 1)
		{
			break;
		}
		if (n % 3 == 0)
		{
			n3 = n / 3;
			auto it = memo.find(n3);
			if (it == memo.end())
			{
				// calculate sequence length for n/3
				it = memo.emplace(n3, total_recursive(n3).size() - 1).first;
			}
			c3 = (*it).second;
		}
		if (n % 2 == 0) {
			n2 = n / 2;
			auto it = memo.find(n2);
			if (it == memo.end())
			{
				// calculate sequence length for n/2
				it = memo.emplace(n2, total_recursive(n2).size() - 1).first;
			}
			c2 = (*it).second;
		}
		it = memo.find(n1);
		if (it == memo.end())
		{
			// calculate sequence length for n-1
			it = memo.emplace(n1, total_recursive(n1).size() - 1).first;
		}
		c1 = (*it).second;

		int minPath = std::min({ c1, c2, c3 });
		memo.emplace(n, minPath + 1);
		if (c3 == minPath)
		{
			n = n3;
		}
		else if (c2 == minPath)
		{
			n = n2;
		}
		else
		{
			n = n1;
		}
	}

	reverse(sequence.begin(), sequence.end());
	return sequence;
}

int minPath;
std::vector<int> minSequence;

int makeRecursiveMove(int curPath, int cur, int branch, int n)
{
	++curPath;

	if (cur == 1)
	{
		if (minPath > curPath)
		{
			minPath = curPath;
		}
		return 0;
	}
	
	auto curPathsIt = paths.find(cur);
	if (curPathsIt == paths.end())
	{
		int curPaths[3]{ n + 1, n + 1, n + 1 };
		curPathsIt = paths.emplace(cur, curPaths).first;
	}

	int c1{ n };
	int c2{ n };
	int c3{ n };
	if (cur % 3 == 0)
	{
		c3 = makeRecursiveMove(curPath, n / 3, 3, n) + 1;
	}
	(*curPathsIt).second[branch - 1] = curPath;

	return std::min({ c1, c2, c3 });
}

vector<int> optimalRecursive(int n)
{
	std::vector<int> sequence;
	int cur = n;
	minPath = n;
	int curPath = 0;
	int c1{ n };
	int c2{ n };
	int c3{ n };

	makeRecursiveMove(curPath, cur, 3, n);
	makeRecursiveMove(curPath, cur, 2, n);
	makeRecursiveMove(curPath, cur, 1, n);

	while (cur > 1)
	{
		sequence.push_back(cur);
		curPath = std::min({ paths[cur][0], paths[cur][1], paths[cur][2] });
		if (paths[cur][0] == curPath)
		{
			++cur;
		}
		else if (paths[cur][1]==curPath)
		{
			cur /= 2;
		}
		else
		{
			cur /= 3;
		}
	}
	reverse(sequence.begin(), sequence.end());
	return sequence;
}

void makeMove(std::vector<int> sequence, int curPath, int cur, int n)
{
	if (cur > n)
	{
		return;
	}
	sequence.push_back(cur);
	++curPath;
	if (cur == n)
	{
		if (minPath > curPath)
		{
			minPath = curPath;
			minSequence = sequence;
			std::cout << "cur minPath: " << minPath << "\n";
		}
		return;
	}
	if (curPath == minPath)
	{
		sequence.pop_back();
		--curPath;
		return;
	}
	if (cur * 3 <= n)
	makeMove(sequence, curPath, cur * 3, n);
	if (cur * 2 <= n)
	makeMove(sequence, curPath, cur * 2, n);
	if (cur * 3 <= n || cur * 2 <= n)
	{
		makeMove(sequence, curPath, cur + 1, n);
	}
	else
	{
		if (n - cur + curPath >= minPath)
		{
			return;
		}
		else
		{
			minPath = n - cur + curPath;
			while (++cur <= n)
			{
				sequence.push_back(cur);
			}
			minSequence = sequence;
		}
	}
}

vector<int> optimal_greedy(int n) {
	std::vector<int> sequence; 
	int cur = 1;
	minPath = n;
	int curPath = 0;

	makeMove(sequence, curPath, cur, n);
	//reverse(sequence.begin(), sequence.end());
	return minSequence;
}

void testSolution(int stop)
{
	int n;
//	for (n = 1; total_recursive(n).size() - 1 != stop; ++n);
	for (n = 1; optimal_greedy(n).size() - 1 != stop; ++n);
	std::cout << n;
}

int main() {
	int n;
	std::cin >> n;
	//testSolution(n);
	vector<int> sequence = optimalRecursive(n);
	std::cout << sequence.size() - 1 << std::endl;
	for (size_t i = 0; i < sequence.size(); ++i) {
		std::cout << sequence[i] << " ";
	}
	std::cout << "\n";
	std::for_each(memo.begin(), memo.end(),[](auto pair)
	{
		std::cout << pair.first << ": " << pair.second << "\n";
	});
	//std::cout << std::min({ 4, 1, 2, 3 });
}
