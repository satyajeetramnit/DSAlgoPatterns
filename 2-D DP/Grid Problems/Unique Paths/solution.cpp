#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int uniquePaths(int m, int n) {
    vector<int> dp(n, 1);

    for (int i = 1; i < m; ++i) {
      for (int j = 1; j < n; ++j) {
        dp[j] += dp[j - 1];
      }
    }

    return dp[n - 1];
  }
};

int main() {
  Solution sol;
  cout << "Test Case 1 (m=3, n=7): " << sol.uniquePaths(3, 7)
       << endl; // Expect 28
  cout << "Test Case 2 (m=3, n=2): " << sol.uniquePaths(3, 2)
       << endl; // Expect 3
  cout << "Test Case 3 (m=7, n=3): " << sol.uniquePaths(7, 3)
       << endl; // Expect 28
  cout << "Test Case 4 (m=1, n=1): " << sol.uniquePaths(1, 1)
       << endl; // Expect 1
  return 0;
}
