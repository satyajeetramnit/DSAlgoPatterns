# Two Sum

## 🧩 Problem Statement
Given an array of integers `nums` and an integer `target`, return indices of the two numbers such that they add up to `target`.

You may assume that each input would have **exactly one solution**, and you may not use the same element twice.

You can return the answer in any order.

### 🔹 Example 1:
#### Input:
```plaintext
nums = [2,7,11,15], target = 9
```
#### Output:
```plaintext
[0,1]
```
#### Explanation:
Because `nums[0] + nums[1] == 9`, we return `[0, 1]`.

### 🔹 Example 2:
#### Input:
```plaintext
nums = [3,2,4], target = 6
```
#### Output:
```plaintext
[1,2]
```

## 🔍 Approaches

### 1. Brute Force
Iterate through each element `x` and find if there is another value that equals to `target - x`.

- **Time Complexity:** $O(n^2)$
- **Space Complexity:** $O(1)$

### 2. Hash Map (One-pass)
While iterating, check if `target - nums[i]` exists in the hash map. If it does, return the current index and the index of the complement. Otherwise, add the current element to the map.

### ✨ Intuition
- We are looking for a complement `y = target - x`.
- As we iterate, we can store visited numbers and their indices in a hash map.
- This allows us to look up "Have I seen the complement before?" in $O(1)$ time.

### 🔥 Algorithm Steps
1. Create an empty hash map `prevMap`.
2. Iterate through `nums` with index `i`.
3. Calculate `diff = target - nums[i]`.
4. If `diff` is in `prevMap`:
   - Return indices `[prevMap[diff], i]`.
5. Store `nums[i]` in `prevMap` with value `i`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(n)$, as we traverse the list containing $n$ elements only once. Each look up in the table costs only $O(1)$ time.
- **Space Complexity:** $O(n)$, the extra space required depends on the number of items stored in the hash table, which stores at most $n$ elements.

## 🚀 Code Implementations

### C++
```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> m;
        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            if (m.count(complement)) {
                return {m[complement], i};
            }
            m[nums[i]] = i;
        }
        return {};
    }
};
```

### Python
```python
class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        prevMap = {}  # val : index
        for i, n in enumerate(nums):
            diff = target - n
            if diff in prevMap:
                return [prevMap[diff], i]
            prevMap[n] = i
        return []
```

### Java
```java
class Solution {
    public int[] twoSum(int[] nums, int target) {
        Map<Integer, Integer> map = new HashMap<>();
        for (int i = 0; i < nums.length; i++) {
            int complement = target - nums[i];
            if (map.containsKey(complement)) {
                return new int[] { map.get(complement), i };
            }
            map.put(nums[i], i);
        }
        return new int[] {};
    }
}
```

## 🌍 Real-World Analogy
### **Shopping with a Budget:**
Imagine you have a gift card worth $50 (target) and you want to buy exactly two items from a store that sum up to exactly $50.
- You pick an item worth $20. You know you need another item worth $30.
- As you browse (iterate), you remember (hash map) the prices and locations of items you've seen.
- When you find the $30 item, you instantly know "I saw the $20 item on aisle 5", so you grab them both.

## 🎯 Summary
✅ **O(n) Time:** Efficient one-pass solution.
✅ **Hash Map:** trades space for speed ($O(1)$ lookups).
✅ **Interview Staple:** One of the most common coding interview questions.
