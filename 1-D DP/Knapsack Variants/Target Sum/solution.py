from typing import List

class Solution:
    def findTargetSumWays(self, nums: List[int], target: int) -> int:
        total_sum = sum(nums)
        
        if (total_sum + target) < 0 or (total_sum + target) % 2 != 0:
            return 0
            
        subset_target = (total_sum + target) // 2
        
        dp = [0] * (subset_target + 1)
        dp[0] = 1
        
        for num in nums:
            for j in range(subset_target, num - 1, -1):
                dp[j] += dp[j - num]
                
        return dp[subset_target]

if __name__ == "__main__":
    sol = Solution()
    
    print(f"Test Case 1 (Target 3): {sol.findTargetSumWays([1, 1, 1, 1, 1], 3)}") # 5
    print(f"Test Case 2 (Target 1): {sol.findTargetSumWays([1], 1)}") # 1
