#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  void sortColors(vector<int> &nums) {
    int low = 0, mid = 0, high = nums.size() - 1;

    while (mid <= high) {
      if (nums[mid] == 0) {
        swap(nums[mid], nums[low]);
        low++;
        mid++;
      } else if (nums[mid] == 1) {
        mid++;
      } else {
        swap(nums[mid], nums[high]);
        high--;
      }
    }
  }
};

int main() {
  Solution sol;
  vector<int> nums = {2, 0, 2, 1, 1, 0};
  sol.sortColors(nums);

  cout << "[";
  for (int i = 0; i < nums.size(); ++i) {
    cout << nums[i] << (i < nums.size() - 1 ? "," : "");
  }
  cout << "]" << endl; // Expected: [0,0,1,1,2,2]
  return 0;
}
