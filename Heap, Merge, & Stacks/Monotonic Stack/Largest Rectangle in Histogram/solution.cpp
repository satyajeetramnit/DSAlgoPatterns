#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
public:
  int largestRectangleArea(vector<int> &heights) {
    heights.push_back(0); // Dummy bar to flush stack
    int n = heights.size();
    stack<int> s;
    int maxArea = 0;

    for (int i = 0; i < n; i++) {
      while (!s.empty() && heights[i] < heights[s.top()]) {
        int h = heights[s.top()];
        s.pop();
        int w = s.empty() ? i : i - s.top() - 1;
        maxArea = max(maxArea, h * w);
      }
      s.push(i);
    }

    return maxArea;
  }
};

int main() {
  Solution sol;
  vector<int> heights = {2, 1, 5, 6, 2, 3};
  cout << "Test Case 1: " << sol.largestRectangleArea(heights)
       << endl; // Expect 10
  return 0;
}
