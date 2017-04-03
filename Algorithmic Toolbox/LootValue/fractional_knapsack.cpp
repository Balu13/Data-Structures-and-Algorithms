#include <iostream>
#include <vector>
#include <map>

using std::vector;

double get_optimal_value(int capacity, vector<int> weights, vector<int> values) {
  double value = 0.0;

  // write your code here
  std::map<double, int> sortedCoefPositions;
  for (int i = 0; i < values.size(); i++)
  {
	  sortedCoefPositions.insert(std::make_pair((double)values[i] / (double)weights[i], i));
  }
  std::map<double, int>::const_reverse_iterator it;
  for (it = sortedCoefPositions.crbegin(); it != sortedCoefPositions.crend(); it++)
  {
	  double coef = (*it).first;
	  int index = (*it).second;
	  if (capacity <= weights[index])
	  {
		  value += coef * capacity;
		  break;
	  }
	  else
	  {
		  value += values[index];
		  capacity -= weights[index];
	  }
  }

  return value;
}

int main() {
  int n;
  int capacity;
  std::cin >> n >> capacity;
  vector<int> values(n);
  vector<int> weights(n);
  for (int i = 0; i < n; i++) {
    std::cin >> values[i] >> weights[i];
  }

  double optimal_value = get_optimal_value(capacity, weights, values);

  std::cout.precision(10);
  std::cout << optimal_value << std::endl;
  return 0;
}
