#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int robLinear(vector<int> &nums, int start, int end) {
    int prev2 = 0, prev1 = 0;
    for (int i = start; i <= end; ++i) {
      int current = max(prev1, prev2 + nums[i]);
      prev2 = prev1;
      prev1 = current;
    }
    return prev1;
  }

  int rob1(vector<int> &nums) {
    if (nums.empty())
      return 0;
    return robLinear(nums, 0, nums.size() - 1);
  }

  int rob2(vector<int> &nums) {
    int n = nums.size();
    if (n == 0)
      return 0;
    if (n == 1)
      return nums[0];
    return max(robLinear(nums, 0, n - 2), robLinear(nums, 1, n - 1));
  }
};

int main() {
  Solution sol;

  // Robber I Tests
  vector<int> nums1 = {1, 2, 3, 1};
  cout << "Robber I - Test 1: " << sol.rob1(nums1) << endl; // Expect 4
  vector<int> nums2 = {2, 7, 9, 3, 1};
  cout << "Robber I - Test 2: " << sol.rob1(nums2) << endl; // Expect 12

  // Robber II Tests
  vector<int> nums3 = {2, 3, 2};
  cout << "Robber II - Test 3: " << sol.rob2(nums3)
       << endl; // Expect 3 (2 or 2, can't take both adjacents, 3 is adj to
                // first and last) Wait, 2,3,2. adjacents: (2,3), (3,2), (2,2).
                // If input is [2, 3, 2].
                // remove last -> [2, 3] -> max is 3.
                // remove first -> [3, 2] -> max is 3.
                // Correct answer is 3.
  vector<int> nums4 = {1, 2, 3, 1};
  cout << "Robber II - Test 4: " << sol.rob2(nums4) << endl; // Expect 4

  return 0;
}
