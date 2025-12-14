from typing import List

class Solution:
    def numberOfSubarrays(self, nums: List[int], k: int) -> int:
        return self.atMost(nums, k) - self.atMost(nums, k - 1)

    def atMost(self, nums, k):
        left = 0
        res = 0
        count = 0
        for right in range(len(nums)):
            if nums[right] % 2 != 0:
                count += 1
            while count > k:
                if nums[left] % 2 != 0:
                    count -= 1
                left += 1
            res += right - left + 1
        return res

if __name__ == "__main__":
    sol = Solution()
    nums1 = [1,1,2,1,1]
    k1 = 3
    print(f"Count 1: {sol.numberOfSubarrays(nums1, k1)}") # Expected: 2

    nums2 = [2,4,6]
    k2 = 1
    print(f"Count 2: {sol.numberOfSubarrays(nums2, k2)}") # Expected: 0
