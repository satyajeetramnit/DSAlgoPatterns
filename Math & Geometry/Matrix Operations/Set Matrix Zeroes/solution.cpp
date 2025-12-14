#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  void setZeroes(vector<vector<int>> &matrix) {
    int m = matrix.size();
    int n = matrix[0].size();
    bool col0 = false;

    for (int i = 0; i < m; ++i) {
      if (matrix[i][0] == 0)
        col0 = true;
      for (int j = 1; j < n; ++j) {
        if (matrix[i][j] == 0) {
          matrix[i][0] = 0;
          matrix[0][j] = 0;
        }
      }
    }

    for (int i = m - 1; i >= 0; --i) {
      for (int j = n - 1; j >= 1; --j) {
        if (matrix[i][0] == 0 || matrix[0][j] == 0) {
          matrix[i][j] = 0;
        }
      }
      if (col0)
        matrix[i][0] = 0;
    }
  }
};

int main() {
  Solution sol;
  vector<vector<int>> matrix = {{1, 1, 1}, {1, 0, 1}, {1, 1, 1}};
  sol.setZeroes(matrix);

  cout << "Test Case 1 Output:" << endl;
  for (const auto &row : matrix) {
    cout << "[ ";
    for (int val : row)
      cout << val << " ";
    cout << "]" << endl;
  }
  // Expect: [[1,0,1], [0,0,0], [1,0,1]]

  return 0;
}
