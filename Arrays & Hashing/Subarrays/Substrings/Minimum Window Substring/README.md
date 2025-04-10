# Minimum Window Substring

## 🧩 Problem Statement
Given two strings **s** and **t** of lengths *m* and *n* respectively, return the **minimum window substring** of **s** such that every character in **t** (including duplicates) is included in the window. If there is no such substring, return the empty string `""`.

### 🔹 Example 1
**Input:**
```plaintext
s = "ADOBECODEBANC", t = "ABC"
```
**Output:**
```plaintext
"BANC"
```
**Explanation:**
The substring `"BANC"` is the smallest window in **s** that contains all characters in **t**.

### 🔹 Example 2
**Input:**
```plaintext
s = "a", t = "a"
```
**Output:**
```plaintext
"a"
```
**Explanation:**
The entire string **s** is the minimum window.

### 🔹 Example 3
**Input:**
```plaintext
s = "a", t = "aa"
```
**Output:**
```plaintext
""
```
**Explanation:**
Since **s** has only one `'a'`, it cannot cover two `'a'` characters required by **t**.

---

## 🔍 Approach (Sliding Window Algorithm)
The optimal solution leverages the **sliding window** technique in combination with hash maps (or dictionaries) to track the frequency of required characters.

### ✨ Intuition
- **Expand and Contract:**  
  Utilize two pointers, **l** (left) and **r** (right), to form a sliding window. Expand the window by moving **r** until it contains all the characters from **t** with the required counts. Then, try to contract the window by moving **l** to minimize its size.
  
- **Frequency Counting:**  
  Use a hash map for **t** to record the frequency of each required character. As the window expands, maintain a running count of each character in another hash map.

- **Matching Condition:**  
  Track the number of characters that meet the required frequency using a variable (often called **formed**). When **formed** equals the number of unique characters in **t**, the current window is a candidate. Then, attempt to shrink the window from the left to find the smallest valid window.

### 🔥 Algorithm Steps
1. **Preprocessing:**  
   - Build a hash map `dictT` to count the frequency of each character in **t**.
   - Define a variable `required` as the number of unique characters in **t**.

2. **Window Initialization:**  
   - Initialize two pointers: `l = 0` and `r = 0`.
   - Use a hash map `windowCounts` to keep count of characters in the current window.
   - Initialize a variable `formed` to keep track of how many unique characters in the current window match their desired frequency.

3. **Expand the Window:**  
   - Iterate **r** over the string **s**:
     - Add the current character to `windowCounts`.
     - If the character's count in `windowCounts` equals its count in `dictT`, increment `formed`.

4. **Contract the Window:**  
   - When `formed == required`:
     - Try to contract the window by moving **l** while still meeting the condition.
     - Update the minimum window size when a smaller valid window is found.
     - If moving **l** causes the frequency condition to break, decrement `formed` and continue with the expansion.

5. **Return Result:**  
   - After processing, return the smallest window found. If no valid window exists, return `""`.

---

## ⏳ Time & Space Complexity
- **Time Complexity:**  
  The algorithm makes at most two passes over **s** (one for expanding and one for contracting the window), resulting in a time complexity of **O(m + n)**.
  
- **Space Complexity:**  
  Additional storage is used for two hash maps: one for **t** and one for the window counts in **s**. This leads to an overall space complexity of **O(m + n)** in the worst case.

---

## 🚀 Code Implementations

### C++ (Sliding Window Technique)
```cpp
#include <iostream>
#include <string>
#include <unordered_map>
#include <climits>
using namespace std;

string minWindow(string s, string t) {
    if (s.empty() || t.empty())
        return "";

    // Dictionary to store counts of characters in t
    unordered_map<char, int> dictT;
    for (char c : t)
        dictT[c]++;

    // Number of unique characters in t that must be present in the window
    int required = dictT.size();

    // Sliding window counters
    unordered_map<char, int> windowCounts;
    int formed = 0;

    // (window length, left, right)
    int minLen = INT_MAX, minLeft = 0;

    int l = 0;
    // Expand the window with right pointer
    for (int r = 0; r < s.size(); r++) {
        char c = s[r];
        windowCounts[c]++;
        
        if (dictT.count(c) && windowCounts[c] == dictT[c])
            formed++;

        // Try to contract the window till the point it's no longer 'desirable'
        while (l <= r && formed == required) {
            // Update smallest window if smaller found
            if (r - l + 1 < minLen) {
                minLen = r - l + 1;
                minLeft = l;
            }
            
            char d = s[l];
            windowCounts[d]--;
            if (dictT.count(d) && windowCounts[d] < dictT[d])
                formed--;
            l++;
        }
    }
    
    return minLen == INT_MAX ? "" : s.substr(minLeft, minLen);
}

int main() {
    string s = "ADOBECODEBANC", t = "ABC";
    cout << "Minimum Window Substring: " << minWindow(s, t) << endl;
    return 0;
}
```

### Python (Sliding Window Technique)
```python
def minWindow(s: str, t: str) -> str:
    if not s or not t:
        return ""
    
    # Frequency map for characters in t
    dict_t = {}
    for char in t:
        dict_t[char] = dict_t.get(char, 0) + 1

    required = len(dict_t)
    l, r = 0, 0
    formed = 0
    window_counts = {}
    
    # (window length, left, right)
    ans = float("inf"), None, None

    while r < len(s):
        char = s[r]
        window_counts[char] = window_counts.get(char, 0) + 1
        
        if char in dict_t and window_counts[char] == dict_t[char]:
            formed += 1

        # Try and contract the window till the condition ceases to be true
        while l <= r and formed == required:
            char = s[l]

            # Save the smallest window
            if r - l + 1 < ans[0]:
                ans = (r - l + 1, l, r)

            window_counts[char] -= 1
            if char in dict_t and window_counts[char] < dict_t[char]:
                formed -= 1

            l += 1    
        r += 1
    
    return "" if ans[0] == float("inf") else s[ans[1] : ans[2] + 1]

# Example usage
s = "ADOBECODEBANC"
t = "ABC"
print("Minimum Window Substring:", minWindow(s, t))
```

### Java (Sliding Window Technique)
```java
import java.util.HashMap;
import java.util.Map;

public class Solution {
    public String minWindow(String s, String t) {
        if (s == null || t == null || s.length() < t.length())
            return "";
        
        // Build frequency map for t
        Map<Character, Integer> dictT = new HashMap<>();
        for (char c : t.toCharArray()) {
            dictT.put(c, dictT.getOrDefault(c, 0) + 1);
        }
        
        int required = dictT.size();
        int l = 0, r = 0, formed = 0;
        Map<Character, Integer> windowCounts = new HashMap<>();
        int[] ans = {-1, 0, 0}; // {window length, left, right}
        
        while (r < s.length()) {
            char c = s.charAt(r);
            windowCounts.put(c, windowCounts.getOrDefault(c, 0) + 1);
            
            if (dictT.containsKey(c) && windowCounts.get(c).intValue() == dictT.get(c).intValue()) {
                formed++;
            }
            
            // Contract the window until it's no longer valid
            while (l <= r && formed == required) {
                c = s.charAt(l);
                
                // Update result if this window is smaller
                if (ans[0] == -1 || r - l + 1 < ans[0]) {
                    ans[0] = r - l + 1;
                    ans[1] = l;
                    ans[2] = r;
                }
                
                windowCounts.put(c, windowCounts.get(c) - 1);
                if (dictT.containsKey(c) && windowCounts.get(c) < dictT.get(c)) {
                    formed--;
                }
                l++;
            }
            r++;
        }
        return ans[0] == -1 ? "" : s.substring(ans[1], ans[2] + 1);
    }
    
    public static void main(String[] args) {
        Solution sol = new Solution();
        String s = "ADOBECODEBANC";
        String t = "ABC";
        System.out.println("Minimum Window Substring: " + sol.minWindow(s, t));
    }
}
```

---

## 🌍 Real-World Analogy
Imagine you’re at a grocery store and have a **shopping list** (**t**) with several items (possibly with duplicates). The store aisle is laid out as a long sequence (**s**).  
Your goal is to quickly locate the **smallest continuous section** of the aisle that contains all the items from your shopping list. By expanding your search until you cover all items and then contracting your search to drop any unnecessary products, you’re essentially applying a sliding window strategy to optimize your shopping trip.

---

## 💡 Variations & Follow-ups
- **Ignoring Case Sensitivity:**  
  Adjust the algorithm if the matching should ignore case differences.
  
- **Multiple Matching Windows:**  
  If you want to find all minimum windows or count their occurrences, the basic approach can be extended.
  
- **Streaming Data:**  
  Modify the algorithm to work with data streams where **s** is continuously updated.

---

## 🎯 Summary
✅ **Sliding Window Technique:** Efficiently finds the smallest window by expanding and contracting.  
✅ **Frequency Matching:** Uses hash maps to ensure that the current window meets all character frequency requirements.  
✅ **Optimal Performance:** Achieves **O(m + n)** time complexity, well suited for large input sizes.  
✅ **Real-World Use:** The approach is analogous to quickly finding a targeted segment in a larger sequence—just like streamlining a shopping trip.