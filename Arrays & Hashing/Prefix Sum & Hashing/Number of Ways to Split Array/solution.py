from typing import List

class Solution:
    def waysToSplitArray(self, nums: List[int]) -> int:
        totalSum = sum(nums)
        leftSum = 0
        count = 0
        
        for i in range(len(nums) - 1):
            leftSum += nums[i]
            rightSum = totalSum - leftSum
            if leftSum >= rightSum:
                count += 1
        return count

if __name__ == "__main__":
    sol = Solution()
    print(sol.waysToSplitArray([10, 4, -8, 7]))
