#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
public:
  int candy(vector<int> &ratings) {
    int n = ratings.size();
    if (n == 0)
      return 0;

    vector<int> candies(n, 1);

    // Left to Right
    for (int i = 1; i < n; i++) {
      if (ratings[i] > ratings[i - 1]) {
        candies[i] = candies[i - 1] + 1;
      }
    }

    // Right to Left
    for (int i = n - 2; i >= 0; i--) {
      if (ratings[i] > ratings[i + 1]) {
        candies[i] = max(candies[i], candies[i + 1] + 1);
      }
    }

    return accumulate(candies.begin(), candies.end(), 0);
  }
};

int main() {
  Solution sol;
  vector<int> r1 = {1, 0, 2};
  cout << "Test Case 1: " << sol.candy(r1) << endl; // Expect 5

  vector<int> r2 = {1, 2, 2};
  cout << "Test Case 2: " << sol.candy(r2) << endl; // Expect 4

  return 0;
}
