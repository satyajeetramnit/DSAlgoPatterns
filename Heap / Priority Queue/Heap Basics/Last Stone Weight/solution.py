import heapq
from typing import List

class Solution:
    def lastStoneWeight(self, stones: List[int]) -> int:
        max_heap = [-s for s in stones]
        heapq.heapify(max_heap)
        
        while len(max_heap) > 1:
            y = -heapq.heappop(max_heap)
            x = -heapq.heappop(max_heap)
            if x != y:
                heapq.heappush(max_heap, -(y - x))
                
        return -max_heap[0] if max_heap else 0

if __name__ == "__main__":
    sol = Solution()
    stones = [2, 7, 4, 1, 8, 1]
    print(f"Test Case 1: {sol.lastStoneWeight(stones)}") # Expect 1
