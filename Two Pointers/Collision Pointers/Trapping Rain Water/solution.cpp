#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int trap(vector<int> &height) {
    if (height.empty())
      return 0;
    int left = 0, right = height.size() - 1;
    int leftMax = height[left], rightMax = height[right];
    int res = 0;

    while (left < right) {
      if (leftMax < rightMax) {
        left++;
        leftMax = max(leftMax, height[left]);
        res += leftMax - height[left];
      } else {
        right--;
        rightMax = max(rightMax, height[right]);
        res += rightMax - height[right];
      }
    }
    return res;
  }
};

int main() {
  Solution sol;
  vector<int> height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
  cout << sol.trap(height) << endl;
  return 0;
}
