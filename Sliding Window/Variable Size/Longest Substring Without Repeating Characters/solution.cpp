#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
  int lengthOfLongestSubstring(string s) {
    unordered_set<char> charSet;
    int left = 0, maxLength = 0;

    for (int right = 0; right < s.length(); right++) {
      while (charSet.count(s[right])) {
        charSet.erase(s[left]);
        left++;
      }
      charSet.insert(s[right]);
      maxLength = max(maxLength, right - left + 1);
    }
    return maxLength;
  }
};

int main() {
  Solution sol;
  string s1 = "abcabcbb";
  cout << "Length 1: " << sol.lengthOfLongestSubstring(s1)
       << endl; // Expected: 3

  string s2 = "bbbbb";
  cout << "Length 2: " << sol.lengthOfLongestSubstring(s2)
       << endl; // Expected: 1

  string s3 = "pwwkew";
  cout << "Length 3: " << sol.lengthOfLongestSubstring(s3)
       << endl; // Expected: 3

  return 0;
}
