#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int minSubArrayLen(int target, vector<int> &nums) {
    int left = 0;
    int currentSum = 0;
    int minLen = INT_MAX;

    for (int right = 0; right < nums.size(); right++) {
      currentSum += nums[right];

      while (currentSum >= target) {
        minLen = min(minLen, right - left + 1);
        currentSum -= nums[left];
        left++;
      }
    }

    return (minLen == INT_MAX) ? 0 : minLen;
  }
};

int main() {
  Solution sol;
  int target1 = 7;
  vector<int> nums1 = {2, 3, 1, 2, 4, 3};
  cout << "Min Length 1: " << sol.minSubArrayLen(target1, nums1)
       << endl; // Expected: 2

  int target2 = 4;
  vector<int> nums2 = {1, 4, 4};
  cout << "Min Length 2: " << sol.minSubArrayLen(target2, nums2)
       << endl; // Expected: 1

  int target3 = 11;
  vector<int> nums3 = {1, 1, 1, 1, 1, 1, 1, 1};
  cout << "Min Length 3: " << sol.minSubArrayLen(target3, nums3)
       << endl; // Expected: 0

  return 0;
}
