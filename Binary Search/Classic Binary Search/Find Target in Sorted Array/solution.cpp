#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int search(vector<int> &nums, int target) {
    int left = 0, right = nums.size() - 1;
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (nums[mid] == target)
        return mid;
      if (nums[mid] < target)
        left = mid + 1;
      else
        right = mid - 1;
    }
    return -1;
  }
};

int main() {
  Solution sol;
  vector<int> nums = {-1, 0, 3, 5, 9, 12};
  int target = 9;
  cout << "Index of " << target << ": " << sol.search(nums, target)
       << endl; // Expected: 4

  target = 2;
  cout << "Index of " << target << ": " << sol.search(nums, target)
       << endl; // Expected: -1
  return 0;
}
