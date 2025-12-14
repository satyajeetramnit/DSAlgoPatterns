#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
  int shortestPathBinaryMatrix(vector<vector<int>> &grid) {
    int n = grid.size();
    if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1)
      return -1;

    queue<pair<int, int>> q;
    q.push({0, 0});
    grid[0][0] = 1; // Mark visited

    int directions[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                            {0, 1},   {1, -1}, {1, 0},  {1, 1}};
    int pathLen = 1;

    while (!q.empty()) {
      int size = q.size();
      while (size--) {
        auto [r, c] = q.front();
        q.pop();

        if (r == n - 1 && c == n - 1)
          return pathLen;

        for (auto &dir : directions) {
          int nr = r + dir[0];
          int nc = c + dir[1];

          if (nr >= 0 && nr < n && nc >= 0 && nc < n && grid[nr][nc] == 0) {
            q.push({nr, nc});
            grid[nr][nc] = 1; // Mark visited
          }
        }
      }
      pathLen++;
    }
    return -1;
  }
};

int main() {
  Solution sol;
  vector<vector<int>> grid1 = {{0, 1}, {1, 0}};
  cout << "Shortest Path 1: " << sol.shortestPathBinaryMatrix(grid1)
       << endl; // Expect 2

  vector<vector<int>> grid2 = {{0, 0, 0}, {1, 1, 0}, {1, 1, 0}};
  cout << "Shortest Path 2: " << sol.shortestPathBinaryMatrix(grid2)
       << endl; // Expect 4

  vector<vector<int>> grid3 = {{1, 0, 0}, {1, 1, 0}, {1, 1, 0}};
  cout << "Shortest Path 3: " << sol.shortestPathBinaryMatrix(grid3)
       << endl; // Expect -1

  return 0;
}
