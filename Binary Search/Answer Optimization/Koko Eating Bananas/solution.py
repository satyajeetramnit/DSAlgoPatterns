import math
from typing import List

class Solution:
    def minEatingSpeed(self, piles: List[int], h: int) -> int:
        left, right = 1, max(piles)
        
        while left <= right:
            k = (left + right) // 2
            hours = sum(math.ceil(p / k) for p in piles)
            
            if hours <= h:
                right = k - 1
            else:
                left = k + 1
        return left

if __name__ == "__main__":
    sol = Solution()
    piles1 = [3,6,7,11]
    h1 = 8
    print(f"Min Speed 1: {sol.minEatingSpeed(piles1, h1)}") # Expected: 4

    piles2 = [30,11,23,4,20]
    h2 = 5
    print(f"Min Speed 2: {sol.minEatingSpeed(piles2, h2)}") # Expected: 30
