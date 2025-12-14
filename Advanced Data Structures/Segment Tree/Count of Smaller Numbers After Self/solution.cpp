#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
  vector<int> bit;
  int n;

  void update(int idx, int val) {
    for (; idx <= n; idx += idx & -idx)
      bit[idx] += val;
  }

  int query(int idx) {
    int sum = 0;
    for (; idx > 0; idx -= idx & -idx)
      sum += bit[idx];
    return sum;
  }

public:
  vector<int> countSmaller(vector<int> &nums) {
    int sz = nums.size();
    vector<int> sortedN = nums;
    sort(sortedN.begin(), sortedN.end());
    // Unique for correct ranking map
    sortedN.erase(unique(sortedN.begin(), sortedN.end()), sortedN.end());

    n = sortedN.size();
    bit.assign(n + 1, 0);
    vector<int> res(sz);

    for (int i = sz - 1; i >= 0; --i) {
      // Rank: index in sorted unique array + 1
      int rank = lower_bound(sortedN.begin(), sortedN.end(), nums[i]) -
                 sortedN.begin() + 1;

      res[i] = query(rank - 1);
      update(rank, 1);
    }
    return res;
  }
};

int main() {
  Solution sol;

  // Test 1: [5,2,6,1] -> [2,1,1,0]
  vector<int> nums1 = {5, 2, 6, 1};
  vector<int> expected1 = {2, 1, 1, 0};
  assert(sol.countSmaller(nums1) == expected1);
  cout << "Test 1 Passed" << endl;

  // Test 2: [-1] -> [0]
  vector<int> nums2 = {-1};
  vector<int> expected2 = {0};
  assert(sol.countSmaller(nums2) == expected2);
  cout << "Test 2 Passed" << endl;

  // Test 3: [-1, -1] -> [0, 0]
  vector<int> nums3 = {-1, -1};
  vector<int> expected3 = {0, 0};
  assert(sol.countSmaller(nums3) == expected3);
  cout << "Test 3 Passed" << endl;

  return 0;
}
