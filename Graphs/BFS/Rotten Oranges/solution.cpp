#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
  int orangesRotting(vector<vector<int>> &grid) {
    int m = grid.size();
    int n = grid[0].size();

    queue<pair<int, int>> q;
    int freshCount = 0;

    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] == 2) {
          q.push({i, j});
        } else if (grid[i][j] == 1) {
          freshCount++;
        }
      }
    }

    if (freshCount == 0)
      return 0;

    int minutes = 0;
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    while (!q.empty() && freshCount > 0) {
      int size = q.size();
      while (size--) {
        auto [r, c] = q.front();
        q.pop();

        for (auto &dir : directions) {
          int nr = r + dir[0];
          int nc = c + dir[1];

          if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] == 1) {
            grid[nr][nc] = 2; // Rot it
            freshCount--;
            q.push({nr, nc});
          }
        }
      }
      minutes++;
    }

    return freshCount == 0 ? minutes : -1;
  }
};

int main() {
  Solution sol;
  vector<vector<int>> grid1 = {{2, 1, 1}, {1, 1, 0}, {0, 1, 1}};
  cout << "Rotten Oranges 1: " << sol.orangesRotting(grid1) << endl; // Expect 4

  vector<vector<int>> grid2 = {{2, 1, 1}, {0, 1, 1}, {1, 0, 1}};
  cout << "Rotten Oranges 2: " << sol.orangesRotting(grid2)
       << endl; // Expect -1

  vector<vector<int>> grid3 = {{0, 2}};
  cout << "Rotten Oranges 3: " << sol.orangesRotting(grid3) << endl; // Expect 0

  return 0;
}
