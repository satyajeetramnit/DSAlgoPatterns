#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  bool checkInclusion(string s1, string s2) {
    if (s1.length() > s2.length())
      return false;

    vector<int> s1Count(26, 0);
    vector<int> s2Count(26, 0);

    for (int i = 0; i < s1.length(); i++) {
      s1Count[s1[i] - 'a']++;
      s2Count[s2[i] - 'a']++;
    }

    if (s1Count == s2Count)
      return true;

    for (int i = s1.length(); i < s2.length(); i++) {
      s2Count[s2[i] - 'a']++;
      s2Count[s2[i - s1.length()] - 'a']--;

      if (s1Count == s2Count)
        return true;
    }

    return false;
  }
};

int main() {
  Solution sol;
  string s1 = "ab";
  string s2 = "eidbaooo";
  cout << "Contains Permutation 1: "
       << (sol.checkInclusion(s1, s2) ? "true" : "false")
       << endl; // Expected: true

  s1 = "ab";
  s2 = "eidboaoo";
  cout << "Contains Permutation 2: "
       << (sol.checkInclusion(s1, s2) ? "true" : "false")
       << endl; // Expected: false

  return 0;
}
