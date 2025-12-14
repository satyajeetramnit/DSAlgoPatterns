# Find Median from Data Stream

## 🧩 Problem Statement
The median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value, and the median is the mean of the two middle values.

For example, for `arr = [2,3,4]`, the median is `3`.
For example, for `arr = [2,3]`, the median is `(2 + 3) / 2 = 2.5`.

Implement the `MedianFinder` class:
- `MedianFinder()` initializes the `MedianFinder` object.
- `void addNum(int num)` adds the integer `num` to the data structure.
- `double findMedian()` returns the median of all elements so far. Answers within `10^-5` of the actual answer will be accepted.

### 🔹 Example 1:
#### Input:
```plaintext
["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
[[], [1], [2], [], [3], []]
```
#### Output:
```plaintext
[null, null, null, 1.5, null, 2.0]
```
#### Explanation:
```plaintext
MedianFinder medianFinder = new MedianFinder();
medianFinder.addNum(1);    // arr = [1]
medianFinder.addNum(2);    // arr = [1, 2]
medianFinder.findMedian(); // return 1.5 (i.e., (1 + 2) / 2)
medianFinder.addNum(3);    // arr[1, 2, 3]
medianFinder.findMedian(); // return 2.0
```

## 🔍 Approaches

### 1. Two Heaps ($O(\log N)$)
- **Concept:** We need quick access to the middle elements. Splitting the list into a lower half and an upper half allows us to access the largest of the lower half and the smallest of the upper half.
- **Data Structures:**
  - `small`: A **Max-Heap** to store the smaller half of the numbers.
  - `large`: A **Min-Heap** to store the larger half of the numbers.
- **Invariant:**
  - $0 \le \text{small.size()} - \text{large.size()} \le 1$. (Meaning `small` will have equal or 1 more element than `large`).
  - All elements in `small` $\le$ all elements in `large`.
- **Add Logic:**
  - Add `num` to `small`.
  - Pop max from `small` and push to `large` (to maintain order property).
  - If `small.size() < large.size()`, pop min from `large` and push to `small` (to maintain size property).
- **Find Median:**
  - If sizes are odd (`small` has 1 more), return `small.top()`.
  - If sizes are even, return `(small.top() + large.top()) / 2.0`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(\log N)$ for `addNum`, $O(1)$ for `findMedian`.
- **Space Complexity:** $O(N)$ to store elements.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

class MedianFinder {
private:
    priority_queue<int> small; // Max-heap
    priority_queue<int, vector<int>, greater<int>> large; // Min-heap    

public:
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        small.push(num);
        large.push(small.top());
        small.pop();
        
        if (small.size() < large.size()) {
            small.push(large.top());
            large.pop();
        }
    }
    
    double findMedian() {
        if (small.size() > large.size()) {
            return (double)small.top();
        } else {
            return (double)(small.top() + large.top()) / 2.0;
        }
    }
};
```

### Python
```python
import heapq

class MedianFinder:

    def __init__(self):
        self.small = [] # Max heap (using negative values)
        self.large = [] # Min heap

    def addNum(self, num: int) -> None:
        heapq.heappush(self.small, -num)
        
        # Max of small must be <= Min of large
        if self.small and self.large and (-self.small[0] > self.large[0]):
            val = -heapq.heappop(self.small)
            heapq.heappush(self.large, val)
            
        # Balance sizes
        if len(self.small) > len(self.large) + 1:
            val = -heapq.heappop(self.small)
            heapq.heappush(self.large, val)
        if len(self.large) > len(self.small):
            val = heapq.heappop(self.large)
            heapq.heappush(self.small, -val)

    def findMedian(self) -> float:
        if len(self.small) > len(self.large):
            return float(-self.small[0])
        else:
            return (-self.small[0] + self.large[0]) / 2.0
```
*(Wait, simple logic: push to small, pop max move to large, if large > small move back)*

**Refined Python Logic:**
```python
    def addNum(self, num: int) -> None:
        heapq.heappush(self.small, -num)
        
        # Ensure every element in small is <= every element in large
        if self.small and self.large and (-self.small[0] > self.large[0]):
            val = -heapq.heappop(self.small)
            heapq.heappush(self.large, val)
            
        # Unlike C++, we need careful manual balancing or just standard pattern:
        # 1. Pushing to small then large ensures order.
        # 2. Balancing size ensures size constraint.
```
Actually, C++ logic works in Python too:
1. Push to small.
2. Pop max from small, push to large.
3. If large > small, pop min from large, push to small.

### Java
```java
import java.util.PriorityQueue;
import java.util.Collections;

class MedianFinder {
    private PriorityQueue<Integer> small; // Max heap
    private PriorityQueue<Integer> large; // Min heap

    public MedianFinder() {
        small = new PriorityQueue<>(Collections.reverseOrder());
        large = new PriorityQueue<>();
    }
    
    public void addNum(int num) {
        small.offer(num);
        large.offer(small.poll());
        
        if (small.size() < large.size()) {
            small.offer(large.poll());
        }
    }
    
    public double findMedian() {
        if (small.size() > large.size()) {
            return (double)small.peek();
        } else {
            return (small.peek() + large.peek()) / 2.0;
        }
    }
}
```

## 🌍 Real-World Analogy
### **Separating the Stack:**
Imagine a stack of papers with numbers. You keep the smaller numbered papers in a pile on the left (sorted so the largest is on top) and larger numbered papers on the right (sorted so smallest is on top). The "median" is just looking at the top of one or both piles.

## 🎯 Summary
✅ **Two Heaps:** The quintessential "median in stream" solution.
