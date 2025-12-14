# Reverse Bits

## 🧩 Problem Statement
Reverse bits of a given 32-bit unsigned integer.

### 🔹 Example 1:
#### Input:
```plaintext
n = 00000010100101000001111010011100
```
#### Output:
```plaintext
964176192 (00111001011110000010100101000000)
```
**Explanation:** The input binary string is reversed.

### 🔹 Example 2:
#### Input:
```plaintext
n = 11111111111111111111111111111101
```
#### Output:
```plaintext
3221225471 (10111111111111111111111111111111)
```

## 🔍 Approaches

### 1. Bitwise Iteration
- **Concept:** Iterate through all 32 bits of the input number `n`.
- **Algorithm:**
  - Initialize `res = 0`.
  - Loop `i` from 0 to 31:
    - Get the $i$-th bit of `n`: `(n >> i) & 1`.
    - Place it in the `(31 - i)`-th position of `res`: `bit << (31 - i)`.
    - `res |= bit`.
  - Return `res`.

### 2. Byte Manipulation (Divide and Conquer)
- **Concept:** Swap adjacent bits, then swap adjacent 2-bit pairs, then 4-bit nibbles, bytes, and finally half-words.
- **Complexity:** $O(1)$ without loop (logarithmic steps with respect to bit width).

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(1)$ (constant 32 iterations).
- **Space Complexity:** $O(1)$.

## 🚀 Code Implementations

### C++
```cpp
#include <cstdint>

class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t res = 0;
        for (int i = 0; i < 32; ++i) {
            // Take the last bit of n
            if ((n >> i) & 1) {
                // Set the corresponding bit in res (from the other end)
                res |= (1 << (31 - i));
            }
        }
        return res;
    }
};
```

### Python
```python
class Solution:
    # @param n, an integer
    # @return an integer
    def reverseBits(self, n: int) -> int:
        res = 0
        for i in range(32):
            bit = (n >> i) & 1
            res = res | (bit << (31 - i))
        return res
```

### Java
```java
public class Solution {
    // you need treat n as an unsigned value
    public int reverseBits(int n) {
        int res = 0;
        for (int i = 0; i < 32; i++) {
            if (((n >> i) & 1) == 1) {
                res |= (1 << (31 - i));
            }
        }
        return res;
    }
}
```

## 🌍 Real-World Analogy
### **Reversing a Tape Reel:**
Imagine a magnetic tape with data written on it. If you physically flip the reel, the data is read backwards.
- The 1st bit moves to the last position, the 2nd bit to the 2nd-to-last, etc.
- We process this by reading the "source" tape from one end and writing to a "destination" tape starting from the other end.

### **Mirror Reflection:**
Like seeing a word in a mirror, the entire sequence is flipped left-to-right. In memory, this is often used in FFT (Fast Fourier Transform) algorithms for bit-reversal permutation.

## 🎯 Summary
✅ **Bit Shifting:** Extract from one end, place at the other.
