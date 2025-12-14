# IPO

## 🧩 Problem Statement
Suppose LeetCode will start its **IPO** soon. In order to sell a good price of its shares to Venture Capital, LeetCode would like to work on some projects to increase its capital before the IPO. Since it has limited resources, it can only finish at most `k` distinct projects before the IPO. Help LeetCode design the best way to maximize its total capital after finishing at most `k` distinct projects.

You are given `n` projects where the `i`th project has a pure profit `profits[i]` and a minimum capital of `capital[i]` is needed to start it.

Initially, you have `w` capital. When you finish a project, you will obtain its pure profit and the profit will be added to your total capital.

Pick a list of **at most** `k` distinct projects from given projects to **maximize your final capital**, and return the final maximized capital.

### 🔹 Example 1:
#### Input:
```plaintext
k = 2, w = 0, profits = [1,2,3], capital = [0,1,1]
```
#### Output:
```plaintext
4
```
#### Explanation:
1. Since your initial capital is 0, you can only start the project indexed 0 (capital needed 0, profit 1).
2. After finishing it, your capital becomes 0 + 1 = 1.
3. With capital 1, you can either start index 1 (capital 1, profit 2) or index 2 (capital 1, profit 3).
4. You choose index 2 for more profit.
5. Final capital = 1 + 3 = 4.

## 🔍 Approaches

### 1. Two Heaps (Greedy) ($O(N \log N)$)
- **Concept:** At any step, we want to choose the project with the **MAX PROFIT** that we can afford (capital needed <= current capital).
- **Data Structures:**
  1. **Min-Heap (Projects by Capital):** Stores all projects sorted by capital needed. This allows us to quickly find all projects we can *currently* afford.
  2. **Max-Heap (Available Projects by Profit):** Stores profits of all "affordable" projects.
- **Algorithm:**
  1. Add all projects to the Min-Heap (sorted by capital).
  2. Loop `k` times:
     - While the cheapest project in Min-Heap has `capital <= w`:
       - Move it to the Max-Heap (store only profit).
     - If Max-Heap is empty, we can't do any more projects. Break.
     - `w += max_heap.pop()`.
  3. Return `w`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N \log N)$ (sorting/pushing all to min-heap) + $O(K \log N)$ (push/pop k times). Dominated by $O(N \log N)$.
- **Space Complexity:** $O(N)$ for heaps.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        int n = profits.size();
        vector<pair<int, int>> projects;
        for (int i = 0; i < n; i++) {
            projects.push_back({capital[i], profits[i]});
        }
        
        // Sort by capital cost
        sort(projects.begin(), projects.end());
        
        priority_queue<int> maxProfit;
        int i = 0;
        
        while (k--) {
            while (i < n && projects[i].first <= w) {
                maxProfit.push(projects[i].second);
                i++;
            }
            
            if (maxProfit.empty()) break;
            
            w += maxProfit.top();
            maxProfit.pop();
        }
        
        return w;
    }
};
```

### Python
```python
import heapq
from typing import List

class Solution:
    def findMaximizedCapital(self, k: int, w: int, profits: List[int], capital: List[int]) -> int:
        projects = sorted(zip(capital, profits))
        n = len(projects)
        max_profit_heap = []
        i = 0
        
        for _ in range(k):
            # Move affordable projects to max_profit_heap
            while i < n and projects[i][0] <= w:
                heapq.heappush(max_profit_heap, -projects[i][1])
                i += 1
            
            if not max_profit_heap:
                break
            
            w += -heapq.heappop(max_profit_heap)
            
        return w
```

### Java
```java
import java.util.PriorityQueue;
import java.util.Arrays;
import java.util.Comparator;

class Solution {
    public int findMaximizedCapital(int k, int w, int[] profits, int[] capital) {
        int n = profits.length;
        int[][] projects = new int[n][2];
        for (int i = 0; i < n; i++) {
            projects[i][0] = capital[i];
            projects[i][1] = profits[i];
        }
        
        // Sort by capital increasing
        Arrays.sort(projects, Comparator.comparingInt(a -> a[0]));
        
        PriorityQueue<Integer> maxProfit = new PriorityQueue<>((a, b) -> b - a);
        int i = 0;
        
        while (k-- > 0) {
            while (i < n && projects[i][0] <= w) {
                maxProfit.add(projects[i][1]);
                i++;
            }
            
            if (maxProfit.isEmpty()) break;
            
            w += maxProfit.poll();
        }
        
        return w;
    }
}
```

## 🌍 Real-World Analogy
### **Video Game Quest Log:**
You have a bunch of quests. Some require Level 5 to start, some Level 10. You are Level 1.
1. Filter quests: "Show me everything requiring Level <= 1".
2. Pick the one with the HIGHEST XP reward.
3. Complete it -> Level Up.
4. Now you might unlock new quests (Level <= new Level). Repeat.

## 🎯 Summary
✅ **Greedy Choice:** Always pick the best available option now; it increases capital the most, unlocking the widest range of future options.
