#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  vector<vector<string>> solveNQueens(int n) {
    vector<vector<string>> res;
    vector<string> board(n, string(n, '.'));
    vector<bool> cols(n, false);
    vector<bool> posDiag(2 * n, false); // row + col
    vector<bool> negDiag(2 * n, false); // row - col + n

    backtrack(0, n, board, cols, posDiag, negDiag, res);
    return res;
  }

private:
  void backtrack(int row, int n, vector<string> &board, vector<bool> &cols,
                 vector<bool> &posDiag, vector<bool> &negDiag,
                 vector<vector<string>> &res) {
    if (row == n) {
      res.push_back(board);
      return;
    }

    for (int col = 0; col < n; ++col) {
      if (cols[col] || posDiag[row + col] || negDiag[row - col + n]) {
        continue;
      }

      cols[col] = true;
      posDiag[row + col] = true;
      negDiag[row - col + n] = true;
      board[row][col] = 'Q';

      backtrack(row + 1, n, board, cols, posDiag, negDiag, res);

      board[row][col] = '.';
      cols[col] = false;
      posDiag[row + col] = false;
      negDiag[row - col + n] = false;
    }
  }
};

void printBoard(const vector<vector<string>> &solutions) {
  cout << "[" << endl;
  for (const auto &sol : solutions) {
    cout << "  [" << endl;
    for (const auto &row : sol) {
      cout << "    \"" << row << "\"," << endl;
    }
    cout << "  ]," << endl;
  }
  cout << "]" << endl;
}

int main() {
  Solution sol;
  int n1 = 4;
  vector<vector<string>> res1 = sol.solveNQueens(n1);
  cout << "Solutions for N=4:" << endl;
  printBoard(res1);

  int n2 = 1;
  vector<vector<string>> res2 = sol.solveNQueens(n2);
  cout << "Solutions for N=1:" << endl;
  printBoard(res2);

  return 0;
}
