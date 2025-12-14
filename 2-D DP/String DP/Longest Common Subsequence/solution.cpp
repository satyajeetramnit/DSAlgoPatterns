#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  int longestCommonSubsequence(string text1, string text2) {
    int m = text1.length();
    int n = text2.length();

    if (m < n)
      return longestCommonSubsequence(text2, text1);

    vector<int> dp(n + 1, 0);

    for (int i = 1; i <= m; ++i) {
      int prev = 0;
      for (int j = 1; j <= n; ++j) {
        int temp = dp[j];
        if (text1[i - 1] == text2[j - 1]) {
          dp[j] = 1 + prev;
        } else {
          dp[j] = max(dp[j], dp[j - 1]);
        }
        prev = temp;
      }
    }

    return dp[n];
  }
};

int main() {
  Solution sol;
  cout << "Test Case 1: " << sol.longestCommonSubsequence("abcde", "ace")
       << endl; // Expect 3
  cout << "Test Case 2: " << sol.longestCommonSubsequence("abc", "abc")
       << endl; // Expect 3
  cout << "Test Case 3: " << sol.longestCommonSubsequence("abc", "def")
       << endl; // Expect 0
  return 0;
}
