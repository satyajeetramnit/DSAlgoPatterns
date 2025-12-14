# Permutations I & II

## 🧩 Problem Statement

### Permutations I
Given an array `nums` of **distinct** integers, return all the possible permutations. You can return the answer in **any order**.

### Permutations II
Given a collection of numbers, `nums`, that might contain **duplicates**, return all possible **unique** permutations in **any order**.

### 🔹 Example 1 (Distinct):
#### Input:
```plaintext
nums = [1,2,3]
```
#### Output:
```plaintext
[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
```

### 🔹 Example 2 (Duplicates):
#### Input:
```plaintext
nums = [1,1,2]
```
#### Output:
```plaintext
[[1,1,2], [1,2,1], [2,1,1]]
```

## 🔍 Approaches

### 1. Backtracking (The General Approach)
Backtracking is about building a solution one step at a time and abandoning "dead" paths. for permutations, a "step" is picking a number for the current position.

#### Idea:
- We have `N` slots to fill.
- For each slot, we can pick any available number.
- **Base Case:** If current path length == `N`, add path to results.
- **Recursive Step:**
  - Iterate through `nums`.
  - If a number is "valid" (not used yet):
    - Mark it as used.
    - Add to current path.
    - Recurse.
    - Backtrack (remove from path, unmark).

### 2. Handling Duplicates (Permutations II)
If the input has duplicates (e.g., `[1, 1, 2]`), simply skipping "used" indices isn't enough because the two `1`s are identical in value but distinct in index.
- **Sort** the array first to group duplicates.
- **Pruning Condition:** Skip `nums[i]` if `nums[i] == nums[i-1]` AND `!used[i-1]`.
  - Why `!used[i-1]`? This ensures that we only use the duplicate numbers in the **fixed order** they appear in the sorted array. We can only pick the 2nd `1` if the 1st `1` has already been picked in the current recursion stack (depth-first). If `!used[i-1]`, it means we skipped the 1st `1` for this slot, so picking the 2nd `1` here would create the exact same tree branch as picking the 1st `1` (which we just finished exploring or decided not to explore).

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N \cdot N!)$. There are $N!$ permutations, and copying each takes $O(N)$.
- **Space Complexity:** $O(N)$ for recruitment stack and path + `used` array.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    // Permutations I
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> path;
        vector<bool> used(nums.size(), false);
        backtrack(nums, path, used, res);
        return res;
    }
    
    // Permutations II
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end()); // Crucial for duplicate handling
        vector<vector<int>> res;
        vector<int> path;
        vector<bool> used(nums.size(), false);
        backtrackUnique(nums, path, used, res);
        return res;
    }

private:
    void backtrack(vector<int>& nums, vector<int>& path, vector<bool>& used, vector<vector<int>>& res) {
        if (path.size() == nums.size()) {
            res.push_back(path);
            return;
        }
        
        for (int i = 0; i < nums.size(); ++i) {
            if (used[i]) continue;
            
            used[i] = true;
            path.push_back(nums[i]);
            backtrack(nums, path, used, res);
            path.pop_back();
            used[i] = false;
        }
    }

    void backtrackUnique(vector<int>& nums, vector<int>& path, vector<bool>& used, vector<vector<int>>& res) {
        if (path.size() == nums.size()) {
            res.push_back(path);
            return;
        }
        
        for (int i = 0; i < nums.size(); ++i) {
            if (used[i]) continue;
            // Handle duplicates: skip if same as prev and prev was NOT used 
            // (meaning we started a new branch with a duplicate value at the same level)
            if (i > 0 && nums[i] == nums[i-1] && !used[i-1]) continue;
            
            used[i] = true;
            path.push_back(nums[i]);
            backtrackUnique(nums, path, used, res);
            path.pop_back();
            used[i] = false;
        }
    }
};
```

### Python
```python
from typing import List

class Solution:
    def permute(self, nums: List[int]) -> List[List[int]]:
        res = []
        self._backtrack(nums, [], [False]*len(nums), res)
        return res

    def _backtrack(self, nums, path, used, res):
        if len(path) == len(nums):
            res.append(path[:])
            return

        for i in range(len(nums)):
            if used[i]:
                continue
            
            used[i] = True
            path.append(nums[i])
            self._backtrack(nums, path, used, res)
            path.pop()
            used[i] = False

    def permuteUnique(self, nums: List[int]) -> List[List[int]]:
        nums.sort() # Key for handling duplicates
        res = []
        self._backtrackUnique(nums, [], [False]*len(nums), res)
        return res

    def _backtrackUnique(self, nums, path, used, res):
        if len(path) == len(nums):
            res.append(path[:])
            return

        for i in range(len(nums)):
            if used[i]:
                continue
            # If current is same as prev and prev not used, skip
            if i > 0 and nums[i] == nums[i-1] and not used[i-1]:
                continue
                
            used[i] = True
            path.append(nums[i])
            self._backtrackUnique(nums, path, used, res)
            path.pop()
            used[i] = False
```

### Java
```java
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class Solution {
    // Permutatios I
    public List<List<Integer>> permute(int[] nums) {
        List<List<Integer>> res = new ArrayList<>();
        backtrack(nums, new ArrayList<>(), new boolean[nums.length], res);
        return res;
    }
    
    private void backtrack(int[] nums, List<Integer> path, boolean[] used, List<List<Integer>> res) {
        if (path.size() == nums.length) {
            res.add(new ArrayList<>(path));
            return;
        }
        
        for (int i = 0; i < nums.length; i++) {
            if (used[i]) continue;
            
            used[i] = true;
            path.add(nums[i]);
            backtrack(nums, path, used, res);
            path.remove(path.size() - 1);
            used[i] = false;
        }
    }

    // Permutations II
    public List<List<Integer>> permuteUnique(int[] nums) {
        Arrays.sort(nums); // Key step
        List<List<Integer>> res = new ArrayList<>();
        backtrackUnique(nums, new ArrayList<>(), new boolean[nums.length], res);
        return res;
    }
    
    private void backtrackUnique(int[] nums, List<Integer> path, boolean[] used, List<List<Integer>> res) {
        if (path.size() == nums.length) {
            res.add(new ArrayList<>(path));
            return;
        }
        
        for (int i = 0; i < nums.length; i++) {
            if (used[i]) continue;
            if (i > 0 && nums[i] == nums[i-1] && !used[i-1]) continue;
            
            used[i] = true;
            path.add(nums[i]);
            backtrackUnique(nums, path, used, res);
            path.remove(path.size() - 1);
            used[i] = false;
        }
    }
}
```

## 🌍 Real-World Analogy
### **Seating Arrangements:**
- **Permutations I:** Seating 3 distinct people (Alice, Bob, Charlie) in 3 chairs. ABC, ACB, BAC... all are distinct.
- **Permutations II:** Seating 3 people where 2 are identical twins wearing identical clothes (Twin1, Twin2, Charlie). If you swap the twins, the photo looks exactly the same. You only want the unique-looking photos.

## 🎯 Summary
✅ **Backtracking:** Standard exploration pattern.
✅ **Duplicate Handling:** Sort + `!used[i-1]` check is the canonical way to deduplicate in backtracking.
