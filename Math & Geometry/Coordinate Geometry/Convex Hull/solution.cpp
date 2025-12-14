#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int cross_product(vector<int> &o, vector<int> &a, vector<int> &b) {
    return (a[0] - o[0]) * (b[1] - o[1]) - (a[1] - o[1]) * (b[0] - o[0]);
  }

  vector<vector<int>> outerTrees(vector<vector<int>> &trees) {
    int n = trees.size();
    if (n <= 1)
      return trees;

    sort(trees.begin(), trees.end(),
         [](const vector<int> &a, const vector<int> &b) {
           return a[0] < b[0] || (a[0] == b[0] && a[1] < b[1]);
         });

    vector<vector<int>> hull;

    // Lower
    for (const auto &p : trees) {
      while (hull.size() >= 2 &&
             cross_product(hull[hull.size() - 2], hull.back(),
                           const_cast<vector<int> &>(p)) < 0) {
        hull.pop_back();
      }
      hull.push_back(p);
    }

    // Upper
    int lower_size = hull.size();
    for (int i = n - 2; i >= 0; --i) {
      while (hull.size() > lower_size &&
             cross_product(hull[hull.size() - 2], hull.back(), trees[i]) < 0) {
        hull.pop_back();
      }
      hull.push_back(trees[i]);
    }

    hull.pop_back();

    // Unique sort
    sort(hull.begin(), hull.end());
    hull.erase(unique(hull.begin(), hull.end()), hull.end());

    return hull;
  }
};

int main() {
  Solution sol;
  vector<vector<int>> points = {{1, 1}, {2, 2}, {2, 0}, {2, 4}, {3, 3}, {4, 2}};
  vector<vector<int>> hull = sol.outerTrees(points);

  cout << "Test Case 1 Output:" << endl;
  for (const auto &p : hull) {
    cout << "[" << p[0] << "," << p[1] << "] ";
  }
  cout << endl;

  return 0;
}
