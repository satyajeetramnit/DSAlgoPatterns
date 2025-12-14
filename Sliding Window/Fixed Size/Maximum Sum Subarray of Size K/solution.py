from typing import List

class Solution:
    def maxSumSubarray(self, nums: List[int], k: int) -> int:
        n = len(nums)
        if n < k:
            return -1

        current_sum = sum(nums[:k])
        max_sum = current_sum

        for i in range(k, n):
            current_sum += nums[i] - nums[i - k]
            max_sum = max(max_sum, current_sum)
        
        return max_sum

if __name__ == "__main__":
    sol = Solution()
    nums1 = [2, 1, 5, 1, 3, 2]
    k1 = 3
    print(f"Max Sum 1: {sol.maxSumSubarray(nums1, k1)}") # Expected: 9

    nums2 = [2, 3, 4, 1, 5]
    k2 = 2
    print(f"Max Sum 2: {sol.maxSumSubarray(nums2, k2)}") # Expected: 7
