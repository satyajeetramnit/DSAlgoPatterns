# Capacity to Ship Packages Within D Days

## 🧩 Problem Statement
A conveyor belt has packages that must be shipped from one port to another within `days` days.
The `i-th` package on the conveyor belt has a weight of `weights[i]`. Each day, we load the ship with packages on the conveyor belt (in the order given by `weights`). We may not load more weight than the maximum weight capacity of the ship.

Return the least weight capacity of the ship that will result in all the packages on the conveyor belt being shipped within `days` days.

### 🔹 Example 1:
#### Input:
```plaintext
weights = [1,2,3,4,5,6,7,8,9,10], days = 5
```
#### Output:
```plaintext
15
```
#### Explanation:
A ship capacity of 15 is the minimum to ship all the packages in 5 days like this:
1st day: 1, 2, 3, 4, 5
2nd day: 6, 7
3rd day: 8
4th day: 9
5th day: 10

Note that the cargo must be shipped in the order given, so using a capacity of 14 and splitting the packages into parts like (2, 3, 4, 5), (1, 6, 7), (8), (9), (10) is not allowed.

### 🔹 Example 2:
#### Input:
```plaintext
weights = [3,2,2,4,1,4], days = 3
```
#### Output:
```plaintext
6
```
#### Explanation:
A ship capacity of 6 is the minimum to ship all the packages in 3 days like this:
1st day: 3, 2
2nd day: 2, 4
3rd day: 1, 4

## 🔍 Approaches

### 1. Binary Search on Answer
Instead of searching for an element in the array, we search for the **answer space**.
- The minimum possible capacity is `max(weights)` (ship must carry at least the heaviest single package).
- The maximum possible capacity is `sum(weights)` (ship carries everything in 1 day).
- The answer lies in the range `[max(weights), sum(weights)]`.
- This range is sorted! 
- We can binary search this range. For a given capacity `mid`, we check if it is possible to ship within `days`.

### ✨ Intuition
- If a capacity `C` works, then any capacity `> C` also works.
- If a capacity `C` is too small, any capacity `< C` is also too small.
- This monotonicity allows Binary Search.
- We want the *minimum* `C` that works.

### 🔥 Algorithm Steps
1. `left = max(weights)`, `right = sum(weights)`.
2. Function `canShip(capacity)`:
   - Iterate through weights.
   - Keep adding to current day's load. 
   - If adding a package exceeds `capacity`, increment days and start a new load.
   - Return `true` if total days needed <= given `days`.
3. Binary Search:
   - `mid = left + (right - left) / 2`.
   - If `canShip(mid)`:
     - Possible answer, try smaller capacity: `ans = mid`, `right = mid - 1`.
   - Else:
     - Capacity too small: `left = mid + 1`.
4. Return `left`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(n \cdot \log(\sum w))$, where $n$ is the number of packages and $\sum w$ is the total weight.
  - The range size is $\sum w - \max w$.
  - Typically, the range is roughly proportional to the total weight.
  - Verification takes $O(n)$.
- **Space Complexity:** $O(1)$.

## 🚀 Code Implementations

### C++
```cpp
class Solution {
public:
    int shipWithinDays(vector<int>& weights, int days) {
        int maxWeight = 0, totalWeight = 0;
        for (int w : weights) {
            maxWeight = max(maxWeight, w);
            totalWeight += w;
        }

        int left = maxWeight, right = totalWeight;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (canShip(weights, days, mid)) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }

private:
    bool canShip(const vector<int>& weights, int days, int capacity) {
        int daysNeeded = 1;
        int currentLoad = 0;
        
        for (int w : weights) {
            if (currentLoad + w > capacity) {
                daysNeeded++;
                currentLoad = 0;
            }
            currentLoad += w;
        }
        return daysNeeded <= days;
    }
};
```

### Python
```python
class Solution:
    def shipWithinDays(self, weights: List[int], days: int) -> int:
        def canShip(capacity):
            days_needed = 1
            current_load = 0
            for w in weights:
                if current_load + w > capacity:
                    days_needed += 1
                    current_load = 0
                current_load += w
            return days_needed <= days

        left, right = max(weights), sum(weights)
        
        while left <= right:
            mid = (left + right) // 2
            if canShip(mid):
                right = mid - 1
            else:
                left = mid + 1
        return left
```

### Java
```java
class Solution {
    public int shipWithinDays(int[] weights, int days) {
        int maxWeight = 0, totalWeight = 0;
        for (int w : weights) {
            maxWeight = Math.max(maxWeight, w);
            totalWeight += w;
        }

        int left = maxWeight, right = totalWeight;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (canShip(weights, days, mid)) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }

    private boolean canShip(int[] weights, int days, int capacity) {
        int daysNeeded = 1;
        int currentLoad = 0;
        
        for (int w : weights) {
            if (currentLoad + w > capacity) {
                daysNeeded++;
                currentLoad = 0;
            }
            currentLoad += w;
        }
        return daysNeeded <= days;
    }
}
```

## 🌍 Real-World Analogy
### **Moving House with a Truck:**
You need to move all your boxes in `D` trips. The boxes are lined up and must be loaded in order.
- If you get a tiny truck, you'll need many trips.
- If you get a huge semi-truck, you can do it in 1 trip.
- You want to rent the *smallest* truck that gets the job done in `D` trips to save money (minimize capacity).

## 🎯 Summary
✅ **Binary Search on Answer:** The problem asks for minimum capacity, and validity is monotonic.
✅ **Greedy Verification:** For a fixed capacity, we pack as much as possible each day (Greedy).
