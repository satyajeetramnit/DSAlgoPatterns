from typing import List
from collections import deque

class Solution:
    def maxDistance(self, grid: List[List[int]]) -> int:
        n = len(grid)
        q = deque()
        
        # Add all land cells to queue
        for i in range(n):
            for j in range(n):
                if grid[i][j] == 1:
                    q.append((i, j))
                    
        if not q or len(q) == n * n:
            return -1
            
        dist = -1
        dirs = [(-1,0), (1,0), (0,-1), (0,1)]
        
        while q:
            dist += 1
            for _ in range(len(q)):
                r, c = q.popleft()
                
                for dr, dc in dirs:
                    nr, nc = r + dr, c + dc
                    
                    if 0 <= nr < n and 0 <= nc < n and grid[nr][nc] == 0:
                        grid[nr][nc] = 1 # Mark visited
                        q.append((nr, nc))
                        
        return dist

if __name__ == "__main__":
    sol = Solution()
    
    grid1 = [[1,0,1],[0,0,0],[1,0,1]]
    print(f"Max Distance 1: {sol.maxDistance([row[:] for row in grid1])}")

    grid2 = [[1,0,0],[0,0,0],[0,0,0]]
    print(f"Max Distance 2: {sol.maxDistance([row[:] for row in grid2])}")

    grid3 = [[0,0,0]]
    print(f"Max Distance 3: {sol.maxDistance([row[:] for row in grid3])}")
