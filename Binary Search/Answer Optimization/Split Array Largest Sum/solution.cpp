#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
public:
  int splitArray(vector<int> &nums, int k) {
    long long left = 0, right = 0;
    for (int n : nums) {
      left = max(left, (long long)n);
      right += n;
    }

    while (left <= right) {
      long long mid = left + (right - left) / 2;
      if (canSplit(nums, k, mid)) {
        right = mid - 1;
      } else {
        left = mid + 1;
      }
    }
    return (int)left;
  }

private:
  bool canSplit(const vector<int> &nums, int k, long long maxSum) {
    int subarrays = 1;
    long long currentSum = 0;

    for (int n : nums) {
      if (currentSum + n > maxSum) {
        subarrays++;
        currentSum = n;
      } else {
        currentSum += n;
      }
    }
    return subarrays <= k;
  }
};

int main() {
  Solution sol;
  vector<int> nums1 = {7, 2, 5, 10, 8};
  int k1 = 2;
  cout << "Min Largest Sum 1: " << sol.splitArray(nums1, k1)
       << endl; // Expected: 18

  vector<int> nums2 = {1, 2, 3, 4, 5};
  int k2 = 2;
  cout << "Min Largest Sum 2: " << sol.splitArray(nums2, k2)
       << endl; // Expected: 9

  return 0;
}
