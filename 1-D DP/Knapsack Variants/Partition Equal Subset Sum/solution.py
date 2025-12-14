from typing import List

class Solution:
    def canPartition(self, nums: List[int]) -> bool:
        total_sum = sum(nums)
        
        if total_sum % 2 != 0:
            return False
            
        target = total_sum // 2
        dp = [False] * (target + 1)
        dp[0] = True
        
        for num in nums:
            for j in range(target, num - 1, -1):
                if dp[j - num]:
                    dp[j] = True
                    
        return dp[target]

if __name__ == "__main__":
    sol = Solution()
    
    print(f"Test Case 1: {sol.canPartition([1, 5, 11, 5])}") # True
    print(f"Test Case 2: {sol.canPartition([1, 2, 3, 5])}") # False
