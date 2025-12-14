# Jump Game II

## 🧩 Problem Statement
You are given a **0-indexed** array of integers `nums` of length `n`. You are initially positioned at `nums[0]`.

Each element `nums[i]` represents the maximum length of a forward jump from index `i`. In other words, if you are at `nums[i]`, you can jump to any `nums[i + j]` where:
- `0 <= j <= nums[i]` and
- `i + j < n`

Return the **minimum number of jumps** to reach `nums[n - 1]`. The test cases are generated such that you can reach `nums[n - 1]`.

### 🔹 Example 1:
#### Input:
```plaintext
nums = [2,3,1,1,4]
```
#### Output:
```plaintext
2
```
#### Explanation:
The minimum number of jumps to reach the last index is 2. Jump 1 step from index 0 to 1, then 3 steps to the last index.

## 🔍 Approaches

### 1. Greedy (Implicit BFS) ($O(N)$)
 This problem asks for the *shortest path* in an unweighted graph (where indices are nodes and jumps are edges). Usually, shortest path implies BFS.
 
 However, we don't need a queue because the edges are special: from `i`, you can go to *any* node in `[i+1, i+nums[i]]`. This forms a contiguous range.
 
 **The Greedy Choice:**
 Instead of deciding exactly where to jump, we decide **when to jump**.
 We process the array in "ranges" or "levels":
 1. **Range 1 (1 jump):** All nodes reachable from index 0. `[0, nums[0]]`.
 2. **Range 2 (2 jumps):** All nodes reachable from any node in Range 1.
 
 **Algorithm:**
 - Maintain `current_end`: The farthest index reachable with the current number of jumps.
 - Maintain `farthest`: The farthest index we can *potentially* reach if we take a jump from any node we are currently visiting.
 - Iterate through the array from `0` to `n-2`:
   - Update `farthest = max(farthest, i + nums[i])`.
   - If we reach `current_end`:
     - We **must** take a jump now to extend our reach.
     - Increment `jumps`.
     - Update `current_end` to `farthest`.
     - (If `current_end >= n-1`, we can stop, but the loop `n-2` handles it naturally).

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N)$. We visit each element once.
- **Space Complexity:** $O(1)$. No extra data structures needed.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return 0;
        
        int jumps = 0;
        int current_end = 0;
        int farthest = 0;
        
        // Iterate up to n-2 because if we are at n-1, we are already there.
        for (int i = 0; i < n - 1; i++) {
            farthest = max(farthest, i + nums[i]);
            
            // If we have come to the end of the current jump range
            if (i == current_end) {
                jumps++;
                current_end = farthest;
                
                // Optional optimization: early exit
                if (current_end >= n - 1) break;
            }
        }
        return jumps;
    }
};
```

### Python
```python
from typing import List

class Solution:
    def jump(self, nums: List[int]) -> int:
        if len(nums) <= 1:
            return 0
            
        jumps = 0
        current_end = 0
        farthest = 0
        
        # Iterate until the second to last element. 
        # By the time we are AT last element, we don't need to jump.
        for i in range(len(nums) - 1):
            farthest = max(farthest, i + nums[i])
            
            if i == current_end:
                jumps += 1
                current_end = farthest
                
                if current_end >= len(nums) - 1:
                    break
                    
        return jumps
```

### Java
```java
class Solution {
    public int jump(int[] nums) {
        if (nums.length <= 1) return 0;
        
        int jumps = 0;
        int currentEnd = 0;
        int farthest = 0;
        
        for (int i = 0; i < nums.length - 1; i++) {
            farthest = Math.max(farthest, i + nums[i]);
            
            if (i == currentEnd) {
                jumps++;
                currentEnd = farthest;
                
                if (currentEnd >= nums.length - 1) break;
            }
        }
        return jumps;
    }
}
```

## 🌍 Real-World Analogy
### **Refueling an Airplane:**
You are flying a plane. You have fuel to reach `current_end`. As you fly over airports (indices `i`), you check their fuel supplies (`nums[i]`) to see how far you *could* go if you refueled there (`i + nums[i]`). You don't land until you absolutely have to (at `current_end`). When you do land, you pick the tank that gets you the `farthest`.

## 🎯 Summary
✅ **Implicit BFS:** We are essentially finding the shortest path in layers without maintaining a queue. The "layer" is defined by `[start, end]`.
