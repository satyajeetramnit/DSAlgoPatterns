# Product of Array Except Self

## 🧩 Problem Statement
Given an integer array `nums`, return an array `answer` such that `answer[i]` is equal to the product of all the elements of `nums` except `nums[i]`.

The product of any prefix or suffix of `nums` is **guaranteed** to fit in a **32-bit** integer.

You must write an algorithm that runs in **O(n)** time and without using the division operation.

### 🔹 Example 1:
#### Input:
```plaintext
nums = [1,2,3,4]
```
#### Output:
```plaintext
[24,12,8,6]
```
#### Explanation:
- index 0: 2*3*4 = 24
- index 1: 1*3*4 = 12
- index 2: 1*2*4 = 8
- index 3: 1*2*3 = 6

### 🔹 Example 2:
#### Input:
```plaintext
nums = [-1,1,0,-3,3]
```
#### Output:
```plaintext
[0,0,9,0,0]
```

## 🔍 Approaches

### 1. Left and Right Products
Since we cannot verify division (handling zeroes would be tricky anyway), we can calculate products from both sides.
`answer[i] = product(left of i) * product(right of i)`.

### ✨ Intuition
- Imagine we want to calculate the product for index `i`.
- It's essentially `(nums[0] * ... * nums[i-1]) * (nums[i+1] * ... * nums[n-1])`.
- The left part is the "prefix product" up to `i-1`.
- The right part is the "suffix product" from `i+1`.
- We can compute these prefixes and suffixes in two passes.

### 🔥 Algorithm Steps
1. Create a result array initialized to 1s.
2. **First Pass (Prefix):** Iterate forward. Keep a running `prefix` product. `res[i]` will initially store the product of elements to the *left* of `i`.
3. **Second Pass (Suffix):** Iterate backward. Keep a running `postfix` product. Multiply `res[i]` by the `postfix` product (which represents product of elements to the *right* of `i`).
4. Return `res`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(n)$, two passes.
- **Space Complexity:** $O(1)$, if we ignore the output array (as per problem statement).

## 🚀 Code Implementations

### C++
```cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n, 1);
        
        int prefix = 1;
        for (int i = 0; i < n; i++) {
            res[i] = prefix;
            prefix *= nums[i];
        }
        
        int postfix = 1;
        for (int i = n - 1; i >= 0; i--) {
            res[i] *= postfix;
            postfix *= nums[i];
        }
        
        return res;
    }
};
```

### Python
```python
class Solution:
    def productExceptSelf(self, nums: List[int]) -> List[int]:
        res = [1] * len(nums)
        
        prefix = 1
        for i in range(len(nums)):
            res[i] = prefix
            prefix *= nums[i]
            
        postfix = 1
        for i in range(len(nums) - 1, -1, -1):
            res[i] *= postfix
            postfix *= nums[i]
            
        return res
```

### Java
```java
class Solution {
    public int[] productExceptSelf(int[] nums) {
        int[] res = new int[nums.length];
        
        int prefix = 1;
        for (int i = 0; i < nums.length; i++) {
            res[i] = prefix;
            prefix *= nums[i];
        }
        
        int postfix = 1;
        for (int i = nums.length - 1; i >= 0; i--) {
            res[i] *= postfix;
            postfix *= nums[i];
        }
        
        return res;
    }
}
```

## 🌍 Real-World Analogy
### **Potluck Dinner:**
Imagine 4 friends bring 4 different dishes.
- Friend A wants to taste everything *except* their own dish.
- Friend B wants to taste everything *except* theirs.
- Instead of everyone eating from one big pot, Friend A takes a scoop from B, C, and D.
- Effectively, A's plate = Total Food - A's Food (if subtraction was allowed/safe).
- With multiplication, A's experience is B * C * D.

## 🎯 Summary
✅ **O(n) Time:** Without division.
✅ **Two-Pass:** Forward for prefix, backward for suffix.
✅ **Space Optimized:** Using the output array itself for storage.
