# Gas Station

## 🧩 Problem Statement
There are `n` gas stations along a circular route, where the amount of gas at the `i-th` station is `gas[i]`.

You have a car with an unlimited gas tank and it costs `cost[i]` of gas to travel from the `i-th` station to its next `(i + 1)` station. You begin the journey with an empty tank at one of the gas stations.

Given two integer arrays `gas` and `cost`, return the starting gas station's index if you can travel around the circuit once in the clockwise direction, otherwise return `-1`. If there exists a solution, it is guaranteed to be unique.

### 🔹 Example 1:
#### Input:
```plaintext
gas = [1,2,3,4,5], cost = [3,4,5,1,2]
```
#### Output:
```plaintext
3
```
#### Explanation:
Start at station 3 (index 3) and fill up with 4 unit of gas. Your tank = 0 + 4 = 4
Travel to station 4. Your tank = 4 - 1 + 5 = 8
Travel to station 0. Your tank = 8 - 2 + 1 = 7
Travel to station 1. Your tank = 7 - 3 + 2 = 6
Travel to station 2. Your tank = 6 - 4 + 3 = 5
Travel to station 3. The cost is 5. Your gas is just enough to return to start.
Therefore, return 3.

## 🔍 Approaches

### 1. Greedy (Total vs Current Surplus) ($O(N)$)
- **Insight 1 (Global Check):** If the total amount of gas available (`sum(gas)`) is less than the total cost to travel (`sum(cost)`), it is **impossible** to complete the circuit. Return `-1`.
- **Insight 2 (Local Start):** If we start at station `A` and get stuck at station `B` (i.e., `current_gas < 0` at `B`), then **no station between A and B (inclusive)** can be a valid starting point.
  - Why? Because we arrived at any intermediate station $k$ with a non-negative amount of gas. If we started at $k$ with 0 gas, we would have run out even sooner.
  - **Greedy Choice:** If we run out of gas at current `i`, reset the starting point to `i + 1` and reset `current_gas` to 0.

- **Algorithm:**
  1. Initialize `total_surplus = 0` and `current_surplus = 0`.
  2. Initialize `start_index = 0`.
  3. Iterate through the array:
     - `total_surplus += gas[i] - cost[i]`
     - `current_surplus += gas[i] - cost[i]`
     - If `current_surplus < 0`:
       - We failed. The start must be *after* `i`.
       - `start_index = i + 1`
       - `current_surplus = 0`
  4. If `total_surplus < 0`, return `-1`. Else, return `start_index`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N)$. Single pass.
- **Space Complexity:** $O(1)$.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <numeric>
#include <iostream>

using namespace std;

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();
        long long total_gas = 0, total_cost = 0;
        
        for (int i = 0; i < n; i++) {
            total_gas += gas[i];
            total_cost += cost[i];
        }
        
        if (total_gas < total_cost) return -1;
        
        int current_tank = 0;
        int start_index = 0;
        
        for (int i = 0; i < n; i++) {
            current_tank += gas[i] - cost[i];
            if (current_tank < 0) {
                // If we run out of gas, we can't start at any station 
                // from start_index to i. Start fresh from i + 1.
                start_index = i + 1;
                current_tank = 0;
            }
        }
        return start_index;
    }
};
```

### Python
```python
from typing import List

class Solution:
    def canCompleteCircuit(self, gas: List[int], cost: List[int]) -> int:
        if sum(gas) < sum(cost):
            return -1
        
        current_tank = 0
        start_index = 0
        
        for i in range(len(gas)):
            current_tank += gas[i] - cost[i]
            
            if current_tank < 0:
                # Failed. New start must be next station.
                start_index = i + 1
                current_tank = 0
                
        return start_index
```

### Java
```java
class Solution {
    public int canCompleteCircuit(int[] gas, int[] cost) {
        int totalGas = 0;
        int totalCost = 0;
        for(int g : gas) totalGas += g;
        for(int c : cost) totalCost += c;
        
        if (totalGas < totalCost) return -1;
        
        int currentTank = 0;
        int startIndex = 0;
        
        for (int i = 0; i < gas.length; i++) {
            currentTank += gas[i] - cost[i];
            if (currentTank < 0) {
                startIndex = i + 1;
                currentTank = 0;
            }
        }
        return startIndex;
    }
}
```

## 🌍 Real-World Analogy
### **Road Trip Budget:**
You have a specific budget for each leg of a trip. If the total cost of the trip is more than your total money, you can't do it. If you have enough total money but run out halfway, it means you started the trip at the wrong time (too early, before getting a paycheck). You need to move your start date later.

## 🎯 Summary
✅ **Global Validity vs Local Validity:** Checking `sum(gas) < sum(cost)` handles the "impossible" case instantly. The loop then just finds the *valid* rotation.
