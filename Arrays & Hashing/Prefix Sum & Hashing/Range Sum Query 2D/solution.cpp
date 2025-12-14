#include <iostream>
#include <vector>

using namespace std;

class NumMatrix {
  vector<vector<int>> dp;

public:
  NumMatrix(vector<vector<int>> &matrix) {
    int m = matrix.size();
    int n = matrix[0].size();
    dp.resize(m + 1, vector<int>(n + 1, 0));

    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        dp[i + 1][j + 1] =
            matrix[i][j] + dp[i][j + 1] + dp[i + 1][j] - dp[i][j];
      }
    }
  }

  int sumRegion(int row1, int col1, int row2, int col2) {
    return dp[row2 + 1][col2 + 1] - dp[row1][col2 + 1] - dp[row2 + 1][col1] +
           dp[row1][col1];
  }
};

int main() {
  vector<vector<int>> matrix = {{3, 0, 1, 4, 2},
                                {5, 6, 3, 2, 1},
                                {1, 2, 0, 1, 5},
                                {4, 1, 0, 1, 7},
                                {1, 0, 3, 0, 5}};
  NumMatrix *obj = new NumMatrix(matrix);
  cout << obj->sumRegion(2, 1, 4, 3) << endl; // 8
  cout << obj->sumRegion(1, 1, 2, 2) << endl; // 11
  cout << obj->sumRegion(1, 2, 2, 4) << endl; // 12
  return 0;
}
