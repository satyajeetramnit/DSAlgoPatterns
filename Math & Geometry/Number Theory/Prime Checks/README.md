# Prime Checks

## 🧩 Problem Statement
1. **Check Primality**: Given an integer `n`, determine if it is a prime number.
2. **Count Primes**: Given an integer `n`, return the number of prime numbers that are **strictly less** than `n`.

### 🔹 Example 1:
#### Input:
```plaintext
n = 10
```
#### Output:
```plaintext
4
```
**Explanation:** Primes less than 10 are 2, 3, 5, 7.

### 🔹 Example 2:
#### Input:
```plaintext
n = 1
```
#### Output:
```plaintext
0
```

## 🔍 Approaches

### 1. Basic Trial Division ($O(\sqrt{N})$)
- **Concept:** A number `n` is prime if it is not divisible by any number from 2 up to $\sqrt{n}$.
- **Optimization:** Check 2 separately, then check odd numbers only.

### 2. Sieve of Eratosthenes ($O(N \log \log N)$)
- **Concept:** To find all primes up to `n`, iteratively mark multiples of each prime starting from 2.
- **Algorithm:**
  - Create a boolean array `isPrime` of size `n`, initialized to true.
  - `isPrime[0] = isPrime[1] = false`.
  - Loop `p` from 2 to $\sqrt{n}$:
    - If `isPrime[p]` is true:
      - Mark multiples `p*p`, `p*(p+1)`, ... as false.
  - Count true values.

## ⏳ Time & Space Complexity
- **Time Complexity:** 
  - Primality Check: $O(\sqrt{N})$.
  - Sieve: $O(N \log \log N)$.
- **Space Complexity:** 
  - Primality Check: $O(1)$.
  - Sieve: $O(N)$.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

class Solution {
public:
    // Basic Check
    bool isPrime(int n) {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

    // Count Primes (Sieve)
    int countPrimes(int n) {
        if (n <= 2) return 0;
        vector<bool> is_prime(n, true);
        is_prime[0] = is_prime[1] = false;
        
        for (int p = 2; p * p < n; ++p) {
            if (is_prime[p]) {
                for (int i = p * p; i < n; i += p) {
                    is_prime[i] = false;
                }
            }
        }
        
        int count = 0;
        for (int i = 2; i < n; ++i) {
            if (is_prime[i]) count++;
        }
        return count;
    }
};
```

### Python
```python
class Solution:
    def isPrime(self, n: int) -> bool:
        if n <= 1: return False
        if n <= 3: return True
        if n % 2 == 0 or n % 3 == 0: return False
        i = 5
        while i * i <= n:
            if n % i == 0 or n % (i + 2) == 0:
                return False
            i += 6
        return True

    def countPrimes(self, n: int) -> int:
        if n <= 2: return 0
        is_prime = [True] * n
        is_prime[0] = is_prime[1] = False
        
        for p in range(2, int(n**0.5) + 1):
            if is_prime[p]:
                # Start from p*p, step by p
                is_prime[p*p:n:p] = [False] * len(is_prime[p*p:n:p])
                
        return sum(is_prime)
```

### Java
```java
import java.util.Arrays;

class Solution {
    public boolean isPrime(int n) {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

    public int countPrimes(int n) {
        if (n <= 2) return 0;
        boolean[] isPrime = new boolean[n];
        Arrays.fill(isPrime, true);
        isPrime[0] = false;
        isPrime[1] = false;
        
        for (int p = 2; p * p < n; p++) {
            if (isPrime[p]) {
                for (int i = p * p; i < n; i += p) {
                    isPrime[i] = false;
                }
            }
        }
        
        int count = 0;
        for (int i = 2; i < n; i++) {
            if (isPrime[i]) count++;
        }
        return count;
    }
}
```

## 🌍 Real-World Analogy
### **Filtering Sand:**
The Sieve of Eratosthenes is exactly like a series of sieves. The `2` sieve catches all even numbers. The `3` sieve catches all multiples of 3. What passes through all sieves are the "prime" grains.

## 🎯 Summary
✅ **Trial Division:** Good for single number checks.
✅ **Sieve:** Optimal for finding ALL primes in a range.
