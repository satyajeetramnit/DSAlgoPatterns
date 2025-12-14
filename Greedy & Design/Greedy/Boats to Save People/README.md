# Boats to Save People

## 🧩 Problem Statement
You are given an array `people` where `people[i]` is the weight of the `i-th` person, and an infinite number of boats where each boat can carry a maximum weight of `limit`. Each boat carries at most two people at the same time, provided the sum of the weight of those people is at most `limit`.

Return the minimum number of boats to carry every given person.

### 🔹 Example 1:
#### Input:
```plaintext
people = [3,2,2,1], limit = 3
```
#### Output:
```plaintext
3
```
#### Explanation:
1. Boat 1: (1, 2)
2. Boat 2: (2)
3. Boat 3: (3)

## 🔍 Approaches

### 1. Greedy with Two Pointers ($O(N \log N)$)
- **Concept:** Pair the heaviest person with the lightest person. If they fit, great. If they don't, the heaviest person is too heavy to be paired with *anyone* (since even the lightest person is too much). So the heaviest person must go alone.
- **Algorithm:**
  1. **Sort** the `people` array.
  2. Use two pointers: `left` (lightest) and `right` (heaviest).
  3. Loop while `left <= right`:
     - If `people[left] + people[right] <= limit`:
       - They can share a boat. `left++`, `right--`.
     - Else:
       - The heaviest person goes alone. `right--`.
     - In both cases, a boat is used. `boats++`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N \log N)$ due to sorting.
- **Space Complexity:** $O(1)$ (or $O(\log N)$ for sort space).

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        sort(people.begin(), people.end());
        int left = 0, right = people.size() - 1;
        int boats = 0;
        
        while (left <= right) {
            if (people[left] + people[right] <= limit) {
                left++;
            }
            right--;
            boats++;
        }
        return boats;
    }
};
```

### Python
```python
from typing import List

class Solution:
    def numRescueBoats(self, people: List[int], limit: int) -> int:
        people.sort()
        left, right = 0, len(people) - 1
        boats = 0
        
        while left <= right:
            if people[left] + people[right] <= limit:
                left += 1
            right -= 1
            boats += 1
            
        return boats
```

### Java
```java
import java.util.Arrays;

class Solution {
    public int numRescueBoats(int[] people, int limit) {
        Arrays.sort(people);
        int left = 0, right = people.length - 1;
        int boats = 0;
        
        while (left <= right) {
            if (people[left] + people[right] <= limit) {
                left++;
            }
            right--;
            boats++;
        }
        return boats;
    }
}
```

## 🌍 Real-World Analogy
### **Lifeboats on Titanic:**
You want to rescue everyone. To be most efficient, you try to put a child (lightest) in with a large adult (heaviest). If the large adult is too big even for a child, they take up the whole boat. You repeat this until everyone is safe.

## 🎯 Summary
✅ **Sorting + Two Pointers:** The core greedy logic is that the heaviest person limits the boat capacity the most, so we handle them first.
