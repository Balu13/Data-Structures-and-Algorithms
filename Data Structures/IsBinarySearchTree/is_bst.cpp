#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node
{
	int key;
	int left;
	int right;

	Node() : key(0), left(-1), right(-1) {}
	Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

int sortedCheck{ 0 };

bool traverseTree(int vertex, const vector<Node> &tree, int** previousSorted)
{
	if (tree[vertex].left != -1 && tree[tree[vertex].left].key >= tree[vertex].key ||
		tree[vertex].right != -1 && tree[tree[vertex].right].key <= tree[vertex].key)
	{
		return false;
	}
	
	if (tree[vertex].left != -1 && !traverseTree(tree[vertex].left, tree, previousSorted))
	{
		return false;
	}
	
	if (*previousSorted != nullptr)
	{
		if ((**previousSorted) > (tree[vertex].key))
		{
			return false;
		}
	}
	else
	{
		*previousSorted = &sortedCheck;
	}
	**previousSorted = tree[vertex].key;
	
	return tree[vertex].right == -1 || traverseTree(tree[vertex].right, tree, previousSorted);
}

bool IsBinarySearchTreeSimple(const vector<Node>& tree)
{
	if (tree.size()==0)
	{
		return true;
	}

	int* pNull{ nullptr };

	return traverseTree(0, tree, &pNull);
}

int main()
{
	int nodes;
	cin >> nodes;
	vector<Node> tree;
	for (int i = 0; i < nodes; ++i)
	{
		int key, left, right;
		cin >> key >> left >> right;
		tree.push_back(Node(key, left, right));
	}
	if (IsBinarySearchTreeSimple(tree))
	{
		cout << "CORRECT" << endl;
	}
	else
	{
		cout << "INCORRECT" << endl;
	}
	return 0;
}
