#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int findMin(vector<int> &nums) {
    int left = 0, right = nums.size() - 1;

    while (left < right) {
      int mid = left + (right - left) / 2;
      if (nums[mid] > nums[right]) {
        left = mid + 1;
      } else {
        right = mid;
      }
    }
    return nums[left];
  }
};

int main() {
  Solution sol;
  vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
  cout << "Min: " << sol.findMin(nums) << endl; // Expected: 0
  return 0;
}
