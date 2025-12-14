#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

struct DSU {
  vector<int> parent;
  DSU(int n) {
    parent.resize(n + 1);
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
  vector<int> findRedundantConnection(vector<vector<int>> &edges) {
    int n = edges.size();
    DSU dsu(n);

    for (auto &edge : edges) {
      if (!dsu.unite(edge[0], edge[1])) {
        return edge;
      }
    }
    return {};
  }
};

void printVector(const vector<int> &v) {
  cout << "[";
  for (size_t i = 0; i < v.size(); ++i) {
    cout << v[i] << (i < v.size() - 1 ? "," : "");
  }
  cout << "]" << endl;
}

int main() {
  Solution sol;
  vector<vector<int>> edges1 = {{1, 2}, {1, 3}, {2, 3}};
  cout << "Redundant 1: ";
  printVector(sol.findRedundantConnection(edges1)); // Expect [2,3]

  vector<vector<int>> edges2 = {{1, 2}, {2, 3}, {3, 4}, {1, 4}, {1, 5}};
  cout << "Redundant 2: ";
  printVector(sol.findRedundantConnection(edges2)); // Expect [1,4]

  return 0;
}
