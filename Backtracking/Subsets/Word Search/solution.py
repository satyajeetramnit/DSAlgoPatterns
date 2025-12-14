from typing import List

class Solution:
    def exist(self, board: List[List[str]], word: str) -> bool:
        rows, cols = len(board), len(board[0])
        
        def dfs(r, c, index):
            if index == len(word):
                return True
            
            if (r < 0 or c < 0 or r >= rows or c >= cols or 
                board[r][c] != word[index]):
                return False
            
            temp = board[r][c]
            board[r][c] = '#' # Mark visited
            
            found = (dfs(r + 1, c, index + 1) or
                     dfs(r - 1, c, index + 1) or
                     dfs(r, c + 1, index + 1) or
                     dfs(r, c - 1, index + 1))
            
            board[r][c] = temp # Backtrack
            return found

        for i in range(rows):
            for j in range(cols):
                if board[i][j] == word[0] and dfs(i, j, 0):
                    return True
        return False

if __name__ == "__main__":
    sol = Solution()
    board = [
        ['A','B','C','E'],
        ['S','F','C','S'],
        ['A','D','E','E']
    ]
    print(f"Exist ABCCED: {sol.exist(board, 'ABCCED')}")
    print(f"Exist SEE: {sol.exist(board, 'SEE')}")
    print(f"Exist ABCB: {sol.exist(board, 'ABCB')}")
