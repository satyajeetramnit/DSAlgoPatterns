#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  void gameOfLife(vector<vector<int>> &board) {
    int m = board.size();
    int n = board[0].size();

    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        int liveNeighbors = 0;

        for (int k = 0; k < 8; ++k) {
          int ni = i + dx[k];
          int nj = j + dy[k];

          if (ni >= 0 && ni < m && nj >= 0 && nj < n) {
            if (board[ni][nj] == 1 || board[ni][nj] == 2) {
              liveNeighbors++;
            }
          }
        }

        if (board[i][j] == 1) {
          if (liveNeighbors < 2 || liveNeighbors > 3) {
            board[i][j] = 2; // Live -> Dead
          }
        } else {
          if (liveNeighbors == 3) {
            board[i][j] = 3; // Dead -> Live
          }
        }
      }
    }

    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (board[i][j] == 2)
          board[i][j] = 0;
        else if (board[i][j] == 3)
          board[i][j] = 1;
      }
    }
  }
};

int main() {
  Solution sol;
  vector<vector<int>> board = {{0, 1, 0}, {0, 0, 1}, {1, 1, 1}, {0, 0, 0}};
  sol.gameOfLife(board);

  cout << "Test Case 1 Output:" << endl;
  for (const auto &row : board) {
    cout << "[ ";
    for (int val : row)
      cout << val << " ";
    cout << "]" << endl;
  }
  // Expect:
  // [ 0 0 0 ]
  // [ 1 0 1 ]
  // [ 0 1 1 ]
  // [ 0 1 0 ]

  return 0;
}
