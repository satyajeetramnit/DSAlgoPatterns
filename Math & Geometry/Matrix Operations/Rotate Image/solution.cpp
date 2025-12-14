#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  void rotate(vector<vector<int>> &matrix) {
    int n = matrix.size();

    // Transpose
    for (int i = 0; i < n; ++i) {
      for (int j = i; j < n; ++j) {
        swap(matrix[i][j], matrix[j][i]);
      }
    }

    // Reverse rows
    for (int i = 0; i < n; ++i) {
      reverse(matrix[i].begin(), matrix[i].end());
    }
  }
};

int main() {
  Solution sol;
  vector<vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  sol.rotate(matrix);

  cout << "Test Case 1 Output:" << endl;
  for (const auto &row : matrix) {
    cout << "[ ";
    for (int val : row)
      cout << val << " ";
    cout << "]" << endl;
  }
  // Expect:
  // [ 7 4 1 ]
  // [ 8 5 2 ]
  // [ 9 6 3 ]

  return 0;
}
