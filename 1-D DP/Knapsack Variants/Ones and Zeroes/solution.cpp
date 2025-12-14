#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  int findMaxForm(vector<string> &strs, int m, int n) {
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (const string &s : strs) {
      int zeros = 0, ones = 0;
      for (char c : s) {
        if (c == '0')
          zeros++;
        else
          ones++;
      }

      for (int i = m; i >= zeros; --i) {
        for (int j = n; j >= ones; --j) {
          dp[i][j] = max(dp[i][j], 1 + dp[i - zeros][j - ones]);
        }
      }
    }

    return dp[m][n];
  }
};

int main() {
  Solution sol;

  vector<string> strs1 = {"10", "0001", "111001", "1", "0"};
  int m1 = 5, n1 = 3;
  cout << "Test Case 1: " << sol.findMaxForm(strs1, m1, n1) << endl; // Expect 4

  vector<string> strs2 = {"10", "0", "1"};
  int m2 = 1, n2 = 1;
  cout << "Test Case 2: " << sol.findMaxForm(strs2, m2, n2) << endl; // Expect 2

  return 0;
}
