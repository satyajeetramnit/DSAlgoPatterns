# Single Element in a Sorted Array

## 🧩 Problem Statement
You are given a sorted array consisting of only integers where every element appears exactly twice, except for one element which appears exactly once. Found this single element that appears only once.

You must accept a solution with a time complexity of `O(log n)` and space complexity of `O(1)`.

### 🔹 Example 1:
#### Input:
```plaintext
nums = [1,1,2,3,3,4,4,8,8]
```
#### Output:
```plaintext
2
```

### 🔹 Example 2:
#### Input:
```plaintext
nums = [3,3,7,7,10,11,11]
```
#### Output:
```plaintext
10
```

## 🔍 Approaches

### 1. Binary Search
Since the array is sorted, we can use binary search.
The key observation is how the pairs are distributed.
- Before the single element, pairs start at even indices: `(0,1), (2,3), (4,5)...`
- After the single element, pairs start at odd indices due to the shift.

### ✨ Intuition
- Choose `mid`.
- If `mid` is even:
  - If `nums[mid] == nums[mid+1]`: We are in the "left half" (good pairs). Single element is to the right. `left = mid + 2`.
  - Otherwise: We are in the "right half" or at the single element. `right = mid`.
- If `mid` is odd:
  - If `nums[mid] == nums[mid-1]`: We are in the "left half". Single element to right. `left = mid + 1`.
  - Otherwise: We are in the "right half". `right = mid - 1` (or `mid` depending on logic).

Better Logic:
- Ensure `mid` is even. If `mid` is odd, subtract 1 to make it even.
- Check if `nums[mid] == nums[mid + 1]`.
  - True: Pattern holds, answer is to the right. `left = mid + 2`.
  - False: Pattern broken (either at answer or after), answer is to the left or is `mid`. `right = mid`.

### 🔥 Algorithm Steps
1. `left = 0`, `right = n - 1`.
2. While `left < right`:
   - `mid = left + (right - left) / 2`.
   - If `mid` is odd, `mid--`. (Force even start).
   - If `nums[mid] == nums[mid + 1]`:
     - Pair is intact. Single element is further right.
     - `left = mid + 2`.
   - Else:
     - Single element is `nums[mid]` or to the left.
     - `right = mid`.
3. Return `nums[left]`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(\log n)$.
- **Space Complexity:** $O(1)$.

## 🚀 Code Implementations

### C++
```cpp
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (mid % 2 == 1) mid--;
            
            if (nums[mid] == nums[mid + 1]) {
                left = mid + 2;
            } else {
                right = mid;
            }
        }
        return nums[left];
    }
};
```

### Python
```python
class Solution:
    def singleNonDuplicate(self, nums: List[int]) -> int:
        left, right = 0, len(nums) - 1
        
        while left < right:
            mid = (left + right) // 2
            if mid % 2 == 1:
                mid -= 1
            
            if nums[mid] == nums[mid + 1]:
                left = mid + 2
            else:
                right = mid
        return nums[left]
```

### Java
```java
class Solution {
    public int singleNonDuplicate(int[] nums) {
        int left = 0, right = nums.length - 1;
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (mid % 2 == 1) mid--;
            
            if (nums[mid] == nums[mid + 1]) {
                left = mid + 2;
            } else {
                right = mid;
            }
        }
        return nums[left];
    }
}
```

## 🌍 Real-World Analogy
### **Broken Dance Partners:**
Couples are dancing in a line. Everyone has a partner except one person.
- Before the lone person, pair pattern is `(A,A), (B,B)`.
- You check a pair. If they match, the lone person is further down.
- If they don't match, the lone person (or the disruption) has already appeared logic-wise.

## 🎯 Summary
✅ **Index Parity:** Exploiting index properties (even/odd) is standard for this problem.
✅ **Binary Search Pattern:** Reduce search space by half based on pair integrity.
