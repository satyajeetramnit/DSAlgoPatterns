import heapq
from typing import List

class Solution:
    def kClosest(self, points: List[List[int]], k: int) -> List[List[int]]:
        heap = []
        for x, y in points:
            dist = -(x*x + y*y)
            heapq.heappush(heap, (dist, x, y))
            if len(heap) > k:
                heapq.heappop(heap)
        
        return [[x, y] for (dist, x, y) in heap]

if __name__ == "__main__":
    sol = Solution()
    points = [[1,3],[-2,2]]
    res = sol.kClosest(points, 1)
    print(f"Test Case 1 Output: {res}") # [[-2, 2]]
