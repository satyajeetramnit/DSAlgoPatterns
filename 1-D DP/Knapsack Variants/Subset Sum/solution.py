from typing import List

class Solution:
    def isSubsetSum(self, nums: List[int], target: int) -> bool:
        # dp[i] will be True if sum i is achievable
        dp = [False] * (target + 1)
        dp[0] = True
        
        for num in nums:
            # Iterate backwards to avoid using the same element twice for the same target
            for j in range(target, num - 1, -1):
                if dp[j - num]:
                    dp[j] = True
                    
        return dp[target]

if __name__ == "__main__":
    sol = Solution()
    
    nums1 = [3, 34, 4, 12, 5, 2]
    print(f"Test Case 1 (Target 9): {sol.isSubsetSum(nums1, 9)}") # True
    print(f"Test Case 2 (Target 30): {sol.isSubsetSum(nums1, 30)}") # False
    
    nums2 = [1, 2, 3]
    print(f"Test Case 3 (Target 6): {sol.isSubsetSum(nums2, 6)}") # True
