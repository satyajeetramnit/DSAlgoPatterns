#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
  int findKthLargest(vector<int> &nums, int k) {
    priority_queue<int, vector<int>, greater<int>> minHeap;
    for (int num : nums) {
      minHeap.push(num);
      if (minHeap.size() > k) {
        minHeap.pop();
      }
    }
    return minHeap.top();
  }
};

int main() {
  Solution sol;
  vector<int> nums = {3, 2, 1, 5, 6, 4};
  int k = 2;
  cout << "Test Case 1: " << sol.findKthLargest(nums, k) << endl; // Expect 5
  return 0;
}
