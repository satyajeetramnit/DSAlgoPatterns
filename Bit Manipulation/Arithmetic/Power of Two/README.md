# Power of Two

## 🧩 Problem Statement
Given an integer `n`, return `true` if it is a power of two. Otherwise, return `false`.

An integer `n` is a power of two, if there exists an integer `x` such that `n == 2^x`.

### 🔹 Example 1:
#### Input:
```plaintext
n = 1
```
#### Output:
```plaintext
true
```

### 🔹 Example 2:
#### Input:
```plaintext
n = 16
```
#### Output:
```plaintext
true
```

### 🔹 Example 3:
#### Input:
```plaintext
n = 3
```
#### Output:
```plaintext
false
```

## 🔍 Approaches

### 1. Bitwise Trick ($(N \ \& \ (N - 1)) == 0$)
- **Concept:** 
  - Powers of two in binary are `1` followed by `0`s (e.g., `100`, `1000`).
  - `N - 1` flips the rightmost `1` and all bits to its right (e.g., `100 - 1 = 011`).
  - `N & (N - 1)` removes the rightmost set bit.
- **Logic:** A power of two has exactly one bit set. Removing it should result in 0.
- **Constraints:** `n` must be positive.
- **Check:** `n > 0` AND `(n & (n - 1)) == 0`.

### 2. Iterative/Recursive Division
- **Concept:** Keep dividing `n` by 2 while `n % 2 == 0`. If you reach 1, it's a power of two.
- **Complexity:** $O(\log n)$. Bitwise is $O(1)$.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(1)$.
- **Space Complexity:** $O(1)$.

## 🚀 Code Implementations

### C++
```cpp
class Solution {
public:
    bool isPowerOfTwo(int n) {
        if (n <= 0) return false;
        // Use long long to prevent potential overflow issues in general, 
        // though n & (n-1) is safe for positive int
        return (n & (n - 1ll)) == 0;
    }
};
```

### Python
```python
class Solution:
    def isPowerOfTwo(self, n: int) -> bool:
        if n <= 0:
            return False
        return (n & (n - 1)) == 0
```

### Java
```java
class Solution {
    public boolean isPowerOfTwo(int n) {
        if (n <= 0) return false;
        return (n & (n - 1)) == 0;
    }
}
```

## 🌍 Real-World Analogy
### **Specific Measurements:**
A standard measuring cup set has sizes that are powers (or halves) of each other. A power of two is like having a container that exactly matches one of the binary standard sizes without needing to combine multiple sizes.

## 🎯 Summary
✅ **Bit Manipulation Basic:** `n & (n - 1)` clears the lowest set bit. If the result is 0, there was only 1 bit set.
