#include <iostream>

using namespace std;

class Solution {
public:
  int totalNQueens(int n) { return solve(0, 0, 0, 0, n); }

private:
  int solve(int row, int cols, int diag1, int diag2, int n) {
    if (row == n)
      return 1;

    int count = 0;
    int availablePositions = ((1 << n) - 1) & ~(cols | diag1 | diag2);

    while (availablePositions) {
      int position = availablePositions & -availablePositions;
      availablePositions &= availablePositions - 1;

      count += solve(row + 1, cols | position, (diag1 | position) << 1,
                     (diag2 | position) >> 1, n);
    }

    return count;
  }
};

int main() {
  Solution sol;
  cout << "Test Case 1 (n=4): " << sol.totalNQueens(4) << endl; // Expect 2
  cout << "Test Case 2 (n=1): " << sol.totalNQueens(1) << endl; // Expect 1
  cout << "Test Case 3 (n=8): " << sol.totalNQueens(8) << endl; // Expect 92
  return 0;
}
