#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
public:
  int maxSumSubarray(vector<int> &nums, int k) {
    if (nums.size() < k)
      return -1;

    long long currentSum = 0;
    for (int i = 0; i < k; i++) {
      currentSum += nums[i];
    }

    long long maxSum = currentSum;
    for (int i = k; i < nums.size(); i++) {
      currentSum += nums[i] - nums[i - k];
      maxSum = max(maxSum, currentSum);
    }
    return (int)maxSum;
  }
};

int main() {
  Solution sol;
  vector<int> nums1 = {2, 1, 5, 1, 3, 2};
  int k1 = 3;
  cout << "Max Sum 1: " << sol.maxSumSubarray(nums1, k1) << endl; // Expected: 9

  vector<int> nums2 = {2, 3, 4, 1, 5};
  int k2 = 2;
  cout << "Max Sum 2: " << sol.maxSumSubarray(nums2, k2) << endl; // Expected: 7

  return 0;
}
