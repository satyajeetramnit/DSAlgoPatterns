#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  vector<vector<string>> partition(string s) {
    vector<vector<string>> res;
    vector<string> path;
    backtrack(s, 0, path, res);
    return res;
  }

private:
  void backtrack(const string &s, int start, vector<string> &path,
                 vector<vector<string>> &res) {
    if (start == s.length()) {
      res.push_back(path);
      return;
    }

    for (int i = start; i < s.length(); ++i) {
      if (isPalindrome(s, start, i)) {
        path.push_back(s.substr(start, i - start + 1));
        backtrack(s, i + 1, path, res);
        path.pop_back();
      }
    }
  }

  bool isPalindrome(const string &s, int left, int right) {
    while (left < right) {
      if (s[left++] != s[right--])
        return false;
    }
    return true;
  }
};

void printRes(const vector<vector<string>> &res) {
  cout << "[";
  for (size_t i = 0; i < res.size(); ++i) {
    cout << "[";
    for (size_t j = 0; j < res[i].size(); ++j) {
      cout << "\"" << res[i][j] << "\"" << (j < res[i].size() - 1 ? "," : "");
    }
    cout << "]" << (i < res.size() - 1 ? "," : "");
  }
  cout << "]" << endl;
}

int main() {
  Solution sol;
  string s = "aab";
  cout << "Partition 'aab': " << endl;
  printRes(sol.partition(s));

  return 0;
}
