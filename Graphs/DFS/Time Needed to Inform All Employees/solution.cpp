#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int numOfMinutes(int n, int headID, vector<int> &manager,
                   vector<int> &informTime) {
    vector<vector<int>> adj(n);
    for (int i = 0; i < n; ++i) {
      if (manager[i] != -1) {
        adj[manager[i]].push_back(i);
      }
    }

    return dfs(headID, adj, informTime);
  }

private:
  int dfs(int u, vector<vector<int>> &adj, vector<int> &informTime) {
    int maxSubTime = 0;
    for (int v : adj[u]) {
      maxSubTime = max(maxSubTime, dfs(v, adj, informTime));
    }
    return informTime[u] + maxSubTime;
  }
};

int main() {
  Solution sol;
  int n1 = 6, headID1 = 2;
  vector<int> manager1 = {2, 2, -1, 2, 2, 2};
  vector<int> informTime1 = {0, 0, 1, 0, 0, 0};
  cout << "Time 1: " << sol.numOfMinutes(n1, headID1, manager1, informTime1)
       << endl; // Expect 1

  int n2 = 7, headID2 = 6;
  vector<int> manager2 = {1, 2, 3, 4, 5, 6, -1};
  vector<int> informTime2 = {0, 6, 5, 4, 3, 2, 1};
  cout << "Time 2: " << sol.numOfMinutes(n2, headID2, manager2, informTime2)
       << endl; // Expect 21

  return 0;
}
