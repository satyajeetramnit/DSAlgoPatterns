#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
public:
  int lastStoneWeightII(vector<int> &stones) {
    int totalSum = accumulate(stones.begin(), stones.end(), 0);
    int target = totalSum / 2;
    vector<bool> dp(target + 1, false);
    dp[0] = true;

    for (int stone : stones) {
      for (int j = target; j >= stone; --j) {
        if (dp[j - stone]) {
          dp[j] = true;
        }
      }
    }

    for (int i = target; i >= 0; --i) {
      if (dp[i]) {
        return totalSum - 2 * i;
      }
    }
    return 0;
  }
};

int main() {
  Solution sol;

  vector<int> stones1 = {2, 7, 4, 1, 8, 1};
  cout << "Test Case 1: " << sol.lastStoneWeightII(stones1) << endl; // Expect 1

  vector<int> stones2 = {31, 26, 33, 21, 40};
  cout << "Test Case 2: " << sol.lastStoneWeightII(stones2) << endl; // Expect 5

  return 0;
}
