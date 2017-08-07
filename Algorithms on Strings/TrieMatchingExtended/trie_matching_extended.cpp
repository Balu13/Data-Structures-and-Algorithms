#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Node
{
private:
	map<char, int> edges;
	char m_symbol;
	bool m_isPatternEnd;

public:
	Node() {}

	Node(char symbol, bool isPatternEnd) : m_symbol(symbol), m_isPatternEnd(isPatternEnd)
	{
	}

	char getSymbol()
	{
		return m_symbol;
	}

	bool isLeaf()
	{
		return edges.empty();
	}

	bool isPatternEnd()
	{
		return m_isPatternEnd;
	}

	void setPatternEnd()
	{
		m_isPatternEnd = true;
	}

	int findEdge(char nextSymbol)
	{
		auto it = edges.find(nextSymbol);
		return it == edges.end() ? -1 : it->second;
	}

	void addEdge(char nextSymbol, int pos)
	{
		edges[nextSymbol] = pos;
	}
};

typedef vector<Node> Trie;

Trie build_trie(const vector<string> & patterns)
{
	Trie t;
	Node root(' ', false);
	t.push_back(root);
	int maxIndex = 0;

	for (string pattern : patterns)
	{
		int currentIndex = 0;
		for (char symbol : pattern)
		{
			int next = t[currentIndex].findEdge(symbol);
			if (next == -1)
			{
				// insert tail of the pattern as new branch in the trie
				Node newNode(symbol, false);
				t.push_back(newNode);
				t[currentIndex].addEdge(symbol, ++maxIndex);
				currentIndex = maxIndex;
			}
			else
			{
				currentIndex = next;
			}
		}
		t[currentIndex].setPatternEnd();
	}

	return t;
}

int match(Trie trie, const string & text)
{
	Node currentNode = trie[0];
	int pos = -1;
	int startPos = -1;

	for (char textSymbol : text)
	{
		int res = currentNode.findEdge(textSymbol);
		if (res == -1)
		{
			break;
		}
		++pos;
		if (startPos == -1)
		{
			startPos = pos;
		}
		currentNode = trie[res];
		if (currentNode.isLeaf() || currentNode.isPatternEnd())
		{
			break;
		}
	}

	return (currentNode.isLeaf() || currentNode.isPatternEnd()) ? startPos : -1;
}

vector <int> solve(const string& text, int n, const vector <string>& patterns)
{
	vector <int> result;

	Trie trie = build_trie(patterns);
	for (int start = 0; start < text.size(); ++start)
	{
		int res = match(trie, text.substr(start, text.size() - start));
		if (res != -1)
		{
			if (std::find(result.begin(), result.end(), res + start) == result.end())
			{
				result.push_back(res + start);
			}
		}
	}

	return result;
}

int main (void)
{
	string t;
	cin >> t;

	int n;
	cin >> n;

	vector <string> patterns (n);
	for (int i = 0; i < n; i++)
	{
		cin >> patterns[i];
	}

	vector <int> ans;
	ans = solve (t, n, patterns);

	for (int i = 0; i < (int) ans.size (); i++)
	{
		cout << ans[i];
		if (i + 1 < (int) ans.size ())
		{
			cout << " ";
		}
		else
		{
			cout << endl;
		}
	}

	return 0;
}
