#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  vector<int> getSubarrayBeauty(vector<int> &nums, int k, int x) {
    int count[101] = {0}; // Offset by 50. Index 0 is -50, 50 is 0.
    int n = nums.size();
    vector<int> result;

    for (int i = 0; i < k; i++) {
      count[nums[i] + 50]++;
    }

    result.push_back(findXth(count, x));

    for (int i = k; i < n; i++) {
      count[nums[i] + 50]++;
      count[nums[i - k] + 50]--;
      result.push_back(findXth(count, x));
    }
    return result;
  }

private:
  int findXth(int count[], int x) {
    int currentCount = 0;
    // Check only negative numbers: -50 to -1
    // Indices 0 to 49 corresponds to -50 to -1
    for (int i = 0; i < 50; i++) {
      currentCount += count[i];
      if (currentCount >= x) {
        return i - 50;
      }
    }
    return 0;
  }
};

int main() {
  Solution sol;
  vector<int> nums1 = {1, -1, -3, -2, 3};
  int k1 = 3, x1 = 2;
  vector<int> res1 = sol.getSubarrayBeauty(nums1, k1, x1);
  cout << "Beauty 1: ";
  for (int b : res1)
    cout << b << " "; // Expected: -1 -2 -2
  cout << endl;

  vector<int> nums2 = {-1, -2, -3};
  int k2 = 2, x2 = 1;
  vector<int> res2 = sol.getSubarrayBeauty(nums2, k2, x2);
  cout << "Beauty 2: ";
  for (int b : res2)
    cout << b << " "; // Expected: -2 -3
  cout << endl;

  return 0;
}
