# Longest Substring Without Repeating Characters

## 🧩 Problem Statement
Given a string `s`, find the length of the **longest substring** without repeating characters.

### 🔹 Example 1:
#### Input:
```plaintext
s = "abcabcbb"
```
#### Output:
```plaintext
3
```
#### Explanation:
The answer is "abc", with the length of 3.

### 🔹 Example 2:
#### Input:
```plaintext
s = "bbbbb"
```
#### Output:
```plaintext
1
```
#### Explanation:
The answer is "b", with the length of 1.

### 🔹 Example 3:
#### Input:
```plaintext
s = "pwwkew"
```
#### Output:
```plaintext
3
```
#### Explanation:
The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.

## 🔍 Approaches

### 1. Sliding Window (Variable Size)
We maintain a window `[left, right]` that contains no duplicates.
- Expand `right` pointer to include a new character.
- If the new character is already in the window, shrink the window from the `left` until the duplicate is removed.
- Record the maximum size of the window.

### ✨ Intuition
Instead of checking all substrings ($O(n^2)$), we dynamically adjust the window. A duplicate means we just need to drop the prefix up to the first occurrence of that duplicate.

### 🔥 Algorithm Steps
1. Initialize `left = 0`, `maxLength = 0`.
2. Use a Set (or Map) `charSet` to store characters in the current window.
3. Iterate `right` from `0` to `n-1`:
   - While `s[right]` is in `charSet`:
     - Remove `s[left]` from `charSet`.
     - Increment `left`.
   - Add `s[right]` to `charSet`.
   - `maxLength = max(maxLength, right - left + 1)`.
4. Return `maxLength`.

### 🚀 Optimization (Map)
Instead of incrementing `left` one by one, if we know the index of the previous occurrence, we can jump `left` directly to `prevIndex + 1`.
- Use a Map: `char -> index`.
- `left = max(left, map[s[right]] + 1)`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(n)$. Each character is added and removed at most once.
- **Space Complexity:** $O(\min(n, \Sigma))$, where $\Sigma$ is the charset size (e.g., 26 or 128).

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> charSet;
        int left = 0, maxLength = 0;
        
        for (int right = 0; right < s.length(); right++) {
            while (charSet.count(s[right])) {
                charSet.erase(s[left]);
                left++;
            }
            charSet.insert(s[right]);
            maxLength = max(maxLength, right - left + 1);
        }
        return maxLength;
    }
};
```

### Python
```python
class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        char_set = set()
        left = 0
        max_length = 0
        
        for right in range(len(s)):
            while s[right] in char_set:
                char_set.remove(s[left])
                left += 1
            char_set.add(s[right])
            max_length = max(max_length, right - left + 1)
            
        return max_length
```

### Java
```java
import java.util.HashSet;
import java.util.Set;

class Solution {
    public int lengthOfLongestSubstring(String s) {
        Set<Character> charSet = new HashSet<>();
        int left = 0;
        int maxLength = 0;
        
        for (int right = 0; right < s.length(); right++) {
            while (charSet.contains(s.charAt(right))) {
                charSet.remove(s.charAt(left));
                left++;
            }
            charSet.add(s.charAt(right));
            maxLength = Math.max(maxLength, right - left + 1);
        }
        return maxLength;
    }
}
```

## 🌍 Real-World Analogy
### **Caterpillar:**
A caterpillar expands its head (`right`). If it touches a "poisonous duplicate" leaf, it pulls its tail (`left`) forward until it is safe again. It wants to stretch as long as possible.

## 🎯 Summary
✅ **Variable Window:** Window size changes dynamically.
✅ **Set/Map:** Used to track constraints (uniqueness).
