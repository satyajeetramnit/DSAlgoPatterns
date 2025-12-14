#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int calculateMinimumHP(vector<vector<int>> &dungeon) {
    int m = dungeon.size();
    int n = dungeon[0].size();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, INT_MAX));

    dp[m][n - 1] = 1;
    dp[m - 1][n] = 1;

    for (int i = m - 1; i >= 0; --i) {
      for (int j = n - 1; j >= 0; --j) {
        int need = min(dp[i + 1][j], dp[i][j + 1]) - dungeon[i][j];
        dp[i][j] = max(1, need);
      }
    }

    return dp[0][0];
  }
};

int main() {
  Solution sol;

  vector<vector<int>> dungeon1 = {{-2, -3, 3}, {-5, -10, 1}, {10, 30, -5}};
  cout << "Test Case 1: " << sol.calculateMinimumHP(dungeon1)
       << endl; // Expect 7

  vector<vector<int>> dungeon2 = {{0}};
  cout << "Test Case 2: " << sol.calculateMinimumHP(dungeon2)
       << endl; // Expect 1

  return 0;
}
