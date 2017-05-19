#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;

class JobQueue
{
private:
	int num_workers_;
	vector<int> jobs_;

	vector<int> assigned_workers_;
	vector<long long> start_times_;

	void WriteResponse() const
	{
		for (int i = 0; i < jobs_.size(); ++i)
		{
			cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
		}
	}

	void ReadData()
	{
		int m;
		cin >> num_workers_ >> m;
		jobs_.resize(m);
		for (int i = 0; i < m; ++i)
			cin >> jobs_[i];
	}

	void AssignJobs()
	{
		assigned_workers_.resize(jobs_.size());
		start_times_.resize(jobs_.size());
		vector<long long> next_free_time(num_workers_, 0);
		vector<int> heap(num_workers_, -1);
		int currentUnusedWorker = 0;

		for (int i = 0; i < jobs_.size(); ++i)
		{
			int duration = jobs_[i];
			if (currentUnusedWorker < num_workers_)
			{
				insert(currentUnusedWorker, heap, i, duration, next_free_time);
			}
			else
			{
				// change thread priority in the heap
				feedNextWorker(heap, i, duration, next_free_time);
			}
		}
	}

	void insert(int& currentUnusedWorker, vector<int>& heap, int jobNo, int jobDuration, vector<long long>& next_free_time)
	{
		assigned_workers_[jobNo] = currentUnusedWorker;
		start_times_[jobNo] = next_free_time[currentUnusedWorker];
		next_free_time[currentUnusedWorker] += jobDuration;
		heap[currentUnusedWorker] = currentUnusedWorker;
		int currentPos = currentUnusedWorker++;
		//liftUp()
		while (currentPos != 0 && next_free_time[heap[currentPos]] < next_free_time[heap[(currentPos - 1) / 2]])
		{
			std::swap(heap[currentPos], heap[(currentPos - 1) / 2]);
			currentPos = (currentPos - 1) / 2;
		}
	}

	void feedNextWorker(vector<int>& heap, int jobNo, int jobDuration, vector<long long>& next_free_time)
	{
		assigned_workers_[jobNo] = heap[0];
		start_times_[jobNo] = next_free_time[heap[0]];
		next_free_time[heap[0]] += jobDuration;
		int currentPos{ 0 };
		//siftDown()
		while (currentPos * 2 + 1 < heap.size())
		{
			if (currentPos * 2 + 2 < heap.size())
			{
				if (next_free_time[heap[currentPos * 2 + 1]] > next_free_time[heap[currentPos * 2 + 2]])
				{
					if (next_free_time[heap[currentPos]] > next_free_time[heap[currentPos * 2 + 2]] ||
						next_free_time[heap[currentPos]] == next_free_time[heap[currentPos * 2 + 2]] && heap[currentPos] > heap[currentPos * 2 + 2])
					{
						std::swap(heap[currentPos], heap[currentPos * 2 + 2]);
						currentPos = currentPos * 2 + 2;
					}
					else
					{
						break;
					}
				}
				else if (next_free_time[heap[currentPos * 2 + 1]] == next_free_time[heap[currentPos * 2 + 2]])
				{
					if (next_free_time[heap[currentPos]] > next_free_time[heap[currentPos * 2 + 1]])
					{
						if (heap[currentPos * 2 + 1] > heap[currentPos * 2 + 2])
						{
							std::swap(heap[currentPos], heap[currentPos * 2 + 2]);
							currentPos = currentPos * 2 + 2;
						}
						else
						{
							std::swap(heap[currentPos], heap[currentPos * 2 + 1]);
							currentPos = currentPos * 2 + 1;
						}
					}
					else if (next_free_time[heap[currentPos]] == next_free_time[heap[currentPos * 2 + 1]])
					{
						if (heap[currentPos] > heap[currentPos * 2 + 1])
						{
							if (heap[currentPos * 2 + 1] > heap[currentPos * 2 + 2])
							{
								std::swap(heap[currentPos], heap[currentPos * 2 + 2]);
								currentPos = currentPos * 2 + 2;
							}
							else
							{
								std::swap(heap[currentPos], heap[currentPos * 2 + 1]);
								currentPos = currentPos * 2 + 1;
							}
						}
						else if (heap[currentPos] > heap[currentPos * 2 + 2])
						{
							std::swap(heap[currentPos], heap[currentPos * 2 + 2]);
							currentPos = currentPos * 2 + 2;
						}
						else
						{
							break;
						}
					}
					else
					{
						break;
					}
				}
				else
				{
					if (next_free_time[heap[currentPos]] > next_free_time[heap[currentPos * 2 + 1]] ||
						next_free_time[heap[currentPos]] == next_free_time[heap[currentPos * 2 + 1]] && heap[currentPos] > heap[currentPos * 2 + 1])
					{
						std::swap(heap[currentPos], heap[currentPos * 2 + 1]);
						currentPos = currentPos * 2 + 1;
					}
					else
					{
						break;
					}
				}
			}
			else
			{
				if (next_free_time[heap[currentPos]] > next_free_time[heap[currentPos * 2 + 1]] ||
					next_free_time[heap[currentPos]] == next_free_time[heap[currentPos * 2 + 1]] && heap[currentPos] > heap[currentPos * 2 + 1])
				{
					std::swap(heap[currentPos], heap[currentPos * 2 + 1]);
					currentPos = currentPos * 2 + 1;
				}
				else
				{
					break;
				}
			}
		}
	}

public:
	void Solve()
	{
		ReadData();
		AssignJobs();
		WriteResponse();
	}
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	JobQueue job_queue;
	job_queue.Solve();
	return 0;
}
