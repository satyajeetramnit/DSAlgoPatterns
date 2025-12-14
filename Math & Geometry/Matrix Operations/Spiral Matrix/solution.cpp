#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  vector<int> spiralOrder(vector<vector<int>> &matrix) {
    vector<int> res;
    if (matrix.empty())
      return res;

    int top = 0, bottom = matrix.size() - 1;
    int left = 0, right = matrix[0].size() - 1;

    while (top <= bottom && left <= right) {
      for (int i = left; i <= right; ++i)
        res.push_back(matrix[top][i]);
      top++;

      for (int i = top; i <= bottom; ++i)
        res.push_back(matrix[i][right]);
      right--;

      if (top <= bottom) {
        for (int i = right; i >= left; --i)
          res.push_back(matrix[bottom][i]);
        bottom--;
      }

      if (left <= right) {
        for (int i = bottom; i >= top; --i)
          res.push_back(matrix[i][left]);
        left++;
      }
    }

    return res;
  }
};

int main() {
  Solution sol;
  vector<vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  vector<int> res = sol.spiralOrder(matrix);

  cout << "Test Case 1 Output: ";
  for (int val : res)
    cout << val << " ";
  cout << endl; // Expect 1 2 3 6 9 8 7 4 5

  return 0;
}
