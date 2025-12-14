#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  vector<int> findArray(vector<int> &pref) {
    int n = pref.size();
    vector<int> arr(n);
    arr[0] = pref[0];

    for (int i = 1; i < n; ++i) {
      arr[i] = pref[i] ^ pref[i - 1];
    }

    return arr;
  }
};

int main() {
  Solution sol;

  vector<int> pref1 = {5, 2, 0, 3, 1};
  vector<int> res1 = sol.findArray(pref1);
  cout << "Test Case 1: ";
  for (int x : res1)
    cout << x << " "; // Expect 5 7 2 3 2
  cout << endl;

  vector<int> pref2 = {13};
  vector<int> res2 = sol.findArray(pref2);
  cout << "Test Case 2: ";
  for (int x : res2)
    cout << x << " "; // Expect 13
  cout << endl;

  return 0;
}
