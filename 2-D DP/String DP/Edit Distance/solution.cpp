#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  int minDistance(string word1, string word2) {
    int m = word1.length();
    int n = word2.length();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    for (int i = 0; i <= m; ++i)
      dp[i][0] = i;
    for (int j = 0; j <= n; ++j)
      dp[0][j] = j;

    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= n; ++j) {
        if (word1[i - 1] == word2[j - 1]) {
          dp[i][j] = dp[i - 1][j - 1];
        } else {
          dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
        }
      }
    }

    return dp[m][n];
  }
};

int main() {
  Solution sol;
  cout << "Test Case 1: " << sol.minDistance("horse", "ros")
       << endl; // Expect 3
  cout << "Test Case 2: " << sol.minDistance("intention", "execution")
       << endl; // Expect 5
  return 0;
}
