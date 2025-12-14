# Online Stock Span

## 🧩 Problem Statement
Design an algorithm that collects daily price quotes for some stock and returns the **span** of that stock's price for the current day.

The **span** of the stock's price today is defined as the maximum number of consecutive days (starting from today and going backward) for which the stock price was less than or equal to today's price.

- For example, if the price of a stock over the next 7 days were `[100,80,60,70,60,75,85]`, then the stock spans would be `[1,1,1,2,1,4,6]`.

Implement the `StockSpanner` class:
- `StockSpanner()` Initializes the object of the class.
- `int next(int price)` Returns the span of the stock's price given that today's price is `price`.

### 🔹 Example 1:
#### Input:
```plaintext
["StockSpanner", "next", "next", "next", "next", "next", "next", "next"]
[[], [100], [80], [60], [70], [60], [75], [85]]
```
#### Output:
```plaintext
[null, 1, 1, 1, 2, 1, 4, 6]
```

## 🔍 Approaches

### 1. Monotonic Decreasing Stack ($O(1)$ Amortized)
- **Concept:** We need to find how many previous days have prices $\le$ current price.
- **Data Structure:** Stack of pairs `(price, span)`.
- **Logic:**
  - Initialize `span = 1` (current day).
  - While stack is not empty AND `top.price <= current_price`:
    - `span += top.span`
    - Pop from stack.
  - Push `(current_price, span)` to stack.
  - Return `span`.
- **Why it works:** When we pop an element, it means the current price is greater than that element. The popped element's span already counted consecutive smaller days before it. By adding that span, we effectively "jump over" those days.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(1)$ amortized. Each element is pushed and popped at most once.
- **Space Complexity:** $O(N)$ for the stack.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

class StockSpanner {
    stack<pair<int, int>> st; // {price, span}
public:
    StockSpanner() {
        
    }
    
    int next(int price) {
        int span = 1;
        while (!st.empty() && st.top().first <= price) {
            span += st.top().second;
            st.pop();
        }
        st.push({price, span});
        return span;
    }
};
```

### Python
```python
class StockSpanner:

    def __init__(self):
        self.stack = [] # (price, span)

    def next(self, price: int) -> int:
        span = 1
        while self.stack and self.stack[-1][0] <= price:
            span += self.stack.pop()[1]
        self.stack.append((price, span))
        return span
```

### Java
```java
import java.util.Stack;

class StockSpanner {
    Stack<int[]> stack; // {price, span}

    public StockSpanner() {
        stack = new Stack<>();
    }
    
    public int next(int price) {
        int span = 1;
        while (!stack.isEmpty() && stack.peek()[0] <= price) {
            span += stack.pop()[1];
        }
        stack.push(new int[]{price, span});
        return span;
    }
}
```

## 🌍 Real-World Analogy
### **Video Game Combo:**
You are building a combo. If your current hit is stronger than the previous one, you "absorb" its combo count into yours. If you hit a weak hit, your combo resets to 1 (just that hit). But if you hit a strong one again, you absorb the weak hit's count plus whatever it absorbed.

## 🎯 Summary
✅ **Merged Spans:** Storing the processed span allows skipping recalculations efficiently.
