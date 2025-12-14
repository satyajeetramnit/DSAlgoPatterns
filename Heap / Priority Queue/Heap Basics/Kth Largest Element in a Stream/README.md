# Kth Largest Element in a Stream

## 🧩 Problem Statement
Design a class to find the `k`th largest element in a stream. Note that it is the `k`th largest element in the sorted order, not the `k`th distinct element.

Implement `KthLargest` class:
- `KthLargest(int k, int[] nums)` Initializes the object with the integer `k` and the stream of integers `nums`.
- `int add(int val)` Appends the integer `val` to the stream and returns the element representing the `k`th largest element in the stream.

### 🔹 Example 1:
#### Input:
```plaintext
["KthLargest", "add", "add", "add", "add", "add"]
[[3, [4, 5, 8, 2]], [3], [5], [10], [9], [4]]
```
#### Output:
```plaintext
[null, 4, 5, 5, 8, 8]
```
#### Explanation:
```plaintext
KthLargest kthLargest = new KthLargest(3, [4, 5, 8, 2]); // nums = [4, 5, 8, 2] -> sorted [2, 4, 5, 8]. 3rd largest is 4.
kthLargest.add(3);   // return 4. nums = [2, 3, 4, 5, 8], 3rd largest is 4.
kthLargest.add(5);   // return 5. nums = [2, 3, 4, 5, 5, 8], 3rd largest is 5.
kthLargest.add(10);  // return 5. nums = [2, 3, 4, 5, 5, 8, 10], 3rd largest is 5.
kthLargest.add(9);   // return 8. nums = [2, 3, 4, 5, 5, 8, 9, 10], 3rd largest is 8.
kthLargest.add(4);   // return 8. nums = [2, 3, 4, 4, 5, 5, 8, 9, 10], 3rd largest is 8.
```

## 🔍 Approaches

### 1. Min-Heap of Size K ($O(N \log K)$)
- **Concept:** We want to keep finding the K-th largest element. This means we only care about the K largest elements seen so far.
- **Data Structure:** A **Min-Heap** of size `k`.
- **Logic:**
  - The heap stores the `k` largest elements found so far.
  - The smallest element in this heap (the root) is the `k`-th largest element overall (because there are `k-1` elements larger than it in the heap).
  - When a new value arrives:
    - Push it into the heap.
    - If heap size exceeds `k`, pop the smallest element (remove the element that is no longer in the top `k`).
  - The root is always the answer.
- **Complexity:**
  - `add()`: $O(\log K)$ because heap size is capped at `K`.
  - Constructor: $O(N \log K)$.

### 2. Sort ($O(N \log N)$)
- Keep array sorted. Adding is $O(N)$. Too slow.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N \log K)$ for initialization, $O(\log K)$ for each `add`.
- **Space Complexity:** $O(K)$ to store the heap.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

class KthLargest {
private:
    priority_queue<int, vector<int>, greater<int>> minHeap;
    int k;
public:
    KthLargest(int k, vector<int>& nums) {
        this->k = k;
        for (int num : nums) {
            add(num);
        }
    }
    
    int add(int val) {
        minHeap.push(val);
        if (minHeap.size() > k) {
            minHeap.pop();
        }
        return minHeap.top();
    }
};
```

### Python
```python
import heapq
from typing import List

class KthLargest:

    def __init__(self, k: int, nums: List[int]):
        self.k = k
        self.heap = []
        for num in nums:
            self.add(num)

    def add(self, val: int) -> int:
        heapq.heappush(self.heap, val)
        if len(self.heap) > self.k:
            heapq.heappop(self.heap)
        return self.heap[0]
```

### Java
```java
import java.util.PriorityQueue;

class KthLargest {
    private PriorityQueue<Integer> minHeap;
    private int k;

    public KthLargest(int k, int[] nums) {
        this.k = k;
        minHeap = new PriorityQueue<>();
        for (int num : nums) {
            add(num);
        }
    }
    
    public int add(int val) {
        minHeap.offer(val);
        if (minHeap.size() > k) {
            minHeap.poll();
        }
        return minHeap.peek();
    }
}
```

## 🌍 Real-World Analogy
### **Top Score Leaderboard:**
A game leaderboard only shows the Top 10 players. When a new player plays, if their score is higher than the 10th person, they knock them off and enter the list. The score to beat is always the lowest score on the leaderboard (the 10th place).

## 🎯 Summary
✅ **Min-Heap:** The perfect tool for maintaining the "Top K" of anything, where you need quick access to the smallest of the top K to decide if a new entry qualifies.
