#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
public:
  int waysToSplitArray(vector<int> &nums) {
    long long totalSum = 0;
    for (int n : nums)
      totalSum += n;

    long long leftSum = 0;
    int count = 0;
    for (int i = 0; i < nums.size() - 1; i++) {
      leftSum += nums[i];
      long long rightSum = totalSum - leftSum;
      if (leftSum >= rightSum) {
        count++;
      }
    }
    return count;
  }
};

int main() {
  Solution sol;
  vector<int> nums = {10, 4, -8, 7};
  int result = sol.waysToSplitArray(nums);
  cout << result << endl;
  return 0;
}
