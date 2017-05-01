#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

class Node;

class Node
{
public:
	int key;
	Node *parent;
	std::vector<Node *> children;

	Node()
	{
		this->parent = NULL;
	}

	void setParent(Node *theParent)
	{
		parent = theParent;
		parent->children.push_back(this);
	}
};

int getMaxTreeHeight(std::vector<Node>& nodes)
{
	// Replace this code with a faster implementation
	int maxHeight = 0;
	for (int leaf_index = 0; leaf_index < nodes.size(); leaf_index++)
	{
		int height = 0;
		for (Node *v = &nodes[leaf_index]; v != NULL; v = v->parent)
		{
			height++;
		}
		maxHeight = std::max(maxHeight, height);
	}
	return maxHeight;
}

int getMaxTreeHeightFast(std::vector<Node>& nodes)
{
	//Failed case #3 / 24: (Wrong answer)

	//	Input :
	//	10
	//	9 7 5 5 2 9 9 9 2 - 1

	//	Your output :
	//5

	//	Correct output :
	//4

	if (nodes.empty())
	{
		return 0;
	}

	int maxHeight = 0;
	std::queue<Node*> buffer;

	// search the root of the tree
	Node *root = &nodes[0];
	while (root->parent != NULL)
	{
		root = root->parent;
	}

	//traverse the tree
	buffer.push(NULL);
	buffer.push(root);
	bool startNewLevel = false;
	while (!buffer.empty())
	{
		Node *current = buffer.front();
		buffer.pop();
		if (current == NULL)
		{
			startNewLevel = true;
			++maxHeight;
			if (buffer.empty())
			{
				break;
			}
			current = buffer.front();
			buffer.pop();
		}
		if (!current->children.empty())
		{
			if (startNewLevel)
			{
				buffer.push(NULL);
				startNewLevel = false;
			}
			for (std::vector<Node*>::iterator curChild = current->children.begin(); curChild != current->children.end(); ++curChild)
			{
				buffer.push(*curChild);
			}
		}
	}

	return maxHeight;
}

int main_with_large_stack_space()
{
	std::ios_base::sync_with_stdio(0);
	int n;
	std::cin >> n;

	std::vector<Node> nodes;
	nodes.resize(n);
	for (int child_index = 0; child_index < n; child_index++)
	{
		int parent_index;
		std::cin >> parent_index;
		if (parent_index >= 0)
		{
			nodes[child_index].setParent(&nodes[parent_index]);
		}
		nodes[child_index].key = child_index;
	}


	std::cout << getMaxTreeHeightFast(nodes) << std::endl;
	return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }

#endif
  return main_with_large_stack_space();
}
