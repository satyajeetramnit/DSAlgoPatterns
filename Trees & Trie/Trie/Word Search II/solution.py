from typing import List

class TrieNode:
    def __init__(self):
        self.children = {}
        self.word = None

class Solution:
    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        root = TrieNode()
        for w in words:
            curr = root
            for c in w:
                if c not in curr.children:
                    curr.children[c] = TrieNode()
                curr = curr.children[c]
            curr.word = w
            
        m, n = len(board), len(board[0])
        res = []
        
        def dfs(i, j, parent):
            letter = board[i][j]
            curr_node = parent.children[letter]
            
            if curr_node.word:
                res.append(curr_node.word)
                curr_node.word = None # Avoid duplicates
            
            board[i][j] = "#"
            
            for r, c in [(i+1, j), (i-1, j), (i, j+1), (i, j-1)]:
                if 0 <= r < m and 0 <= c < n and board[r][c] in curr_node.children:
                    dfs(r, c, curr_node)
            
            board[i][j] = letter
            
            # Optimization: leaf node pruning
            if not curr_node.children:
                del parent.children[letter]
        
        for i in range(m):
            for j in range(n):
                if board[i][j] in root.children:
                    dfs(i, j, root)
                    
        return res

if __name__ == "__main__":
    sol = Solution()
    board = [
        ["o","a","a","n"],
        ["e","t","a","e"],
        ["i","h","k","r"],
        ["i","f","l","v"]
    ]
    words = ["oath","pea","eat","rain"]
    result = sol.findWords(board, words)
    result.sort()
    print(f"Test Case 1: {result}") # Expect ["eat", "oath"]
