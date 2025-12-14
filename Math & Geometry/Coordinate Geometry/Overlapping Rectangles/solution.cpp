#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  // rec = [x1, y1, x2, y2]
  bool isRectangleOverlap(vector<int> &rec1, vector<int> &rec2) {
    // Standard strict overlap check
    // width overlap && height overlap
    // width overlap: max(x1, x1') < min(x2, x2')
    return (max(rec1[0], rec2[0]) < min(rec1[2], rec2[2])) &&
           (max(rec1[1], rec2[1]) < min(rec1[3], rec2[3]));
  }
};

int main() {
  Solution sol;

  vector<int> r1 = {0, 0, 2, 2};
  vector<int> r2 = {1, 1, 3, 3};
  cout << boolalpha
       << "Test Case 1 (Overlap): " << sol.isRectangleOverlap(r1, r2)
       << endl; // true

  vector<int> r3 = {0, 0, 1, 1};
  vector<int> r4 = {1, 0, 2, 1};
  cout << "Test Case 2 (Touch): " << sol.isRectangleOverlap(r3, r4)
       << endl; // false

  return 0;
}
