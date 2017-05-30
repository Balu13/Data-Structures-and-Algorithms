#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::vector;

struct DisjointSetsElement
{
	int size, parent, rank/*, requestedParent*/;

	DisjointSetsElement(int size = 0, int parent = -1, int rank = 0) :
		size(size), parent(parent), rank(rank)/*, requestedParent(parent)*/ {}
};

struct DisjointSets
{
	int size;
	int max_table_size;
	vector <DisjointSetsElement> sets;

	DisjointSets(int size) : size(size), max_table_size(0), sets(size)
	{
		for (int i = 0; i < size; i++)
		{
			sets[i].parent = i;
		}
	}

	int getParent(int table)
	{
		std::vector<int> toCompress;
		while (sets[table].parent != table)
		{
			toCompress.push_back(table);
			table = sets[table].parent;
		}
		std::for_each(toCompress.begin(), toCompress.end(), [this, table](int t)
		{
			sets[t].parent = table;
		});
		
		return table;
	}

	int getParentR(int table)
	{
		if (sets[table].parent != table)
		{
			sets[table].parent = getParent(sets[table].parent);
			//sets[table].requestedParent = sets[table].parent;
		}

		return sets[table].parent;
	}

	void merge(int destination, int source)
	{
		int realDestination = getParentR(destination);
		int realSource = getParentR(source);
		if (realDestination != realSource)
		{
			//sets[realSource].requestedParent = realDestination;
			if (sets[realSource].rank <= sets[realDestination].rank)
			{
				sets[realSource].parent = realDestination;
				sets[realDestination].size += sets[realSource].size;
				max_table_size = std::max(max_table_size, sets[realDestination].size);
				if (sets[realSource].rank == sets[realDestination].rank)
				{
					++sets[realDestination].rank;
				}
			}
			else
			{
				sets[realDestination].parent = realSource;
				sets[realSource].size += sets[realDestination].size;
				max_table_size = std::max(max_table_size, sets[realSource].size);
			}
		}
	}
};

int main()
{
	int n, m;
	cin >> n >> m;

	DisjointSets tables(n);
	for (auto &table : tables.sets)
	{
		cin >> table.size;
		tables.max_table_size = max(tables.max_table_size, table.size);
	}

/*	for (int i = 0; i < m; i++)
	{
		int destination, source;
		cin >> destination >> source;
		--destination;
		--source;

		tables.merge(destination, source);
		cout << tables.max_table_size << endl;
	}
*/
	vector<std::pair<int, int>> merges;
	for (int i = 0; i < m; i++)
	{
		int destination, source;
		cin >> destination >> source;
		--destination;
		--source;
		merges.push_back(std::make_pair(destination, source));
	}

	for (int j = 0; j < merges.size(); ++j)
	{
		tables.merge(merges[j].first, merges[j].second);
		cout << tables.max_table_size << endl;
	}

	return 0;
}
