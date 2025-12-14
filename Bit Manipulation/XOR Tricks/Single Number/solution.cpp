#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
public:
  // Single Number I
  int singleNumber(vector<int> &nums) {
    int res = 0;
    for (int n : nums)
      res ^= n;
    return res;
  }

  // Single Number II
  int singleNumberII(vector<int> &nums) {
    int ones = 0, twos = 0;
    for (int num : nums) {
      ones = (ones ^ num) & ~twos;
      twos = (twos ^ num) & ~ones;
    }
    return ones;
  }

  // Single Number III
  vector<int> singleNumberIII(vector<int> &nums) {
    long long diff = 0;
    for (int n : nums)
      diff ^= n;

    diff &= -diff;

    vector<int> res(2, 0);
    for (int n : nums) {
      if (n & diff)
        res[0] ^= n;
      else
        res[1] ^= n;
    }
    return res;
  }
};

int main() {
  Solution sol;

  // I
  vector<int> nums1 = {2, 2, 1};
  cout << "Single Number I (2,2,1): " << sol.singleNumber(nums1) << endl; // 1

  // II
  vector<int> nums2 = {2, 2, 3, 2};
  cout << "Single Number II (2,2,3,2): " << sol.singleNumberII(nums2)
       << endl; // 3

  // III
  vector<int> nums3 = {1, 2, 1, 3, 2, 5};
  vector<int> res3 = sol.singleNumberIII(nums3);
  cout << "Single Number III (1,2,1,3,2,5): " << res3[0] << ", " << res3[1]
       << endl; // 3, 5 (order varies)

  return 0;
}
