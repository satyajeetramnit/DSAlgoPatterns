#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
  vector<vector<int>> adj;
  vector<int> disc;
  vector<int> low;
  int time;
  vector<vector<int>> bridges;

  void dfs(int u, int p = -1) {
    disc[u] = low[u] = time++;

    for (int v : adj[u]) {
      if (v == p)
        continue; // Skip parent

      if (disc[v] != -1) {
        // Back-edge
        low[u] = min(low[u], disc[v]);
      } else {
        // Tree-edge
        dfs(v, u);
        low[u] = min(low[u], low[v]);
        if (low[v] > disc[u]) {
          bridges.push_back({u, v});
        }
      }
    }
  }

public:
  vector<vector<int>> criticalConnections(int n,
                                          vector<vector<int>> &connections) {
    adj.assign(n, vector<int>());
    for (auto &edge : connections) {
      adj[edge[0]].push_back(edge[1]);
      adj[edge[1]].push_back(edge[0]);
    }

    disc.assign(n, -1);
    low.assign(n, -1);
    time = 0;
    bridges.clear();

    dfs(0);
    return bridges;
  }
};

int main() {
  Solution sol;

  // Test 1: n = 4, edges = [[0,1],[1,2],[2,0],[1,3]]
  // Bridge should be [1,3] (or [3,1])
  vector<vector<int>> conn1 = {{0, 1}, {1, 2}, {2, 0}, {1, 3}};
  vector<vector<int>> res1 = sol.criticalConnections(4, conn1);

  assert(res1.size() == 1);
  // Sort edge for consistent check
  if (res1[0][0] > res1[0][1])
    swap(res1[0][0], res1[0][1]);
  assert(res1[0][0] == 1 && res1[0][1] == 3);
  cout << "Test 1 Passed" << endl;

  // Test 2: n = 2, edges = [[0,1]]
  // Bridge should be [0,1]
  vector<vector<int>> conn2 = {{0, 1}};
  vector<vector<int>> res2 = sol.criticalConnections(2, conn2);
  assert(res2.size() == 1);
  if (res2[0][0] > res2[0][1])
    swap(res2[0][0], res2[0][1]);
  assert(res2[0][0] == 0 && res2[0][1] == 1);
  cout << "Test 2 Passed" << endl;

  return 0;
}
