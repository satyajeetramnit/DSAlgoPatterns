#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int longestSubarray(vector<int> &nums, int limit) {
    deque<int> maxD, minD;
    int left = 0, res = 0;

    for (int right = 0; right < nums.size(); ++right) {
      while (!maxD.empty() && nums[maxD.back()] <= nums[right])
        maxD.pop_back();
      while (!minD.empty() && nums[minD.back()] >= nums[right])
        minD.pop_back();

      maxD.push_back(right);
      minD.push_back(right);

      while (nums[maxD.front()] - nums[minD.front()] > limit) {
        left++;
        if (maxD.front() < left)
          maxD.pop_front();
        if (minD.front() < left)
          minD.pop_front();
      }
      res = max(res, right - left + 1);
    }
    return res;
  }
};

int main() {
  Solution sol;
  vector<int> nums1 = {8, 2, 4, 7};
  int limit1 = 4;
  cout << "Longest 1: " << sol.longestSubarray(nums1, limit1)
       << endl; // Expected: 2

  vector<int> nums2 = {10, 1, 2, 4, 7, 2};
  int limit2 = 5;
  cout << "Longest 2: " << sol.longestSubarray(nums2, limit2)
       << endl; // Expected: 4

  return 0;
}
