# GCD & LCM

## 🧩 Problem Statement
Given two integers `a` and `b`, calculate their **Greatest Common Divisor (GCD)** and **Least Common Multiple (LCM)**.

- **GCD (Greatest Common Divisor)**: The largest positive integer that divides both numbers without a remainder.
- **LCM (Least Common Multiple)**: The smallest positive integer that is divisible by both numbers.

### 🔹 Example 1:
#### Input:
```plaintext
a = 12, b = 18
```
#### Output:
```plaintext
GCD: 6, LCM: 36
```
**Explanation:** 
- Divisors of 12: 1, 2, 3, 4, 6, 12
- Divisors of 18: 1, 2, 3, 6, 9, 18
- Max common: 6.
- LCM: (12 * 18) / 6 = 36.

### 🔹 Example 2:
#### Input:
```plaintext
a = 5, b = 7
```
#### Output:
```plaintext
GCD: 1, LCM: 35
```

## 🔍 Approaches

### 1. Euclidean Algorithm (GCD)
- **Concept:** `GCD(a, b) = GCD(b, a % b)`.
- **Base Case:** `GCD(a, 0) = a`.
- **Algorithm:**
  - While `b != 0`:
    - `temp = b`
    - `b = a % b`
    - `a = temp`
  - Return `a`.

### 2. LCM Formula
- **Concept:** `LCM(a, b) = |a * b| / GCD(a, b)`.
- **Note:** To prevent overflow, calculate as `(a / GCD(a, b)) * b`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(\log(\min(a, b)))$ by Lame's Theorem (number of steps similar to number of digits).
- **Space Complexity:** $O(1)$ for iterative, $O(\log(\min(a, b)))$ for recursive stack.

## 🚀 Code Implementations

### C++
```cpp
#include <numeric>
#include <iostream>

using namespace std;

class Solution {
public:
    // Iterative
    int gcd(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    // LCM
    long long lcm(int a, int b) {
        if (a == 0 || b == 0) return 0;
        return (1LL * abs(a) / gcd(a, b)) * abs(b);
    }
};
```

### Python
```python
class Solution:
    def gcd(self, a: int, b: int) -> int:
        while b:
            a, b = b, a % b
        return a

    def lcm(self, a: int, b: int) -> int:
        if a == 0 or b == 0:
            return 0
        return abs(a * b) // self.gcd(a, b)
```

### Java
```java
class Solution {
    public int gcd(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    public long lcm(int a, int b) {
        if (a == 0 || b == 0) return 0;
        return (long) Math.abs(a) / gcd(a, b) * Math.abs(b);
    }
}
```

## 🌍 Real-World Analogy
### **Tiling a Floor:**
If you want to tile a rectangular room of size `A x B` with square tiles, the largest square tile you can use without cutting is size `GCD(A, B)`.
### **Running on Tracks:**
Two runners start at the same time. One completes a lap in `A` minutes, the other in `B` minutes. They will meet again at the start line after `LCM(A, B)` minutes.

## 🎯 Summary
✅ **Euclidean Algo:** The standard, efficient way to find GCD.
✅ **LCM Relationship:** Always derived from GCD.
