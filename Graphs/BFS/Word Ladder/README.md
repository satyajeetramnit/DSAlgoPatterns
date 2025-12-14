# Word Ladder

## 🧩 Problem Statement
A **transformation sequence** from word `beginWord` to word `endWord` using a dictionary `wordList` is a sequence of words `beginWord -> s1 -> s2 -> ... -> sk` such that:
1. Every adjacent pair of words differs by a single letter.
2. Every `si` for `1 <= i <= k` is in `wordList`. Note that `beginWord` does not need to be in `wordList`.
3. `sk == endWord`.

Given two words, `beginWord` and `endWord`, and a dictionary `wordList`, return the **number of words** in the **shortest transformation sequence** from `beginWord` to `endWord`, or `0` if no such sequence exists.

### 🔹 Example 1:
#### Input:
```plaintext
beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
```
#### Output:
```plaintext
5
```
**Explanation:** One shortest transformation sequence is `"hit" -> "hot" -> "dot" -> "dog" -> "cog"`, which is 5 words long.

### 🔹 Example 2:
#### Input:
```plaintext
beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
```
#### Output:
```plaintext
0
```
**Explanation:** The endWord "cog" is not in wordList, therefore there is no valid transformation sequence.

## 🔍 Approaches

### 1. Breadth-First Search (BFS)
Since we need the **shortest** transformation sequence, logic dictates BFS. We can treat each word as a node in a graph. An edge exists between two nodes if they differ by exactly one character.

#### Algorithm Steps:
1. **Pre-processing:** Convert `wordList` to a `Set` for $O(1)$ lookups. If `endWord` not in set, return 0.
2. **Initialize:** Queue `q` with `(beginWord, 1)`. `1` is the current sequence length.
3. **BFS:**
   - Loop while queue is not empty.
   - Pop `currentWord`.
   - If `currentWord == endWord`, return `currentLength`.
   - **Neighbors Generation:**
     - For each position `j` in `currentWord` (0 to L-1):
       - Try replacing with every char `a-z`.
       - If new word exists in `Set`:
         - Add to `q` with `currentLength + 1`.
         - **Remove from Set** to mark as visited (prevent cycles and redundant processing).
4. If queue empties, return 0.

### 🏛️ Visual Logic: BFS Layering for "hit" -> "cog"

#### Step 1: Initialize
- **Queue**: `[("hit", 1)]`
- **Visited**: `{"hit"}` (implicitly)
- **Goal**: Reach "cog"

<!-- slide -->

#### Step 2: Level 1 Expansion
- **Process**: "hit"
- **Neighbors**: Change 'i' -> 'o' gives "hot" (in list).
- **Queue**: `[("hot", 2)]`
- **Visited**: `{"hit", "hot"}`

<!-- slide -->

#### Step 3: Level 2 Expansion
- **Process**: "hot"
- **Neighbors**:
  - h -> d ("dot")
  - h -> l ("lot")
- **Queue**: `[("dot", 3), ("lot", 3)]`
- **Visited**: `+ "dot", "lot"`

<!-- slide -->

#### Step 4: Level 3 Expansion
- **Process**: "dot" -> neighbors "dog"
- **Process**: "lot" -> neighbors "log"
- **Queue**: `[("dog", 4), ("log", 4)]`
- **Visited**: `+ "dog", "log"`

<!-- slide -->

#### Step 5: Level 4 Expansion (Goal)
- **Process**: "dog" -> neighbors "cog" (Goal!)
- **Result**: Return Length **5**.


## ⏳ Time & Space Complexity
- **Time Complexity:** $O(M^2 \cdot N)$, where M is word length and N is number of words. Generating neighbors takes $O(M \cdot 26)$, and string operations take $O(M)$.
- **Space Complexity:** $O(N)$ for the queue.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <string>
#include <unordered_set>
#include <queue>

using namespace std;

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        if (wordSet.find(endWord) == wordSet.end()) return 0;
        
        queue<pair<string, int>> q;
        q.push({beginWord, 1});
        
        while (!q.empty()) {
            auto [word, len] = q.front();
            q.pop();
            
            if (word == endWord) return len;
            
            for (int i = 0; i < word.length(); ++i) {
                char original = word[i];
                for (char c = 'a'; c <= 'z'; ++c) {
                    if (c == original) continue;
                    word[i] = c;
                    if (wordSet.count(word)) {
                        q.push({word, len + 1});
                        wordSet.erase(word); // Mark visited
                    }
                }
                word[i] = original; // Restore
            }
        }
        return 0;
    }
};
```

### Python
```python
from typing import List
from collections import deque

class Solution:
    def ladderLength(self, beginWord: str, endWord: str, wordList: List[str]) -> int:
        wordSet = set(wordList)
        if endWord not in wordSet:
            return 0
        
        q = deque([(beginWord, 1)])
        
        while q:
            word, length = q.popleft()
            
            if word == endWord:
                return length
            
            for i in range(len(word)):
                original_char = word[i]
                for c in "abcdefghijklmnopqrstuvwxyz":
                    if c == original_char:
                        continue
                        
                    new_word = word[:i] + c + word[i+1:]
                    
                    if new_word in wordSet:
                        wordSet.remove(new_word) # Mark visited
                        q.append((new_word, length + 1))
        return 0
```

### Java
```java
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.Set;

class Solution {
    public int ladderLength(String beginWord, String endWord, List<String> wordList) {
        Set<String> wordSet = new HashSet<>(wordList);
        if (!wordSet.contains(endWord)) return 0;
        
        Queue<String> q = new LinkedList<>();
        q.offer(beginWord);
        int length = 1;
        
        while (!q.isEmpty()) {
            int size = q.size();
            while (size-- > 0) {
                String word = q.poll();
                if (word.equals(endWord)) return length;
                
                char[] chars = word.toCharArray();
                for (int i = 0; i < chars.length; i++) {
                    char original = chars[i];
                    for (char c = 'a'; c <= 'z'; c++) {
                        if (c == original) continue;
                        chars[i] = c;
                        String newWord = new String(chars);
                        
                        if (wordSet.contains(newWord)) {
                            q.offer(newWord);
                            wordSet.remove(newWord); // Mark visited
                        }
                    }
                    chars[i] = original; // Restore
                }
            }
            length++;
        }
        return 0;
    }
}
```

## 🌍 Real-World Analogy
### **Genetic Mutation:**
Imagine a DNA sequence mutating one gene at a time. The dictionary represents viable organisms. You want to see how many mutations it takes to evolve from Organism A to Organism B.

## 🎯 Summary
✅ **Implied Graph:** Nodes are words, edges are 1-letter changes.
✅ **Visited Set:** `wordSet.remove(newWord)` acts as efficient visited tracking.
