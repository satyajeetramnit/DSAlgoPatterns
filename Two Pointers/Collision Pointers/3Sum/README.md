# 3Sum

## 🧩 Problem Statement
Given an integer array `nums`, return all the triplets `[nums[i], nums[j], nums[k]]` such that `i != j`, `i != k`, and `j != k`, and `nums[i] + nums[j] + nums[k] == 0`.

Notice that the solution set must not contain duplicate triplets.

### 🔹 Example 1:
#### Input:
```plaintext
nums = [-1,0,1,2,-1,-4]
```
#### Output:
```plaintext
[[-1,-1,2],[-1,0,1]]
```
#### Explanation:
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
The distinct triplets are `[-1,0,1]` and `[-1,-1,2]`.

### 🔹 Example 2:
#### Input:
```plaintext
nums = [0,1,1]
```
#### Output:
```plaintext
[]
```

## 🔍 Approaches

### 1. Sorting + Two Pointers
The problem asks for $a + b + c = 0$, which is equivalent to $a + b = -c$.
This looks like **Two Sum** (finding two numbers that sum to a target), but we need to do it for *every* element in the array as the target.
To efficiently find pairs and handle duplicates, sorting the array first is crucial.

### ✨ Intuition
- Sort the array.
- Iterate through the array with index `i` (this fixes the first element `a`).
- Use two pointers, `left` and `right`, to find `b` and `c` in the remaining part of the array such that `b + c = -a`.
- **Handling Duplicates:**
  - If `nums[i] == nums[i-1]`, skip `i` to avoid duplicate triplets starting with the same value.
  - When a triplet is found, move `left` forward and skip any duplicates (`nums[left] == nums[left-1]`).

### 🔥 Algorithm Steps
1. Sort `nums`.
2. Iterate `i` from `0` to `n-3`.
   - If `nums[i] > 0`, break (since the array is sorted, we can't sum to 0 with only positive numbers).
   - If `i > 0` and `nums[i] == nums[i-1]`, continue (skip duplicate `a`).
   - Initialize `l = i + 1`, `r = n - 1`.
   - While `l < r`:
     - `sum = nums[i] + nums[l] + nums[r]`.
     - If `sum < 0`: `l++` (need larger sum).
     - If `sum > 0`: `r--` (need smaller sum).
     - If `sum == 0`:
       - Add triplet `[nums[i], nums[l], nums[r]]` to result.
       - `l++`, `r--`.
       - While `l < r` and `nums[l] == nums[l-1]`: `l++` (skip duplicate `b`).
3. Return result.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(n^2)$. Sorting takes $O(n \log n)$, and the two-pointer search takes $O(n)$ for each of the $n$ elements.
- **Space Complexity:** $O(1)$ or $O(n)$ depending on the sorting implementation (usually $O(\log n)$ or $O(n)$ for Python's Timsort).

## 🚀 Code Implementations

### C++
```cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] > 0) break;
            if (i > 0 && nums[i] == nums[i-1]) continue;
            
            int l = i + 1, r = nums.size() - 1;
            while (l < r) {
                int sum = nums[i] + nums[l] + nums[r];
                if (sum > 0) {
                    r--;
                } else if (sum < 0) {
                    l++;
                } else {
                    res.push_back({nums[i], nums[l], nums[r]});
                    l++;
                    r--;
                    while (l < r && nums[l] == nums[l-1]) l++;
                }
            }
        }
        return res;
    }
};
```

### Python
```python
class Solution:
    def threeSum(self, nums: List[int]) -> List[List[int]]:
        res = []
        nums.sort()
        
        for i, a in enumerate(nums):
            if a > 0:
                break
            if i > 0 and a == nums[i - 1]:
                continue
            
            l, r = i + 1, len(nums) - 1
            while l < r:
                threeSum = a + nums[l] + nums[r]
                if threeSum > 0:
                    r -= 1
                elif threeSum < 0:
                    l += 1
                else:
                    res.append([a, nums[l], nums[r]])
                    l += 1
                    r -= 1
                    while l < r and nums[l] == nums[l - 1]:
                        l += 1
        return res
```

### Java
```java
class Solution {
    public List<List<Integer>> threeSum(int[] nums) {
        Arrays.sort(nums);
        List<List<Integer>> res = new ArrayList<>();
        
        for (int i = 0; i < nums.length - 2; i++) {
            if (nums[i] > 0) break;
            if (i > 0 && nums[i] == nums[i-1]) continue;
            
            int l = i + 1, r = nums.length - 1;
            while (l < r) {
                int sum = nums[i] + nums[l] + nums[r];
                if (sum > 0) {
                    r--;
                } else if (sum < 0) {
                    l++;
                } else {
                    res.add(Arrays.asList(nums[i], nums[l], nums[r]));
                    l++;
                    r--;
                    while (l < r && nums[l] == nums[l-1]) l++;
                }
            }
        }
        return res;
    }
}
```

## 🌍 Real-World Analogy
### **Finding a Trio:**
Imagine forming a team of 3 where the total skill rating must be balanced (zero). 
- If you pick a person with skill -5 (requires +5 support), you look for two others who sum to +5.
- Sorting people by skill helps: if you picked a very negative person, you know you need very positive people (from the other end of the line).

## 🎯 Summary
✅ **O(n^2) Time:** Standard for 3Sum.
✅ **Duplicates:** Sorting makes it easy to skip duplicates.
✅ **Two Pointers:** Reduces the inner pair search to O(n).
