#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int maxEnvelopes(vector<vector<int>> &envelopes) {
    // Sort: width ascending, height descending
    sort(envelopes.begin(), envelopes.end(),
         [](const vector<int> &a, const vector<int> &b) {
           if (a[0] == b[0])
             return a[1] > b[1];
           return a[0] < b[0];
         });

    vector<int> tails;
    for (const auto &env : envelopes) {
      int h = env[1];
      auto it = lower_bound(tails.begin(), tails.end(), h);
      if (it == tails.end()) {
        tails.push_back(h);
      } else {
        *it = h;
      }
    }

    return tails.size();
  }
};

int main() {
  Solution sol;

  vector<vector<int>> envelopes1 = {{5, 4}, {6, 4}, {6, 7}, {2, 3}};
  cout << "Test Case 1: " << sol.maxEnvelopes(envelopes1) << endl; // Expect 3

  vector<vector<int>> envelopes2 = {{1, 1}, {1, 1}, {1, 1}};
  cout << "Test Case 2: " << sol.maxEnvelopes(envelopes2) << endl; // Expect 1

  return 0;
}
