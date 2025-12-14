#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int nthUglyNumber(int n) {
    vector<int> dp(n);
    dp[0] = 1;
    int p2 = 0, p3 = 0, p5 = 0;

    for (int i = 1; i < n; i++) {
      int next2 = dp[p2] * 2;
      int next3 = dp[p3] * 3;
      int next5 = dp[p5] * 5;

      dp[i] = min({next2, next3, next5});

      if (dp[i] == next2)
        p2++;
      if (dp[i] == next3)
        p3++;
      if (dp[i] == next5)
        p5++;
    }

    return dp[n - 1];
  }
};

int main() {
  Solution sol;
  cout << "Test Case 1 (n=10): " << sol.nthUglyNumber(10) << endl; // Expect 12
  cout << "Test Case 2 (n=1): " << sol.nthUglyNumber(1) << endl;   // Expect 1
  return 0;
}
