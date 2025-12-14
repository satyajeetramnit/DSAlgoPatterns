#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int maxProduct(vector<int> &nums) {
    int res = *max_element(nums.begin(), nums.end());
    int curMin = 1, curMax = 1;

    for (int n : nums) {
      if (n == 0) {
        curMin = 1;
        curMax = 1;
        continue;
      }
      int tmp = curMax * n;
      curMax = max({n * curMax, n * curMin, n});
      curMin = min({tmp, n * curMin, n});
      res = max(res, curMax);
    }
    return res;
  }
};

int main() {
  Solution sol;
  vector<int> nums = {2, 3, -2, 4};
  int result = sol.maxProduct(nums);
  cout << result << endl;
  return 0;
}
