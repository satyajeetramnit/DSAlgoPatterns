#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  vector<int> xorQueries(vector<int> &arr, vector<vector<int>> &queries) {
    int n = arr.size();
    // Compute prefix XOR in-place
    // Note: passing by reference modifies original array, which is fine
    // If we needed to keep original, we'd copy it.
    for (int i = 1; i < n; ++i) {
      arr[i] ^= arr[i - 1];
    }

    vector<int> res;
    for (auto &q : queries) {
      int L = q[0], R = q[1];
      if (L > 0)
        res.push_back(arr[R] ^ arr[L - 1]);
      else
        res.push_back(arr[R]);
    }
    return res;
  }
};

int main() {
  Solution sol;

  vector<int> arr1 = {1, 3, 4, 8};
  vector<vector<int>> q1 = {{0, 1}, {1, 2}, {0, 3}, {3, 3}};
  vector<int> res1 = sol.xorQueries(arr1, q1);

  cout << "Test Case 1: ";
  for (int x : res1)
    cout << x << " "; // Expect 2 7 14 8
  cout << endl;

  vector<int> arr2 = {4, 8, 2, 10};
  vector<vector<int>> q2 = {{2, 3}, {1, 3}, {0, 0}, {0, 3}};
  vector<int> res2 = sol.xorQueries(arr2, q2);

  cout << "Test Case 2: ";
  for (int x : res2)
    cout << x << " "; // Expect 8 0 4 4
  cout << endl;

  return 0;
}
