# Longest Repeating Character Replacement

## 🧩 Problem Statement
You are given a string `s` and an integer `k`. You can choose any character of the string and change it to any other uppercase English character. You can perform this operation at most `k` times.

Return the length of the longest substring containing the same letter you can get after performing the above operations.

### 🔹 Example 1:
#### Input:
```plaintext
s = "ABAB", k = 2
```
#### Output:
```plaintext
4
```
#### Explanation:
Replace the two 'A's with 'B's or vice versa. The resulting string is "AAAA" or "BBBB".

### 🔹 Example 2:
#### Input:
```plaintext
s = "AABABBA", k = 1
```
#### Output:
```plaintext
4
```
#### Explanation:
Replace the one 'B' in the middle with 'A'. Substring "AABA" becomes "AAAA".

## 🔍 Approaches

### 1. Sliding Window (Frequency Count)
The goal is to find the longest substring where `(Length) - (Count of most frequent char) <= k`.
- `Length` is the total characters in the window.
- `Count of most frequent char` are the characters we *don't* want to change.
- The remaining characters are the ones we *must* change. If this count is $\le k$, the window is valid.

### ✨ Intuition
We want to keep the window valid.
- Expand `right` to grow.
- Update frequency of `s[right]`. Track `maxFreq` seen in the current window.
- Check condition: `(right - left + 1) - maxFreq > k`.
- If invalid (need too many replacements), shrink `left` until valid.

### 🔥 Algorithm Steps
1. Initialize `left = 0`, `maxFreq = 0`, `maxLen = 0`.
2. Frequency array/map `count`.
3. Iterate `right` from `0` to `n-1`:
   - `count[s[right]]++`.
   - `maxFreq = max(maxFreq, count[s[right]])`.
   - While `(right - left + 1) - maxFreq > k`:
     - `count[s[left]]--`.
     - `left++`.
     - (Note: We don't need to update `maxFreq` downwards for the logic to finding the *longest* valid window, but strictly for validity we might. In the standard optimal solution, we don't strictly decrease `maxFreq`, because we only care if we find a *better* maxFreq to support a larger window).
   - `maxLen = max(maxLen, right - left + 1)`.
4. Return `maxLen`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(n)$.
- **Space Complexity:** $O(26)$ or $O(1)$.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int characterReplacement(string s, int k) {
        vector<int> count(26, 0);
        int left = 0, maxFreq = 0, maxLen = 0;
        
        for (int right = 0; right < s.length(); right++) {
            count[s[right] - 'A']++;
            maxFreq = max(maxFreq, count[s[right] - 'A']);
            
            // If replacements needed > k, shrink window
            // Use if statement instead of while for optimal performance 
            // because we only care if window grows larger than known maxLen
            if ((right - left + 1) - maxFreq > k) {
                count[s[left] - 'A']--;
                left++;
            }
            
            maxLen = max(maxLen, right - left + 1);
        }
        return maxLen;
    }
};
```

### Python
```python
class Solution:
    def characterReplacement(self, s: str, k: int) -> int:
        count = {}
        left = 0
        max_freq = 0
        max_len = 0
        
        for right in range(len(s)):
            char = s[right]
            count[char] = count.get(char, 0) + 1
            max_freq = max(max_freq, count[char])
            
            # If invalid, shrink
            if (right - left + 1) - max_freq > k:
                count[s[left]] -= 1
                left += 1
            
            max_len = max(max_len, right - left + 1)
            
        return max_len
```

### Java
```java
class Solution {
    public int characterReplacement(String s, int k) {
        int[] count = new int[26];
        int left = 0;
        int maxFreq = 0;
        int maxLen = 0;
        
        for (int right = 0; right < s.length(); right++) {
            count[s.charAt(right) - 'A']++;
            maxFreq = Math.max(maxFreq, count[s.charAt(right) - 'A']);
            
            if ((right - left + 1) - maxFreq > k) {
                count[s.charAt(left) - 'A']--;
                left++;
            }
            
            maxLen = Math.max(maxLen, right - left + 1);
        }
        return maxLen;
    }
}
```

## 🌍 Real-World Analogy
### **Renovating a Fence:**
You have a fence with painted planks. You have `k` cans of paint.
You want the longest continuous section of the same color.
You pick a section. Identify the dominant color. Can you paint the other planks with `k` cans? If yes, great. If not, pick a smaller or different section.

## 🎯 Summary
✅ **Validity Condition:** `WindowSize - MaxCharCount <= k`.
✅ **Optimization:** We don't strictly need to shrink the window size (just shift it) if we haven't found a better `maxFreq` to support a larger size.
