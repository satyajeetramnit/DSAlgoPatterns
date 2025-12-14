#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int minEatingSpeed(vector<int> &piles, int h) {
    int left = 1;
    int right = 0;
    for (int p : piles)
      right = max(right, p);

    while (left <= right) {
      int mid = left + (right - left) / 2;
      long long hours = 0;
      for (int p : piles) {
        // Equivalent to ceil(p / mid)
        hours += (long long)p / mid + (p % mid != 0);
      }

      if (hours <= h) {
        right = mid - 1;
      } else {
        left = mid + 1;
      }
    }
    return left;
  }
};

int main() {
  Solution sol;
  vector<int> piles1 = {3, 6, 7, 11};
  int h1 = 8;
  cout << "Min Speed 1: " << sol.minEatingSpeed(piles1, h1)
       << endl; // Expected: 4

  vector<int> piles2 = {30, 11, 23, 4, 20};
  int h2 = 5;
  cout << "Min Speed 2: " << sol.minEatingSpeed(piles2, h2)
       << endl; // Expected: 30

  return 0;
}
