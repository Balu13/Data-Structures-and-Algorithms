#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

int optimal_weight(int W, vector<int> &w)
{
	w.insert(w.begin(), 0);
	vector<vector<int>> matrix = *(new vector<vector<int>>(w.size()));
	//matrix[0] = *(new vector<int>(W + 1, 0));
	/*for (int j = 0; j <= W; ++j)
	{
		matrix[0][j] = 0;
	}*/
	for (size_t i = 0; i < w.size(); ++i)
	{
		matrix[i] = *(new vector<int>(W + 1, 0));
//		matrix[i][0] = 0;
	}

	for (size_t i = 1; i < w.size(); ++i)
	{
		for (int j = 1; j <= W; ++j)
		{
			if (w[i] > j)
			{
				matrix[i][j] = matrix[i - 1][j];
			}
			else
			{
				matrix[i][j] = std::max(matrix[i - 1][j], matrix[i - 1][j - w[i]] + w[i]);
			}
		}
	}

	return matrix[w.size() - 1][W];
}

int main()
{
	int n, W;
	std::cin >> W >> n;
	vector<int> w(n);
	for (int i = 0; i < n; i++) {
		std::cin >> w[i];
	}
	std::cout << optimal_weight(W, w) << '\n';
}
