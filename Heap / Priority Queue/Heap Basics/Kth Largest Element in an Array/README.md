# Kth Largest Element in an Array

## 🧩 Problem Statement
Given an integer array `nums` and an integer `k`, return the `k`th largest element in the array.

Note that it is the `k`th largest element in the sorted order, not the `k`th distinct element.

### 🔹 Example 1:
#### Input:
```plaintext
nums = [3,2,1,5,6,4], k = 2
```
#### Output:
```plaintext
5
```

### 🔹 Example 2:
#### Input:
```plaintext
nums = [3,2,3,1,2,4,5,5,6], k = 4
```
#### Output:
```plaintext
4
```

## 🔍 Approaches

### 1. Min-Heap ($O(N \log K)$)
- **Concept:** Maintain a Min-Heap of size `k`.
- **Logic:**
  - The heap stores the `k` largest elements encountered so far.
  - The root of the heap is the smallest of these `k` elements, which corresponds to the `k`-th largest overall.
  - Iterate through `nums`:
    - Push element.
    - If heap size > `k`, pop min.
  - Return heap top.

### 2. QuickSelect (Average $O(N)$)
- **Concept:** Based on QuickSort partitioning.
- Pick a pivot. Partition array into `smaller` and `larger`.
- If pivot index matches `N - k`, we found it.
- Else, recurse into the appropriate half.
- **Worst Case:** $O(N^2)$ if pivot is always bad (sorted array).

We implement **Min-Heap** here as it fits the "Heap Basics" theme and guarantees $O(N \log K)$.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N \log K)$.
- **Space Complexity:** $O(K)$.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> minHeap;
        for (int num : nums) {
            minHeap.push(num);
            if (minHeap.size() > k) {
                minHeap.pop();
            }
        }
        return minHeap.top();
    }
};
```

### Python
```python
import heapq
from typing import List

class Solution:
    def findKthLargest(self, nums: List[int], k: int) -> int:
        min_heap = []
        for num in nums:
            heapq.heappush(min_heap, num)
            if len(min_heap) > k:
                heapq.heappop(min_heap)
        
        return min_heap[0]
```

### Java
```java
import java.util.PriorityQueue;

class Solution {
    public int findKthLargest(int[] nums, int k) {
        PriorityQueue<Integer> minHeap = new PriorityQueue<>();
        for (int num : nums) {
            minHeap.offer(num);
            if (minHeap.size() > k) {
                minHeap.poll();
            }
        }
        return minHeap.peek();
    }
}
```

## 🌍 Real-World Analogy
### **Class Rank:**
To find the 10th highest grade in a class, you don't need to sort everyone perfectly. You just need to keep track of the "Top 10" you've seen so far. The lowest grade in your "Top 10" list is the cutoff to beat.

## 🎯 Summary
✅ **Min-Heap:** Simple and efficient for "Top K" problems with guaranteed bounds.
