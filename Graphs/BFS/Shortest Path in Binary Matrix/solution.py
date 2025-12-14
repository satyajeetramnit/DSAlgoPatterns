from typing import List
from collections import deque

class Solution:
    def shortestPathBinaryMatrix(self, grid: List[List[int]]) -> int:
        n = len(grid)
        if grid[0][0] == 1 or grid[n-1][n-1] == 1:
            return -1
            
        q = deque([(0, 0)])
        grid[0][0] = 1 # Mark visited
        path_len = 1
        
        directions = [
            (-1, -1), (-1, 0), (-1, 1),
            (0, -1),           (0, 1),
            (1, -1),  (1, 0),  (1, 1)
        ]
        
        while q:
            for _ in range(len(q)):
                r, c = q.popleft()
                if r == n - 1 and c == n - 1:
                    return path_len
                
                for dr, dc in directions:
                    nr, nc = r + dr, c + dc
                    if 0 <= nr < n and 0 <= nc < n and grid[nr][nc] == 0:
                        q.append((nr, nc))
                        grid[nr][nc] = 1 # Mark visited
            path_len += 1
            
        return -1

if __name__ == "__main__":
    sol = Solution()
    
    grid1 = [[0,1],[1,0]]
    # Note: Pass copies because the function modifies the grid
    print(f"Shortest Path 1: {sol.shortestPathBinaryMatrix([row[:] for row in grid1])}")
    
    grid2 = [[0,0,0],[1,1,0],[1,1,0]]
    print(f"Shortest Path 2: {sol.shortestPathBinaryMatrix([row[:] for row in grid2])}")

    grid3 = [[1,0,0],[1,1,0],[1,1,0]]
    print(f"Shortest Path 3: {sol.shortestPathBinaryMatrix([row[:] for row in grid3])}")
