#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

struct DSU {
  vector<int> parent;
  int count; // Number of connected components

  DSU(int n) {
    parent.resize(n);
    iota(parent.begin(), parent.end(), 0);
    count = n;
  }
  int find(int x) {
    if (x != parent[x])
      parent[x] = find(parent[x]);
    return parent[x];
  }
  void unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
      parent[rootX] = rootY;
      count--;
    }
  }
};

class Solution {
public:
  int findCircleNum(vector<vector<int>> &isConnected) {
    int n = isConnected.size();
    DSU dsu(n);

    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        if (isConnected[i][j] == 1) {
          dsu.unite(i, j);
        }
      }
    }
    return dsu.count;
  }
};

int main() {
  Solution sol;
  vector<vector<int>> isConnected1 = {{1, 1, 0}, {1, 1, 0}, {0, 0, 1}};
  cout << "Provinces 1: " << sol.findCircleNum(isConnected1)
       << endl; // Expect 2

  vector<vector<int>> isConnected2 = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
  cout << "Provinces 2: " << sol.findCircleNum(isConnected2)
       << endl; // Expect 3

  return 0;
}
