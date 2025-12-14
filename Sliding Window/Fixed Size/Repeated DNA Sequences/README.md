# Repeated DNA Sequences

## 🧩 Problem Statement
The DNA sequence is composed of a series of nucleotides abbreviated as `'A'`, `'C'`, `'G'`, and `'T'`.
Given a string `s` that represents a DNA sequence, return all the **10-letter-long** sequences (substrings) that occur more than once in a DNA molecule. You may return the answer in **any order**.

### 🔹 Example 1:
#### Input:
```plaintext
s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"
```
#### Output:
```plaintext
["AAAAACCCCC","CCCCCAAAAA"]
```

### 🔹 Example 2:
#### Input:
```plaintext
s = "AAAAAAAAAAAAA"
```
#### Output:
```plaintext
["AAAAAAAAAA"]
```

## 🔍 Approaches

### 1. Sliding Window with Hash Set
We need to check every substring of length 10.
- Use a sliding window of size `L = 10`.
- Maintain a `seen` hash set to track substrings we've encountered.
- Maintain a `repeated` hash set to track the answers (to avoid duplicates in the output).
- Iterate through the string, extracting the substring at each position `i`.
- If substring is in `seen`, add to `repeated`.
- Else, add to `seen`.

### ✨ Intuition
This is a direct application of checking "have I seen this before?". Since the window size is fixed and small (10), extracting and hashing the substring is efficient enough for typical constraints ($N \le 10^5$).

### 🔥 Algorithm Steps
1. Create `seen` set and `repeated` set.
2. Iterate `i` from `0` to `n - 10`.
3. Extract `sub = s.substring(i, i + 10)`.
4. If `sub` in `seen`:
   - Add `sub` to `repeated`.
5. Else:
   - Add `sub` to `seen`.
6. Return elements of `repeated`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N \cdot L)$, where $N$ is string length and $L=10$.
- **Space Complexity:** $O(N \cdot L)$, to store the substrings in the sets.

## 🚀 Code Implementations

### C++
```cpp
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        unordered_set<string> seen, repeated;
        if (s.length() < 10) return {};
        
        for (int i = 0; i <= s.length() - 10; ++i) {
            string sub = s.substr(i, 10);
            if (seen.count(sub)) {
                repeated.insert(sub);
            } else {
                seen.insert(sub);
            }
        }
        return vector<string>(repeated.begin(), repeated.end());
    }
};
```

### Python
```python
class Solution:
    def findRepeatedDnaSequences(self, s: str) -> List[str]:
        seen, repeated = set(), set()
        
        for i in range(len(s) - 9):
            sub = s[i : i+10]
            if sub in seen:
                repeated.add(sub)
            else:
                seen.add(sub)
                
        return list(repeated)
```

### Java
```java
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

class Solution {
    public List<String> findRepeatedDnaSequences(String s) {
        Set<String> seen = new HashSet<>();
        Set<String> repeated = new HashSet<>();
        
        for (int i = 0; i <= s.length() - 10; i++) {
            String sub = s.substring(i, i + 10);
            if (seen.contains(sub)) {
                repeated.add(sub);
            } else {
                seen.add(sub);
            }
        }
        return new ArrayList<>(repeated);
    }
}
```

## 🌍 Real-World Analogy
### **Plagiarism Detection:**
Imagine scanning a long essay. You look at every sequence of 10 words.
- You write down every 10-word phrase you see.
- If you encounter a phrase you've already written down, you flag it as "repeated" (potential plagiarism or just a common phrase).

## 🎯 Summary
✅ **Fixed Window:** Window size is constant (10).
✅ **Hashing:** Using hashing allows $O(1)$ (amortized) lookup to check for duplicates.
