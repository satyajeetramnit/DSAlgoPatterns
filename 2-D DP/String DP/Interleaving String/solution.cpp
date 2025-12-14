#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  bool isInterleave(string s1, string s2, string s3) {
    int m = s1.length(), n = s2.length(), k = s3.length();
    if (m + n != k)
      return false;

    vector<bool> dp(n + 1, false);
    dp[0] = true;

    for (int j = 1; j <= n; ++j) {
      dp[j] = dp[j - 1] && (s2[j - 1] == s3[j - 1]);
    }

    for (int i = 1; i <= m; ++i) {
      dp[0] = dp[0] && (s1[i - 1] == s3[i - 1]);
      for (int j = 1; j <= n; ++j) {
        bool fromTop = dp[j] && (s1[i - 1] == s3[i + j - 1]);
        bool fromLeft = dp[j - 1] && (s2[j - 1] == s3[i + j - 1]);
        dp[j] = fromTop || fromLeft;
      }
    }

    return dp[n];
  }
};

int main() {
  Solution sol;
  cout << "Test Case 1: "
       << (sol.isInterleave("aabcc", "dbbca", "aadbbcbcac") ? "True" : "False")
       << endl; // Expect True
  cout << "Test Case 2: "
       << (sol.isInterleave("aabcc", "dbbca", "aadbbbaccc") ? "True" : "False")
       << endl; // Expect False
  return 0;
}
