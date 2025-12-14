from typing import List

class Solution:
    def search(self, nums: List[int], target: int) -> int:
        left, right = 0, len(nums) - 1
        
        while left <= right:
            mid = (left + right) // 2
            if nums[mid] == target:
                return mid
            
            # Left half is sorted
            if nums[left] <= nums[mid]:
                if nums[left] <= target < nums[mid]:
                    right = mid - 1
                else:
                    left = mid + 1
            # Right half is sorted
            else:
                if nums[mid] < target <= nums[right]:
                    left = mid + 1
                else:
                    right = mid - 1
        return -1

if __name__ == "__main__":
    sol = Solution()
    nums = [4, 5, 6, 7, 0, 1, 2]
    print(f"Index of 0: {sol.search(nums, 0)}") # Expected: 4
    print(f"Index of 3: {sol.search(nums, 3)}") # Expected: -1
