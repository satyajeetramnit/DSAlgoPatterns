# Find Original Array of Prefix XOR

## 🧩 Problem Statement
You are given an integer array `pref` of size `n`. Find and return the array `arr` of size `n` that satisfies:
- `pref[i] = arr[0] ^ arr[1] ^ ... ^ arr[i]`.

Note that `arr[0] ^ ... ^ arr[i]` denotes the bitwise-XOR of the first `i + 1` non-negative integers.

### 🔹 Example 1:
#### Input:
```plaintext
pref = [5,2,0,3,1]
```
#### Output:
```plaintext
[5,7,2,3,2]
```
**Explanation:** 
- `pref[0] = 5` => `arr[0] = 5`
- `pref[1] = 5 ^ 7 = 2` => `arr[1] = 7`
- `pref[2] = 5 ^ 7 ^ 2 = 0` => `arr[2] = 2`
- `pref[3] = 5 ^ 7 ^ 2 ^ 3 = 3` => `arr[3] = 3`
- `pref[4] = 5 ^ 7 ^ 2 ^ 3 ^ 2 = 1` => `arr[4] = 2`

### 🔹 Example 2:
#### Input:
```plaintext
pref = [13]
```
#### Output:
```plaintext
[13]
```

## 🔍 Approaches

### 1. Inverse XOR (Single Pass)
- **Property:** If `C = A ^ B`, then `B = A ^ C` and `A = B ^ C` (XOR is its own inverse).
- **Given:** `pref[i] = pref[i-1] ^ arr[i]` (where `pref[-1] = 0`).
- **Derivation:** `arr[i] = pref[i] ^ pref[i-1]`.
- **Base Case:** `arr[0] = pref[0]`.
- **Algorithm:**
  - `arr[0] = pref[0]`
  - For `i > 0`, `arr[i] = pref[i] ^ pref[i-1]`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N)$
- **Space Complexity:** $O(1)$ (ignoring output space).

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<int> findArray(vector<int>& pref) {
        int n = pref.size();
        vector<int> arr(n);
        arr[0] = pref[0];
        
        for (int i = 1; i < n; ++i) {
            arr[i] = pref[i] ^ pref[i-1];
        }
        
        return arr;
    }
};
```

### Python
```python
from typing import List

class Solution:
    def findArray(self, pref: List[int]) -> List[int]:
        n = len(pref)
        arr = [0] * n
        arr[0] = pref[0]
        
        for i in range(1, n):
            arr[i] = pref[i] ^ pref[i-1]
            
        return arr
```

### Java
```java
class Solution {
    public int[] findArray(int[] pref) {
        int n = pref.length;
        int[] arr = new int[n];
        arr[0] = pref[0];
        
        for (int i = 1; i < n; i++) {
            arr[i] = pref[i] ^ pref[i-1];
        }
        return arr;
    }
}
```

## 🌍 Real-World Analogy
### **Reconstructing Daily Steps:**
Imagine your smartwatch only stores the "Total Steps Taken" since you bought it.
- `pref[i]` is the total steps on Day `i`.
- You want to find out how many steps you walked *specifically* on Day `i`.
- You take the total for Day `i` and "undo" the total for Day `i-1`. In XOR world, "undoing" addition (accumulation) is done by XORing again.

### **Decrypting a Message Stream:**
Imagine a stream cipher where each character is XORed with a cumulative key. To recover the original message (array), you need to "undo" the XOR operation using the previous state (prefix).

## 🎯 Summary
✅ **XOR Inverse:** Knowing the current cumulative state and the previous cumulative state allows you to deduce the current input.
