#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
  int maxDistance(vector<vector<int>> &grid) {
    int n = grid.size();
    queue<pair<int, int>> q;

    // Add all land cells to queue
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] == 1) {
          q.push({i, j});
        }
      }
    }

    // All water or all land
    if (q.empty() || q.size() == n * n)
      return -1;

    int dist = -1;
    int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    while (!q.empty()) {
      int size = q.size();
      dist++;

      while (size--) {
        auto [r, c] = q.front();
        q.pop();

        for (auto &d : dirs) {
          int nr = r + d[0];
          int nc = c + d[1];

          if (nr >= 0 && nr < n && nc >= 0 && nc < n && grid[nr][nc] == 0) {
            grid[nr][nc] = 1; // Mark visited
            q.push({nr, nc});
          }
        }
      }
    }
    return dist;
  }
};

int main() {
  Solution sol;
  vector<vector<int>> grid1 = {{1, 0, 1}, {0, 0, 0}, {1, 0, 1}};
  cout << "Max Distance 1: " << sol.maxDistance(grid1) << endl; // Expect 2

  vector<vector<int>> grid2 = {{1, 0, 0}, {0, 0, 0}, {0, 0, 0}};
  cout << "Max Distance 2: " << sol.maxDistance(grid2) << endl; // Expect 4

  vector<vector<int>> grid3 = {{0, 0, 0}};
  cout << "Max Distance 3: " << sol.maxDistance(grid3) << endl; // Expect -1

  return 0;
}
