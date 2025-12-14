# Word Search II

## 🧩 Problem Statement
Given an `m x n` board of characters and a list of strings `words`, return all words on the board.

Each word must be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.

### 🔹 Example 1:
#### Input:
```plaintext
board = [["o","a","a","n"],
         ["e","t","a","e"],
         ["i","h","k","r"],
         ["i","f","l","v"]]
words = ["oath","pea","eat","rain"]
```
#### Output:
```plaintext
["eat","oath"]
```

## 🔍 Approaches

### 1. Backtracking + Trie (Prefix Tree) ($O(M \cdot N \cdot 4^L)$)
- **Concept:** Instead of searching for each word individually (which would be `num_words * board_size * 4^len`), we can search for *all* words simultaneously using a Trie.
- **Algorithm:**
  1. **Build Trie:** Insert all words into a Trie. Store the actual `word` at the leaf node to avoid reconstructing it.
  2. **DFS (Backtracking):** Iterate through every cell `(i, j)` in the board.
     - Start DFS from `(i, j)` if `board[i][j]` is a child of the Trie root.
  3. **Trie Pruning:**
     - To optimize, when a word is found, remove it from the Trie (or mark it found) to avoid duplicate results.
     - Even better: Incrementally prune leaf nodes from the Trie. If a node has no children after finding a word, remove it from the parent's children map. This aggressively prunes the search space.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(M \cdot N \cdot 3^L)$ in worst case, where $L$ is max word length. However, Trie pruning makes it much faster on average.
- **Space Complexity:** $O(W \cdot L)$, where $W$ is number of words and $L$ is max length (for Trie storage).

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

class TrieNode {
public:
    TrieNode* children[26];
    string* word; // Store pointer to word at leaf
    
    TrieNode() {
        word = nullptr;
        for (int i = 0; i < 26; i++) children[i] = nullptr;
    }
};

class Solution {
    TrieNode* root;
    vector<string> result;
    int m, n;
    
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        root = new TrieNode();
        for (string& w : words) {
            insert(w);
        }
        
        m = board.size();
        n = board[0].size();
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (root->children[board[i][j] - 'a']) {
                    dfs(board, i, j, root);
                }
            }
        }
        return result;
    }
    
    void insert(string& word) {
        TrieNode* curr = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!curr->children[idx]) curr->children[idx] = new TrieNode();
            curr = curr->children[idx];
        }
        curr->word = &word;
    }
    
    void dfs(vector<vector<char>>& board, int i, int j, TrieNode* parent) {
        char letter = board[i][j];
        TrieNode* curr = parent->children[letter - 'a'];
        
        if (curr->word) {
            result.push_back(*curr->word);
            curr->word = nullptr; // Avoid duplicates
            // Optimization: Could prune leaf nodes here
        }
        
        board[i][j] = '#'; // Mark visited
        
        int dirs[4][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};
        for (auto& d : dirs) {
            int r = i + d[0], c = j + d[1];
            if (r >= 0 && r < m && c >= 0 && c < n && board[r][c] != '#' && curr->children[board[r][c] - 'a']) {
                dfs(board, r, c, curr);
            }
        }
        
        board[i][j] = letter; // Backtrack
    }
};
```

### Python
```python
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
```

### Java
```java
import java.util.*;

class Solution {
    class TrieNode {
        TrieNode[] children = new TrieNode[26];
        String word;
    }
    
    public List<String> findWords(char[][] board, String[] words) {
        TrieNode root = new TrieNode();
        for (String w : words) {
            TrieNode curr = root;
            for (char c : w.toCharArray()) {
                int idx = c - 'a';
                if (curr.children[idx] == null) curr.children[idx] = new TrieNode();
                curr = curr.children[idx];
            }
            curr.word = w;
        }
        
        List<String> result = new ArrayList<>();
        int m = board.length, n = board[0].length;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (root.children[board[i][j] - 'a'] != null) {
                    dfs(board, i, j, root, result);
                }
            }
        }
        return result;
    }
    
    // Pass parent to allow easier traversal to child
    private void dfs(char[][] board, int i, int j, TrieNode parent, List<String> result) {
        char letter = board[i][j];
        TrieNode curr = parent.children[letter - 'a'];
        
        if (curr.word != null) {
            result.add(curr.word);
            curr.word = null; // Avoid duplicates
        }
        
        board[i][j] = '#'; // Mark
        
        int[][] dirs = {{0,1}, {0,-1}, {1,0}, {-1,0}};
        for (int[] d : dirs) {
            int r = i + d[0];
            int c = j + d[1];
            if (r >= 0 && r < board.length && c >= 0 && c < board[0].length && 
                board[r][c] != '#' && curr.children[board[r][c] - 'a'] != null) {
                dfs(board, r, c, curr, result);
            }
        }
        
        board[i][j] = letter; // Backtrack
    }
}
```

## 🌍 Real-World Analogy
### **Boggle Game:**
You are scanning a grid of letters to find valid words. Using a dictionary (Trie), you instantly know if "Q-U-A..." can possibly lead to a word or if you should stop looking down this path.

## 🎯 Summary
✅ **Simultaneous Search:** The Trie allows checking all candidate words at once during the grid traversal.
