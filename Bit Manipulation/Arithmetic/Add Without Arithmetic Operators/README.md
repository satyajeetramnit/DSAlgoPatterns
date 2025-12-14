# Add Without Arithmetic Operators

## 🧩 Problem Statement
Calculate the sum of two integers `a` and `b`, but you are **not allowed** to use the operator `+` and `-`.

### 🔹 Example 1:
#### Input:
```plaintext
a = 1, b = 2
```
#### Output:
```plaintext
3
```

### 🔹 Example 2:
#### Input:
```plaintext
a = -2, b = 3
```
#### Output:
```plaintext
1
```

## 🔍 Approaches

### 1. Bit Manipulation (XOR & AND)
- **Concept:** Addition can be broken down into two parts:
  1. **Sum without carry:** Equivalent to `a ^ b` (XOR).
     - $0+0=0, 0+1=1, 1+0=1, 1+1=0$ (modulo 2 sum).
  2. **Carry:** Equivalent to `(a & b) << 1`.
     - Carry occurs only when both bits are 1 ($1+1$).
- **Algorithm:**
  - Repeat until `carry` becomes 0:
    - `sum_without_carry = a ^ b`
    - `carry = (a & b) << 1`
    - Update `a = sum_without_carry`, `b = carry`.
- **Handling Negatives:** In languages like Java/C++, two's complement handles negatives automatically. In Python, integers have arbitrary precision, so mask to 32-bit (or similar) to simulate overflow/correct behavior for negatives.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(1)$ (specifically number of bits, e.g., 32). The carry propagates at most 32 times.
- **Space Complexity:** $O(1)$.

## 🚀 Code Implementations

### C++
```cpp
#include <iostream>

using namespace std;

class Solution {
public:
    int getSum(int a, int b) {
        while (b != 0) {
            // Use unsigned to prevent undefined behavior on left shift of negative value
            unsigned int carry = (unsigned int)(a & b) << 1;
            a = a ^ b;
            b = carry;
        }
        return a;
    }
};
```

### Python
```python
class Solution:
    def getSum(self, a: int, b: int) -> int:
        mask = 0xFFFFFFFF
        
        while b != 0:
            # Calculate sum without carry and carry separately
            sum_val = (a ^ b) & mask
            carry = ((a & b) << 1) & mask
            
            a = sum_val
            b = carry
        
        # If a is negative in 32-bit sense (highest bit 1), convert to Python's negative int
        if a > 0x7FFFFFFF:
            a = ~(a ^ mask)
            
        return a
```

### Java
```java
class Solution {
    public int getSum(int a, int b) {
        while (b != 0) {
            int carry = (a & b) << 1;
            a = a ^ b;
            b = carry;
        }
        return a;
    }
}
```

## 🌍 Real-World Analogy
### **Mechanical Counter:**
Imagine a mechanical counter where gears turn. `XOR` represents turning the current gear digit without affecting the next gear. `AND << 1` represents purely the mechanism that detects if a gear completed a full turn to "carry over" to the next gear. You repeat this until all gears settle.

## 🎯 Summary
✅ **XOR as Sum:** `^` adds bits without carry.
✅ **AND+Shift as Carry:** `&` finds where carry happens, `<< 1` moves it to the correct position.
