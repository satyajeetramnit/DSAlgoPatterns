#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
public:
  int shipWithinDays(vector<int> &weights, int days) {
    int maxWeight = 0, totalWeight = 0;
    for (int w : weights) {
      maxWeight = max(maxWeight, w);
      totalWeight += w;
    }

    int left = maxWeight, right = totalWeight;

    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (canShip(weights, days, mid)) {
        right = mid - 1;
      } else {
        left = mid + 1;
      }
    }
    return left;
  }

private:
  bool canShip(const vector<int> &weights, int days, int capacity) {
    int daysNeeded = 1;
    int currentLoad = 0;

    for (int w : weights) {
      if (currentLoad + w > capacity) {
        daysNeeded++;
        currentLoad = 0;
      }
      currentLoad += w;
    }
    return daysNeeded <= days;
  }
};

int main() {
  Solution sol;
  vector<int> weights1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int days1 = 5;
  cout << "Min Capacity 1: " << sol.shipWithinDays(weights1, days1)
       << endl; // Expected: 15

  vector<int> weights2 = {3, 2, 2, 4, 1, 4};
  int days2 = 3;
  cout << "Min Capacity 2: " << sol.shipWithinDays(weights2, days2)
       << endl; // Expected: 6

  return 0;
}
