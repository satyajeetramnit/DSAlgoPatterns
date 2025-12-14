#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  // Combination Sum I
  vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
    vector<vector<int>> res;
    vector<int> path;
    backtrack1(candidates, target, 0, path, res);
    return res;
  }

  // Combination Sum II
  vector<vector<int>> combinationSum2(vector<int> &candidates, int target) {
    sort(candidates.begin(), candidates.end()); // Required for dedup
    vector<vector<int>> res;
    vector<int> path;
    backtrack2(candidates, target, 0, path, res);
    return res;
  }

private:
  void backtrack1(vector<int> &candidates, int target, int start,
                  vector<int> &path, vector<vector<int>> &res) {
    if (target == 0) {
      res.push_back(path);
      return;
    }
    if (target < 0)
      return;

    for (int i = start; i < candidates.size(); ++i) {
      path.push_back(candidates[i]);
      // Stay at i for unlimited usage
      backtrack1(candidates, target - candidates[i], i, path, res);
      path.pop_back();
    }
  }

  void backtrack2(vector<int> &candidates, int target, int start,
                  vector<int> &path, vector<vector<int>> &res) {
    if (target == 0) {
      res.push_back(path);
      return;
    }
    if (target < 0)
      return;

    for (int i = start; i < candidates.size(); ++i) {
      // Skip duplicates
      if (i > start && candidates[i] == candidates[i - 1])
        continue;

      path.push_back(candidates[i]);
      // Move to i + 1 for single usage
      backtrack2(candidates, target - candidates[i], i + 1, path, res);
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

  vector<int> c1 = {2, 3, 6, 7};
  int t1 = 7;
  cout << "Combination Sum I [2,3,6,7] t=7: " << endl;
  printRes(sol.combinationSum(c1, t1));

  vector<int> c2 = {10, 1, 2, 7, 6, 1, 5};
  int t2 = 8;
  cout << "Combination Sum II [10,1,2,7,6,1,5] t=8: " << endl;
  printRes(sol.combinationSum2(c2, t2));

  return 0;
}
