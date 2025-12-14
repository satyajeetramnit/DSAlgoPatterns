#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int maxCoins(vector<int> &nums) {
    vector<int> paddedNums;
    paddedNums.push_back(1);
    for (int x : nums)
      paddedNums.push_back(x);
    paddedNums.push_back(1);

    int n = paddedNums.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int len = 1; len <= nums.size(); ++len) {
      for (int left = 0; left < n - len - 1; ++left) {
        int right = left + len + 1;
        for (int k = left + 1; k < right; ++k) {
          dp[left][right] =
              max(dp[left][right],
                  paddedNums[left] * paddedNums[k] * paddedNums[right] +
                      dp[left][k] + dp[k][right]);
        }
      }
    }

    return dp[0][n - 1];
  }
};

int main() {
  Solution sol;

  vector<int> nums1 = {3, 1, 5, 8};
  cout << "Test Case 1: " << sol.maxCoins(nums1) << endl; // Expect 167

  vector<int> nums2 = {1, 5};
  cout << "Test Case 2: " << sol.maxCoins(nums2) << endl; // Expect 10

  return 0;
}
