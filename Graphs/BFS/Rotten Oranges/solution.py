from typing import List
from collections import deque

class Solution:
    def orangesRotting(self, grid: List[List[int]]) -> int:
        rows, cols = len(grid), len(grid[0])
        q = deque()
        fresh_count = 0
        
        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == 2:
                    q.append((r, c))
                elif grid[r][c] == 1:
                    fresh_count += 1
                    
        if fresh_count == 0:
            return 0
            
        minutes = 0
        directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
        
        while q and fresh_count > 0:
            for _ in range(len(q)):
                r, c = q.popleft()
                
                for dr, dc in directions:
                    nr, nc = r + dr, c + dc
                    if 0 <= nr < rows and 0 <= nc < cols and grid[nr][nc] == 1:
                        grid[nr][nc] = 2 # Rot it
                        fresh_count -= 1
                        q.append((nr, nc))
            minutes += 1
            
        return minutes if fresh_count == 0 else -1

if __name__ == "__main__":
    sol = Solution()
    
    grid1 = [[2,1,1],[1,1,0],[0,1,1]]
    print(f"Rotten Oranges 1: {sol.orangesRotting([row[:] for row in grid1])}")

    grid2 = [[2,1,1],[0,1,1],[1,0,1]]
    print(f"Rotten Oranges 2: {sol.orangesRotting([row[:] for row in grid2])}")

    grid3 = [[0,2]]
    print(f"Rotten Oranges 3: {sol.orangesRotting([row[:] for row in grid3])}")
