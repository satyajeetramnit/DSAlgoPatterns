#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  vector<string> generateParenthesis(int n) {
    vector<string> res;
    backtrack(n, 0, 0, "", res);
    return res;
  }

private:
  void backtrack(int n, int open, int close, string current,
                 vector<string> &res) {
    if (current.length() == n * 2) {
      res.push_back(current);
      return;
    }

    if (open < n) {
      backtrack(n, open + 1, close, current + "(", res);
    }

    if (close < open) {
      backtrack(n, open, close + 1, current + ")", res);
    }
  }
};

void printRes(const vector<string> &res) {
  cout << "[";
  for (size_t i = 0; i < res.size(); ++i) {
    cout << "\"" << res[i] << "\"" << (i < res.size() - 1 ? "," : "");
  }
  cout << "]" << endl;
}

int main() {
  Solution sol;
  cout << "Generate Parentheses n=3: " << endl;
  printRes(sol.generateParenthesis(3));

  cout << "Generate Parentheses n=1: " << endl;
  printRes(sol.generateParenthesis(1));

  return 0;
}
