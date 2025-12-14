from typing import List

class Solution:
    def gameOfLife(self, board: List[List[int]]) -> None:
        m, n = len(board), len(board[0])
        neighbors = [(-1,-1), (-1,0), (-1,1), (0,-1), (0,1), (1,-1), (1,0), (1,1)]
        
        for i in range(m):
            for j in range(n):
                live_neighbors = 0
                for r, c in neighbors:
                    nr, nc = i + r, j + c
                    if 0 <= nr < m and 0 <= nc < n and abs(board[nr][nc]) == 1:
                        live_neighbors += 1
                
                if board[i][j] == 1 and (live_neighbors < 2 or live_neighbors > 3):
                    board[i][j] = -1 # Live -> Dead
                if board[i][j] == 0 and live_neighbors == 3:
                    board[i][j] = 2 # Dead -> Live
                    
        for i in range(m):
            for j in range(n):
                if board[i][j] > 0:
                    board[i][j] = 1
                else:
                    board[i][j] = 0

if __name__ == "__main__":
    sol = Solution()
    board = [[0,1,0],[0,0,1],[1,1,1],[0,0,0]]
    sol.gameOfLife(board)
    print(f"Test Case 1 Output: {board}")
    # Expect: [[0, 0, 0], [1, 0, 1], [0, 1, 1], [0, 1, 0]]
