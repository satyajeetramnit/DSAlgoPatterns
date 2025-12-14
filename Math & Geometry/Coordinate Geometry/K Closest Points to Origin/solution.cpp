#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
  vector<vector<int>> kClosest(vector<vector<int>> &points, int k) {
    // Max heap: pair <distance_squared, index>
    priority_queue<pair<long, int>> maxHeap;

    for (int i = 0; i < points.size(); ++i) {
      long dist =
          (long)points[i][0] * points[i][0] + (long)points[i][1] * points[i][1];
      maxHeap.push({dist, i});
      if (maxHeap.size() > k) {
        maxHeap.pop();
      }
    }

    vector<vector<int>> result;
    while (!maxHeap.empty()) {
      result.push_back(points[maxHeap.top().second]);
      maxHeap.pop();
    }

    return result;
  }
};

int main() {
  Solution sol;
  vector<vector<int>> points = {{1, 3}, {-2, 2}};
  vector<vector<int>> res = sol.kClosest(points, 1);

  cout << "Test Case 1 Output:" << endl;
  for (const auto &p : res) {
    cout << "[" << p[0] << "," << p[1] << "] ";
  }
  cout << endl; // Expect [-2, 2]

  return 0;
}
