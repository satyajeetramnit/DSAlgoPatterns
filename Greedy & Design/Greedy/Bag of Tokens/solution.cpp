#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int bagOfTokensScore(vector<int> &tokens, int power) {
    sort(tokens.begin(), tokens.end());
    int left = 0, right = tokens.size() - 1;
    int score = 0, max_score = 0;

    while (left <= right) {
      if (power >= tokens[left]) {
        power -= tokens[left];
        score++;
        left++;
        max_score = max(max_score, score);
      } else if (score > 0) {
        if (left == right)
          break;

        power += tokens[right];
        score--;
        right--;
      } else {
        break;
      }
    }
    return max_score;
  }
};

int main() {
  Solution sol;
  vector<int> t1 = {100};
  cout << "Test Case 1: " << sol.bagOfTokensScore(t1, 50) << endl; // Expect 0

  vector<int> t2 = {100, 200};
  cout << "Test Case 2: " << sol.bagOfTokensScore(t2, 150) << endl; // Expect 1

  vector<int> t3 = {100, 200, 300, 400};
  cout << "Test Case 3: " << sol.bagOfTokensScore(t3, 200) << endl; // Expect 2
  return 0;
}
