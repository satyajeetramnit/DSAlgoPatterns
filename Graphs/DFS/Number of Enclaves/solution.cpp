#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int numEnclaves(vector<vector<int>> &grid) {
    int m = grid.size();
    int n = grid[0].size();

    // 1. Sink all land connected to the boundary
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if ((i == 0 || j == 0 || i == m - 1 || j == n - 1) && grid[i][j] == 1) {
          dfs(grid, i, j, m, n);
        }
      }
    }

    // 2. Count remaining land
    int count = 0;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] == 1) {
          count++;
        }
      }
    }
    return count;
  }

private:
  void dfs(vector<vector<int>> &grid, int r, int c, int m, int n) {
    if (r < 0 || r >= m || c < 0 || c >= n || grid[r][c] == 0)
      return;

    grid[r][c] = 0; // Sink the land

    dfs(grid, r + 1, c, m, n);
    dfs(grid, r - 1, c, m, n);
    dfs(grid, r, c + 1, m, n);
    dfs(grid, r, c - 1, m, n);
  }
};

int main() {
  Solution sol;
  vector<vector<int>> grid1 = {
      {0, 0, 0, 0}, {1, 0, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}};
  cout << "Enclaves 1: " << sol.numEnclaves(grid1) << endl; // Expect 3

  vector<vector<int>> grid2 = {
      {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}};
  cout << "Enclaves 2: " << sol.numEnclaves(grid2) << endl; // Expect 0

  return 0;
}
