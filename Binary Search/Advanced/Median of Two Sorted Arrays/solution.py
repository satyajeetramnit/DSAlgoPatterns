from typing import List

class Solution:
    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:
        if len(nums1) > len(nums2):
            return self.findMedianSortedArrays(nums2, nums1)
        
        m, n = len(nums1), len(nums2)
        left, right = 0, m
        
        while left <= right:
            partitionX = (left + right) // 2
            partitionY = (m + n + 1) // 2 - partitionX
            
            maxLeftX = float('-inf') if partitionX == 0 else nums1[partitionX - 1]
            minRightX = float('inf') if partitionX == m else nums1[partitionX]
            
            maxLeftY = float('-inf') if partitionY == 0 else nums2[partitionY - 1]
            minRightY = float('inf') if partitionY == n else nums2[partitionY]
            
            if maxLeftX <= minRightY and maxLeftY <= minRightX:
                if (m + n) % 2 == 0:
                    return (max(maxLeftX, maxLeftY) + min(minRightX, minRightY)) / 2
                else:
                    return max(maxLeftX, maxLeftY)
            elif maxLeftX > minRightY:
                right = partitionX - 1
            else:
                left = partitionX + 1
        return 0.0

if __name__ == "__main__":
    sol = Solution()
    nums1 = [1, 3]
    nums2 = [2]
    print(f"Median 1: {sol.findMedianSortedArrays(nums1, nums2)}") # Expected: 2.0

    nums3 = [1, 2]
    nums4 = [3, 4]
    print(f"Median 2: {sol.findMedianSortedArrays(nums3, nums4)}") # Expected: 2.5
