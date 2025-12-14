#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int numRescueBoats(vector<int> &people, int limit) {
    sort(people.begin(), people.end());
    int left = 0, right = people.size() - 1;
    int boats = 0;

    while (left <= right) {
      if (people[left] + people[right] <= limit) {
        left++;
      }
      right--;
      boats++;
    }
    return boats;
  }
};

int main() {
  Solution sol;
  vector<int> p1 = {1, 2};
  cout << "Test Case 1: " << sol.numRescueBoats(p1, 3) << endl; // Expect 1

  vector<int> p2 = {3, 2, 2, 1};
  cout << "Test Case 2: " << sol.numRescueBoats(p2, 3) << endl; // Expect 3

  vector<int> p3 = {3, 5, 3, 4};
  cout << "Test Case 3: " << sol.numRescueBoats(p3, 5) << endl; // Expect 4
  return 0;
}
