#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  // Subsets I
  vector<vector<int>> subsets(vector<int> &nums) {
    vector<vector<int>> res;
    vector<int> path;
    backtrack(nums, 0, path, res);
    return res;
  }

  // Subsets II
  vector<vector<int>> subsetsWithDup(vector<int> &nums) {
    sort(nums.begin(), nums.end()); // Crucial for dedup
    vector<vector<int>> res;
    vector<int> path;
    backtrackWithDup(nums, 0, path, res);
    return res;
  }

private:
  void backtrack(vector<int> &nums, int start, vector<int> &path,
                 vector<vector<int>> &res) {
    res.push_back(path); // Add every valid path

    for (int i = start; i < nums.size(); ++i) {
      path.push_back(nums[i]);
      backtrack(nums, i + 1, path, res);
      path.pop_back();
    }
  }

  void backtrackWithDup(vector<int> &nums, int start, vector<int> &path,
                        vector<vector<int>> &res) {
    res.push_back(path);

    for (int i = start; i < nums.size(); ++i) {
      if (i > start && nums[i] == nums[i - 1])
        continue; // Skip duplicates

      path.push_back(nums[i]);
      backtrackWithDup(nums, i + 1, path, res);
      path.pop_back();
    }
  }
};

void printRes(const vector<vector<int>> &res) {
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

  vector<int> nums1 = {1, 2, 3};
  cout << "Subsets [1,2,3]: " << endl;
  printRes(sol.subsets(nums1));

  vector<int> nums2 = {1, 2, 2};
  cout << "SubsetsWithDup [1,2,2]: " << endl;
  printRes(sol.subsetsWithDup(nums2));

  return 0;
}
