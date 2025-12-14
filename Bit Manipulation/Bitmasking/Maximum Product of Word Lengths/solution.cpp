#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  int maxProduct(vector<string> &words) {
    int n = words.size();
    vector<int> masks(n, 0);
    vector<int> lens(n, 0);

    for (int i = 0; i < n; ++i) {
      lens[i] = words[i].size();
      for (char c : words[i]) {
        masks[i] |= (1 << (c - 'a'));
      }
    }

    int maxProd = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        if ((masks[i] & masks[j]) == 0) {
          maxProd = max(maxProd, lens[i] * lens[j]);
        }
      }
    }

    return maxProd;
  }
};

int main() {
  Solution sol;
  vector<string> words1 = {"abcw", "baz", "foo", "bar", "xtfn", "abcdef"};
  cout << "Test Case 1: " << sol.maxProduct(words1) << endl; // Expect 16

  vector<string> words2 = {"a", "ab", "abc", "d", "cd", "bcd", "abcd"};
  cout << "Test Case 2: " << sol.maxProduct(words2) << endl; // Expect 4

  vector<string> words3 = {"a", "aa", "aaa", "aaaa"};
  cout << "Test Case 3: " << sol.maxProduct(words3) << endl; // Expect 0

  return 0;
}
