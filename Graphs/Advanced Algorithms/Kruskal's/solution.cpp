#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

struct DSU {
  vector<int> parent;
  DSU(int n) {
    parent.resize(n);
    iota(parent.begin(), parent.end(), 0);
  }
  int find(int x) {
    if (x != parent[x])
      parent[x] = find(parent[x]);
    return parent[x];
  }
  bool unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
      parent[rootX] = rootY;
      return true;
    }
    return false;
  }
};

class Solution {
public:
  int minSpanningTree(int V, vector<vector<int>> &edges) {
    sort(
        edges.begin(), edges.end(),
        [](const vector<int> &a, const vector<int> &b) { return a[2] < b[2]; });

    DSU dsu(V);
    int mstWeight = 0;

    for (auto &edge : edges) {
      int u = edge[0];
      int v = edge[1];
      int w = edge[2];

      if (dsu.unite(u, v)) {
        mstWeight += w;
      }
    }
    return mstWeight;
  }
};

int main() {
  Solution sol;
  int V1 = 3;
  vector<vector<int>> edges1 = {{0, 1, 5}, {1, 2, 3}, {0, 2, 1}};
  cout << "MST 1: " << sol.minSpanningTree(V1, edges1) << endl; // Expect 4

  int V2 = 2;
  vector<vector<int>> edges2 = {{0, 1, 5}};
  cout << "MST 2: " << sol.minSpanningTree(V2, edges2) << endl; // Expect 5

  return 0;
}
