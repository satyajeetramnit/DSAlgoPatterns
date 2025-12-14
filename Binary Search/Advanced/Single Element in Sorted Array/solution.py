from typing import List

class Solution:
    def singleNonDuplicate(self, nums: List[int]) -> int:
        left, right = 0, len(nums) - 1
        
        while left < right:
            mid = (left + right) // 2
            if mid % 2 == 1:
                mid -= 1
            
            if nums[mid] == nums[mid + 1]:
                left = mid + 2
            else:
                right = mid
        return nums[left]

if __name__ == "__main__":
    sol = Solution()
    nums1 = [1,1,2,3,3,4,4,8,8]
    print(f"Single Element 1: {sol.singleNonDuplicate(nums1)}") # Expected: 2

    nums2 = [3,3,7,7,10,11,11]
    print(f"Single Element 2: {sol.singleNonDuplicate(nums2)}") # Expected: 10
