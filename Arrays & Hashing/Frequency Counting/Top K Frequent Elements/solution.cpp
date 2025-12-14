#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
  vector<int> topKFrequent(vector<int> &nums, int k) {
    unordered_map<int, int> count;
    for (int n : nums)
      count[n]++;

    vector<vector<int>> bucket(nums.size() + 1);
    for (auto &p : count) {
      bucket[p.second].push_back(p.first);
    }

    vector<int> res;
    for (int i = bucket.size() - 1; i >= 0; i--) {
      for (int n : bucket[i]) {
        res.push_back(n);
        if (res.size() == k)
          return res;
      }
    }
    return res;
  }
};

int main() {
  Solution sol;
  vector<int> nums = {1, 1, 1, 2, 2, 3};
  int k = 2;
  vector<int> result = sol.topKFrequent(nums, k);
  cout << "[";
  for (int i = 0; i < result.size(); ++i) {
    cout << result[i] << (i < result.size() - 1 ? ", " : "");
  }
  cout << "]" << endl;
  return 0;
}
