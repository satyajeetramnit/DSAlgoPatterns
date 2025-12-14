#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int lengthOfLIS(vector<int> &nums) {
    if (nums.empty())
      return 0;

    vector<int> tails;

    for (int num : nums) {
      auto it = lower_bound(tails.begin(), tails.end(), num);
      if (it == tails.end()) {
        tails.push_back(num);
      } else {
        *it = num;
      }
    }

    return tails.size();
  }
};

int main() {
  Solution sol;

  vector<int> nums1 = {10, 9, 2, 5, 3, 7, 101, 18};
  cout << "Test Case 1: " << sol.lengthOfLIS(nums1) << endl; // Expect 4

  vector<int> nums2 = {0, 1, 0, 3, 2, 3};
  cout << "Test Case 2: " << sol.lengthOfLIS(nums2) << endl; // Expect 4

  vector<int> nums3 = {7, 7, 7, 7, 7, 7, 7};
  cout << "Test Case 3: " << sol.lengthOfLIS(nums3) << endl; // Expect 1

  return 0;
}
