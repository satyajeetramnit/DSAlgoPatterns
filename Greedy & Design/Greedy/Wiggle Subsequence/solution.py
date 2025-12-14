from typing import List

class Solution:
    def wiggleMaxLength(self, nums: List[int]) -> int:
        if not nums:
            return 0
            
        up = 1
        down = 1
        
        for i in range(1, len(nums)):
            if nums[i] > nums[i-1]:
                up = down + 1
            elif nums[i] < nums[i-1]:
                down = up + 1
                
        return max(up, down)

if __name__ == "__main__":
    sol = Solution()
    print(f"Test Case 1: {sol.wiggleMaxLength([1,7,4,9,2,5])}") # Expect 6
    print(f"Test Case 2: {sol.wiggleMaxLength([1,17,5,10,13,15,10,5,16,8])}") # Expect 7
    print(f"Test Case 3: {sol.wiggleMaxLength([1,2,3,4,5,6,7,8,9])}") # Expect 2
