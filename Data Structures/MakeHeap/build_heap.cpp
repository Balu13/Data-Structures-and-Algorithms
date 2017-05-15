#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder
{
private:
	vector<int> data_;
	vector< pair<int, int> > swaps_;

	void WriteResponse() const
	{
		cout << swaps_.size() << "\n";
		for (int i = 0; i < swaps_.size(); ++i)
		{
			cout << swaps_[i].first << " " << swaps_[i].second << "\n";
		}
	}

	void ReadData()
	{
		int n;
		cin >> n;
		data_.resize(n);
		for (int i = 0; i < n; ++i)
		{
			cin >> data_[i];
		}
	}

	void GenerateSwaps()
	{
		swaps_.clear();
		// The following naive implementation just sorts 
		// the given sequence using selection sort algorithm
		// and saves the resulting sequence of swaps.
		// This turns the given array into a heap, 
		// but in the worst case gives a quadratic number of swaps.
		//
		// TODO: replace by a more efficient implementation
		/*for (int i = 0; i < data_.size(); ++i)
		{
			for (int j = i + 1; j < data_.size(); ++j)
			{
				if (data_[i] > data_[j])
				{
					swap(data_[i], data_[j]);
					swaps_.push_back(make_pair(i, j));
				}
			}
		}*/
		if (data_.size() > 1)
		{
			for (int i = data_.size() / 2; i >= 0; --i)
			{
				int j;
				int current{ -1 };
				while (i != (j = siftDown(i)))
				{
					if (current < 0)
					{
						current = i;
					}
					i = j;
				}
				if (current >= 0)
				{
					i = current;
				}
			}
		}
	}

	int siftDown(int index)
	{
		int leftChild = 2 * index + 1;
		if (leftChild >= data_.size())
		{
			return index;
		}
		int rightChild = leftChild + 1;
		int test;
		if (rightChild >= data_.size())
		{
			test = leftChild;
		}
		else
		{
			test = data_[leftChild] < data_[rightChild] ? leftChild : rightChild;
		}

		if (data_[index] > data_[test])
		{
			swap(data_[index], data_[test]);
			swaps_.push_back(make_pair(index, test));
		}

		return test;
	}

public:
	void Solve()
	{
		ReadData();
		GenerateSwaps();
		WriteResponse();
	}
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	HeapBuilder heap_builder;
	heap_builder.Solve();
	return 0;
}
