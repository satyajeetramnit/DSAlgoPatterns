#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int jump(vector<int> &nums) {
    int n = nums.size();
    if (n <= 1)
      return 0;

    int jumps = 0;
    int current_end = 0;
    int farthest = 0;

    for (int i = 0; i < n - 1; i++) {
      farthest = max(farthest, i + nums[i]);

      if (i == current_end) {
        jumps++;
        current_end = farthest;

        if (current_end >= n - 1)
          break;
      }
    }
    return jumps;
  }
};

int main() {
  Solution sol;
  vector<int> nums1 = {2, 3, 1, 1, 4}; // Expect 2
  cout << "Test Case 1: " << sol.jump(nums1) << endl;

  vector<int> nums2 = {2, 3, 0, 1, 4}; // Expect 2
  cout << "Test Case 2: " << sol.jump(nums2) << endl;

  return 0;
}
