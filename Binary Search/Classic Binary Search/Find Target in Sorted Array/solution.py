from typing import List

class Solution:
    def search(self, nums: List[int], target: int) -> int:
        left, right = 0, len(nums) - 1
        
        while left <= right:
            mid = (left + right) // 2
            if nums[mid] == target:
                return mid
            elif nums[mid] < target:
                left = mid + 1
            else:
                right = mid - 1
        return -1

if __name__ == "__main__":
    sol = Solution()
    nums = [-1, 0, 3, 5, 9, 12]
    print(f"Index of 9: {sol.search(nums, 9)}") # Expected: 4
    print(f"Index of 2: {sol.search(nums, 2)}") # Expected: -1
