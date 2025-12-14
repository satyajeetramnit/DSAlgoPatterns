from typing import List
from collections import deque

class Solution:
    def longestSubarray(self, nums: List[int], limit: int) -> int:
        max_d = deque()
        min_d = deque()
        left = 0
        res = 0
        
        for right, num in enumerate(nums):
            while max_d and nums[max_d[-1]] <= num:
                max_d.pop()
            while min_d and nums[min_d[-1]] >= num:
                min_d.pop()
            
            max_d.append(right)
            min_d.append(right)
            
            while nums[max_d[0]] - nums[min_d[0]] > limit:
                left += 1
                if max_d[0] < left:
                    max_d.popleft()
                if min_d[0] < left:
                    min_d.popleft()
            
            res = max(res, right - left + 1)
            
        return res

if __name__ == "__main__":
    sol = Solution()
    nums1 = [8,2,4,7]
    limit1 = 4
    print(f"Longest 1: {sol.longestSubarray(nums1, limit1)}") # Expected: 2

    nums2 = [10,1,2,4,7,2]
    limit2 = 5
    print(f"Longest 2: {sol.longestSubarray(nums2, limit2)}") # Expected: 4
