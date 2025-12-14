# Design Add and Search Words Data Structure

## 🧩 Problem Statement
Design a data structure that supports adding new words and finding if a string matches any previously added string.

Implement the `WordDictionary` class:
- `WordDictionary()` Initializes the object.
- `void addWord(word)` Adds `word` to the data structure, it can be matched later.
- `bool search(word)` Returns `true` if there is any string in the data structure that matches `word` or `false` otherwise. `word` may contain dots `'.'` where dots can be matched with any letter.

### 🔹 Example 1:
#### Input:
```plaintext
WordDictionary wordDictionary = new WordDictionary();
wordDictionary.addWord("bad");
wordDictionary.addWord("dad");
wordDictionary.addWord("mad");
wordDictionary.search("pad"); // return False
wordDictionary.search("bad"); // return True
wordDictionary.search(".ad"); // return True
wordDictionary.search("b.."); // return True
```

## 🔍 Approaches

### 1. Trie + DFS ($O(M)$)
- **Concept:** Standard Trie for storage.
- **Search (Wildcard `.`):**
  - If char is a letter, proceed as normal.
  - If char is `.`, we must try **all 26 possible children** of the current node. If any path returns `true`, then the word matches.
- **Algorithm:**
  - `addWord`: Standard Trie insert.
  - `search(word, index, node)`:
    - Base case: if `index == length`, return `node.isEnd`.
    - If `word[index]` is a character: go to that child.
    - If `word[index]` is `.`: Loop through all children of `node`. Recurse for each non-null child.

## ⏳ Time & Space Complexity
- **Time Complexity:**
  - `addWord`: $O(L)$
  - `search`: $O(L)$ for words without dots. $O(26^L)$ worst case for strings like `"...."` (effectively iterating the whole trie), though typically much faster.
- **Space Complexity:** $O(N \cdot L)$ for Trie storage.

## 🚀 Code Implementations

### C++
```cpp
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class TrieNode {
public:
    TrieNode* children[26];
    bool isEnd;
    
    TrieNode() {
        isEnd = false;
        for (int i = 0; i < 26; i++) children[i] = nullptr;
    }
};

class WordDictionary {
    TrieNode* root;
public:
    WordDictionary() {
        root = new TrieNode();
    }
    
    void addWord(string word) {
        TrieNode* curr = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!curr->children[idx]) curr->children[idx] = new TrieNode();
            curr = curr->children[idx];
        }
        curr->isEnd = true;
    }
    
    bool search(string word) {
        return searchHelper(word, 0, root);
    }
    
    bool searchHelper(string& word, int index, TrieNode* node) {
        if (index == word.length()) {
            return node->isEnd;
        }
        
        char c = word[index];
        if (c == '.') {
            for (int i = 0; i < 26; i++) {
                if (node->children[i] && searchHelper(word, index + 1, node->children[i])) {
                    return true;
                }
            }
            return false;
        } else {
            int idx = c - 'a';
            if (!node->children[idx]) return false;
            return searchHelper(word, index + 1, node->children[idx]);
        }
    }
};
```

### Python
```python
class TrieNode:
    def __init__(self):
        self.children = {}
        self.is_end = False

class WordDictionary:
    def __init__(self):
        self.root = TrieNode()

    def addWord(self, word: str) -> None:
        curr = self.root
        for char in word:
            if char not in curr.children:
                curr.children[char] = TrieNode()
            curr = curr.children[char]
        curr.is_end = True

    def search(self, word: str) -> bool:
        def dfs(index, node):
            if index == len(word):
                return node.is_end
            
            char = word[index]
            if char == ".":
                for child in node.children.values():
                    if dfs(index + 1, child):
                        return True
                return False
            else:
                if char not in node.children:
                    return False
                return dfs(index + 1, node.children[char])
        
        return dfs(0, self.root)
```

### Java
```java
class TrieNode {
    TrieNode[] children = new TrieNode[26];
    boolean isEnd = false;
}

class WordDictionary {
    private TrieNode root;

    public WordDictionary() {
        root = new TrieNode();
    }
    
    public void addWord(String word) {
        TrieNode curr = root;
        for (char c : word.toCharArray()) {
            int idx = c - 'a';
            if (curr.children[idx] == null) curr.children[idx] = new TrieNode();
            curr = curr.children[idx];
        }
        curr.isEnd = true;
    }
    
    public boolean search(String word) {
        return searchHelper(word, 0, root);
    }
    
    private boolean searchHelper(String word, int index, TrieNode node) {
        if (index == word.length()) {
            return node.isEnd;
        }
        
        char c = word.charAt(index);
        if (c == '.') {
            for (int i = 0; i < 26; i++) {
                if (node.children[i] != null && searchHelper(word, index + 1, node.children[i])) {
                    return true;
                }
            }
            return false;
        } else {
            int idx = c - 'a';
            if (node.children[idx] == null) return false;
            return searchHelper(word, index + 1, node.children[idx]);
        }
    }
}
```

## 🌍 Real-World Analogy
### **Crossword Solver:**
You have "C _ T". You check your dictionary. Is "CAT" there? Yes. Is "COT" there? Yes. Is "CUT" there? Yes. The dot represents "any letter fits here".

## 🎯 Summary
✅ **Handling Wildcards:** The DFS approach allows branching out to all possible children when a wildcard is encountered, effectively searching multiple paths.
