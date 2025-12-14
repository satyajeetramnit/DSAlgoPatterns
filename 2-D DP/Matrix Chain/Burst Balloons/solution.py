from typing import List

class Solution:
    def maxCoins(self, nums: List[int]) -> int:
        padded_nums = [1] + nums + [1]
        n = len(padded_nums)
        dp = [[0] * n for _ in range(n)]
        
        for length in range(1, len(nums) + 1):
            for left in range(n - length - 1):
                right = left + length + 1
                for k in range(left + 1, right):
                    dp[left][right] = max(dp[left][right],
                        padded_nums[left] * padded_nums[k] * padded_nums[right] + dp[left][k] + dp[k][right])
                        
        return dp[0][n-1]

if __name__ == "__main__":
    sol = Solution()
    print(f"Test Case 1: {sol.maxCoins([3,1,5,8])}") # 167
    print(f"Test Case 2: {sol.maxCoins([1,5])}") # 10
