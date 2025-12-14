from typing import List

class Solution:
    def solveNQueens(self, n: int) -> List[List[str]]:
        res = []
        col_set = set()
        pos_diag = set() # r + c
        neg_diag = set() # r - c
        board = [['.'] * n for _ in range(n)]
        
        def backtrack(r):
            if r == n:
                copy = ["".join(row) for row in board]
                res.append(copy)
                return
            
            for c in range(n):
                if c in col_set or (r + c) in pos_diag or (r - c) in neg_diag:
                    continue
                
                col_set.add(c)
                pos_diag.add(r + c)
                neg_diag.add(r - c)
                board[r][c] = 'Q'
                
                backtrack(r + 1)
                
                col_set.remove(c)
                pos_diag.remove(r + c)
                neg_diag.remove(r - c)
                board[r][c] = '.'
                
        backtrack(0)
        return res

if __name__ == "__main__":
    sol = Solution()
    n1 = 4
    print(f"Solutions for N=4: {sol.solveNQueens(n1)}")
    
    n2 = 1
    print(f"Solutions for N=1: {sol.solveNQueens(n2)}")
