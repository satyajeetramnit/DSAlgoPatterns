#include <algorithm>
#include <climits>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
public:
  int mctFromLeafValues(vector<int> &arr) {
    int res = 0;
    stack<int> st;
    st.push(INT_MAX); // Sentinel

    for (int num : arr) {
      while (st.top() <= num) {
        int mid = st.top();
        st.pop();
        res += mid * min(st.top(), num);
      }
      st.push(num);
    }

    // Process remaining elements
    while (st.size() > 2) {
      int mid = st.top();
      st.pop();
      res += mid * st.top();
    }

    return res;
  }
};

int main() {
  Solution sol;

  vector<int> arr1 = {6, 2, 4};
  cout << "Test Case 1: " << sol.mctFromLeafValues(arr1) << endl; // Expect 32

  vector<int> arr2 = {4, 11};
  cout << "Test Case 2: " << sol.mctFromLeafValues(arr2) << endl; // Expect 44

  return 0;
}
