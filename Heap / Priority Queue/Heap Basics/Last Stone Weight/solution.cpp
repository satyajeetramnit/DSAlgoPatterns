#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
  int lastStoneWeight(vector<int> &stones) {
    priority_queue<int> maxHeap(stones.begin(), stones.end());

    while (maxHeap.size() > 1) {
      int y = maxHeap.top();
      maxHeap.pop();
      int x = maxHeap.top();
      maxHeap.pop();
      if (x != y) {
        maxHeap.push(y - x);
      }
    }

    return maxHeap.empty() ? 0 : maxHeap.top();
  }
};

int main() {
  Solution sol;
  vector<int> stones = {2, 7, 4, 1, 8, 1};
  cout << "Test Case 1: " << sol.lastStoneWeight(stones) << endl; // Expect 1
  return 0;
}
