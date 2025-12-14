from typing import List

class Solution:
    def coinChange(self, coins: List[int], amount: int) -> int:
        dp = [amount + 1] * (amount + 1)
        dp[0] = 0
        
        for i in range(1, amount + 1):
            for coin in coins:
                if i - coin >= 0:
                    dp[i] = min(dp[i], dp[i - coin] + 1)
                    
        return dp[amount] if dp[amount] <= amount else -1

if __name__ == "__main__":
    sol = Solution()
    
    print(f"Test Case 1 (Amt 11): {sol.coinChange([1, 2, 5], 11)}") # 3
    print(f"Test Case 2 (Amt 3): {sol.coinChange([2], 3)}") # -1
    print(f"Test Case 3 (Amt 0): {sol.coinChange([1], 0)}") # 0
