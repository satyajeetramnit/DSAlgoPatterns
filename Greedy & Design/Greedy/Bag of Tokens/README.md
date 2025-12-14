# Bag of Tokens

## 🧩 Problem Statement
You have an initial **power** of `power` and an initial **score** of `0`. You are given a bag of `tokens`, where `tokens[i]` is the value of the `i-th` token (0-indexed).

Your goal is to maximize your total **score** by playing tokens strategically. In each move, you can play an **unplayed** token in one of two ways:

1. **Face-up:** If your current power is at least `tokens[i]`, you can play token `i` face-up. Your power reduces by `tokens[i]`, and your score increases by `1`.
2. **Face-down:** If your current score is at least `1`, you can play token `i` face-down. Your score decreases by `1`, and your power increases by `tokens[i]`.

Return the **maximum** possible score you can achieve after playing any number of tokens.

### 🔹 Example 1:
#### Input:
```plaintext
tokens = [100,200,300,400], power = 200
```
#### Output:
```plaintext
2
```
#### Explanation:
1. Play 100 face-up (Power: 200 - 100 = 100, Score: 1)
2. Play 400 face-down (Power: 100 + 400 = 500, Score: 0)
3. Play 200 face-up (Power: 500 - 200 = 300, Score: 1)
4. Play 300 face-up (Power: 300 - 300 = 0, Score: 2)
Max score is 2.

## 🔍 Approaches

### 1. Greedy with Two Pointers ($O(N \log N)$)
- **Concept:** We want to buy score (face-up) using the **cheapest** tokens to save power. We want to sell score (face-down) to gain the **maximum** power (using the most expensive tokens) to fuel future buys.
- **Algorithm:**
  1. **Sort** the tokens in ascending order.
  2. Use two pointers: `left` (smallest tokens) and `right` (largest tokens).
  3. Loop while `left <= right`:
     - **Buy:** If `power >= tokens[left]`, play `left` face-up. `power -= tokens[left]`, `score++`, `left++`, update `max_score`.
     - **Sell:** Else if `score > 0` and we have future tokens to buy (`left < right`): play `right` face-down. `power += tokens[right]`, `score--`, `right--`.
     - **Stop:** Else, we can't make a move. Break.
  
  **Why check `left < right` when selling?**
  It never makes sense to sell a score for power if that's the very last token (because selling reduces score, and we can't use that power to buy anything else to regain the score).

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N \log N)$ due to sorting.
- **Space Complexity:** $O(1)$ (or $O(\log N)$ for sort space).

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    int bagOfTokensScore(vector<int>& tokens, int power) {
        sort(tokens.begin(), tokens.end());
        int left = 0, right = tokens.size() - 1;
        int score = 0, max_score = 0;
        
        while (left <= right) {
            if (power >= tokens[left]) {
                power -= tokens[left];
                score++;
                left++;
                max_score = max(max_score, score);
            } else if (score > 0) {
                // Optimization: Don't sell if you can't buy anything else
                if (left == right) break; 
                
                power += tokens[right];
                score--;
                right--;
            } else {
                break;
            }
        }
        return max_score;
    }
};
```

### Python
```python
from typing import List

class Solution:
    def bagOfTokensScore(self, tokens: List[int], power: int) -> int:
        tokens.sort()
        left, right = 0, len(tokens) - 1
        score = 0
        max_score = 0
        
        while left <= right:
            if power >= tokens[left]:
                power -= tokens[left]
                score += 1
                left += 1
                max_score = max(max_score, score)
            elif score > 0:
                if left == right:
                    break
                power += tokens[right]
                score -= 1
                right -= 1
            else:
                break
                
        return max_score
```

### Java
```java
import java.util.Arrays;

class Solution {
    public int bagOfTokensScore(int[] tokens, int power) {
        Arrays.sort(tokens);
        int left = 0, right = tokens.length - 1;
        int score = 0, maxScore = 0;
        
        while (left <= right) {
            if (power >= tokens[left]) {
                power -= tokens[left];
                score++;
                left++;
                maxScore = Math.max(maxScore, score);
            } else if (score > 0) {
                if (left == right) break; // Don't sell last token
                
                power += tokens[right];
                score--;
                right--;
            } else {
                break;
            }
        }
        return maxScore;
    }
}
```

## 🌍 Real-World Analogy
### **Trading Strategy:**
Buy low, sell high. You use your cash (power) to buy cheap stocks (small tokens) to build your portfolio (score). When you enter a cash crunch but have a portfolio, you sell your most expensive stock (large token) to get a massive influx of cash, allowing you to buy many more cheap stocks.

## 🎯 Summary
✅ **Sorting is Key:** The greedy strategy relies entirely on being able to pick the absolute min for cost and absolute max for gain.
