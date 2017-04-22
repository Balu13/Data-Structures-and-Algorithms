#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using std::vector;

//Failed case #7 / 16: (Wrong answer)
//got: 19 expected : 18
//	Input :
//8639
//20
//1 3 4 8 16 17 51 52 53 159 318 319 957 958 959 2877 2878 2879 8637 8638 8639
//
//	8638
//	Your output :
//19
//1 3 4 8 16 17 51 52 53 159 318 319 957 958 959 2877 2878 2879 8637 8638
//		 Correct output :
//18
//1 3 6 12 13 26 52 53 159 318 319 957 958 959 2877 2878 2879 8637 8638

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

int makeRecursiveMove(int curPath, int cur, int n, std::map<int, vector<int>>& paths)
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
	if (curPath >= minPath)
	{
		return n + 1;
	}

	auto curPathsIt = paths.find(cur);
	if (curPathsIt == paths.end())
	{
		vector<int> curPaths{ n + 2, n + 2, n + 2 };
		curPathsIt = paths.emplace(cur, curPaths).first;

		int c1{ n };
		int c2{ n };
		int c3{ n };

		c3 = ((cur % 3 == 0)
			? makeRecursiveMove(curPath, cur / 3, n, paths)
			: n) + 1;
		c2 = ((cur % 2 == 0)
			? makeRecursiveMove(curPath, cur / 2, n, paths)
			: n) + 1;
		c1 = makeRecursiveMove(curPath, cur - 1, n, paths) + 1;

		(*curPathsIt).second[0] = c1;
		(*curPathsIt).second[1] = c2;
		(*curPathsIt).second[2] = c3;
	}
	else
	{
		if ((*curPathsIt).second[2] == n + 2)
		{
			(*curPathsIt).second[2] = ((cur % 3 == 0)
				? makeRecursiveMove(curPath, cur / 3, n, paths)
				: n) + 1;
		}
		if ((*curPathsIt).second[1] == n + 2)
		{
			(*curPathsIt).second[1] = ((cur % 2 == 0)
				? makeRecursiveMove(curPath, cur / 2, n, paths)
				: n) + 1;
		}
		if ((*curPathsIt).second[0] == n + 2)
		{
			(*curPathsIt).second[0] = makeRecursiveMove(curPath, cur - 1, n, paths) + 1;
		}
		curPath += std::min({ (*curPathsIt).second[0], (*curPathsIt).second[1], (*curPathsIt).second[2] });
		if (minPath > curPath)
		{
			minPath = curPath;
		}
	}

	int min = std::min({ (*curPathsIt).second[0], (*curPathsIt).second[1], (*curPathsIt).second[2] });
	return min == n + 2 ? n + 1 : min;
}

vector<int> optimalRecursive(int n, bool doTraverse, std::map<int, vector<int>>& paths)
{
	std::vector<int> sequence;
	int cur = n;
	minPath = n;
	int curPath = -1;

	makeRecursiveMove(curPath, cur, n, paths);
	if (doTraverse)
	while (cur >= 1)
	{
		sequence.push_back(cur);
		if (cur == 1)
		{
			break;
		}
		curPath = std::min({ paths[cur][0], paths[cur][1], paths[cur][2] });
		if (paths[cur][0] == curPath)
		{
			--cur;
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

bool testSolution(int stop, std::map<int, vector<int>>& paths)
{
	int n;
	int min;
	std::map<int, vector<int>> paths1;
	//std::cout << "  " << "   1  2  3   min" << "\n";
	//std::cout << " 1" << ":  0  0  0 :  0" << "\n";
	//	for (n = 1; total_recursive(n).size() - 1 != stop; ++n);
	for (n = 2; n <= stop /*(min = (optimalRecursive(n).size() - 1)) != stop*/; ++n)
	{
		//paths.clear();
		int min = optimalRecursive(n, /*true*/false, paths).size() - 1;
		//optimalRecursive(n, true/*false*/, paths1);
		//if (min == 19) {
			//int c1 = paths[n][0] == n + 1 ? -1 : paths[n][0] == n + 2 ? -2 : paths[n][0];
			//int c2 = paths[n][1] == n + 1 ? -1 : paths[n][1] == n + 2 ? -2 : paths[n][1];
			//int c3 = paths[n][2] == n + 1 ? -1 : paths[n][2] == n + 2 ? -2 : paths[n][2];
			//std::cout << (n < 10 && n >= 0 ? " " : "") << n << ": " << (c1 < 10 && c1 >= 0 ? " " : "") << c1 << (c2 < 10 && c2 >= 0 ? "  " : " ") << c2 << (c3 < 10 && c3 >= 0 ? "  " : " ") << c3 << (min < 10 && min >= 0 ? " :  " : " : ") << min << "\n";
		//}
	}
	//for (n = 2; n <= stop; ++n)
	//{
	//	if (paths.find(n) != paths.end()) {
	//		int c1 = paths[n][0] == stop + 1 ? -1 : paths[n][0] == stop + 2 ? -2 : paths[n][0];
	//		int c2 = paths[n][1] == stop + 1 ? -1 : paths[n][1] == stop + 2 ? -2 : paths[n][1];
	//		int c3 = paths[n][2] == stop + 1 ? -1 : paths[n][2] == stop + 2 ? -2 : paths[n][2];
	//		int cc1 = paths1[n][0] == n + 1 ? -1 : paths1[n][0] > n + 1 ? -2 : paths1[n][0];
	//		int cc2 = paths1[n][1] == n + 1 ? -1 : paths1[n][1] > n + 1 ? -2 : paths1[n][1];
	//		int cc3 = paths1[n][2] == n + 1 ? -1 : paths1[n][2] > n + 1 ? -2 : paths1[n][2];
	//		if (c1>-2 && cc1>-2 && c1 != cc1 || c2>-2 && cc2>-2 && c2 != cc2 || c3>-2 && cc3>-2 && c3 != cc3)
	//		{
	//			std::cout << (n < 10 && n >= 0 ? " " : "") << n << ": " << (c1 < 10 && c1 >= 0 ? " " : "") << c1 << (c2 < 10 && c2 >= 0 ? "  " : " ") << c2 << (c3 < 10 && c3 >= 0 ? "  " : " ") << c3 << "\n";
	//			std::cout << (n < 10 && n >= 0 ? " " : "") << n << ": " << (cc1 < 10 && cc1 >= 0 ? " " : "") << cc1 << (cc2 < 10 && cc2 >= 0 ? "  " : " ") << cc2 << (cc3 < 10 && cc3 >= 0 ? "  " : " ") << cc3 << "\n";
	//			return false;
	//		}
	//	}
	//}
	return true;
}

int main() {
	int n;
	std::map<int, vector<int>> paths;
	std::cin >> n;
	testSolution(n-1, paths);
	//for (int i = 2; i <= n; ++i) {
	//	std::cout << "test for n=" << i << "... ";
	//	if (!testSolution(n/*-1*/, paths))
	//	{
	//		std::cout << "error" << "\n";
	//		break;
	//	}
	//	std::cout << "ok" << "\n";
	//}
	vector<int> sequence = optimalRecursive(n,true, paths);
	std::cout << sequence.size() - 1 << std::endl;
	for (size_t i = 0; i < sequence.size(); ++i) {
		std::cout << sequence[i] << " ";
	}
	std::cout << "\n";
	//std::for_each(memo.begin(), memo.end(),[](auto pair)
	//{
	//	std::cout << pair.first << ": " << pair.second << "\n";
	//});
}
