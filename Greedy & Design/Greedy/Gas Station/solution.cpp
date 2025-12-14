#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
public:
  int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
    int n = gas.size();
    long long total_gas = 0, total_cost = 0;

    for (int i = 0; i < n; i++) {
      total_gas += gas[i];
      total_cost += cost[i];
    }

    if (total_gas < total_cost)
      return -1;

    int current_tank = 0;
    int start_index = 0;

    for (int i = 0; i < n; i++) {
      current_tank += gas[i] - cost[i];
      if (current_tank < 0) {
        start_index = i + 1;
        current_tank = 0;
      }
    }
    return start_index;
  }
};

int main() {
  Solution sol;
  vector<int> gas1 = {1, 2, 3, 4, 5};
  vector<int> cost1 = {3, 4, 5, 1, 2};
  cout << "Test Case 1: " << sol.canCompleteCircuit(gas1, cost1)
       << endl; // Expect 3

  vector<int> gas2 = {2, 3, 4};
  vector<int> cost2 = {3, 4, 3};
  cout << "Test Case 2: " << sol.canCompleteCircuit(gas2, cost2)
       << endl; // Expect -1

  return 0;
}
