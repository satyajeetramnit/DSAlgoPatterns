# Combination Sum I & II

## 🧩 Problem Statement

### Combination Sum I
Given an array of **distinct** integers `candidates` and a target integer `target`, return a list of all **unique combinations** of `candidates` where the chosen numbers sum to `target`.
- The **same** number may be chosen from `candidates` an **unlimited number of times**.
- Two combinations are unique if the frequency of at least one of the chosen numbers is different.

### Combination Sum II
Given a collection of candidate numbers `candidates` and a target number `target`, find all unique combinations in `candidates` where the candidate numbers sum to `target`.
- Each number in `candidates` may only be used **once** in the combination.
- The solution set must not contain duplicate combinations.

### 🔹 Example 1 (Combination Sum I):
#### Input:
```plaintext
candidates = [2,3,6,7], target = 7
```
#### Output:
```plaintext
[[2,2,3],[7]]
```

### 🔹 Example 2 (Combination Sum II):
#### Input:
```plaintext
candidates = [10,1,2,7,6,1,5], target = 8
```
#### Output:
```plaintext
[[1,1,6], [1,2,5], [1,7], [2,6]]
```

## 🔍 Approaches

### 1. Backtracking (Generic)
We explore the decision tree: at each step, we can either **include** a candidate or **skip** it.

#### Combination Sum I (Unlimited Usage)
- At index `i`, if we pick `candidates[i]`, we **stay at index `i`** for the next recursion (allowing reuse).
- If we skip `candidates[i]`, we move to `i + 1`.
- **Target Reduction:** `newTarget = target - candidates[i]`.

#### Combination Sum II (Single Usage + Duplicates)
- **Sort** the array first to handle duplicates easily.
- Use a Loop-based backtracking approach.
- Iterate from `start` index to end.
- **Skip Duplicates:** If `i > start` and `candidates[i] == candidates[i-1]`, continue.
- If we pick `candidates[i]`, we move to `i + 1` (single usage).

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(2^T)$ where T is target value (roughly). It depends on branching factor.
- **Space Complexity:** $O(T/min\_candidate)$ for recursion stack.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    // Combination Sum I
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        vector<int> path;
        backtrack1(candidates, target, 0, path, res);
        return res;
    }
    
    // Combination Sum II
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end()); // Required for dedup
        vector<vector<int>> res;
        vector<int> path;
        backtrack2(candidates, target, 0, path, res);
        return res;
    }

private:
    void backtrack1(vector<int>& candidates, int target, int start, 
                    vector<int>& path, vector<vector<int>>& res) {
        if (target == 0) {
            res.push_back(path);
            return;
        }
        if (target < 0) return;
        
        for (int i = start; i < candidates.size(); ++i) {
            path.push_back(candidates[i]);
            // Stay at i for unlimited usage
            backtrack1(candidates, target - candidates[i], i, path, res);
            path.pop_back();
        }
    }
    
    void backtrack2(vector<int>& candidates, int target, int start, 
                    vector<int>& path, vector<vector<int>>& res) {
        if (target == 0) {
            res.push_back(path);
            return;
        }
        if (target < 0) return;
        
        for (int i = start; i < candidates.size(); ++i) {
            // Skip duplicates
            if (i > start && candidates[i] == candidates[i-1]) continue;
            
            path.push_back(candidates[i]);
            // Move to i + 1 for single usage
            backtrack2(candidates, target - candidates[i], i + 1, path, res);
            path.pop_back();
        }
    }
};
```

### Python
```python
from typing import List

class Solution:
    def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:
        res = []
        self._dfs1(candidates, target, 0, [], res)
        return res

    def _dfs1(self, candidates, target, start, path, res):
        if target == 0:
            res.append(path[:])
            return
        if target < 0:
            return
            
        for i in range(start, len(candidates)):
            path.append(candidates[i])
            self._dfs1(candidates, target - candidates[i], i, path, res)
            path.pop()

    def combinationSum2(self, candidates: List[int], target: int) -> List[List[int]]:
        candidates.sort()
        res = []
        self._dfs2(candidates, target, 0, [], res)
        return res

    def _dfs2(self, candidates, target, start, path, res):
        if target == 0:
            res.append(path[:])
            return
        if target < 0:
            return
        
        for i in range(start, len(candidates)):
            if i > start and candidates[i] == candidates[i-1]:
                continue
            path.append(candidates[i])
            self._dfs2(candidates, target - candidates[i], i + 1, path, res)
            path.pop()
```

### Java
```java
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class Solution {
    // Combination Sum I
    public List<List<Integer>> combinationSum(int[] candidates, int target) {
        List<List<Integer>> res = new ArrayList<>();
        backtrack1(candidates, target, 0, new ArrayList<>(), res);
        return res;
    }

    private void backtrack1(int[] candidates, int target, int start, 
                            List<Integer> path, List<List<Integer>> res) {
        if (target == 0) {
            res.add(new ArrayList<>(path));
            return;
        }
        if (target < 0) return;

        for (int i = start; i < candidates.length; i++) {
            path.add(candidates[i]);
            // Reuse same element: i
            backtrack1(candidates, target - candidates[i], i, path, res);
            path.remove(path.size() - 1);
        }
    }

    // Combination Sum II
    public List<List<Integer>> combinationSum2(int[] candidates, int target) {
        Arrays.sort(candidates);
        List<List<Integer>> res = new ArrayList<>();
        backtrack2(candidates, target, 0, new ArrayList<>(), res);
        return res;
    }

    private void backtrack2(int[] candidates, int target, int start, 
                            List<Integer> path, List<List<Integer>> res) {
        if (target == 0) {
            res.add(new ArrayList<>(path));
            return;
        }
        if (target < 0) return;

        for (int i = start; i < candidates.length; i++) {
            if (i > start && candidates[i] == candidates[i-1]) continue;
            
            path.add(candidates[i]);
            // Next element: i + 1
            backtrack2(candidates, target - candidates[i], i + 1, path, res);
            path.remove(path.size() - 1);
        }
    }
}
```

## 🌍 Real-World Analogy
### **Shopping with Coins:**
- **I:** You have an infinite supply of coin types (2, 3, 5). How to make 10? (2+2+2+2+2, 5+5, etc).
- **II:** You have a specific handful of coins in your pocket (2, 2, 3, 5). You can't use a coin more times than you have it.

## 🎯 Summary
✅ **Use Index:** `start` determines the subset of candidates available.
✅ **Unlimited vs Single:** Pass `i` vs `i+1` to recursion.
✅ **Dedup:** Sort + `i > start` check.
