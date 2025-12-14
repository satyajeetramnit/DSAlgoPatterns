# Maximum Product of Word Lengths

## 🧩 Problem Statement
Given a string array `words`, return the maximum value of `length(word[i]) * length(word[j])` where the two words do not share common letters. If no such two words exist, return 0.

### 🔹 Example 1:
#### Input:
```plaintext
words = ["abcw","baz","foo","bar","xtfn","abcdef"]
```
#### Output:
```plaintext
16
```
**Explanation:** The two words can be "abcw", "xtfn".

### 🔹 Example 2:
#### Input:
```plaintext
words = ["a","ab","abc","d","cd","bcd","abcd"]
```
#### Output:
```plaintext
4
```
**Explanation:** The two words can be "ab", "cd".

### 🔹 Example 3:
#### Input:
```plaintext
words = ["a","aa","aaa","aaaa"]
```
#### Output:
```plaintext
0
```
**Explanation:** No such pair of words.

## 🔍 Approaches

### 1. Bitmask Optimization
- **Goal:** Check intersection of characters between two words efficiently.
- **Representation:** Since words consist of lowercase English letters ('a'-'z'), we can use a 26-bit integer (mask) for each word.
  - If character 'a' is present, set 0-th bit.
  - If 'b' is present, set 1-st bit, etc.
- **Intersection Check:** `(mask[i] & mask[j]) == 0` implies no common letters.
- **Optimization:** If multiple words have the same bitmask (same set of unique characters), we only care about the one with the maximum length. Store `map<mask, max_length>`.
- **Algorithm:**
  1. Compute mask and length for each word. Store `max_len[mask] = max(max_len[mask], length)`.
  2. Iterate through all pairs of masks.
  3. If `(mask1 & mask2) == 0`: `result = max(result, len1 * len2)`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N^2 + N \cdot L)$, where $N$ is number of words and $L$ is average length.
- **Space Complexity:** $O(N)$ to store masks.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int maxProduct(vector<string>& words) {
        int n = words.size();
        vector<int> masks(n, 0);
        vector<int> lens(n, 0);
        
        for (int i = 0; i < n; ++i) {
            lens[i] = words[i].size();
            for (char c : words[i]) {
                masks[i] |= (1 << (c - 'a'));
            }
        }
        
        int maxProd = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if ((masks[i] & masks[j]) == 0) {
                    maxProd = max(maxProd, lens[i] * lens[j]);
                }
            }
        }
        
        return maxProd;
    }
};
```

### Python
```python
from typing import List

class Solution:
    def maxProduct(self, words: List[str]) -> int:
        n = len(words)
        masks = [0] * n
        lens = [0] * n
        
        for i, w in enumerate(words):
            lens[i] = len(w)
            for char in w:
                masks[i] |= (1 << (ord(char) - ord('a')))
                
        max_prod = 0
        for i in range(n):
            for j in range(i + 1, n):
                if (masks[i] & masks[j]) == 0:
                    max_prod = max(max_prod, lens[i] * lens[j])
                    
        return max_prod
```

### Java
```java
class Solution {
    public int maxProduct(String[] words) {
        int n = words.length;
        int[] masks = new int[n];
        int[] lens = new int[n];
        
        for (int i = 0; i < n; i++) {
            lens[i] = words[i].length();
            for (char c : words[i].toCharArray()) {
                masks[i] |= (1 << (c - 'a'));
            }
        }
        
        int maxProd = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if ((masks[i] & masks[j]) == 0) {
                    maxProd = Math.max(maxProd, lens[i] * lens[j]);
                }
            }
        }
        
        return maxProd;
    }
}
```

## 🌍 Real-World Analogy
### **Chemistry Lab Scheduling:**
Two experiments can run simultaneously only if they don't share any hazardous chemicals. Each chemical is a bit in a mask. If the AND of two experiment masks is zero, they are safe (disjoint) and can be chosen to maximize throughput (product).

## 🎯 Summary
✅ **Data Compression:** Reducing a string's character set to a single integer allows O(1) intersection checks.
