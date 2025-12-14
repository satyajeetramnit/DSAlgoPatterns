import heapq
from typing import List

class Solution:
    def findKthLargest(self, nums: List[int], k: int) -> int:
        min_heap = []
        for num in nums:
            heapq.heappush(min_heap, num)
            if len(min_heap) > k:
                heapq.heappop(min_heap)
        
        return min_heap[0]

if __name__ == "__main__":
    sol = Solution()
    nums = [3,2,1,5,6,4]
    k = 2
    print(f"Test Case 1: {sol.findKthLargest(nums, k)}") # Expect 5
