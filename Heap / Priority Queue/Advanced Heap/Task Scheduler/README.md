# Task Scheduler

## 🧩 Problem Statement
Given a characters array `tasks`, representing the tasks a CPU needs to do, where each letter represents a different task. Tasks could be done in any order. Each task is done in one unit of time. For each unit of time, the CPU could complete either one task or just be idle.

However, there is a non-negative integer `n` that represents the cooldown period between two **same tasks** (the same letter in the array), that is that there must be at least `n` units of time between any two same tasks.

Return the least number of units of times that the CPU will take to finish all the given tasks.

### 🔹 Example 1:
#### Input:
```plaintext
tasks = ["A","A","A","B","B","B"], n = 2
```
#### Output:
```plaintext
8
```
#### Explanation:
A -> B -> idle -> A -> B -> idle -> A -> B.
Total 8 units.

## 🔍 Approaches

### 1. Max-Heap Simulation ($O(N)$ or $O(TotalTime)$)
- **Concept:** Always greedily execute the task with the highest remaining frequency to get it out of the way.
- **Data Structures:**
  - **Max-Heap:** Store available tasks by frequency.
  - **Queue:** Store waiting tasks `[frequency, time_to_active]`.
- **Algorithm:**
  - Count frequencies. Push to Max-Heap.
  - Time = 0.
  - Loop while Heap or Queue is not empty:
    - Time++.
    - If Heap not empty:
      - Pop task (highest freq).
      - Decrement freq.
      - If freq > 0, push to Queue with `time + n`.
    - Check Queue: if `head.time == time`, move to Heap.
  - Return Time.

### 2. Math / Greedy Construction ($O(N)$)
- **Concept:** The problem is bottlenecked by the most frequent task.
- Let `max_freq` be the count of the most frequent task (e.g., 'A').
- We need `(max_freq - 1)` groups of size `(n + 1)`.
- Last group contains all tasks with frequency `max_freq`.
- **Formula:** `(max_freq - 1) * (n + 1) + count_of_max_freq_tasks`.
- **Edge Case:** If `n` is small, we might finish filling slots and still have other tasks. Result is `max(tasks.length, calculated)`.

We will implement **Max-Heap Simulation** as it is more intuitive and fits the category.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N)$ (counting takes $N$, heap ops are bounded by constant 26).
- **Space Complexity:** $O(1)$ (26 chars).

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <queue>
#include <unordered_map>
#include <iostream>

using namespace std;

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        unordered_map<char, int> counts;
        for (char t : tasks) counts[t]++;
        
        priority_queue<int> maxHeap;
        for (auto& pair : counts) maxHeap.push(pair.second);
        
        int time = 0;
        queue<pair<int, int>> q; // {freq, active_time}
        
        while (!maxHeap.empty() || !q.empty()) {
            time++;
            
            if (!maxHeap.empty()) {
                int freq = maxHeap.top();
                maxHeap.pop();
                freq--;
                if (freq > 0) {
                    q.push({freq, time + n});
                }
            }
            
            if (!q.empty() && q.front().second == time) {
                maxHeap.push(q.front().first);
                q.pop();
            }
        }
        
        return time;
    }
};
```

### Python
```python
import heapq
from collections import Counter, deque
from typing import List

class Solution:
    def leastInterval(self, tasks: List[str], n: int) -> int:
        count = Counter(tasks)
        max_heap = [-cnt for cnt in count.values()]
        heapq.heapify(max_heap)
        
        time = 0
        q = deque() # pairs of [-freq, idle_until_time]
        
        while max_heap or q:
            time += 1
            if max_heap:
                cnt = 1 + heapq.heappop(max_heap) # cnt is negative
                if cnt != 0:
                    q.append((cnt, time + n))
            
            if q and q[0][1] == time:
                heapq.heappush(max_heap, q.popleft()[0])
                
        return time
```

### Java
```java
import java.util.*;

class Solution {
    public int leastInterval(char[] tasks, int n) {
        Map<Character, Integer> counts = new HashMap<>();
        for (char t : tasks) counts.put(t, counts.getOrDefault(t, 0) + 1);
        
        PriorityQueue<Integer> maxHeap = new PriorityQueue<>(Collections.reverseOrder());
        maxHeap.addAll(counts.values());
        
        int time = 0;
        Queue<int[]> q = new LinkedList<>(); // {freq, active_time}
        
        while (!maxHeap.isEmpty() || !q.isEmpty()) {
            time++;
            
            if (!maxHeap.isEmpty()) {
                int freq = maxHeap.poll();
                freq--;
                if (freq > 0) {
                    q.offer(new int[]{freq, time + n});
                }
            }
            
            if (!q.isEmpty() && q.peek()[1] == time) {
                maxHeap.offer(q.poll()[0]);
            }
        }
        
        return time;
    }
}
```

## 🌍 Real-World Analogy
### **Doing Laundry:**
If you have 3 loads of Whites (A) and 3 loads of Colors (B), and your washer takes 1 hour but needs 2 hours cooldown between same types (maybe specific detergent refill?). You do A, then B (while A-detergent refills), then wait (if n=2), then A...

## 🎯 Summary
✅ **Simulation:** Simulates the CPU clock cycle by cycle.
