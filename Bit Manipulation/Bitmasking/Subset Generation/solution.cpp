#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  vector<vector<int>> subsets(vector<int> &nums) {
    int n = nums.size();
    int totalSubsets = 1 << n;
    vector<vector<int>> res;

    for (int mask = 0; mask < totalSubsets; ++mask) {
      vector<int> subset;
      for (int i = 0; i < n; ++i) {
        if ((mask >> i) & 1) {
          subset.push_back(nums[i]);
        }
      }
      res.push_back(subset);
    }

    return res;
  }
};

int main() {
  Solution sol;
  vector<int> nums = {1, 2, 3};
  vector<vector<int>> res = sol.subsets(nums);

  cout << "Test Case 1 (Size should be 8): " << res.size() << endl;

  // Print all subsets
  for (const auto &sub : res) {
    cout << "[";
    for (int i = 0; i < sub.size(); ++i) {
      cout << sub[i] << (i < sub.size() - 1 ? "," : "");
    }
    cout << "] ";
  }
  cout << endl;

  return 0;
}
