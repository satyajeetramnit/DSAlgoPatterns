#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int closedIsland(vector<vector<int>> &grid) {
    if (grid.empty())
      return 0;
    int m = grid.size();
    int n = grid[0].size();

    // 1. Flood fill from boundaries to remove open islands
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if ((i == 0 || j == 0 || i == m - 1 || j == n - 1) && grid[i][j] == 0) {
          dfs(grid, i, j, m, n);
        }
      }
    }

    // 2. Count remaining closed islands
    int count = 0;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] == 0) {
          count++;
          dfs(grid, i, j, m, n);
        }
      }
    }
    return count;
  }

private:
  void dfs(vector<vector<int>> &grid, int r, int c, int m, int n) {
    if (r < 0 || r >= m || c < 0 || c >= n || grid[r][c] == 1)
      return;

    grid[r][c] = 1; // Mark as visited (water)

    dfs(grid, r + 1, c, m, n);
    dfs(grid, r - 1, c, m, n);
    dfs(grid, r, c + 1, m, n);
    dfs(grid, r, c - 1, m, n);
  }
};

int main() {
  Solution sol;
  vector<vector<int>> grid1 = {{1, 1, 1, 1, 1, 1, 1, 0},
                               {1, 0, 0, 0, 0, 1, 1, 0},
                               {1, 0, 1, 0, 1, 1, 1, 0},
                               {1, 0, 0, 0, 0, 1, 0, 1},
                               {1, 1, 1, 1, 1, 1, 1, 0}};
  cout << "Closed Islands 1: " << sol.closedIsland(grid1) << endl; // Expect 2

  vector<vector<int>> grid2 = {
      {0, 0, 1, 0, 0}, {0, 1, 0, 1, 0}, {0, 1, 1, 1, 0}};
  cout << "Closed Islands 2: " << sol.closedIsland(grid2) << endl; // Expect 1

  return 0;
}
