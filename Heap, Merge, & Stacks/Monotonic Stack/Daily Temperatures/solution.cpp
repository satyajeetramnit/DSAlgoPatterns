#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
public:
  vector<int> dailyTemperatures(vector<int> &temperatures) {
    int n = temperatures.size();
    vector<int> answer(n, 0);
    stack<int> st; // stores indices

    for (int i = 0; i < n; i++) {
      while (!st.empty() && temperatures[i] > temperatures[st.top()]) {
        int prevIndex = st.top();
        st.pop();
        answer[prevIndex] = i - prevIndex;
      }
      st.push(i);
    }

    return answer;
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
  vector<int> temps = {73, 74, 75, 71, 69, 72, 76, 73};
  vector<int> result = sol.dailyTemperatures(temps);
  cout << "Test Case 1: ";
  printVector(result); // Expect [1,1,4,2,1,1,0,0]
  return 0;
}
