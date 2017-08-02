#include <string>
#include <iostream>
#include <vector>
#include <map>

using std::map;
using std::vector;
using std::string;

typedef map<char, int> Node;
typedef vector<Node> Trie;

Trie build_trie(vector<string> & patterns)
{
	Trie t;
	Node root;
	t.push_back(root);
	int maxIndex = 0;

	for (string pattern : patterns)
	{
		int currentIndex = 0;
		for (char symbol : pattern)
		{
			auto it = t[currentIndex].find(symbol);
			if (it == t[currentIndex].end())
			{
				// insert tail of the pattern as new branch in the trie
				Node newNode;
				t.push_back(newNode);
				t[currentIndex][symbol] = ++maxIndex;
				currentIndex = maxIndex;
			}
			else
			{
				currentIndex = it->second;
			}
		}
	}

	return t;
}

int main()
{
	size_t n;
	std::cin >> n;
	vector<string> patterns;
	for (size_t i = 0; i < n; i++)
	{
		string s;
		std::cin >> s;
		patterns.push_back(s);
	}

	Trie t = build_trie(patterns);
	for (size_t i = 0; i < t.size(); ++i)
	{
		for (const auto & j : t[i])
		{
			std::cout << i << "->" << j.second << ":" << j.first << "\n";
		}
	}

	return 0;
}