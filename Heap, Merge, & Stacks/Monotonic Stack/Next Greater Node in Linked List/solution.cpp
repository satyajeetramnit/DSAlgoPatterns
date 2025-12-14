#include <iostream>
#include <stack>
#include <vector>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
  vector<int> nextLargerNodes(ListNode *head) {
    vector<int> vals;
    while (head) {
      vals.push_back(head->val);
      head = head->next;
    }

    vector<int> res(vals.size(), 0);
    stack<int> st; // stores indices

    for (int i = 0; i < vals.size(); i++) {
      while (!st.empty() && vals[i] > vals[st.top()]) {
        res[st.top()] = vals[i];
        st.pop();
      }
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
  ListNode *head = new ListNode(2);
  head->next = new ListNode(1);
  head->next->next = new ListNode(5);

  vector<int> result = sol.nextLargerNodes(head);
  cout << "Test Case 1: ";
  printVector(result); // Expect [5, 5, 0]
  return 0;
}
