# Candy

## 🧩 Problem Statement
There are `n` children standing in a line. Each child is assigned a rating value given in the integer array `ratings`.

You are giving candies to these children subjected to the following requirements:

1. Each child must have at least one candy.
2. Children with a higher rating get more candies than their neighbors.

Return the **minimum number of candies** you need to have to distribute the candies to the children.

### 🔹 Example 1:
#### Input:
```plaintext
ratings = [1,0,2]
```
#### Output:
```plaintext
5
```
#### Explanation:
You can allocate to the first, second and third child with 2, 1, 2 candies respectively.

### 🔹 Example 2:
#### Input:
```plaintext
ratings = [1,2,2]
```
#### Output:
```plaintext
4
```
#### Explanation:
You can allocate to the first, second and third child with 1, 2, 1 candies respectively.
The third child gets 1 candy because it satisfies the above two conditions.

## 🔍 Approaches

### 1. Two-Pass Greedy ($O(N)$)
- **Concept:** Satisfying two neighbor conditions simultaneously is hard. Instead, satisfy left-neighbor condition and right-neighbor condition separately.
- **Algorithm:**
  1. Initialize `candies` array with all `1`s (everyone gets at least one).
  2. **Left-to-Right Pass:** Check if `ratings[i] > ratings[i-1]`. If so, `candies[i] = candies[i-1] + 1`. This ensures `i` has more than its left neighbor.
  3. **Right-to-Left Pass:** Check if `ratings[i] > ratings[i+1]`. If so, ensure `candies[i]` is greater than `candies[i+1]`.
     - Update: `candies[i] = max(candies[i], candies[i+1] + 1)`.
     - Why `max`? Because we must *also* keep the condition from the first pass satisfied. `candies[i]` might already be huge because of its left neighbor; we shouldn't shrink it.
  4. Sum up the `candies` array.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N)$ for two passes.
- **Space Complexity:** $O(N)$ to store the `candies` array.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <numeric>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        if (n == 0) return 0;
        
        vector<int> candies(n, 1);
        
        // Left to Right
        for (int i = 1; i < n; i++) {
            if (ratings[i] > ratings[i-1]) {
                candies[i] = candies[i-1] + 1;
            }
        }
        
        // Right to Left
        for (int i = n - 2; i >= 0; i--) {
            if (ratings[i] > ratings[i+1]) {
                candies[i] = max(candies[i], candies[i+1] + 1);
            }
        }
        
        return accumulate(candies.begin(), candies.end(), 0);
    }
};
```

### Python
```python
from typing import List

class Solution:
    def candy(self, ratings: List[int]) -> int:
        n = len(ratings)
        candies = [1] * n
        
        # Left to Right
        for i in range(1, n):
            if ratings[i] > ratings[i-1]:
                candies[i] = candies[i-1] + 1
        
        # Right to Left
        for i in range(n - 2, -1, -1):
            if ratings[i] > ratings[i+1]:
                candies[i] = max(candies[i], candies[i+1] + 1)
                
        return sum(candies)
```

### Java
```java
import java.util.Arrays;

class Solution {
    public int candy(int[] ratings) {
        int n = ratings.length;
        int[] candies = new int[n];
        Arrays.fill(candies, 1);
        
        // Left to Right
        for (int i = 1; i < n; i++) {
            if (ratings[i] > ratings[i-1]) {
                candies[i] = candies[i-1] + 1;
            }
        }
        
        // Right to Left
        for (int i = n - 2; i >= 0; i--) {
            if (ratings[i] > ratings[i+1]) {
                candies[i] = Math.max(candies[i], candies[i+1] + 1);
            }
        }
        
        int sum = 0;
        for (int c : candies) sum += c;
        return sum;
    }
}
```

## 🌍 Real-World Analogy
### **Salary Negotiations:**
Imagine employees in a cubicle row. If you are performing better than the person to your left, you demand a higher salary than them. If you are performing better than the person to your right, you demand a higher salary than them too. HR (the algorithm) walks down the row to satisfy the "left" demand, then walks back up to satisfy the "right" demand, ensuring everyone gets the minimum possible salary that respects these ego battles.

## 🎯 Summary
✅ **Decomposition:** Breaking the "neighbors" condition into strictly "left neighbors" and "right neighbors" makes the problem linear and strictly greedy.
