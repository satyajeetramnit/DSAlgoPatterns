# Permutation in String

## 🧩 Problem Statement
Given two strings `s1` and `s2`, return `true` if `s2` contains a permutation of `s1`, or `false` otherwise.

In other words, return `true` if one of `s1`'s permutations is the substring of `s2`.

### 🔹 Example 1:
#### Input:
```plaintext
s1 = "ab", s2 = "eidbaooo"
```
#### Output:
```plaintext
true
```
#### Explanation:
s2 contains one permutation of s1 ("ba").

### 🔹 Example 2:
#### Input:
```plaintext
s1 = "ab", s2 = "eidboaoo"
```
#### Output:
```plaintext
false
```

## 🔍 Approaches

### 1. Sliding Window with Frequency Array
A permutation of `s1` means a string with the same characters with the same frequencies.
The problem is equivalent to: Find if `s2` has a substring of length `len(s1)` with the same character counts.

We use a fixed-size sliding window of size `len(s1)`.
- Maintain a frequency array (or hash map) for `s1`.
- Maintain a frequency array for the current window in `s2`.
- As we slide the window:
  - Add the new character on the right.
  - Remove the old character on the left.
  - Check if the two frequency arrays match.

### ✨ Intuition
Instead of generating all permutations (factorial complexity), we just check character "fingerprints". If the sorted versions (or count maps) match, it's a permutation. Since sorting is $O(k \log k)$, and counting is $O(k)$, counting is faster for checking every window.

### 🔥 Algorithm Steps
1. Lengths: `m = len(s1)`, `n = len(s2)`. If `m > n`, return `false`.
2. Count freqs of `s1` and first `m` chars of `s2`.
3. If `freq1 == freq2`, return `true`.
4. Iterate `i` from `m` to `n - 1`:
   - Add `s2[i]` to `freq2`.
   - Remove `s2[i - m]` from `freq2`.
   - If `freq1 == freq2`, return `true`.
5. Return `false`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(n)$ or $O(26 \cdot n)$. Comparing arrays of size 26 is $O(1)$.
- **Space Complexity:** $O(1)$ (since map size is fixed at 26).

## 🚀 Code Implementations

### C++
```cpp
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        if (s1.length() > s2.length()) return false;
        
        vector<int> s1Count(26, 0);
        vector<int> s2Count(26, 0);
        
        for (int i = 0; i < s1.length(); i++) {
            s1Count[s1[i] - 'a']++;
            s2Count[s2[i] - 'a']++;
        }
        
        if (s1Count == s2Count) return true;
        
        for (int i = s1.length(); i < s2.length(); i++) {
            s2Count[s2[i] - 'a']++;
            s2Count[s2[i - s1.length()] - 'a']--;
            
            if (s1Count == s2Count) return true;
        }
        
        return false;
    }
};
```

### Python
```python
class Solution:
    def checkInclusion(self, s1: str, s2: str) -> bool:
        if len(s1) > len(s2):
            return False
        
        s1_count = [0] * 26
        s2_count = [0] * 26
        
        # Initialize
        for i in range(len(s1)):
            s1_count[ord(s1[i]) - ord('a')] += 1
            s2_count[ord(s2[i]) - ord('a')] += 1
            
        if s1_count == s2_count:
            return True
            
        # Slide
        for i in range(len(s1), len(s2)):
            s2_count[ord(s2[i]) - ord('a')] += 1
            s2_count[ord(s2[i - len(s1)]) - ord('a')] -= 1
            
            if s1_count == s2_count:
                return True
                
        return False
```

### Java
```java
import java.util.Arrays;

class Solution {
    public boolean checkInclusion(String s1, String s2) {
        if (s1.length() > s2.length()) return false;
        
        int[] s1Count = new int[26];
        int[] s2Count = new int[26];
        
        for (int i = 0; i < s1.length(); i++) {
            s1Count[s1.charAt(i) - 'a']++;
            s2Count[s2.charAt(i) - 'a']++;
        }
        
        if (Arrays.equals(s1Count, s2Count)) return true;
        
        for (int i = s1.length(); i < s2.length(); i++) {
            s2Count[s2.charAt(i) - 'a']++;
            s2Count[s2.charAt(i - s1.length()) - 'a']--;
            
            if (Arrays.equals(s1Count, s2Count)) return true;
        }
        
        return false;
    }
}
```

## 🌍 Real-World Analogy
### **ID Badge scanner:**
You have a specific ID code (s1). The scanner reads a continuous stream of data (s2). It needs to detect if the ID code appears anywhere in the stream, but the order of matched bytes doesn't matter (permutation), only their presence and counts count.

## 🎯 Summary
✅ **Fixed Size:** Window size is always `len(s1)`.
✅ **Fingerprint:** Use frequency arrays to represent "content" regardless of order.
