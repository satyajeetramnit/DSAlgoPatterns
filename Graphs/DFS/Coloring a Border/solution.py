from typing import List

class Solution:
    def colorBorder(self, grid: List[List[int]], row: int, col: int, color: int) -> List[List[int]]:
        old_color = grid[row][col]
        rows, cols = len(grid), len(grid[0])
        visited = set()
        borders = []
        
        def dfs(r, c):
            visited.add((r, c))
            is_border = False
            
            for dr, dc in [(-1,0), (1,0), (0,-1), (0,1)]:
                nr, nc = r + dr, c + dc
                
                if 0 <= nr < rows and 0 <= nc < cols:
                    if grid[nr][nc] == old_color:
                        if (nr, nc) not in visited:
                            dfs(nr, nc)
                    else:
                        is_border = True # Neighbor is diff color
                else:
                    is_border = True # Out of bounds
            
            if is_border:
                borders.append((r, c))
        
        dfs(row, col)
        
        for r, c in borders:
            grid[r][c] = color
            
        return grid

if __name__ == "__main__":
    sol = Solution()
    
    grid1 = [[1,1],[1,2]]
    print(f"Colored 1: {sol.colorBorder([row[:] for row in grid1], 0, 0, 3)}")

    grid2 = [[1,2,2],[2,3,2]]
    print(f"Colored 2: {sol.colorBorder([row[:] for row in grid2], 0, 1, 3)}")
