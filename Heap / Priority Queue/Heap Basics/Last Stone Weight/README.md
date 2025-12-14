# Last Stone Weight

## 🧩 Problem Statement
You are given an array of integers `stones` where `stones[i]` is the weight of the `i`th stone.

We are playing a game with the stones. On each turn, we choose the **heaviest two stones** and smash them together. Suppose the stones have weights `x` and `y` with `x <= y`. The result of this smash is:
- If `x == y`, both stones are destroyed.
- If `x != y`, the stone of weight `x` is destroyed, and the stone of weight `y` has new weight `y - x`.

At the end of the game, there is **at most one** stone left. Return the smallest possible weight of the left stone. If there are no stones left, return `0`.

### 🔹 Example 1:
#### Input:
```plaintext
stones = [2,7,4,1,8,1]
```
#### Output:
```plaintext
1
```
#### Explanation:
1. Combine 7 and 8 to get 1 so the array converts to [2,4,1,1,1].
2. Combine 2 and 4 to get 2 so the array converts to [2,1,1,1].
3. Combine 2 and 1 to get 1 so the array converts to [1,1,1].
4. Combine 1 and 1 to get 0 so the array converts to [1].
   The value of the last stone is 1.

## 🔍 Approaches

### 1. Max-Heap Simulation ($O(N \log N)$)
- **Concept:** We always need the two heaviest stones. A Max-Heap gives us the maximum element in $O(1)$ and removal in $O(\log N)$.
- **Algorithm:**
  1. Build a Max-Heap from the stones.
  2. While Heap size > 1:
     - Pop `y` (heaviest).
     - Pop `x` (second heaviest).
     - If `x != y`, push `y - x` back into the heap.
  3. If Heap empty, return 0. Else return the single element.

### 2. Sort and Insert ($O(N^2)$)
- Maintain a sorted list. Removing is fast, but inserting the new stone weight requires finding the correct position ($O(N)$) or re-sorting ($O(N \log N)$). Heap is generally better.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N \log N)$ (heap operations in a loop).
- **Space Complexity:** $O(N)$ to store the heap.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        priority_queue<int> maxHeap(stones.begin(), stones.end());
        
        while (maxHeap.size() > 1) {
            int y = maxHeap.top(); maxHeap.pop();
            int x = maxHeap.top(); maxHeap.pop();
            if (x != y) {
                maxHeap.push(y - x);
            }
        }
        
        return maxHeap.empty() ? 0 : maxHeap.top();
    }
};
```

### Python
```python
import heapq
from typing import List

class Solution:
    def lastStoneWeight(self, stones: List[int]) -> int:
        # Python uses min-heap, so negate values to simulate max-heap
        max_heap = [-s for s in stones]
        heapq.heapify(max_heap)
        
        while len(max_heap) > 1:
            y = -heapq.heappop(max_heap)
            x = -heapq.heappop(max_heap)
            if x != y:
                heapq.heappush(max_heap, -(y - x))
                
        return -max_heap[0] if max_heap else 0
```

### Java
```java
import java.util.PriorityQueue;
import java.util.Collections;

class Solution {
    public int lastStoneWeight(int[] stones) {
        PriorityQueue<Integer> maxHeap = new PriorityQueue<>(Collections.reverseOrder());
        for (int s : stones) maxHeap.offer(s);
        
        while (maxHeap.size() > 1) {
            int y = maxHeap.poll();
            int x = maxHeap.poll();
            if (x != y) {
                maxHeap.offer(y - x);
            }
        }
        
        return maxHeap.isEmpty() ? 0 : maxHeap.peek();
    }
}
```

## 🌍 Real-World Analogy
### **Sumo Wrestling Tournament:**
Imagine a tournament where the two strongest wrestlers fight. The weaker one is eliminated, and the stronger one continues but is "tired" (weight reduces by the effort). This continues until one winner remains.

## 🎯 Summary
✅ **Max-Heap:** Essential for efficient "get max" and "update" cycles.
