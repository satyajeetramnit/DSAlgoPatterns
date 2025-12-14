#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
  vector<vector<string>> groupAnagrams(vector<string> &strs) {
    unordered_map<string, vector<string>> m;
    for (string s : strs) {
      string t = s;
      sort(t.begin(), t.end());
      m[t].push_back(s);
    }
    vector<vector<string>> result;
    for (auto p : m) {
      result.push_back(p.second);
    }
    return result;
  }
};

int main() {
  Solution sol;
  vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
  vector<vector<string>> result = sol.groupAnagrams(strs);
  for (const auto &group : result) {
    cout << "[";
    for (int i = 0; i < group.size(); ++i) {
      cout << group[i] << (i < group.size() - 1 ? ", " : "");
    }
    cout << "] ";
  }
  cout << endl;
  return 0;
}
