#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
public:
  int findTargetSumWays(vector<int> &nums, int target) {
    long long totalSum = accumulate(nums.begin(), nums.end(), 0LL);

    // Check for validity
    // Logic: sum(P) - sum(N) = target
    // sum(P) + sum(N) = totalSum
    // 2 * sum(P) = target + totalSum
    // sum(P) = (target + totalSum) / 2
    if ((totalSum + target) < 0 || (totalSum + target) % 2 != 0) {
      return 0;
    }

    int subsetTarget = (totalSum + target) / 2;
    vector<int> dp(subsetTarget + 1, 0);
    dp[0] = 1;

    for (int num : nums) {
      for (int j = subsetTarget; j >= num; --j) {
        dp[j] += dp[j - num];
      }
    }

    return dp[subsetTarget];
  }
};

int main() {
  Solution sol;

  vector<int> nums1 = {1, 1, 1, 1, 1};
  int target1 = 3;
  cout << "Test Case 1 (Target 3): " << sol.findTargetSumWays(nums1, target1)
       << endl; // Expect 5

  vector<int> nums2 = {1};
  int target2 = 1;
  cout << "Test Case 2 (Target 1): " << sol.findTargetSumWays(nums2, target2)
       << endl; // Expect 1

  return 0;
}
