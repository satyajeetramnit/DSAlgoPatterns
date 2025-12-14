from typing import List
from collections import deque

class Solution:
    def maxSlidingWindow(self, nums: List[int], k: int) -> List[int]:
        dq = deque()
        res = []
        
        for i, num in enumerate(nums):
            # Remove out of bounds
            if dq and dq[0] == i - k:
                dq.popleft()
            
            # Remove smaller elements
            while dq and nums[dq[-1]] < num:
                dq.pop()
            
            dq.append(i)
            
            if i >= k - 1:
                res.append(nums[dq[0]])
                
        return res

if __name__ == "__main__":
    sol = Solution()
    nums1 = [1,3,-1,-3,5,3,6,7]
    k1 = 3
    res1 = sol.maxSlidingWindow(nums1, k1)
    print(f"Max Window 1: {res1}") # Expected: [3, 3, 5, 5, 6, 7]

    nums2 = [1]
    k2 = 1
    res2 = sol.maxSlidingWindow(nums2, k2)
    print(f"Max Window 2: {res2}") # Expected: [1]
