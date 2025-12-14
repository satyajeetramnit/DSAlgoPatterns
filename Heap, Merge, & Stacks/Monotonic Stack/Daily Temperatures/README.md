# Daily Temperatures

## 🧩 Problem Statement
Given an array of integers `temperatures` represents the daily temperatures, return an array `answer` such that `answer[i]` is the number of days you have to wait after the `i`th day to get a warmer temperature. If there is no future day for which this is possible, keep `answer[i] == 0`.

### 🔹 Example 1:
#### Input:
```plaintext
temperatures = [73,74,75,71,69,72,76,73]
```
#### Output:
```plaintext
[1,1,4,2,1,1,0,0]
```

## 🔍 Approaches

### 1. Monotonic Decreasing Stack ($O(N)$)
- **Concept:** We want to find the **next greater element**.
- **Stack Property:** Maintain indices in the stack such that the temperatures at these indices are in **decreasing** order.
- **Algorithm:**
  - Initialize `answer` array with 0s.
  - Iterate through `temperatures` with index `i`.
  - While stack is not empty AND `temperatures[i] > temperatures[stack.top()]`:
    - This means we found a warmer day for `stack.top()`.
    - `idx = stack.pop()`.
    - `answer[idx] = i - idx`.
  - Push `i` onto stack.
- **Why this works:** The stack stores days that haven't found a warmer day yet. Since we pop whenever we find a warmer day, the stack naturally stays sorted (decreasing).

### 2. Brute Force ($O(N^2)$)
- For each day, look ahead until you find a warmer day.

We will implement the **Monotonic Stack** ($O(N)$).

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N)$. Each element is pushed and popped at most once.
- **Space Complexity:** $O(N)$ for the stack.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> answer(n, 0);
        stack<int> st; // stores indices
        
        for (int i = 0; i < n; i++) {
            while (!st.empty() && temperatures[i] > temperatures[st.top()]) {
                int prevIndex = st.top();
                st.pop();
                answer[prevIndex] = i - prevIndex;
            }
            st.push(i);
        }
        
        return answer;
    }
};
```

### Python
```python
from typing import List

class Solution:
    def dailyTemperatures(self, temperatures: List[int]) -> List[int]:
        n = len(temperatures)
        answer = [0] * n
        stack = [] # stores indices
        
        for i, temp in enumerate(temperatures):
            while stack and temp > temperatures[stack[-1]]:
                idx = stack.pop()
                answer[idx] = i - idx
            stack.append(i)
            
        return answer
```

### Java
```java
import java.util.Stack;

class Solution {
    public int[] dailyTemperatures(int[] temperatures) {
        int n = temperatures.length;
        int[] answer = new int[n];
        Stack<Integer> stack = new Stack<>(); // stores indices
        
        for (int i = 0; i < n; i++) {
            while (!stack.isEmpty() && temperatures[i] > temperatures[stack.peek()]) {
                int prevIndex = stack.pop();
                answer[prevIndex] = i - prevIndex;
            }
            stack.push(i);
        }
        
        return answer;
    }
}
```

## 🌍 Real-World Analogy
### **Waiting for a Sale:**
You write down the price of a game every day on a sticky note and stack them. If today's price is LOWER than the top note, you add today's note. If today's price is HIGHER, you realize "Oh, the previous days were cheaper? No wait, we want warmer/higher...".
Let's reverse: You want a warmer day.
You are looking for someone taller than you in a line. You see people shorter than you, you ignore them (they can't block your view). The moment you see someone taller, you know they are the "next greater".

## 🎯 Summary
✅ **Monotonic Stack:** The standard pattern for "Next Greater Element" problems.
