# Group Anagrams

## 🧩 Problem Statement
Given an array of strings `strs`, group the anagrams together. You can return the answer in **any order**.

An **Anagram** is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once.

### 🔹 Example 1:
#### Input:
```plaintext
strs = ["eat","tea","tan","ate","nat","bat"]
```
#### Output:
```plaintext
[["bat"],["nat","tan"],["ate","eat","tea"]]
```

### 🔹 Example 2:
#### Input:
```plaintext
strs = [""]
```
#### Output:
```plaintext
[[""]]
```

## 🔍 Approaches

### 1. Categorize by Count (Hash Map)
Two strings are anagrams if and only if their character counts (how many 'a's, 'b's, etc.) are exactly the same.

### ✨ Intuition
- We can transform each string into a "key" that represents its character count.
- `eat` -> `1 'a', 1 'e', 1 't'` -> key `(1, 0, 0, ..., 1, ..., 1)` (tuple of 26 counts).
- `tea` -> key `(1, 0, 0, ..., 1, ..., 1)`.
- All anagrams will map to the same key.
- We group strings in a hash map where `key` -> `list of strings`.

### 🔥 Algorithm Steps
1. Initialize `ans` as a default dictionary (hash map) mapping values to lists.
2. Iterate through each string `s` in `strs`.
3. Create a count array of size 26 (initialized to 0) for each string.
4. Count the frequency of each char in `s` and update the array.
5. Convert the array to a tuple (immutable) to use as a key.
6. Append `s` to the list at `ans[key]`.
7. Return `ans.values()`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(m \cdot n)$, where $m$ is the number of strings and $n$ is the average length of a string. Counting takes $O(n)$ for each string.
- **Space Complexity:** $O(m \cdot n)$, to store the strings in the hash map.

## 🚀 Code Implementations

### C++
```cpp
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> m;
        for (string s : strs) {
            string t = s;
            sort(t.begin(), t.end()); // Using sorted string as key
            m[t].push_back(s);
        }
        vector<vector<string>> result;
        for (auto p : m) {
            result.push_back(p.second);
        }
        return result;
    }
};
```
> **Note:** The C++ solution above uses sorting as the key ($O(m \cdot n \log n)$) which is easier to implement with `std::string`.

### Python
```python
from collections import defaultdict

class Solution:
    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        ans = defaultdict(list)
        
        for s in strs:
            count = [0] * 26
            for c in s:
                count[ord(c) - ord("a")] += 1
            ans[tuple(count)].append(s)
        return list(ans.values())
```

### Java
```java
class Solution {
    public List<List<String>> groupAnagrams(String[] strs) {
        if (strs == null || strs.length == 0) return new ArrayList<>();
        Map<String, List<String>> map = new HashMap<>();
        for (String s : strs) {
            char[] ca = s.toCharArray();
            Arrays.sort(ca);
            String keyStr = String.valueOf(ca);
            if (!map.containsKey(keyStr)) map.put(keyStr, new ArrayList<>());
            map.get(keyStr).add(s);
        }
        return new ArrayList<>(map.values());
    }
}
```

## 🌍 Real-World Analogy
### **Sorting Laundry:**
Imagine you have a pile of socks (strings).
- You want to group them by type (anagrams).
- You pick up a sock, identify its "signature" (color, pattern, size) -> this is grouping by "character count".
- You throw all matching socks into the same basket (list).

## 🎯 Summary
✅ **Canonical Form:** Anagrams share a canonical form (sorted string or char count).
✅ **Hash Map:** Efficiently groups items by key.
