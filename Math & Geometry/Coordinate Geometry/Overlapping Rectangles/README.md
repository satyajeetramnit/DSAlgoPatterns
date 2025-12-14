# Overlapping Rectangles

## 🧩 Problem Statement
Determine if two axis-aligned rectangles overlap.

Each rectangle is represented by its bottom-left `(x1, y1)` and top-right `(x2, y2)` coordinates.

### 🔹 Example 1:
#### Input:
```plaintext
rec1 = [0,0,2,2], rec2 = [1,1,3,3]
```
#### Output:
```plaintext
true
```

### 🔹 Example 2:
#### Input:
```plaintext
rec1 = [0,0,1,1], rec2 = [1,0,2,1]
```
#### Output:
```plaintext
false
```
**Explanation:** They touch at the edge but typically "overlap" implies positive area. In some variations, touching is allowed, but usually strict overlap is required (area > 0). We will assume strict overlap.

## 🔍 Approaches

### 1. Coordinate Check ($O(1)$)
- **Concept:** Two rectangles DO NOT overlap if one is completely to the left, right, top, or bottom of the other.
- **Logic (Non-Overlap):**
  - `rec1` is Left of `rec2`: `rec1.x2 <= rec2.x1`
  - `rec1` is Right of `rec2`: `rec1.x1 >= rec2.x2`
  - `rec1` is Below `rec2`: `rec1.y2 <= rec2.y1`
  - `rec1` is Above `rec2`: `rec1.y1 >= rec2.y2`
- **Overlap Condition:** The negation of the above.
- **Formula:** `!(Left || Right || Below || Above)`
- **Simplified:** `rec1.x1 < rec2.x2 && rec1.x2 > rec2.x1 && rec1.y1 < rec2.y2 && rec1.y2 > rec2.y1`

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(1)$.
- **Space Complexity:** $O(1)$.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
        // Check if rec1 is completely left, right, top, or bottom of rec2
        return !(rec1[2] <= rec2[0] ||  // left
                 rec1[3] <= rec2[1] ||  // bottom
                 rec1[0] >= rec2[2] ||  // right
                 rec1[1] >= rec2[3]);   // top
    }
};
```

### Python
```python
from typing import List

class Solution:
    def isRectangleOverlap(self, rec1: List[int], rec2: List[int]) -> bool:
        # rec1 = [x1, y1, x2, y2]
        # Overlap if: 
        #   rec1.x1 < rec2.x2 AND rec1.x2 > rec2.x1 AND
        #   rec1.y1 < rec2.y2 AND rec1.y2 > rec2.y1
        return (rec1[0] < rec2[2] and rec1[2] > rec2[0] and
                rec1[1] < rec2[3] and rec1[3] > rec2[1])
```

### Java
```java
class Solution {
    public boolean isRectangleOverlap(int[] rec1, int[] rec2) {
        return (rec1[0] < rec2[2] && rec1[2] > rec2[0] &&
                rec1[1] < rec2[3] && rec1[3] > rec2[1]);
    }
}
```

## 🌍 Real-World Analogy
### **Window Selection:**
On a computer screen, a window is focused (interactable) if it's on top. If you try to drag a selection box, it selects icons only if the selection rectangle overlaps with the icon's bounding box.

## 🎯 Summary
✅ **Negation Logic:** Easier to check when they *don't* overlap.
