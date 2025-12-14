from typing import List

class Solution:
    def countSmaller(self, nums: List[int]) -> List[int]:
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

if __name__ == "__main__":
    sol = Solution()
    
    # Test 1
    nums1 = [5, 2, 6, 1]
    expected1 = [2, 1, 1, 0]
    assert sol.countSmaller(nums1) == expected1, f"Expected {expected1}, got {sol.countSmaller(nums1)}"
    print("Test 1 Passed")
    
    # Test 2
    nums2 = [-1]
    expected2 = [0]
    assert sol.countSmaller(nums2) == expected2
    print("Test 2 Passed")
