#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  int characterReplacement(string s, int k) {
    vector<int> count(26, 0);
    int left = 0, maxFreq = 0, maxLen = 0;

    for (int right = 0; right < s.length(); right++) {
      count[s[right] - 'A']++;
      maxFreq = max(maxFreq, count[s[right] - 'A']);

      if ((right - left + 1) - maxFreq > k) {
        count[s[left] - 'A']--;
        left++;
      }

      maxLen = max(maxLen, right - left + 1);
    }
    return maxLen;
  }
};

int main() {
  Solution sol;
  string s1 = "ABAB";
  int k1 = 2;
  cout << "Max Length 1: " << sol.characterReplacement(s1, k1)
       << endl; // Expected: 4

  string s2 = "AABABBA";
  int k2 = 1;
  cout << "Max Length 2: " << sol.characterReplacement(s2, k2)
       << endl; // Expected: 4

  return 0;
}
