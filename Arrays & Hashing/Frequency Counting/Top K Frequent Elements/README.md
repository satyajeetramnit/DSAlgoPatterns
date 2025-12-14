# Top K Frequent Elements

## 🧩 Problem Statement
Given an integer array `nums` and an integer `k`, return the `k` most frequent elements. You may return the answer in **any order**.

### 🔹 Example 1:
#### Input:
```plaintext
nums = [1,1,1,2,2,3], k = 2
```
#### Output:
```plaintext
[1,2]
```

### 🔹 Example 2:
#### Input:
```plaintext
nums = [1], k = 1
```
#### Output:
```plaintext
[1]
```

## 🔍 Approaches

### 1. Bucket Sort (Optimized)
Instead of sorting the frequencies ($O(n \log n)$), we can use the fact that the maximum possible frequency is $n$ (length of array).

### ✨ Intuition
- Count the frequency of each number. Map: `1 -> 3`, `2 -> 2`, `3 -> 1`.
- We can create "buckets" where the index represents the *frequency*.
- `bucket[3]` will contain `[1]` (numbers that appeared 3 times).
- `bucket[2]` will contain `[2]`.
- `bucket[1]` will contain `[3]`.
- Iterate from the highest frequency bucket down to 1 and collect `k` elements.

### 🔥 Algorithm Steps
1. Create a `count` hash map to store frequency of each number.
2. Create `freq` (arrays of lists), where `freq[i]` stores list of numbers that appear `i` times.
3. Iterate through `nums` to populate `count`.
4. Iterate through `count` to populate `freq`.
5. Iterate `freq` backwards (from $n$ to 1). Append elements to `res`.
6. Stop when `len(res) == k`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(n)$, since we iterate through the array to count, then map to buckets, then iterate buckets. All are linear passes.
- **Space Complexity:** $O(n)$, to store the hash map and the bucket array.

## 🚀 Code Implementations

### C++
```cpp
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> count;
        for (int n : nums) count[n]++;
        
        vector<vector<int>> bucket(nums.size() + 1);
        for (auto& p : count) {
            bucket[p.second].push_back(p.first);
        }
        
        vector<int> res;
        for (int i = bucket.size() - 1; i >= 0; i--) {
            for (int n : bucket[i]) {
                res.push_back(n);
                if (res.size() == k) return res;
            }
        }
        return res;
    }
};
```

### Python
```python
class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        count = {}
        freq = [[] for i in range(len(nums) + 1)]
        
        for n in nums:
            count[n] = 1 + count.get(n, 0)
        for n, c in count.items():
            freq[c].append(n)
            
        res = []
        for i in range(len(freq) - 1, 0, -1):
            for n in freq[i]:
                res.append(n)
                if len(res) == k:
                    return res
```

### Java
```java
class Solution {
    public int[] topKFrequent(int[] nums, int k) {
        Map<Integer, Integer> count = new HashMap<>();
        for (int n : nums) {
            count.put(n, count.getOrDefault(n, 0) + 1);
        }
        
        List<Integer>[] bucket = new List[nums.length + 1];
        for (int key : count.keySet()) {
            int frequency = count.get(key);
            if (bucket[frequency] == null) {
                bucket[frequency] = new ArrayList<>();
            }
            bucket[frequency].add(key);
        }
        
        int[] res = new int[k];
        int index = 0;
        for (int i = bucket.length - 1; i >= 0 && index < k; i--) {
            if (bucket[i] != null) {
                for (int n : bucket[i]) {
                    res[index++] = n;
                    if (index == k) return res;
                }
            }
        }
        return res;
    }
}
```

## 🌍 Real-World Analogy
### **Video Trending Chart:**
Imagine YouTube ranking videos.
- Every time a video is watched (`num`), we increment its view count (`frequency`).
- To find the "Top 10 Trending" (`k=10`), we don't need to sort ALL videos.
- We group them: "Videos with 1M views", "Videos with 900k views"...
- We just pick from the top buckets until we have 10 videos.

## 🎯 Summary
✅ **O(n) Time:** Beating the $O(n \log n)$ sorting approach.
✅ **Bucket Sort:** Useful technique when values are bounded (freq $\le n$).
