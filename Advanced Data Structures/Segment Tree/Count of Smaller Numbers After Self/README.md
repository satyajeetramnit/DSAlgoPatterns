# Count of Smaller Numbers After Self

## 🧩 Problem Statement
Given an integer array `nums`, return an integer array `counts` where `counts[i]` is the number of smaller elements to the right of `nums[i]`.

### 🔹 Example 1:
#### Input:
```plaintext
nums = [5,2,6,1]
```
#### Output:
```plaintext
[2,1,1,0]
```
#### Explanation:
- To the right of 5 there are 2 smaller elements (2 and 1).
- To the right of 2 there is 1 smaller element (1).
- To the right of 6 there is 1 smaller element (1).
- To the right of 1 there is 0 smaller elements.

### 🔹 Example 2:
#### Input:
```plaintext
nums = [-1]
```
#### Output:
```plaintext
[0]
```

## 🔍 Approaches

### 1. Binary Indexed Tree (Fenwick Tree) - Optimal
- **Concept:** Iterate through the array from **right to left**.
- Ideally, we want to know: "How many numbers currently 'visited' are smaller than `current_num`?"
- We can track frequencies of visited numbers in a BIT.
- **Query:** `sum(0 to current_num - 1)` gives counts of smaller visited numbers.
- **Update:** `add(current_num, 1)` marks the current number as visited.
- **Coordinate Compression:** Since `nums[i]` can be large or negative (e.g., `-10^4` to `10^4`), we map them to ranks `1` to `N` based on sorted order.

### 2. Merge Sort (Alternative)
- During the "merge" step, if we pick a number from the right subarray (smaller), we know it contributes to the "inversion count" of remaining elements in the left subarray.

### 🏛️ Visual Logic: BIT Processing `[5, 2, 6, 1]`

**Ranks**: `1->1, 2->2, 5->3, 6->4` (Sorted: `1, 2, 5, 6`).
Array mapped to ranks: `[3, 2, 4, 1]`.


#### Step 1: Process Index 3 (Value 1, Rank 1)
- **BIT State**: `[0, 0, 0, 0, 0]` (Empty).
- **Query(Rank 1 - 1)**: `query(0)`. Result = `0`.
- **Update(Rank 1)**: Add 1 at idx 1.
- **Counts**: `[?, ?, ?, 0]`.

<!-- slide -->

#### Step 2: Process Index 2 (Value 6, Rank 4)
- **BIT State**: Has `1` at idx 1.
- **Query(Rank 4 - 1)**: `query(3)`. Sum of freq in `[1..3]`. Result = `1` (from Rank 1).
- **Update(Rank 4)**: Add 1 at idx 4.
- **Counts**: `[?, ?, 1, 0]`.

<!-- slide -->

#### Step 3: Process Index 1 (Value 2, Rank 2)
- **BIT State**: Has `1` at idx 1, `1` at idx 4.
- **Query(Rank 2 - 1)**: `query(1)`. Result = `1` (Rank 1).
- **Update(Rank 2)**: Add 1 at idx 2.
- **Counts**: `[?, 1, 1, 0]`.

<!-- slide -->

#### Step 4: Process Index 0 (Value 5, Rank 3)
- **BIT State**: Has `1` at idx 1, 2, 4.
- **Query(Rank 3 - 1)**: `query(2)`. Sum `[1..2]`. Result = `2` (Rank 1 and 2).
- **Update(Rank 3)**: Add 1 at idx 3.
- **Counts**: `[2, 1, 1, 0]`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N \log N)$ (Coordinate Compression + N queries on BIT).
- **Space Complexity:** $O(N)$ for BIT and Rank Map.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

class Solution {
    vector<int> bit;
    int n;

    void update(int idx, int val) {
        for (; idx <= n; idx += idx & -idx)
            bit[idx] += val;
    }

    int query(int idx) {
        int sum = 0;
        for (; idx > 0; idx -= idx & -idx)
            sum += bit[idx];
        return sum;
    }

public:
    vector<int> countSmaller(vector<int>& nums) {
        int sz = nums.size();
        vector<int> sortedN = nums;
        sort(sortedN.begin(), sortedN.end());
        
        // Coordinate Compression: Value -> Rank (1-based)
        // Use unique to handle duplicates if strictly smaller logic? 
        // Problem asks strict smaller. Equal doesn't count.
        // lower_bound gives first occurrence, effectively handling duplicates correctly for rank mapping?
        // Actually we need `lower_bound` index + 1.
        
        n = sz; // BIT size limit
        bit.assign(n + 1, 0);
        vector<int> res(sz);
        
        for (int i = sz - 1; i >= 0; --i) {
            // Rank: index in sorted array + 1
            int rank = lower_bound(sortedN.begin(), sortedN.end(), nums[i]) - sortedN.begin() + 1;
            
            // Query: sum of items with rank < current_rank
            res[i] = query(rank - 1);
            
            // Update: add 1 to current_rank
            update(rank, 1);
        }
        return res;
    }
};
```

### Python
```python
from typing import List
import bisect

class Solution:
    def countSmaller(self, nums: List[int]) -> List[int]:
        # Coordinate Compression
        sorted_nums = sorted(nums)
        ranks = {val: i + 1 for i, val in enumerate(sorted_nums)}
        # Wait, simple map fails duplicates?
        # If duplicates exist, standard 'rank' usually implies unique values?
        # Actually simplest is just bisect_left for on-the-fly rank, or mapping unique values.
        # Let's map unique sorted values.
        
        unique_sorted = sorted(list(set(nums)))
        rank_map = {val: i + 1 for i, val in enumerate(unique_sorted)}
        
        n = len(unique_sorted)
        bit = [0] * (n + 1)
        
        def update(i, delta):
            while i <= n:
                bit[i] += delta
                i += i & (-i)
        
        def query(i):
            s = 0
            while i > 0:
                s += bit[i]
                i -= i & (-i)
            return s
            
        res = []
        for x in reversed(nums):
            rank = rank_map[x]
            res.append(query(rank - 1))
            update(rank, 1)
            
        return res[::-1]
```

### Java
```java
import java.util.*;

class Solution {
    int[] bit;
    int n;

    private void update(int idx, int val) {
        while (idx <= n) {
            bit[idx] += val;
            idx += idx & -idx;
        }
    }

    private int query(int idx) {
        int sum = 0;
        while (idx > 0) {
            sum += bit[idx];
            idx -= idx & -idx;
        }
        return sum;
    }

    public List<Integer> countSmaller(int[] nums) {
        int[] sorted = nums.clone();
        Arrays.sort(sorted);
        // Remove duplicates for cleaner ranking?
        // Or simply iterate? 
        // With duplicates: {1, 1}. Rank 1 and 2? No, same rank makes sense or relying on binary search.
        // Using unique ranks is standard.
        
        // Let's create a map of unique ranks
        Map<Integer, Integer> ranks = new HashMap<>();
        int rank = 1;
        for (int num : sorted) {
            if (!ranks.containsKey(num)) {
                ranks.put(num, rank++);
            }
        }
        
        n = ranks.size();
        bit = new int[n + 1];
        List<Integer> res = new ArrayList<>();
        
        for (int i = nums.length - 1; i >= 0; i--) {
            int r = ranks.get(nums[i]);
            res.add(query(r - 1));
            update(r, 1);
        }
        
        Collections.reverse(res);
        return res;
    }
}
```

## 🌍 Real-World Analogy
### **Game Leaderboard Ranking:**
Imagine players joining a game server with different scores. You want to tell each player: "You are better than X players who joined AFTER you." (Wait, problem is Reverse: Right side).
Actually, simpler: **Traffic Overtaking**.
You are driving on a highway. You ($V_i$) look ahead (Right side of array). How many cars ahead of you satisfy ($V_{ahead} < V_i$) i.e., are driving slower than you? These are the cars you will inevitably overtake.
- BIT helps keep a live frequency count of speeds observed so far (scanning backwards from horizon to you).
