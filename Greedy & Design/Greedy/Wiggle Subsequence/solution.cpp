#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int wiggleMaxLength(vector<int> &nums) {
    if (nums.empty())
      return 0;
    int up = 1;
    int down = 1;

    for (int i = 1; i < nums.size(); i++) {
      if (nums[i] > nums[i - 1]) {
        up = down + 1;
      } else if (nums[i] < nums[i - 1]) {
        down = up + 1;
      }
    }
    return max(up, down);
  }
};

int main() {
  Solution sol;
  vector<int> n1 = {1, 7, 4, 9, 2, 5};
  cout << "Test Case 1: " << sol.wiggleMaxLength(n1) << endl; // Expect 6

  vector<int> n2 = {1, 17, 5, 10, 13, 15, 10, 5, 16, 8};
  cout << "Test Case 2: " << sol.wiggleMaxLength(n2) << endl; // Expect 7

  vector<int> n3 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  cout << "Test Case 3: " << sol.wiggleMaxLength(n3) << endl; // Expect 2
  return 0;
}
