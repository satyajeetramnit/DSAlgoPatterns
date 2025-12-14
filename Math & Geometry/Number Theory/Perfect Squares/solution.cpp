#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int numSquares(int n) {
    vector<int> dp(n + 1, n); // Initialize with max possible (1+1+...+1)
    dp[0] = 0;

    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j * j <= i; ++j) {
        dp[i] = min(dp[i], dp[i - j * j] + 1);
      }
    }
    return dp[n];
  }
};

int main() {
  Solution sol;
  cout << "Test Case 1 (12): " << sol.numSquares(12)
       << endl; // Expect 3 (4+4+4)
  cout << "Test Case 2 (13): " << sol.numSquares(13) << endl; // Expect 2 (4+9)
  return 0;
}
