# Maximum Subarray (Kadane's Algorithm)

## 🧩 Problem Statement
Given an array of integers, find the **contiguous subarray** (containing at least one number) which has the **largest sum**, and return that sum.

### 🔹 Example
#### Input:
```plaintext
nums = [-2,1,-3,4,-1,2,1,-5,4]
```
#### Output:
```plaintext
6
```
#### Explanation:
The contiguous subarray `[4, -1, 2, 1]` has the largest sum = **6**.

## 🔍 Approach (Kadane's Algorithm)
Kadane’s Algorithm efficiently finds the maximum sum of a contiguous subarray using a single pass.

### ✨ Intuition
- Maintain three variables:
  1. `current_sum`: Maximum sum ending at the current index.
  2. `max_sum`: The overall maximum sum encountered so far.
  3. `start`, `end`, and `temp_start` to track the indices of the subarray.
- Iterate through the array and decide at each step whether to extend the current subarray or start fresh.
- The key observation is:
  - If `current_sum` becomes negative, reset it to `0` and update `temp_start` to the next index.

### 🔥 Algorithm Steps
1. Initialize `max_sum` with the first element (`nums[0]`).
2. Set `current_sum = 0` and tracking indices `start = 0`, `end = 0`, `temp_start = 0`.
3. Iterate through the array:
   - Add `nums[i]` to `current_sum`.
   - If `current_sum > max_sum`, update `max_sum`, `start = temp_start`, and `end = i`.
   - If `current_sum < 0`, reset it to `0` and update `temp_start = i + 1`.
4. Return `max_sum` along with `[start, end]` for the subarray.

## ⏳ Time & Space Complexity
- **Time Complexity:** `O(n)`, as we traverse the array once.
- **Space Complexity:** `O(1)`, as we use only a few extra variables.

## 🚀 Code Implementations

### C++ (With Subarray Tracking)
```cpp
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int maxSubArray(vector<int>& nums) {
    int max_sum = nums[0], current_sum = 0;
    int start = 0, end = 0, temp_start = 0;
    
    for (int i = 0; i < nums.size(); i++) {
        current_sum += nums[i];
        
        if (current_sum > max_sum) {
            max_sum = current_sum;
            start = temp_start;
            end = i;
        }
        
        if (current_sum < 0) {
            current_sum = 0;
            temp_start = i + 1;
        }
    }
    cout << "Subarray: [";
    for (int i = start; i <= end; i++) {
        cout << nums[i] << (i < end ? ", " : "");
    }
    cout << "]" << endl;
    return max_sum;
}

int main() {
    vector<int> nums = {-2,1,-3,4,-1,2,1,-5,4};
    cout << "Maximum Subarray Sum: " << maxSubArray(nums) << endl;
    return 0;
}
```

### Python (With Subarray Tracking)
```python
def maxSubArray(nums):
    max_sum = nums[0]
    current_sum = 0
    start = end = temp_start = 0
    
    for i in range(len(nums)):
        current_sum += nums[i]
        
        if current_sum > max_sum:
            max_sum = current_sum
            start, end = temp_start, i
        
        if current_sum < 0:
            current_sum = 0
            temp_start = i + 1
    
    print("Subarray:", nums[start:end+1])
    return max_sum

# Example usage
nums = [-2,1,-3,4,-1,2,1,-5,4]
print("Maximum Subarray Sum:", maxSubArray(nums))
```

### Java (With Subarray Tracking)
```java
class Solution {
    public int maxSubArray(int[] nums) {
        int maxSum = nums[0], currentSum = 0;
        int start = 0, end = 0, tempStart = 0;
        
        for (int i = 0; i < nums.length; i++) {
            currentSum += nums[i];
            
            if (currentSum > maxSum) {
                maxSum = currentSum;
                start = tempStart;
                end = i;
            }
            
            if (currentSum < 0) {
                currentSum = 0;
                tempStart = i + 1;
            }
        }
        System.out.println("Subarray: " + java.util.Arrays.toString(java.util.Arrays.copyOfRange(nums, start, end + 1)));
        return maxSum;
    }
    
    public static void main(String[] args) {
        Solution sol = new Solution();
        int[] nums = {-2,1,-3,4,-1,2,1,-5,4};
        System.out.println("Maximum Subarray Sum: " + sol.maxSubArray(nums));
    }
}
```

## 🌍 Real-World Analogy
### **Stock Market Profit Maximization:**
Imagine you are tracking **daily profits and losses** from your stock investments. You want to find a **continuous period** where you made the **highest profit**.
- **Positive numbers** represent **gains**.
- **Negative numbers** represent **losses**.
- Kadane’s Algorithm helps **identify the best time frame** to maximize your profit!
- Example:
  ```plaintext
  Daily Profits: [-2, 1, -3, 4, -1, 2, 1, -5, 4]
  Best period: [4, -1, 2, 1] → Maximum profit: 6
  ```

## 💡 Variations & Follow-ups
- **Find the subarray itself:** Now included in the code.
- **Handle circular arrays:** Apply **Kadane’s twice** (normal & inverted sum).
- **What if we have constraints like subarray length `k`?** Use **Sliding Window**.

## 🎯 Summary
✅ **O(n) Complexity:** One pass is enough!  
✅ **Handles Negative Values:** Always finds the best subarray.  
✅ **Tracks Subarray Indices:** Shows exactly which part of the array contributes to max sum.  
✅ **Practical Usage:** Used in stock trading, signal processing, and optimization problems.

Happy Coding! 🎯🔥

