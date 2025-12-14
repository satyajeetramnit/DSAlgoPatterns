#include <deque>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  vector<int> maxSlidingWindow(vector<int> &nums, int k) {
    deque<int> dq;
    vector<int> res;
    for (int i = 0; i < nums.size(); ++i) {
      if (!dq.empty() && dq.front() == i - k) {
        dq.pop_front();
      }
      while (!dq.empty() && nums[dq.back()] < nums[i]) {
        dq.pop_back();
      }
      dq.push_back(i);
      if (i >= k - 1) {
        res.push_back(nums[dq.front()]);
      }
    }
    return res;
  }
};

int main() {
  Solution sol;
  vector<int> nums1 = {1, 3, -1, -3, 5, 3, 6, 7};
  int k1 = 3;
  vector<int> res1 = sol.maxSlidingWindow(nums1, k1);
  cout << "Max Window 1: ";
  for (int x : res1)
    cout << x << " "; // Expected: 3 3 5 5 6 7
  cout << endl;

  vector<int> nums2 = {1};
  int k2 = 1;
  vector<int> res2 = sol.maxSlidingWindow(nums2, k2);
  cout << "Max Window 2: ";
  for (int x : res2)
    cout << x << " "; // Expected: 1
  cout << endl;

  return 0;
}
