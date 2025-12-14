#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int numIslands(vector<vector<char>> &grid) {
    if (grid.empty())
      return 0;
    int m = grid.size();
    int n = grid[0].size();
    int count = 0;

    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] == '1') {
          count++;
          dfs(grid, i, j, m, n);
        }
      }
    }
    return count;
  }

private:
  void dfs(vector<vector<char>> &grid, int r, int c, int m, int n) {
    if (r < 0 || r >= m || c < 0 || c >= n || grid[r][c] == '0') {
      return;
    }

    grid[r][c] = '0'; // Mark as visited (sink the island)

    dfs(grid, r + 1, c, m, n);
    dfs(grid, r - 1, c, m, n);
    dfs(grid, r, c + 1, m, n);
    dfs(grid, r, c - 1, m, n);
  }
};

int main() {
  Solution sol;
  vector<vector<char>> grid1 = {{'1', '1', '1', '1', '0'},
                                {'1', '1', '0', '1', '0'},
                                {'1', '1', '0', '0', '0'},
                                {'0', '0', '0', '0', '0'}};
  cout << "Islands 1: " << sol.numIslands(grid1) << endl; // Expect 1

  vector<vector<char>> grid2 = {{'1', '1', '0', '0', '0'},
                                {'1', '1', '0', '0', '0'},
                                {'0', '0', '1', '0', '0'},
                                {'0', '0', '0', '1', '1'}};
  cout << "Islands 2: " << sol.numIslands(grid2) << endl; // Expect 3

  return 0;
}
