from typing import List

class Solution:
    def searchInsert(self, nums: List[int], target: int) -> int:
        left, right = 0, len(nums) - 1
        
        while left <= right:
            mid = (left + right) // 2
            
            if nums[mid] == target:
                return mid
            
            if nums[mid] < target:
                left = mid + 1
            else:
                right = mid - 1
                
        return left

if __name__ == "__main__":
    sol = Solution()
    nums = [1, 3, 5, 6]
    print(f"Insert 5: {sol.searchInsert(nums, 5)}") # Expected: 2
    print(f"Insert 2: {sol.searchInsert(nums, 2)}") # Expected: 1
    print(f"Insert 7: {sol.searchInsert(nums, 7)}") # Expected: 4
