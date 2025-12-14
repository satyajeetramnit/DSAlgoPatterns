from typing import List

class Solution:
    def splitArray(self, nums: List[int], k: int) -> int:
        def canSplit(max_sum):
            subarrays = 1
            current_sum = 0
            for num in nums:
                if current_sum + num > max_sum:
                    subarrays += 1
                    current_sum = num
                else:
                    current_sum += num
            return subarrays <= k

        left, right = max(nums), sum(nums)
        
        while left <= right:
            mid = (left + right) // 2
            if canSplit(mid):
                right = mid - 1
            else:
                left = mid + 1
        return left

if __name__ == "__main__":
    sol = Solution()
    nums1 = [7,2,5,10,8]
    k1 = 2
    print(f"Min Largest Sum 1: {sol.splitArray(nums1, k1)}") # Expected: 18

    nums2 = [1,2,3,4,5]
    k2 = 2
    print(f"Min Largest Sum 2: {sol.splitArray(nums2, k2)}") # Expected: 9
