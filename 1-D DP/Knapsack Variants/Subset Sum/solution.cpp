#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  bool isSubsetSum(vector<int> &nums, int target) {
    int n = nums.size();
    vector<bool> dp(target + 1, false);

    dp[0] = true; // Sum of 0 is always possible

    for (int num : nums) {
      // Iterate backwards to avoid using the same element multiple times
      // for the current iteration's contribution
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

  vector<int> nums1 = {3, 34, 4, 12, 5, 2};
  int target1 = 9;
  cout << "Test Case 1 (Target 9): "
       << (sol.isSubsetSum(nums1, target1) ? "True" : "False")
       << endl; // Expect True (4+5)

  int target2 = 30;
  cout << "Test Case 2 (Target 30): "
       << (sol.isSubsetSum(nums1, target2) ? "True" : "False")
       << endl; // Expect False

  vector<int> nums2 = {1, 2, 3};
  int target3 = 6;
  cout << "Test Case 3 (Target 6): "
       << (sol.isSubsetSum(nums2, target3) ? "True" : "False")
       << endl; // Expect True (1+2+3)

  return 0;
}
