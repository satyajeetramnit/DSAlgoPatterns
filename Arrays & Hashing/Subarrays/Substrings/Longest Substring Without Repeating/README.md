# Longest Substring Without Repeating Characters

## 🧩 Problem Statement
Given a string **s**, find the **longest substring** without repeating characters. In other words, identify the contiguous sequence within **s** where all characters are unique. You may either return the substring itself or its length. For this example, we’ll focus on returning the substring.

---

## 🔹 Example 1
**Input:**  
```plaintext
s = "abcabcbb"
```
**Output:**  
```plaintext
"abc"
```
**Explanation:**  
The answer is `"abc"`, which has a length of 3. While there are multiple substrings without repeating characters (like `"bca"` or `"cab"`), `"abc"` is one valid answer.

---

## 🔹 Example 2
**Input:**  
```plaintext
s = "bbbbb"
```
**Output:**  
```plaintext
"b"
```
**Explanation:**  
Since all characters are the same, the longest substring without duplicates is `"b"` with a length of 1.

---

## 🔍 Approach (Sliding Window with Hash Map)
The problem is optimally solved using a **sliding window** technique together with a hash map (or dictionary) to track the last seen index of each character.

### ✨ Intuition
- **Sliding Window:**  
  Utilize two pointers (**l** and **r**) that define the current window in the string. As you iterate with the right pointer, expand the window until you hit a repeated character.
  
- **Tracking Characters:**  
  Use a hash map to store the most recent index of every character encountered. When a duplicate is found that lies within the current window, slide the left pointer to one position right of the previous occurrence of that duplicate.
  
- **Window Update:**  
  Continuously update the maximum window size (and its starting index) as you progress through the string.

### 🔥 Detailed Algorithm Steps
1. **Initialization:**
   - Create a hash map (`lastIndex`) to store the last seen index for each character.
   - Initialize two pointers: `l = 0` (left pointer) and iterate `r` (right pointer) over the string.
   - Track the starting index (`maxStart`) and length (`maxLen`) of the maximum window found.
   
2. **Iterate and Update:**
   - For each character at index `r`, check:
     - If the character has been seen before and its stored index is at least `l`, update `l` to `lastIndex[s[r]] + 1`. This ensures the window excludes the previous occurrence of the repeated character.
     - Store/update the index of the current character in the hash map.
     - If the current window size (`r - l + 1`) exceeds `maxLen`, update `maxLen` and `maxStart` accordingly.
     
3. **Return the Result:**
   - After processing, return the substring defined by `maxStart` and `maxLen`.
   - If the input string is empty, return an empty string.

### ⏳ Time & Space Complexity
- **Time Complexity:**  
  **O(n)** – Each character is processed once with the right pointer, and the left pointer moves at most *n* times.
  
- **Space Complexity:**  
  **O(min(m, n))** – In the worst case (all unique characters), the hash map stores all characters from the input string (where *m* is the size of the character set and *n* is the length of **s**).

---

## 🚀 Code Implementations

### C++ Implementation
```cpp
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

string longestUniqueSubstring(const string &s) {
    unordered_map<char, int> lastIndex; // To store the last seen index of each character.
    int l = 0, maxStart = 0, maxLen = 0;

    for (int r = 0; r < s.size(); r++) {
        char currentChar = s[r];
        // If the character is seen and is within the current window, move left pointer.
        if (lastIndex.find(currentChar) != lastIndex.end() && lastIndex[currentChar] >= l) {
            l = lastIndex[currentChar] + 1;
        }
        // Update the last seen index of the current character.
        lastIndex[currentChar] = r;
        
        // Update maximum window if a longer substring is found.
        if (r - l + 1 > maxLen) {
            maxLen = r - l + 1;
            maxStart = l;
        }
    }
    
    return s.substr(maxStart, maxLen);
}

int main() {
    string s = "abcabcbb";
    cout << "Longest Unique Substring: " << longestUniqueSubstring(s) << endl;
    return 0;
}
```

### Python Implementation
```python
def longestUniqueSubstring(s: str) -> str:
    last_index = {}
    l = 0
    max_len = 0
    max_start = 0

    for r, char in enumerate(s):
        # If character is found in the current window, shift the left pointer.
        if char in last_index and last_index[char] >= l:
            l = last_index[char] + 1
        last_index[char] = r

        # Update the maximum window.
        if r - l + 1 > max_len:
            max_len = r - l + 1
            max_start = l

    return s[max_start:max_start + max_len]

# Example usage
s = "abcabcbb"
print("Longest Unique Substring:", longestUniqueSubstring(s))
```

### Java Implementation
```java
import java.util.HashMap;
import java.util.Map;

public class Solution {
    public String longestUniqueSubstring(String s) {
        int l = 0, maxStart = 0, maxLen = 0;
        Map<Character, Integer> lastIndex = new HashMap<>();

        for (int r = 0; r < s.length(); r++) {
            char c = s.charAt(r);
            // If the character is within the current window, update the left pointer.
            if (lastIndex.containsKey(c) && lastIndex.get(c) >= l) {
                l = lastIndex.get(c) + 1;
            }
            lastIndex.put(c, r);

            // Update the maximum window if a longer one is found.
            if (r - l + 1 > maxLen) {
                maxLen = r - l + 1;
                maxStart = l;
            }
        }
        return s.substring(maxStart, maxStart + maxLen);
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        String s = "abcabcbb";
        System.out.println("Longest Unique Substring: " + sol.longestUniqueSubstring(s));
    }
}
```

---

## 🌍 Real-World Analogy
Imagine you're planning a road trip where each city must be visited only once to keep the journey unique. Here, the string is your list of cities, and you want the longest sequence of stops (a continuous road trip) with no repeated visits. You continuously adjust your trip—skipping past a city if it appears again—to ensure every city in your travel segment is unique. This is exactly what the sliding window method does: it expands and contracts the window to maintain a sequence with unique characters.

---

## 💡 Variations & Follow-ups
- **Return the Length Instead:**  
  If only the length of the longest substring is needed, you can simplify the return value to just `maxLen`.
  
- **Case Sensitivity Options:**  
  Depending on the application, you might want to treat uppercase and lowercase letters as equivalent. Consider converting the input to all one case if needed.
  
- **Extension to Other Character Sets:**  
  The solution can be extended to support Unicode or other extended character sets by using an appropriate data structure for character tracking.

---

## 🎯 Summary
✅ **Sliding Window Technique:** Efficiently explores substrings while ensuring uniqueness.  
✅ **Hash Map Utilization:** Quickly retrieves and updates character indices to adjust the window.  
✅ **Optimal Performance:** Achieves **O(n)** time complexity with **O(min(m, n))** space, making it suitable for real-world applications.  
✅ **Real-World Analogy:** Similar to planning a journey with unique stops, ensuring no repetition along the way.