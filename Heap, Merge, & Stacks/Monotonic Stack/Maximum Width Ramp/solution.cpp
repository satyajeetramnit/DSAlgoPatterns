#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
public:
  int maxWidthRamp(vector<int> &nums) {
    int n = nums.size();
    stack<int> s;

    for (int i = 0; i < n; i++) {
      if (s.empty() || nums[s.top()] > nums[i]) {
        s.push(i);
      }
    }

    int maxWidth = 0;
    for (int j = n - 1; j >= 0; j--) {
      while (!s.empty() && nums[s.top()] <= nums[j]) {
        maxWidth = max(maxWidth, j - s.top());
        s.pop();
      }
    }

    return maxWidth;
  }
};

int main() {
  Solution sol;
  vector<int> nums = {6, 0, 8, 2, 1, 5};
  cout << "Test Case 1: " << sol.maxWidthRamp(nums) << endl; // Expect 4
  return 0;
}
