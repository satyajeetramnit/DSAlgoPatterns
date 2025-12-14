# Convex Hull

## 🧩 Problem Statement
Given a set of points in a 2D plane, find the convex hull. The convex hull is the smallest convex polygon containing all the points.

Return the points that form the boundary of the convex hull in counter-clockwise order.

### 🔹 Example 1:
#### Input:
```plaintext
points = [[1,1],[2,2],[2,0],[2,4],[3,3],[4,2]]
```
#### Output:
```plaintext
[[1,1],[2,0],[4,2],[3,3],[2,4]]
```
**Explanation:** These points form the outer boundary.

## 🔍 Approaches

### 1. Monotone Chain Algorithm ($O(N \log N)$)
- **Concept:** Construct the upper and lower hulls separately.
- **Algorithm:**
  1. Sort points by x-coordinate (and y-coordinate for ties).
  2. **Lower Hull:** Iterate through sorted points. For each point `P`, while the last two points added `L2`, `L1` and `P` make a "right turn" (clockwise reference) or are collinear, remove `L1`. Add `P`.
  3. **Upper Hull:** Iterate through sorted points in reverse. Similar logic.
  4. Concatenate Lower and Upper hulls (remove duplicates at start/end).
- **Cross Product:** To determine turn direction of $O \to A \to B$: `(A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x)`.
  - Positive: Counter-Clockwise (Left Turn).
  - Negative: Clockwise (Right Turn).
  - Zero: Collinear.

### 2. Graham Scan ($O(N \log N)$)
- **Concept:** Sort by polar angle with respect to the lowest-leftmost point.
- **Logic:** Iterate and maintain stack to ensure only left turns.

### 3. Jarvis March ($O(NH)$)
- **Concept:** "Gift wrapping". Find the next hull point by checking all other points.
- **Efficiency:** Good if $H$ (hull size) is small, bad if $H \approx N$ ($O(N^2)$).

 We will implement **Monotone Chain** as it's typically easier to implement correctly and robust.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N \log N)$ due to sorting.
- **Space Complexity:** $O(N)$ for storing the hull.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    // Cross product of vectors OA and OB
    // returns > 0 for CCW, < 0 for CW, 0 for collinear
    int cross_product(vector<int>& o, vector<int>& a, vector<int>& b) {
        return (a[0] - o[0]) * (b[1] - o[1]) - (a[1] - o[1]) * (b[0] - o[0]);
    }

    vector<vector<int>> outerTrees(vector<vector<int>>& trees) {
        int n = trees.size();
        if (n <= 1) return trees;

        sort(trees.begin(), trees.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0] || (a[0] == b[0] && a[1] < b[1]);
        });

        vector<vector<int>> hull;
        
        // Lower Hull
        for (const auto& p : trees) {
            while (hull.size() >= 2 && cross_product(hull[hull.size()-2], hull.back(), const_cast<vector<int>&>(p)) < 0) {
                hull.pop_back();
            }
            hull.push_back(p);
        }

        // Upper Hull
        int lower_size = hull.size();
        for (int i = n - 2; i >= 0; --i) {
            while (hull.size() > lower_size && cross_product(hull[hull.size()-2], hull.back(), trees[i]) < 0) {
                hull.pop_back();
            }
            hull.push_back(trees[i]);
        }
        
        // Remove duplicate of start point
        hull.pop_back();
        
        // Remove duplicate points if any (simple logic above might keep collinear points if check is <= 0 vs < 0)
        // With <0, we keep collinear points which is often required for "boundary" problems.
        // If strict convexity needed, change to <= 0.
        // For standard "Erect the Fence" (LeetCode 587), collinear points on hull are included.
        
        // Unique logic just in case
        sort(hull.begin(), hull.end());
        hull.erase(unique(hull.begin(), hull.end()), hull.end());
        
        return hull;
    }
};
```

### Python
```python
from typing import List

class Solution:
    def outerTrees(self, trees: List[List[int]]) -> List[List[int]]:
        def cross_product(o, a, b):
            return (a[0] - o[0]) * (b[1] - o[1]) - (a[1] - o[1]) * (b[0] - o[0])

        trees.sort(key=lambda x: (x[0], x[1]))
        
        # Lower Hull
        lower = []
        for p in trees:
            while len(lower) >= 2 and cross_product(lower[-2], lower[-1], p) < 0:
                lower.pop()
            lower.append(tuple(p))
            
        # Upper Hull
        upper = []
        for p in reversed(trees):
            while len(upper) >= 2 and cross_product(upper[-2], upper[-1], p) < 0:
                upper.pop()
            upper.append(tuple(p))
            
        return list(set(lower + upper))
```

### Java
```java
import java.util.*;

class Solution {
    public int crossProduct(int[] o, int[] a, int[] b) {
        return (a[0] - o[0]) * (b[1] - o[1]) - (a[1] - o[1]) * (b[0] - o[0]);
    }

    public int[][] outerTrees(int[][] trees) {
        if (trees.length <= 1) return trees;
        
        Arrays.sort(trees, (a, b) -> (a[0] == b[0]) ? a[1] - b[1] : a[0] - b[0]);
        
        Stack<int[]> hull = new Stack<>();
        
        // Lower Hull
        for (int[] p : trees) {
            while (hull.size() >= 2) {
                int[] last = hull.pop();
                int[] secondLast = hull.peek();
                if (crossProduct(secondLast, last, p) >= 0) { // Keep if >= 0 (Left or Collinear)
                    hull.push(last);
                    break;
                }
            }
            hull.push(p);
        }
        
        // In Java logic above is tricky with stack peek/pop dance.
        // Better to use ArrayList for random access
        List<int[]> result = new ArrayList<>();
        
        // Correct Lower Hull
        for(int[] p : trees) {
            while(result.size() >= 2 && crossProduct(result.get(result.size()-2), result.get(result.size()-1), p) < 0) {
                result.remove(result.size()-1); 
            }
            result.add(p);
        }
        
        // Upper Hull
        int lowerSize = result.size();
        for(int i = trees.length - 2; i >= 0; i--) {
            while(result.size() > lowerSize && crossProduct(result.get(result.size()-2), result.get(result.size()-1), trees[i]) < 0) {
                result.remove(result.size()-1);
            }
            result.add(trees[i]);
        }
        
        // Remove duplicate of start point (which is at end)
        if (result.size() > 1) result.remove(result.size() - 1);
        
        // Use Set for unique
        Set<String> unique = new HashSet<>();
        List<int[]> finalHull = new ArrayList<>();
        for(int[] p : result) {
            String key = p[0] + "," + p[1];
            if(unique.add(key)) finalHull.add(p);
        }
        
        return finalHull.toArray(new int[finalHull.size()][]);
    }
}
```

## 🌍 Real-World Analogy
### **Rubber Band:**
Imagine pegs on a board representing points. If you stretch a rubber band around all pegs and let it snap tight, the shape it forms is the Convex Hull.

## 🎯 Summary
✅ **Monotone Chain:** Separately builds upper and lower bounds.
✅ **Cross Product:** The key math tool to determine "turn direction".
