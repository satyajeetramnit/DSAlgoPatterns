#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  vector<vector<int>> colorBorder(vector<vector<int>> &grid, int row, int col,
                                  int color) {
    int oldColor = grid[row][col];
    int m = grid.size();
    int n = grid[0].size();
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    vector<pair<int, int>> borders;

    dfs(grid, row, col, oldColor, visited, borders);

    for (auto &p : borders) {
      grid[p.first][p.second] = color;
    }
    return grid;
  }

private:
  void dfs(vector<vector<int>> &grid, int r, int c, int oldColor,
           vector<vector<bool>> &visited, vector<pair<int, int>> &borders) {

    visited[r][c] = true;
    bool isBorder = false;

    int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    for (auto &d : dirs) {
      int nr = r + d[0];
      int nc = c + d[1];

      if (nr < 0 || nr >= grid.size() || nc < 0 || nc >= grid[0].size()) {
        isBorder = true;
      } else if (grid[nr][nc] != oldColor) {
        isBorder = true;
      } else if (!visited[nr][nc]) {
        dfs(grid, nr, nc, oldColor, visited, borders);
      }
    }

    if (isBorder) {
      borders.push_back({r, c});
    }
  }
};

void printGrid(const vector<vector<int>> &grid) {
  cout << "[";
  for (size_t i = 0; i < grid.size(); ++i) {
    cout << "[";
    for (size_t j = 0; j < grid[i].size(); ++j) {
      cout << grid[i][j] << (j < grid[i].size() - 1 ? "," : "");
    }
    cout << "]" << (i < grid.size() - 1 ? "," : "");
  }
  cout << "]" << endl;
}

int main() {
  Solution sol;
  vector<vector<int>> grid1 = {{1, 1}, {1, 2}};
  cout << "Original 1: ";
  printGrid(grid1);
  vector<vector<int>> res1 = sol.colorBorder(grid1, 0, 0, 3);
  cout << "Colored 1: ";
  printGrid(res1); // Expect [[3,3],[3,2]]

  vector<vector<int>> grid2 = {{1, 2, 2}, {2, 3, 2}};
  cout << "Original 2: ";
  printGrid(grid2);
  vector<vector<int>> res2 = sol.colorBorder(grid2, 0, 1, 3);
  cout << "Colored 2: ";
  printGrid(res2); // Expect [[1,3,3],[2,3,3]] ... wait.
  // grid2: 0,1 is '2'. It's top.
  // component: (0,1), (0,2), (1,2) [all '2']. (1,0) is '2' but disconnected? No
  // (0,0)=1. (0,1) neighbors: (0,0)=1 (diff), (0,2)=2 (same), (1,1)=3 (diff).
  // Border=Yes. (0,2) neighbors: (0,1)=2 (same), (1,2)=2 (same). Out of bounds
  // Right. Border=Yes. (1,2) neighbors: (0,2)=2 (same), (1,1)=3 (diff), (1,0)=2
  // (Wait, (1,0) is 2. Is it connected to (1,2)? (1,1)=3 breaks it. So (1,0)
  // not connected to (1,2). (1,2) out of bounds Bottom, Right. Border=Yes. So
  // all 3 cells are borders. Color=3. Result: [[1,3,3],[2,3,3]].

  return 0;
}
