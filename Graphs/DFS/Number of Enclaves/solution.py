from typing import List

class Solution:
    def numEnclaves(self, grid: List[List[int]]) -> int:
        rows, cols = len(grid), len(grid[0])
        
        def dfs(r, c):
            if r < 0 or c < 0 or r >= rows or c >= cols or grid[r][c] == 0:
                return
            
            grid[r][c] = 0 # Sink
            
            dfs(r + 1, c)
            dfs(r - 1, c)
            dfs(r, c + 1)
            dfs(r, c - 1)
            
        # 1. Sink boundary-connected land
        for r in range(rows):
            for c in range(cols):
                if (r == 0 or c == 0 or r == rows - 1 or c == cols - 1) and grid[r][c] == 1:
                    dfs(r, c)
                    
        # 2. Count remaining
        count = 0
        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == 1:
                    count += 1
        return count

if __name__ == "__main__":
    sol = Solution()
    
    grid1 = [
        [0,0,0,0],
        [1,0,1,0],
        [0,1,1,0],
        [0,0,0,0]
    ]
    print(f"Enclaves 1: {sol.numEnclaves([row[:] for row in grid1])}")

    grid2 = [
        [0,1,1,0],
        [0,0,1,0],
        [0,0,1,0],
        [0,0,0,0]
    ]
    print(f"Enclaves 2: {sol.numEnclaves([row[:] for row in grid2])}")
