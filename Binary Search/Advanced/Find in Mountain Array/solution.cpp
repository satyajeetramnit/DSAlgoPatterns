#include <iostream>
#include <vector>

using namespace std;

// Mock interface
class MountainArray {
  vector<int> arr;

public:
  MountainArray(vector<int> a) : arr(a) {}
  int get(int index) { return arr[index]; }
  int length() { return arr.size(); }
};

class Solution {
public:
  int findInMountainArray(int target, MountainArray &mountainArr) {
    int n = mountainArr.length();
    // 1. Find Peak
    int left = 0, right = n - 1;
    while (left < right) {
      int mid = left + (right - left) / 2;
      if (mountainArr.get(mid) < mountainArr.get(mid + 1)) {
        left = mid + 1;
      } else {
        right = mid;
      }
    }
    int peak = left;

    // 2. Search Left (Ascending)
    left = 0;
    right = peak;
    while (left <= right) {
      int mid = left + (right - left) / 2;
      int val = mountainArr.get(mid);
      if (val == target)
        return mid;
      if (val < target)
        left = mid + 1;
      else
        right = mid - 1;
    }

    // 3. Search Right (Descending)
    left = peak + 1;
    right = n - 1;
    while (left <= right) {
      int mid = left + (right - left) / 2;
      int val = mountainArr.get(mid);
      if (val == target)
        return mid;
      if (val > target)
        left = mid + 1; // Reverse logic
      else
        right = mid - 1;
    }

    return -1;
  }
};

int main() {
  Solution sol;
  vector<int> arr1 = {1, 2, 3, 4, 5, 3, 1};
  MountainArray ma1(arr1);
  cout << "Index of 3: " << sol.findInMountainArray(3, ma1)
       << endl; // Expected: 2 (min index)

  vector<int> arr2 = {0, 1, 2, 4, 2, 1};
  MountainArray ma2(arr2);
  cout << "Index of 3: " << sol.findInMountainArray(3, ma2)
       << endl; // Expected: -1

  return 0;
}
