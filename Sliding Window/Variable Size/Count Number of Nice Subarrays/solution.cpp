#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int numberOfSubarrays(vector<int> &nums, int k) {
    return atMost(nums, k) - atMost(nums, k - 1);
  }

private:
  int atMost(vector<int> &nums, int k) {
    int left = 0, res = 0, count = 0;
    for (int right = 0; right < nums.size(); right++) {
      if (nums[right] % 2 != 0) {
        count++;
      }
      while (count > k) {
        if (nums[left] % 2 != 0) {
          count--;
        }
        left++;
      }
      res += right - left + 1;
    }
    return res;
  }
};

int main() {
  Solution sol;
  vector<int> nums1 = {1, 1, 2, 1, 1};
  int k1 = 3;
  cout << "Count 1: " << sol.numberOfSubarrays(nums1, k1)
       << endl; // Expected: 2

  vector<int> nums2 = {2, 4, 6};
  int k2 = 1;
  cout << "Count 2: " << sol.numberOfSubarrays(nums2, k2)
       << endl; // Expected: 0

  return 0;
}
