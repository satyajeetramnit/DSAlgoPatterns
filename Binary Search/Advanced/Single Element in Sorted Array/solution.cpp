#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int singleNonDuplicate(vector<int> &nums) {
    int left = 0, right = nums.size() - 1;

    while (left < right) {
      int mid = left + (right - left) / 2;
      if (mid % 2 == 1)
        mid--;

      if (nums[mid] == nums[mid + 1]) {
        left = mid + 2;
      } else {
        right = mid;
      }
    }
    return nums[left];
  }
};

int main() {
  Solution sol;
  vector<int> nums1 = {1, 1, 2, 3, 3, 4, 4, 8, 8};
  cout << "Single Element 1: " << sol.singleNonDuplicate(nums1)
       << endl; // Expected: 2

  vector<int> nums2 = {3, 3, 7, 7, 10, 11, 11};
  cout << "Single Element 2: " << sol.singleNonDuplicate(nums2)
       << endl; // Expected: 10

  return 0;
}
