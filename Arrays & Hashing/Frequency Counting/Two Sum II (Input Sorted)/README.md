# Two Sum II - Input Array Is Sorted

## 🧩 Problem Statement
Given a **1-indexed** array of integers `numbers` that is already **sorted in non-decreasing order**, find two numbers such that they add up to a specific `target` number. Let these two numbers be `numbers[index1]` and `numbers[index2]` where `1 <= index1 < index2 <= numbers.length`.

Return the indices of the two numbers, `index1` and `index2`, added by one as an integer array `[index1, index2]` of length 2.

The tests are generated such that there is **exactly one solution**. You may not use the same element twice.

Your solution must use only constant extra space.

### 🔹 Example 1:
#### Input:
```plaintext
numbers = [2,7,11,15], target = 9
```
#### Output:
```plaintext
[1,2]
```
#### Explanation:
The sum of 2 and 7 is 9. Therefore, index1 = 1, index2 = 2. We return [1, 2].

### 🔹 Example 2:
#### Input:
```plaintext
numbers = [2,3,4], target = 6
```
#### Output:
```plaintext
[1,3]
```

## 🔍 Approaches

### 1. Two Pointers
Since the array is sorted, we can use two pointers technique.

### ✨ Intuition
- Start with one pointer at the beginning (`left`) and one at the end (`right`).
- Calculate `sum = numbers[left] + numbers[right]`.
- If `sum > target`, we need a smaller sum. Since the array is sorted, moving the `right` pointer to the left will decrease the sum.
- If `sum < target`, we need a larger sum. Moving the `left` pointer to the right will increase the sum.
- If `sum == target`, we found our pair.

### 🔥 Algorithm Steps
1. Initialize `left = 0` and `right = numbers.length - 1`.
2. While `left < right`:
   - Calculate `currentSum = numbers[left] + numbers[right]`.
   - If `currentSum == target`, return `[left + 1, right + 1]`.
   - If `currentSum > target`, decrement `right`.
   - If `currentSum < target`, increment `left`.
3. Iterate until the solution is found (guaranteed to exist).

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(n)$, where $n$ is the number of elements. In the worst case, we touch each element at most once.
- **Space Complexity:** $O(1)$, as we only use two pointers and a few variables.

## 🚀 Code Implementations

### C++
```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int left = 0, right = numbers.size() - 1;
        while (left < right) {
            int currentSum = numbers[left] + numbers[right];
            if (currentSum > target) {
                right--;
            } else if (currentSum < target) {
                left++;
            } else {
                return {left + 1, right + 1};
            }
        }
        return {};
    }
};
```

### Python
```python
class Solution:
    def twoSum(self, numbers: List[int], target: int) -> List[int]:
        l, r = 0, len(numbers) - 1
        
        while l < r:
            curSum = numbers[l] + numbers[r]
            
            if curSum > target:
                r -= 1
            elif curSum < target:
                l += 1
            else:
                return [l + 1, r + 1]
        return []
```

### Java
```java
class Solution {
    public int[] twoSum(int[] numbers, int target) {
        int left = 0, right = numbers.length - 1;
        while (left < right) {
            int currentSum = numbers[left] + numbers[right];
            if (currentSum > target) {
                right--;
            } else if (currentSum < target) {
                left++;
            } else {
                return new int[] { left + 1, right + 1 };
            }
        }
        return new int[] {};
    }
}
```

## 🌍 Real-World Analogy
### **Finding a Book:**
Imagine a bookshelf sorted by book height. You want to pick two books whose combined height is exactly $X$.
- You pick the shortest (left) and tallest (right).
- If their combined height is too much, the tallest one is definitely too tall to pair with the shortest (or any other book). So you discard the tallest and pick the second tallest.
- If their combined height is too little, the shortest is definitely too short. So you discard it and pick the second shortest.

## 🎯 Summary
✅ **O(n) Time:** Efficient single pass.
✅ **O(1) Space:** No hash map needed due to sorted property.
✅ **Two Pointers:** Classic pattern for sorted arrays.
