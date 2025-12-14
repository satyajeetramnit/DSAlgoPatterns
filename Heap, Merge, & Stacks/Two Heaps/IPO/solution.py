import heapq
from typing import List

class Solution:
    def findMaximizedCapital(self, k: int, w: int, profits: List[int], capital: List[int]) -> int:
        projects = sorted(zip(capital, profits))
        n = len(projects)
        max_profit_heap = []
        i = 0
        
        for _ in range(k):
            # Move affordable projects to max_profit_heap
            while i < n and projects[i][0] <= w:
                heapq.heappush(max_profit_heap, -projects[i][1])
                i += 1
            
            if not max_profit_heap:
                break
            
            w += -heapq.heappop(max_profit_heap)
            
        return w

if __name__ == "__main__":
    sol = Solution()
    k = 2
    w = 0
    profits = [1, 2, 3]
    capital = [0, 1, 1]
    print(f"Test Case 1: {sol.findMaximizedCapital(k, w, profits, capital)}") # Expect 4
