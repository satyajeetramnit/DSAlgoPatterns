#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  vector<int> productExceptSelf(vector<int> &nums) {
    int n = nums.size();
    vector<int> res(n, 1);

    int prefix = 1;
    for (int i = 0; i < n; i++) {
      res[i] = prefix;
      prefix *= nums[i];
    }

    int postfix = 1;
    for (int i = n - 1; i >= 0; i--) {
      res[i] *= postfix;
      postfix *= nums[i];
    }

    return res;
  }
};

int main() {
  Solution sol;
  vector<int> nums = {1, 2, 3, 4};
  vector<int> result = sol.productExceptSelf(nums);
  cout << "[";
  for (int i = 0; i < result.size(); ++i) {
    cout << result[i] << (i < result.size() - 1 ? ", " : "");
  }
  cout << "]" << endl;
  return 0;
}
