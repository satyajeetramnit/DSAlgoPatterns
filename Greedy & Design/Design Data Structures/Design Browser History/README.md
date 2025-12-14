# Design Browser History

## 🧩 Problem Statement
You have a browser of one tab where you start on the `homepage` and you can visit another `url`, get back in the history number of `steps` or move forward in the history number of `steps`.

Implement the `BrowserHistory` class:

- `BrowserHistory(string homepage)` Initializes the object with the `homepage` of the browser.
- `void visit(string url)` Visits `url` from the current page. It clears up all the forward history.
- `string back(int steps)` Move `steps` back in history. If you can only return `x` steps in the history and `steps > x`, you will return only `x` steps. Return the current `url` after moving back in history **at most** `steps`.
- `string forward(int steps)` Move `steps` forward in history. If you can only forward `x` steps in the history and `steps > x`, you will forward only `x` steps. Return the current `url` after forwarding in history **at most** `steps`.

## 🔍 Approaches

### 1. Doubly Linked List / Dynamic Array ($O(1)$)
- **Concept:** Browser history is linear. We can track the `current` position. 
- **Structure:**
  - **Array/List:** `history` stores the sequence of URLs.
  - **Pointer:** `currIndex` tracks where we are in that list.
  - **Size:** `limit` tracks the effective end of history (because `visit` cuts off the forward history).
- **Operations:**
  - `visit(url)`: 
    - `currIndex++`.
    - `history[currIndex] = url`.
    - `limit = currIndex`. (Forward history is invalidated).
  - `back(steps)`:
    - `currIndex = max(0, currIndex - steps)`.
    - Return `history[currIndex]`.
  - `forward(steps)`:
    - `currIndex = min(limit, currIndex + steps)`.
    - Return `history[currIndex]`.

### 🏛️ Design Diagram
```mermaid
graph LR
    subgraph History List
    h1[Home]
    h2[Google]
    h3[Facebook] 
    h4[YouTube]
    
    h1 --> h2 --> h3 --> h4
    end

    curr((Current Ptr))
    limit[Limit (End of Forward)]
    
    curr -.-> h3
    limit -.-> h4
    
    style curr fill:#ff9800,stroke:#333
    style h3 fill:#4caf50,stroke:#333
```
*After `visit(Twitter)` from Facebook:*
```mermaid
graph LR
    subgraph New History
    h1[Home] --> h2[Google] --> h3[Facebook] --> hNew[Twitter]
    end
    
    h4[YouTube (Deleted)]
    
    curr((Current Ptr)) -.-> hNew
```

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(1)$ for all operations.
- **Space Complexity:** $O(N)$ where $N$ is total URLs visited.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class BrowserHistory {
    vector<string> history;
    int curr, limit;
public:
    BrowserHistory(string homepage) {
        history.push_back(homepage);
        curr = 0;
        limit = 0;
    }
    
    void visit(string url) {
        curr++;
        if (curr < history.size()) {
            history[curr] = url;
        } else {
            history.push_back(url);
        }
        limit = curr; // Clear forward history
    }
    
    string back(int steps) {
        curr = max(0, curr - steps);
        return history[curr];
    }
    
    string forward(int steps) {
        curr = min(limit, curr + steps);
        return history[curr];
    }
};
```

### Python
```python
class BrowserHistory:

    def __init__(self, homepage: str):
        self.history = [homepage]
        self.curr = 0

    def visit(self, url: str) -> None:
        # Clear forward history
        # Python list slicing creates a copy, which is O(N).
        # To be strict O(1), we should treat it like an array with a limit pointer, 
        # but Python lists are dynamic.
        # Strict O(1) approach: Separate `curr` pointer and maintain list size implicitly?
        # Actually slicing is standard for Python solutions unless we use a custom implementation.
        # But slicing is O(K) where K is removed elements. That's acceptable.
        
        # Optimization: Just maintain a `limit` index like C++?
        # If we use `self.history = self.history[:self.curr+1]`, it frees memory but costs time.
        # Let's simple slice.
        self.curr += 1
        self.history = self.history[:self.curr]
        self.history.append(url)

    def back(self, steps: int) -> str:
        self.curr = max(0, self.curr - steps)
        return self.history[self.curr]

    def forward(self, steps: int) -> str:
        self.curr = min(len(self.history) - 1, self.curr + steps)
        return self.history[self.curr]
```

### Java
```java
import java.util.ArrayList;
import java.util.List;

class BrowserHistory {
    private List<String> history;
    private int curr, limit;

    public BrowserHistory(String homepage) {
        history = new ArrayList<>();
        history.add(homepage);
        curr = 0;
        limit = 0;
    }
    
    public void visit(String url) {
        curr++;
        if (curr < history.size()) {
            history.set(curr, url);
        } else {
            history.add(url);
        }
        limit = curr; // Invalidate forward history
    }
    
    public String back(int steps) {
        curr = Math.max(0, curr - steps);
        return history.get(curr);
    }
    
    public String forward(int steps) {
        curr = Math.min(limit, curr + steps);
        return history.get(curr);
    }
}
```

## 🌍 Real-World Analogy
### **Tape Recorder:**
Imagine a tape. You can rewind (`back`) and fast-forward (`forward`) to any song you've already recorded. But if you rewind to the middle and press **Record** (`visit`), you overwrite everything that came after that point with the new song.

## 🎯 Summary
✅ **Index Management:** Using a simple index `curr` and a boundary `limit` allows $O(1)$ navigation and "overwriting" history simulated by moving the limit.
