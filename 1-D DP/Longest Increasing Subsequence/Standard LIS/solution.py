from typing import List
import bisect

class Solution:
    def lengthOfLIS(self, nums: List[int]) -> int:
        tails = []
        for x in nums:
            idx = bisect.bisect_left(tails, x)
            if idx < len(tails):
                tails[idx] = x
            else:
                tails.append(x)
        return len(tails)

if __name__ == "__main__":
    sol = Solution()
    
    print(f"Test Case 1: {sol.lengthOfLIS([10,9,2,5,3,7,101,18])}") # 4
    print(f"Test Case 2: {sol.lengthOfLIS([0,1,0,3,2,3])}") # 4
    print(f"Test Case 3: {sol.lengthOfLIS([7,7,7,7,7,7,7])}") # 1
