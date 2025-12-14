#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
  vector<string> findRepeatedDnaSequences(string s) {
    unordered_set<string> seen, repeated;
    if (s.length() < 10)
      return {};

    for (int i = 0; i <= s.length() - 10; ++i) {
      string sub = s.substr(i, 10);
      if (seen.count(sub)) {
        repeated.insert(sub);
      } else {
        seen.insert(sub);
      }
    }
    return vector<string>(repeated.begin(), repeated.end());
  }
};

int main() {
  Solution sol;
  string s1 = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT";
  vector<string> res1 = sol.findRepeatedDnaSequences(s1);
  cout << "Repeated 1: ";
  for (const string &seq : res1)
    cout << seq << " "; // Expected: AAAAACCCCC CCCCCAAAAA (order varies)
  cout << endl;

  string s2 = "AAAAAAAAAAAAA";
  vector<string> res2 = sol.findRepeatedDnaSequences(s2);
  cout << "Repeated 2: ";
  for (const string &seq : res2)
    cout << seq << " "; // Expected: AAAAAAAAAA
  cout << endl;

  return 0;
}
