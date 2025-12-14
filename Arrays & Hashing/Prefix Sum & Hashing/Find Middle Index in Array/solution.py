from typing import List

class Solution:
    def findMiddleIndex(self, nums: List[int]) -> int:
        totalSum = sum(nums)
        leftSum = 0
        
        for i, n in enumerate(nums):
            rightSum = totalSum - leftSum - n
            if leftSum == rightSum:
                return i
            leftSum += n
        return -1

if __name__ == "__main__":
    sol = Solution()
    print(sol.findMiddleIndex([2, 3, -1, 8, 4]))
