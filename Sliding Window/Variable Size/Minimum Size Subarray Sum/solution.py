from typing import List

class Solution:
    def minSubArrayLen(self, target: int, nums: List[int]) -> int:
        left = 0
        current_sum = 0
        min_len = float('inf')
        
        for right in range(len(nums)):
            current_sum += nums[right]
            
            while current_sum >= target:
                min_len = min(min_len, right - left + 1)
                current_sum -= nums[left]
                left += 1
                
        return 0 if min_len == float('inf') else min_len

if __name__ == "__main__":
    sol = Solution()
    target1 = 7
    nums1 = [2,3,1,2,4,3]
    print(f"Min Length 1: {sol.minSubArrayLen(target1, nums1)}") # Expected: 2

    target2 = 4
    nums2 = [1,4,4]
    print(f"Min Length 2: {sol.minSubArrayLen(target2, nums2)}") # Expected: 1
    
    target3 = 11
    nums3 = [1,1,1,1,1,1,1,1]
    print(f"Min Length 3: {sol.minSubArrayLen(target3, nums3)}") # Expected: 0
