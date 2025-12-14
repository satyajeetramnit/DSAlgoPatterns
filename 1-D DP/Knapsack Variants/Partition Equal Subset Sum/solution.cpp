#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
public:
  bool canPartition(vector<int> &nums) {
    int totalSum = accumulate(nums.begin(), nums.end(), 0);

    // If sum is odd, cannot partition into two equal integer subsets
    if (totalSum % 2 != 0)
      return false;

    int target = totalSum / 2;
    vector<bool> dp(target + 1, false);
    dp[0] = true;

    for (int num : nums) {
      for (int j = target; j >= num; --j) {
        if (dp[j - num]) {
          dp[j] = true;
        }
      }
    }

    return dp[target];
  }
};

int main() {
  Solution sol;

  vector<int> nums1 = {1, 5, 11, 5};
  cout << "Test Case 1: " << (sol.canPartition(nums1) ? "True" : "False")
       << endl; // Expect True (11 = 1+5+5)

  vector<int> nums2 = {1, 2, 3, 5};
  cout << "Test Case 2: " << (sol.canPartition(nums2) ? "True" : "False")
       << endl; // Expect False (Sum 11, odd)

  return 0;
}
