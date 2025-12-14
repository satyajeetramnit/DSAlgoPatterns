#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  vector<vector<int>> threeSum(vector<int> &nums) {
    vector<vector<int>> res;
    sort(nums.begin(), nums.end());

    for (int i = 0; i < nums.size(); i++) {
      if (nums[i] > 0)
        break;
      if (i > 0 && nums[i] == nums[i - 1])
        continue;

      int l = i + 1, r = nums.size() - 1;
      while (l < r) {
        int sum = nums[i] + nums[l] + nums[r];
        if (sum > 0) {
          r--;
        } else if (sum < 0) {
          l++;
        } else {
          res.push_back({nums[i], nums[l], nums[r]});
          l++;
          r--;
          while (l < r && nums[l] == nums[l - 1])
            l++;
        }
      }
    }
    return res;
  }
};

int main() {
  Solution sol;
  vector<int> nums = {-1, 0, 1, 2, -1, -4};
  vector<vector<int>> result = sol.threeSum(nums);
  cout << "[";
  for (int i = 0; i < result.size(); ++i) {
    cout << "[";
    for (int j = 0; j < result[i].size(); ++j) {
      cout << result[i][j] << (j < result[i].size() - 1 ? "," : "");
    }
    cout << "]" << (i < result.size() - 1 ? "," : "");
  }
  cout << "]" << endl;
  return 0;
}
