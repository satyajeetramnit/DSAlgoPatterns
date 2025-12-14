# Find the Duplicate Number

## 🧩 Problem Statement
Given an array of integers `nums` containing `n + 1` integers where each integer is in the range `[1, n]` inclusive.

There is only **one repeated number** in `nums`, return this sorted repeated number.

You must solve the problem **without modifying** the array `nums` and uses only constant extra space.

### 🔹 Example 1:
#### Input:
```plaintext
nums = [1,3,4,2,2]
```
#### Output:
```plaintext
2
```

### 🔹 Example 2:
#### Input:
```plaintext
nums = [3,1,3,4,2]
```
#### Output:
```plaintext
3
```

## 🔍 Approaches

### 1. Floyd's Tortoise and Hare (Cycle Detection)
The problem constraints (range `[1, n]` and `n+1` numbers) imply a mapping from index to value that forms a linked list structure.
Since there's a duplicate, two indices point to the same value, creating a cycle.

### ✨ Intuition
- Treat `nums[i]` as the `next` pointer of a linked list node at index `i`.
- `0 -> nums[0] -> nums[nums[0]] -> ...`
- Since values are in `[1, n]`, index 0 is never pointed to (outside valid range of values), making it a safe entry point.
- The duplicate number is the start of the cycle.
- Use Floyd's Algorithm to find the cycle entry.

### 🔥 Algorithm Steps
1. Initialize `slow = 0`, `fast = 0`.
2. **Phase 1 (Intersection):**
   - `slow = nums[slow]`
   - `fast = nums[nums[fast]]`
   - Repeat until `slow == fast`.
3. **Phase 2 (Entrance):**
   - Reset `slow = 0`.
   - While `slow != fast`:
     - `slow = nums[slow]`
     - `fast = nums[fast]`
4. Return `slow`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(n)$.
- **Space Complexity:** $O(1)$.

## 🚀 Code Implementations

### C++
```cpp
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int slow = 0;
        int fast = 0;
        
        while (true) {
            slow = nums[slow];
            fast = nums[nums[fast]];
            if (slow == fast) break;
        }
        
        slow = 0;
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }
        return slow;
    }
};
```

### Python
```python
class Solution:
    def findDuplicate(self, nums: List[int]) -> int:
        slow, fast = 0, 0
        while True:
            slow = nums[slow]
            fast = nums[nums[fast]]
            if slow == fast:
                break
        
        slow = 0
        while slow != fast:
            slow = nums[slow]
            fast = nums[fast]
        return slow
```

### Java
```java
class Solution {
    public int findDuplicate(int[] nums) {
        int slow = 0;
        int fast = 0;
        
        while (true) {
            slow = nums[slow];
            fast = nums[nums[fast]];
            if (slow == fast) break;
        }
        
        slow = 0;
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }
        return slow;
    }
}
```

## 🌍 Real-World Analogy
### **Secret Agent Rendezvous:**
You have instructions in lockers. Locker 0 tells you to go to Locker X. Locker X tells you to go to Locker Y.
- Since there are `N` lockers and `N+1` instructions, one locker number is written inside two different lockers (the duplicate).
- Following instructions creates a loop.
- To find which locker number is duplicated, you use the "FAST" agent and "SLOW" agent meeting technique.

## 🎯 Summary
✅ **O(n) Time, O(1) Space:** Meets strict constraints.
✅ **Linked List on Array:** Clever transformation of the problem.
