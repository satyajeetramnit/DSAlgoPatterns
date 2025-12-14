#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  // Permutations I
  vector<vector<int>> permute(vector<int> &nums) {
    vector<vector<int>> res;
    vector<int> path;
    vector<bool> used(nums.size(), false);
    backtrack(nums, path, used, res);
    return res;
  }

  // Permutations II
  vector<vector<int>> permuteUnique(vector<int> &nums) {
    sort(nums.begin(), nums.end()); // Crucial for duplicate handling
    vector<vector<int>> res;
    vector<int> path;
    vector<bool> used(nums.size(), false);
    backtrackUnique(nums, path, used, res);
    return res;
  }

private:
  void backtrack(vector<int> &nums, vector<int> &path, vector<bool> &used,
                 vector<vector<int>> &res) {
    if (path.size() == nums.size()) {
      res.push_back(path);
      return;
    }

    for (int i = 0; i < nums.size(); ++i) {
      if (used[i])
        continue;

      used[i] = true;
      path.push_back(nums[i]);
      backtrack(nums, path, used, res);
      path.pop_back();
      used[i] = false;
    }
  }

  void backtrackUnique(vector<int> &nums, vector<int> &path, vector<bool> &used,
                       vector<vector<int>> &res) {
    if (path.size() == nums.size()) {
      res.push_back(path);
      return;
    }

    for (int i = 0; i < nums.size(); ++i) {
      if (used[i])
        continue;
      // Handle duplicates: skip if same as prev and prev was NOT used
      // (meaning we started a new branch with a duplicate value at the same
      // level)
      if (i > 0 && nums[i] == nums[i - 1] && !used[i - 1])
        continue;

      used[i] = true;
      path.push_back(nums[i]);
      backtrackUnique(nums, path, used, res);
      path.pop_back();
      used[i] = false;
    }
  }
};

void printResult(const vector<vector<int>> &res) {
  cout << "[";
  for (size_t i = 0; i < res.size(); ++i) {
    cout << "[";
    for (size_t j = 0; j < res[i].size(); ++j) {
      cout << res[i][j] << (j < res[i].size() - 1 ? "," : "");
    }
    cout << "]" << (i < res.size() - 1 ? "," : "");
  }
  cout << "]" << endl;
}

int main() {
  Solution sol;

  // Permutations I
  vector<int> nums1 = {1, 2, 3};
  vector<vector<int>> res1 = sol.permute(nums1);
  cout << "Permute [1,2,3]: ";
  printResult(res1);

  // Permutations II
  vector<int> nums2 = {1, 1, 2};
  vector<vector<int>> res2 = sol.permuteUnique(nums2);
  cout << "PermuteUnique [1,1,2]: ";
  printResult(res2); // Expected: unique permutations only

  return 0;
}
