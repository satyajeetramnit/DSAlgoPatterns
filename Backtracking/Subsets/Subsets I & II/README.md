# Subsets I & II

## 🧩 Problem Statement

### Subsets I
Given an integer array `nums` of **unique** elements, return all possible subsets (the power set).
The solution set **must not** contain duplicate subsets. Return the solution in **any order**.

### Subsets II
Given an integer array `nums` that may contain **duplicates**, return all possible subsets (the power set).
The solution set **must not** contain duplicate subsets. Return the solution in **any order**.

### 🔹 Example 1 (Subsets I):
#### Input:
```plaintext
nums = [1,2,3]
```
#### Output:
```plaintext
[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
```

### 🔹 Example 2 (Subsets II):
#### Input:
```plaintext
nums = [1,2,2]
```
#### Output:
```plaintext
[[],[1],[1,2],[1,2,2],[2],[2,2]]
```

## 🔍 Approaches

### 1. Backtracking (The General Approach)
We want to verify every possible combination.
- Use a `start` index to know which elements are available to be added.
- **Subsets I**: At every step, add the current `path` to the results. Then iterate from `start` to `end`, adding `nums[i]` and recursing.
- **Subsets II**: Same as above, but **Sort** the array first. Skip duplicates in the loop: if `i > start` and `nums[i] == nums[i-1]`, continue.

### 2. Cascading (Iterative)
Start with `[[]]`.
For each number in `nums`:
- Take all existing subsets.
- Create a new copy of each and append the current number.
- Add these new subsets to the result list.
- **For Subsets II**: Only append duplicate numbers to subsets generated in the *previous step*.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N \cdot 2^N)$. We generate $2^N$ subsets, and copying each takes $O(N)$.
- **Space Complexity:** $O(N)$ for recursion stack.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    // Subsets I
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> path;
        backtrack(nums, 0, path, res);
        return res;
    }

    // Subsets II
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end()); // Crucial for dedup
        vector<vector<int>> res;
        vector<int> path;
        backtrackWithDup(nums, 0, path, res);
        return res;
    }

private:
    void backtrack(vector<int>& nums, int start, vector<int>& path, vector<vector<int>>& res) {
        res.push_back(path); // Add every valid path
        
        for (int i = start; i < nums.size(); ++i) {
            path.push_back(nums[i]);
            backtrack(nums, i + 1, path, res);
            path.pop_back();
        }
    }
    
    void backtrackWithDup(vector<int>& nums, int start, vector<int>& path, vector<vector<int>>& res) {
        res.push_back(path);
        
        for (int i = start; i < nums.size(); ++i) {
            if (i > start && nums[i] == nums[i-1]) continue; // Skip duplicates
            
            path.push_back(nums[i]);
            backtrackWithDup(nums, i + 1, path, res);
            path.pop_back();
        }
    }
};
```

### Python
```python
from typing import List

class Solution:
    def subsets(self, nums: List[int]) -> List[List[int]]:
        res = []
        self._backtrack(nums, 0, [], res)
        return res

    def _backtrack(self, nums, start, path, res):
        res.append(path[:])
        
        for i in range(start, len(nums)):
            path.append(nums[i])
            self._backtrack(nums, i + 1, path, res)
            path.pop()

    def subsetsWithDup(self, nums: List[int]) -> List[List[int]]:
        nums.sort()
        res = []
        self._backtrackWithDup(nums, 0, [], res)
        return res

    def _backtrackWithDup(self, nums, start, path, res):
        res.append(path[:])
        
        for i in range(start, len(nums)):
            if i > start and nums[i] == nums[i-1]:
                continue
            path.append(nums[i])
            self._backtrackWithDup(nums, i + 1, path, res)
            path.pop()
```

### Java
```java
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class Solution {
    // Subsets I
    public List<List<Integer>> subsets(int[] nums) {
        List<List<Integer>> res = new ArrayList<>();
        backtrack(nums, 0, new ArrayList<>(), res);
        return res;
    }
    
    private void backtrack(int[] nums, int start, List<Integer> path, List<List<Integer>> res) {
        res.add(new ArrayList<>(path));
        
        for (int i = start; i < nums.length; i++) {
            path.add(nums[i]);
            backtrack(nums, i + 1, path, res);
            path.remove(path.size() - 1);
        }
    }

    // Subsets II
    public List<List<Integer>> subsetsWithDup(int[] nums) {
        Arrays.sort(nums);
        List<List<Integer>> res = new ArrayList<>();
        backtrackWithDup(nums, 0, new ArrayList<>(), res);
        return res;
    }
    
    private void backtrackWithDup(int[] nums, int start, List<Integer> path, List<List<Integer>> res) {
        res.add(new ArrayList<>(path));
        
        for (int i = start; i < nums.length; i++) {
            if (i > start && nums[i] == nums[i-1]) continue;
            
            path.add(nums[i]);
            backtrackWithDup(nums, i + 1, path, res);
            path.remove(path.size() - 1);
        }
    }
}
```

## 🌍 Real-World Analogy
### **Pizza Toppings:**
- **Subsets I:** You have distinct toppings: Pepperoni, Mushroom, Olives. You can choose any combination (none, just one, two, or all three).
- **Subsets II:** You have extra supply of Pepperoni (Pepperoni 1, Pepperoni 2, Mushroom). Asking for "Pepperoni 1 and Mushroom" is effectively the same pizza as "Pepperoni 2 and Mushroom". You only care about the distinct flavor combinations.

## 🎯 Summary
✅ **Power Set:** Generates all $2^N$ subsets.
✅ **Sorting:** Essential for handling duplicates.
