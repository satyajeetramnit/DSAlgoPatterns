#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int coinChange(vector<int> &coins, int amount) {
    // Initialize dp array with amount + 1 (impossible max value since min coin
    // is 1)
    vector<int> dp(amount + 1, amount + 1);
    dp[0] = 0;

    for (int i = 1; i <= amount; ++i) {
      for (int coin : coins) {
        if (i - coin >= 0) {
          dp[i] = min(dp[i], dp[i - coin] + 1);
        }
      }
    }

    return (dp[amount] > amount) ? -1 : dp[amount];
  }
};

int main() {
  Solution sol;

  vector<int> coins1 = {1, 2, 5};
  int amount1 = 11;
  cout << "Test Case 1 (Amt 11): " << sol.coinChange(coins1, amount1)
       << endl; // Expect 3

  vector<int> coins2 = {2};
  int amount2 = 3;
  cout << "Test Case 2 (Amt 3): " << sol.coinChange(coins2, amount2)
       << endl; // Expect -1

  vector<int> coins3 = {1};
  int amount3 = 0;
  cout << "Test Case 3 (Amt 0): " << sol.coinChange(coins3, amount3)
       << endl; // Expect 0

  return 0;
}
