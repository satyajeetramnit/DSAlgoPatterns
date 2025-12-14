#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int searchInsert(vector<int> &nums, int target) {
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
    return left;
  }
};

int main() {
  Solution sol;
  vector<int> nums = {1, 3, 5, 6};

  cout << "Insert 5: " << sol.searchInsert(nums, 5) << endl; // Expected: 2
  cout << "Insert 2: " << sol.searchInsert(nums, 2) << endl; // Expected: 1
  cout << "Insert 7: " << sol.searchInsert(nums, 7) << endl; // Expected: 4

  return 0;
}
