#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int findDuplicate(vector<int> &nums) {
    int slow = 0;
    int fast = 0;

    while (true) {
      slow = nums[slow];
      fast = nums[nums[fast]];
      if (slow == fast)
        break;
    }

    slow = 0;
    while (slow != fast) {
      slow = nums[slow];
      fast = nums[fast];
    }
    return slow;
  }
};

int main() {
  Solution sol;
  vector<int> nums = {1, 3, 4, 2, 2};
  cout << "Duplicate: " << sol.findDuplicate(nums) << endl;
  return 0;
}
