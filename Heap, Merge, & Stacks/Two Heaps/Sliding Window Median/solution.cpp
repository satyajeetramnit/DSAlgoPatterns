#include <iomanip>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

class Solution {
public:
  vector<double> medianSlidingWindow(vector<int> &nums, int k) {
    multiset<long long> window(nums.begin(), nums.begin() + k);
    auto mid = next(window.begin(), k / 2);
    vector<double> medians;

    for (int i = k;; i++) {
      // Push median
      if (k % 2 == 1)
        medians.push_back((double)*mid);
      else
        medians.push_back(((double)*mid + (double)*prev(mid)) / 2.0);

      if (i == nums.size())
        break;

      // Insert nums[i]
      window.insert(nums[i]);
      if (nums[i] < *mid)
        mid--;

      // Remove nums[i-k]
      if (nums[i - k] < *mid)
        mid++;
      // If removed element is >= mid, iterator doesn't need implicit shift
      // unless it points to the element itself

      // To safely remove the exact element without breaking 'mid' iterator if
      // it points to it: multiset erase can take value, but it erases ALL
      // instances. We need one.
      auto it = window.lower_bound(nums[i - k]);
      if (it == mid)
        mid++; // if we are erasing what mid points to, move mid to next
      window.erase(it);
    }

    return medians;
  }
};

void printVector(const vector<double> &v) {
  cout << "[";
  for (int i = 0; i < v.size(); i++) {
    cout << v[i] << (i < v.size() - 1 ? ", " : "");
  }
  cout << "]" << endl;
}

int main() {
  Solution sol;
  vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
  int k = 3;
  vector<double> result = sol.medianSlidingWindow(nums, k);
  cout << "Test Case 1: ";
  printVector(result); // Expect [1, -1, -1, 3, 5, 6]
  return 0;
}
