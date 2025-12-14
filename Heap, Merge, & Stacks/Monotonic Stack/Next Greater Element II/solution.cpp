#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
public:
  vector<int> nextGreaterElements(vector<int> &nums) {
    int n = nums.size();
    vector<int> res(n, -1);
    stack<int> st; // stores indices

    for (int i = 0; i < 2 * n; i++) {
      while (!st.empty() && nums[i % n] > nums[st.top()]) {
        res[st.top()] = nums[i % n];
        st.pop();
      }
      if (i < n)
        st.push(i);
    }

    return res;
  }
};

void printVector(const vector<int> &v) {
  cout << "[";
  for (int i = 0; i < v.size(); i++) {
    cout << v[i] << (i < v.size() - 1 ? "," : "");
  }
  cout << "]" << endl;
}

int main() {
  Solution sol;
  vector<int> nums = {1, 2, 1};
  vector<int> result = sol.nextGreaterElements(nums);
  cout << "Test Case 1: ";
  printVector(result); // Expect [2, -1, 2]
  return 0;
}
